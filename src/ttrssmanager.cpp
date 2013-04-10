#include "ttrssmanager.hpp"

#include "settings.hpp"

#include "data/category.hpp"

#include "packets/getcategories.hpp"
#include "packets/login.hpp"

#include <bb/data/JsonDataAccess>
#include <QtCore/QDebug>

TTRSSManager::TTRSSManager() :	_networkAccessManager(new QNetworkAccessManager(this)),
								_loginStatus(NOT_LOGGED_IN),
								_currentPacketID(0) {
	connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(requestFinished(QNetworkReply*)));

	login();
}

TTRSSManager::~TTRSSManager() {
	delete _networkAccessManager;
	for (QList<Category*>::Iterator it = _categories.begin(), end = _categories.end(); it != end; ++it)
		delete *it;
}

void TTRSSManager::login() {
	_loginStatus = IN_PROGRESS;
	sendPacket(new Login(Settings::getValueFor("serverLogin", "").toString(), Settings::getValueFor("serverPassword", "").toString(), this, _currentPacketID++));
}

void TTRSSManager::requestCategories() {
	sendPacket(new GetCategories(	Settings::getValueFor("unreadOnly", true).toBool(),
									Settings::getValueFor("enableNested", false).toBool(),
									Settings::getValueFor("includeEmpty", false).toBool(),
									this,
									_currentPacketID++));
}

void TTRSSManager::addCategory(Category* category) {
	_categories.append(category);
	QVariant v;
	v.setValue(qobject_cast<QObject*>(category));
	emit categoryAdded(v);
}

void TTRSSManager::sendPacket(APacket* packet) {
	_waitingPackets.insert(packet->getId(), packet);
	sendRequest(packet->getRequestData());
}

void TTRSSManager::sendRequest(QByteArray requestData) {
	QByteArray postDataSize = QByteArray::number(requestData.size());

	QNetworkRequest request(Settings::getApiPath());
	request.setRawHeader("User-Agent", "tt-rss for BlackBerry 10");
	request.setRawHeader("X-Custom-User-Agent", "tt-rss for BlackBerry 10");
	request.setRawHeader("Content-Type", "application/json");
	request.setRawHeader("Content-Length", postDataSize);

	_networkAccessManager->post(request, requestData);
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
	qDebug() << reply;
	QMap<QString, QVariant> mReply = reply.toMap();
	if (!mReply.contains("status") || !mReply.contains("seq") || !mReply.contains("content")) {
		// TODO: proper error handling
		qDebug() << "Invalid packet received";
	} else {
		unsigned long long seq = mReply.value("seq").toLongLong();
		// TODO: find?
		if (_waitingPackets.contains(seq)) {
			APacket* packet = _waitingPackets.take(seq);
			packet->handleReply(mReply);
		} else {
			// TODO: handle error
			qDebug() << "Received answer to uknown packet" << seq;
		}
	}
}

void TTRSSManager::handleNetworkError(QNetworkReply::NetworkError error) {
	QString errorMessage;
	switch (error) {
	case QNetworkReply::ConnectionRefusedError:
		errorMessage = tr("Connection to %1 refused.").arg(Settings::getValueFor("serverAddress", "").toString());
		break;
	case QNetworkReply::HostNotFoundError:
		errorMessage = tr("Host %1 not found.").arg(Settings::getValueFor("serverAddress", "").toString());
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
