#include "getfeeds.hpp"

#include "ttrssmanager.hpp"

#include "data/category.hpp"
#include "data/feed.hpp"

#include <QtCore/QDebug>

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
		Category* category = getManager()->getCategory(_categoryId);
		if (category && mFeed.value("id").toInt() >= 0) {
			Feed* feed = new Feed(mFeed.value("id").toInt(), mFeed.value("title").toString(), QUrl(mFeed.value("feed_url").toString()), QList<Article*>());
			category->addFeed(feed);
			getManager()->requestHeadlines(feed->getId());
		} else {
			qDebug() << "Received feed for unknown category" << _categoryId;
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
