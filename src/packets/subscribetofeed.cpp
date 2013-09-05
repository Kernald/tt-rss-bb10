#include "subscribetofeed.hpp"

#include <QtCore/QDebug>

namespace ttrss {
	namespace packets {
		SubscribeToFeed::SubscribeToFeed(QString url, TTRSSManager* manager, unsigned long long id): APacket(manager, id), _url(url) {
		}

		SubscribeToFeed::~SubscribeToFeed() {
		}

		void SubscribeToFeed::handleSuccess(QVariant reply) {
			int status = reply.toMap().value("status").toMap().value("code").toInt();
			// TODO: handle result
			switch (status) {
			case 0:
				// OK, feed already exists
				break;
			case 1:
				// OK
				break;
			default:
				// Error
				break;
			}
		}

		void SubscribeToFeed::handleError(QVariant reply) {
			qDebug() << "SubscribeToFeed::handleError(): " << reply;
		}

		QVariantMap SubscribeToFeed::getRequestDataImpl() const {
			QVariantMap packet;
			packet["op"] = "subscribeToFeed";
			packet["feed_url"] = _url;
			return packet;
		}
	}
}
