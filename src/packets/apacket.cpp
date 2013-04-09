#include "apacket.hpp"

#include "ttrssmanager.hpp"

#include <bb/data/JsonDataAccess>

APacket::APacket(TTRSSManager* manager, unsigned long long id) : _manager(manager), _id(id) {
}

APacket::~APacket() {
}

QByteArray APacket::getRequestData() const {
	QVariantMap packetMap = getRequestDataImpl();
	packetMap["seq"] = _id;
	QByteArray packet;
	bb::data::JsonDataAccess jda;
	jda.saveToBuffer(packetMap, &packet);
	return packet;
}

void APacket::handleReply(QMap<QString, QVariant> reply) {
	int status = reply.value("status").toInt();
	switch (status) {
	case TTRSSManager::API_STATUS_OK:
		handleSuccess(reply);
		break;

	case TTRSSManager::API_STATUS_ERR:
	default:
		handleError(reply);
		break;
	}
}
