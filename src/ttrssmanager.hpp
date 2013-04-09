#ifndef __TTRSS_MANAGER_HPP__
#define __TTRSS_MANAGER_HPP__

class APacket;

class QNetworkAccessManager;

#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtNetwork/QNetworkReply>

class TTRSSManager : public QObject {

	Q_OBJECT

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

	void login();
	ELoginStatus loginStatus() const;

signals:
	void networkError(QVariant error);
	void loginResult(bool result);

private slots:
	void requestFinished(QNetworkReply* reply);

private:
	void sendPacket(APacket* packet);
	void sendRequest(QByteArray requestData);

	void handleReply(QVariant reply);
	void handleNetworkError(QNetworkReply::NetworkError error);

	QNetworkAccessManager*				_networkAccessManager;
	ELoginStatus						_loginStatus;
	unsigned long long					_currentPacketID;
	QMap<unsigned long long, APacket*>	_waitingPackets;
};

inline TTRSSManager::ELoginStatus TTRSSManager::loginStatus() const {
	return _loginStatus;
}

#endif // __TTRSS_MANAGER_HPP__
