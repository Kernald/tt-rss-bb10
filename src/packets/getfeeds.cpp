#include "getfeeds.hpp"

#include "ttrssmanager.hpp"

#include "data/category.hpp"
#include "data/feed.hpp"

#include <QtCore/QDebug>

namespace ttrss {
	namespace packets {
		GetFeeds::GetFeeds(	int categoryId,
							bool unreadOnly,
							TTRSSManager* manager,
							unsigned long long id) :
								APacket(manager, id),
								_categoryId(categoryId),
								_unreadOnly(unreadOnly) {
		}

		GetFeeds::~GetFeeds() {
		}

		void GetFeeds::handleSuccess(QVariant reply) {
			QList<QVariant> lReply = reply.toList();
			for (QList<QVariant>::ConstIterator it = lReply.constBegin(), end = lReply.constEnd(); it != end; ++it) {
				QMap<QString, QVariant> mFeed = it->toMap();
				if (mFeed.value("id").toInt() >= 0) {
					data::Category* category = getManager()->getCategory(_categoryId);
					if (category) {
						data::Feed* feed = new data::Feed(	mFeed.value("id").toInt(),
															mFeed.value("title").toString(),
															QUrl(mFeed.value("feed_url").toString()),
															QList<data::Article*>(),
															category);
						category->addFeed(feed);
						getManager()->addFeed(feed);
						getManager()->requestHeadlines(feed->getId());
					} else {
						qDebug() << "Received feed for unknown category" << _categoryId;
					}
				}
			}
		}

		void GetFeeds::handleError(QVariant /*reply*/) {
			qDebug() << "GetFeeds::error";
		}

		QVariantMap GetFeeds::getRequestDataImpl() const {
			QVariantMap packet;
			packet["op"] = "getFeeds";
			packet["cat_id"] = _categoryId;
			packet["unread_only"] = _unreadOnly;
			return packet;
		}
	}
}
