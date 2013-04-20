#include "getconfig.hpp"

#include "ttrssmanager.hpp"

#include <QtCore/QDebug>

namespace ttrss {
	namespace packets {
		GetConfig::GetConfig(TTRSSManager* manager, unsigned long long id): APacket(manager, id) {
		}

		GetConfig::~GetConfig() {
		}

		void GetConfig::handleSuccess(QVariant reply) {
			QMap<QString, QVariant> mReply = reply.toMap();
			getManager()->setIconsUrl(mReply.value("icons_url").toString());
			getManager()->requestCategories();
		}

		void GetConfig::handleError(QVariant reply) {
			qDebug() << "GetConfig::error:" << reply;
		}

		QVariantMap GetConfig::getRequestDataImpl() const {
			QVariantMap packet;
			packet["op"] = "getConfig";
			return packet;
		}
	}
}
