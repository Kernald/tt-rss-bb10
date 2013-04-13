#include "login.hpp"

#include "ttrssmanager.hpp"

#include <QtCore/QDebug>

Login::Login(QString login, QString password, TTRSSManager* manager, unsigned long long id) :	APacket(manager, id),
																								_login(login), _password(password) {
}

Login::~Login() {
}

void Login::handleSuccess(QVariant reply) {
	QMap<QString, QVariant> mReply = reply.toMap();
	QMap<QString, QVariant>::ConstIterator it = mReply.constFind("session_id");
	if (it != mReply.constEnd()) {
		qDebug() << "Successfuly logged in as user" << _login;
		getManager()->setLoginStatus(TTRSSManager::LOGGED_IN);
		getManager()->setSessionID(it->toString());
	} else {
		qDebug() << "Error in login answer: no session_id";
		getManager()->setLoginStatus(TTRSSManager::FAILED);
	}
}

void Login::handleError(QVariant /*reply*/) {
	qDebug() << "Error logging in as user" << _login;
	getManager()->setLoginStatus(TTRSSManager::FAILED);
}

QVariantMap Login::getRequestDataImpl() const {
	QVariantMap packet;
	packet["op"] = "login";
	packet["user"] = _login;
	packet["password"] = _password;
	return packet;
}
