#include "ttrssmanager.hpp"

#include "feediconloader.hpp"
#include "settings.hpp"

#include "data/article.hpp"
#include "data/category.hpp"
#include "data/feed.hpp"

#include "packets/getarticle.hpp"
#include "packets/getcategories.hpp"
#include "packets/getconfig.hpp"
#include "packets/getfeeds.hpp"
#include "packets/getheadlines.hpp"
#include "packets/login.hpp"
#include "packets/updatearticle.hpp"

#include <bb/data/JsonDataAccess>
#include <QtCore/QDebug>

namespace ttrss {
	TTRSSManager::TTRSSManager() :	_networkAccessManager(new QNetworkAccessManager(this)),
									_loginStatus(NOT_LOGGED_IN),
									_currentPacketID(0) {
		connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
				this, SLOT(requestFinished(QNetworkReply*)));
	}

	TTRSSManager::~TTRSSManager() {
		delete _networkAccessManager;
		qDeleteAll(_categories);
	}

	void TTRSSManager::requestConfig() {
		sendPacket(new packets::GetConfig(this, _currentPacketID++));
	}

	void TTRSSManager::login() {
		_loginStatus = IN_PROGRESS;
		sendPacket(new packets::Login(	Settings::getValueFor("serverLogin", "").toString(),
										Settings::getValueFor("serverPassword", "").toString(),
										this,
										_currentPacketID++));
	}

	void TTRSSManager::requestCategories() {
		sendPacket(new packets::GetCategories(	Settings::getValueFor("unreadOnly", true).toBool(),
												Settings::getValueFor("enableNested", false).toBool(),
												Settings::getValueFor("includeEmpty", false).toBool(),
												this,
												_currentPacketID++));
	}

	bool TTRSSManager::addCategory(data::Category* category) {
		// Don't add the same category twice
		QListIterator<data::Category*> i(_categories);
		while (i.hasNext())
			if (i.next()->getId() == category->getId())
				return false;

		_categories.append(category);
		QVariant v;
		v.setValue(qobject_cast<QObject*>(category));
		emit categoryAdded(v);
		return true;
	}

	data::Category* TTRSSManager::getCategory(int categoryId) const {
		for (QList<data::Category*>::ConstIterator it = _categories.constBegin(), end = _categories.constEnd(); it != end; ++it)
			if ((*it)->getId() == categoryId)
				return *it;
		return NULL;
	}

	void TTRSSManager::requestFeeds(int categoryId) {
		sendPacket(new packets::GetFeeds(	categoryId,
											Settings::getValueFor("unreadOnly", true).toBool(),
											this,
											_currentPacketID++));
	}

	void TTRSSManager::addFeed(data::Feed* feed) {
		emit feedAdded(feed);
		setFeedIcon(feed);
	}

	data::Feed* TTRSSManager::getFeed(int feedId) const {
		for (QList<data::Category*>::ConstIterator itC = _categories.constBegin(), endC = _categories.constEnd(); itC != endC; ++itC) {
			data::Category* c = *itC;
			for (QList<data::Feed*>::ConstIterator itF = c->getFeeds().constBegin(), endF = c->getFeeds().constEnd(); itF != endF; ++itF)
				if ((*itF)->getId() == feedId)
					return *itF;
		}
		return NULL;
	}

	QList<data::Feed*> TTRSSManager::getFeeds() const {
		QList<data::Feed*> res;
		for (QList<data::Category*>::ConstIterator itC = _categories.constBegin(), endC = _categories.constEnd(); itC != endC; ++itC) {
			data::Category* c = *itC;
			for (QList<data::Feed*>::ConstIterator itF = c->getFeeds().constBegin(), endF = c->getFeeds().constEnd(); itF != endF; ++itF)
				res << *itF;
		}

		return res;
	}

	void TTRSSManager::requestHeadlines(int feedId) {
		sendPacket(new packets::GetHeadlines(feedId, Settings::getValueFor("unreadOnly", true).toBool(), this, _currentPacketID++));
	}

	void TTRSSManager::addArticle(data::Article* article) {
		emit articleAdded(article);
	}

	void TTRSSManager::requestArticleDetails(data::Article* article) {
		sendPacket(new packets::GetArticle(article, this, _currentPacketID++));
	}

	void TTRSSManager::setFeedIcon(data::Feed* feed) {
		QString url(Settings::getValueFor("serverAddress", QVariant("")).toString() + QString("/%1/%2.ico").arg(_iconsUrl).arg(feed->getId()));
		FeedIconLoader* loader = new FeedIconLoader(url, feed, this);
		loader->load();
	}

	void TTRSSManager::subscribe(QString url) {
		Q_UNUSED(url);
		// TODO:
		qDebug() << "Subscription not implemented yet";
	}

	void TTRSSManager::setUnreadStatus(unsigned int articleId, bool unreadStatus) {
		sendPacket(new packets::UpdateArticle(articleId, packets::UpdateArticle::UNREAD, unreadStatus, "", this, _currentPacketID++));
	}

	void TTRSSManager::setMarkedStatus(unsigned int articleId, bool markedStatus) {
		sendPacket(new packets::UpdateArticle(articleId, packets::UpdateArticle::STARRED, markedStatus, "", this, _currentPacketID++));
	}

	void TTRSSManager::setPublishedStatus(unsigned int articleId, bool publishedStatus) {
		sendPacket(new packets::UpdateArticle(articleId, packets::UpdateArticle::PUBLISHED, publishedStatus, "", this, _currentPacketID++));
	}

	void TTRSSManager::sendPacket(packets::APacket* packet) {
		_waitingPackets.insert(packet->getId(), packet);
		emit workingStateChanged(true);
		sendRequest(packet->getRequestData());
	}

	void TTRSSManager::sendRequest(QByteArray requestData) {
		QByteArray postDataSize = QByteArray::number(requestData.size());

		QNetworkRequest request(Settings::getApiPath());
		request.setRawHeader("User-Agent", "tt-rss for BlackBerry 10");
		request.setRawHeader("X-Custom-User-Agent", "tt-rss for BlackBerry 10");
		request.setRawHeader("Content-Type", "application/json");
		request.setRawHeader("Content-Length", postDataSize);

		QNetworkReply* reply = _networkAccessManager->post(request, requestData);
		if (Settings::getValueFor("ignoreSslErrors", QVariant(false)).toBool())
			reply->ignoreSslErrors();
	}

	void TTRSSManager::requestFinished(QNetworkReply* reply) {
		if (reply->error() == QNetworkReply::NoError) {
			bb::data::JsonDataAccess jda;
			handleReply(jda.loadFromBuffer(reply->readAll()));
		} else {
			handleNetworkError(reply->error());
		}

		reply->deleteLater();
	}

	void TTRSSManager::handleReply(QVariant reply) {
		QMap<QString, QVariant> mReply = reply.toMap();
		if (!mReply.contains("status") || !mReply.contains("seq") || !mReply.contains("content")) {
			// TODO: proper error handling
			qDebug() << "Invalid packet received" << reply;
		} else {
			unsigned long long seq = mReply.value("seq").toLongLong();
			// TODO: find?
			if (_waitingPackets.contains(seq)) {
				packets::APacket* packet = _waitingPackets.take(seq);
				emit workingStateChanged(false);
				packet->handleReply(mReply);
				delete packet;
			} else {
				// TODO: handle error
				qDebug() << "Received answer to unknown packet" << seq;
			}
		}
	}

	void TTRSSManager::handleNetworkError(QNetworkReply::NetworkError error) {
		// TODO: delete original packet
		QString errorMessage;
		switch (error) {
		case QNetworkReply::ConnectionRefusedError:
			errorMessage = tr("Connection to %1 refused.").arg(Settings::getValueFor("serverAddress", "").toString());
			break;
		case QNetworkReply::HostNotFoundError:
			errorMessage = tr("Host %1 not found.").arg(Settings::getValueFor("serverAddress", "").toString());
			break;
		case QNetworkReply::SslHandshakeFailedError:
			errorMessage = tr("SSL handshake failed.");
			break;
		case QNetworkReply::ContentNotFoundError:
			errorMessage = tr("%1 not found.").arg(Settings::getApiPath().toString());
			break;
		default:
			errorMessage = tr("Network error.");
			break;
		}
		emit networkError(QVariant(errorMessage));
		qDebug() << "Network error:" << error << "-" << errorMessage;

		// If login was in progress, it has probably failed
		_loginStatus = FAILED;
	}
}
