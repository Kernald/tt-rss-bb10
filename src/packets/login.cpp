#include "login.hpp"

#include <QtCore/QDebug>

Login::Login(QString login, QString password, TTRSSManager* manager, unsigned long long id) :	APacket(manager, id),
																								_login(login), _password(password) {
}

Login::~Login() {
}

void Login::handleSuccess(QMap<QString, QVariant> reply) {
	// TODO
	qDebug() << "Successfuly logged in as user" << _login;
}

void Login::handleError(QMap<QString, QVariant> reply) {
	// TODO
	qDebug() << "Error logging in as user" << _login;
}

QVariantMap Login::getRequestDataImpl() const {
	QVariantMap packet;
	packet["op"] = "login";
	packet["user"] = _login;
	packet["password"] = _password;
	return packet;
}
