#ifndef __TTRSS_MANAGER_HPP__
#define __TTRSS_MANAGER_HPP__

namespace ttrss {
	namespace data {
		class Article;
		class Category;
		class Feed;
	}
	namespace packets {
		class APacket;
	}
}

class QNetworkAccessManager;

#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtNetwork/QNetworkReply>

namespace ttrss {
	class TTRSSManager : public QObject {

		Q_OBJECT

		Q_PROPERTY(bool working READ isWorking NOTIFY workingStateChanged);

	public:
		enum ELoginStatus {
			NOT_LOGGED_IN,
			LOGGED_IN,
			FAILED,
			IN_PROGRESS
		};

		static const int API_STATUS_OK	= 0;
		static const int API_STATUS_ERR	= 1;

		TTRSSManager();
		virtual ~TTRSSManager();

		bool isWorking() const;

		void requestConfig();

		void login();
		ELoginStatus loginStatus() const;
		void setLoginStatus(ELoginStatus loginStatus);
		QString sessionID() const;
		void setSessionID(QString sessionID);

		void requestCategories();
		void addCategory(data::Category* category);
		data::Category* getCategory(int categoryId) const;

		void requestFeeds(int categoryId);
		void addFeed(data::Feed* feed);
		data::Feed* getFeed(int feedId) const;
		QList<data::Feed*> getFeeds() const;

		void requestHeadlines(int feedId);
		void addArticle(data::Article* article);

		void requestArticleDetails(data::Article* article);

		void setUnreadStatus(unsigned int articleId, bool unreadStatus);
		void setMarkedStatus(unsigned int articleId, bool markedStatus);
		void setPublishedStatus(unsigned int articleId, bool publishedStatus);

		void setIconsUrl(QString url);
		void setFeedIcon(data::Feed* feed);

	Q_SIGNALS:
		void workingStateChanged(bool working);
		void networkError(QVariant error);
		void loginResult(bool result);
		void categoryAdded(QVariant category);
		void feedAdded(QObject* feed);
		void articleAdded(QObject* article);

	private Q_SLOTS:
		void requestFinished(QNetworkReply* reply);

	private:
		void sendPacket(packets::APacket* packet);
		void sendRequest(QByteArray requestData);

		void handleReply(QVariant reply);
		void handleNetworkError(QNetworkReply::NetworkError error);

		QNetworkAccessManager*						_networkAccessManager;
		ELoginStatus								_loginStatus;
		QString										_sessionID;
		unsigned long long							_currentPacketID;
		QMap<unsigned long long, packets::APacket*>	_waitingPackets;

		QString										_iconsUrl;
		QList<data::Category*>						_categories;
	};

	inline bool TTRSSManager::isWorking() const {
		return _waitingPackets.size() > 0;
	}

	inline TTRSSManager::ELoginStatus TTRSSManager::loginStatus() const {
		return _loginStatus;
	}

	inline void TTRSSManager::setLoginStatus(TTRSSManager::ELoginStatus loginStatus) {
		_loginStatus = loginStatus;
	}

	inline QString TTRSSManager::sessionID() const {
		return _sessionID;
	}

	inline void TTRSSManager::setSessionID(QString sessionID) {
		_sessionID = sessionID;
		requestConfig();
	}

	inline void TTRSSManager::setIconsUrl(QString url) {
		_iconsUrl = url;
	}
}

#endif // __TTRSS_MANAGER_HPP__
