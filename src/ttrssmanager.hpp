#ifndef __TTRSS_MANAGER_HPP__
#define __TTRSS_MANAGER_HPP__

class APacket;
class Category;
class Feed;

class QNetworkAccessManager;

#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtNetwork/QNetworkReply>

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

	void login();
	ELoginStatus loginStatus() const;
	void setLoginStatus(ELoginStatus loginStatus);
	QString sessionID() const;
	void setSessionID(QString sessionID);

	void requestCategories();
	void addCategory(Category* category);
	Category* getCategory(int categoryId) const;

	void requestFeeds(int categoryId);
	void addFeed(Feed* feed);
	Feed* getFeed(int feedId) const;
	QList<Feed*> getFeeds() const;

	void requestHeadlines(int feedId);

Q_SIGNALS:
	void workingStateChanged(bool working);
	void networkError(QVariant error);
	void loginResult(bool result);
	void categoryAdded(QVariant category);
	void feedAdded(QObject* feed);

private Q_SLOTS:
	void requestFinished(QNetworkReply* reply);

private:
	void sendPacket(APacket* packet);
	void sendRequest(QByteArray requestData);

	void handleReply(QVariant reply);
	void handleNetworkError(QNetworkReply::NetworkError error);

	QNetworkAccessManager*				_networkAccessManager;
	ELoginStatus						_loginStatus;
	QString								_sessionID;
	unsigned long long					_currentPacketID;
	QMap<unsigned long long, APacket*>	_waitingPackets;

	QList<Category*>					_categories;
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
	requestCategories();
}

#endif // __TTRSS_MANAGER_HPP__
