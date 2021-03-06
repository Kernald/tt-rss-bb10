#include "apacket.hpp"

#include "ttrssmanager.hpp"

#include <bb/data/JsonDataAccess>

namespace ttrss {
	namespace packets {
		APacket::APacket(TTRSSManager* manager, unsigned long long id) : _manager(manager), _id(id) {
		}

		APacket::~APacket() {
		}

		QByteArray APacket::getRequestData() const {
			QVariantMap packetMap = getRequestDataImpl();
			packetMap["seq"] = _id;
			if (getManager()->loginStatus() == TTRSSManager::LOGGED_IN)
				packetMap["sid"] = getManager()->sessionID();
			QByteArray packet;
			bb::data::JsonDataAccess jda;
			jda.saveToBuffer(packetMap, &packet);
			return packet;
		}

		void APacket::handleReply(QMap<QString, QVariant> reply) {
			int status = reply.value("status").toInt();
			QVariant content = reply.value("content");
			switch (status) {
			case TTRSSManager::API_STATUS_OK:
				handleSuccess(content);
				break;

			case TTRSSManager::API_STATUS_ERR:
			default:
				handleError(content);
				break;
			}
		}
	}
}
