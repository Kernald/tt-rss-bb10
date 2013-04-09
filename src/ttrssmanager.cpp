#include "ttrssmanager.hpp"

#include "settings.hpp"

#include <bb/data/JsonDataAccess>
#include <QtCore/QDebug>
#include <QtNetwork/QNetworkReply>

TTRSSManager::TTRSSManager() {
	_networkAccessManager = new QNetworkAccessManager(this);
	connect(_networkAccessManager, SIGNAL(finished(QNetworkReply*)),
			this, SLOT(requestFinished(QNetworkReply*)));

	login();
}

TTRSSManager::~TTRSSManager() {
	delete _networkAccessManager;
}

void TTRSSManager::login() {
	QVariantMap loginPacket;
	loginPacket["op"] = "login";
	loginPacket["user"] = Settings::getValueFor("serverLogin", "");
	loginPacket["password"] = Settings::getValueFor("serverPassword", "");
	QByteArray packet;
	bb::data::JsonDataAccess jda;
	jda.saveToBuffer(loginPacket, &packet);
	sendRequest(packet);
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
		handleError(reply->error());
	}

	reply->deleteLater();
}

void TTRSSManager::handleReply(QVariant reply) const {
	qDebug() << reply;
}

void TTRSSManager::handleError(QNetworkReply::NetworkError error) const {
	emit networkError(error);
	qDebug() << "Network error: " << error;
}
