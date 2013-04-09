#ifndef __TTRSS_MANAGER_HPP__
#define __TTRSS_MANAGER_HPP__

class QNetworkAccessManager;
class QNetworkReply;

#include <QtCore/QObject>

class TTRSSManager : public QObject {

	Q_OBJECT

public:
	TTRSSManager();
	virtual ~TTRSSManager();

	void login();

signals:
	void networkError(QNetworkReply::NetworkError error);
	void loginResult(bool result);

private:
	void sendRequest(QByteArray requestData);

private slots:
	void requestFinished(QNetworkReply* reply);

private:
	void handleReply(QVariant reply) const;
	void handleNetworkError(QNetworkReply::NetworkError error) const;
	QNetworkAccessManager*	_networkAccessManager;
};

#endif // __TTRSS_MANAGER_HPP__
