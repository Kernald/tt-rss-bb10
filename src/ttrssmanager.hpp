#ifndef __TTRSS_MANAGER_HPP__
#define __TTRSS_MANAGER_HPP__

class QNetworkAccessManager;

#include <QtCore/QObject>
#include <QtNetwork/QNetworkReply>

class TTRSSManager : public QObject {

	Q_OBJECT

public:
	TTRSSManager();
	virtual ~TTRSSManager();

	void login();

signals:
	void networkError(QVariant error);
	void loginResult(bool result);

private slots:
	void requestFinished(QNetworkReply* reply);

private:
	void sendRequest(QByteArray requestData);

	void handleReply(QVariant reply);
	void handleNetworkError(QNetworkReply::NetworkError error);
	QNetworkAccessManager*	_networkAccessManager;
};

#endif // __TTRSS_MANAGER_HPP__
