#include "getheadlines.hpp"

#include "ttrssmanager.hpp"

#include "data/article.hpp"
#include "data/feed.hpp"

#include <QtCore/QDebug>

GetHeadlines::GetHeadlines(	int feedId,
							bool unreadOnly,
							TTRSSManager* manager,
							unsigned long long id) :
								APacket(manager, id),
								_feedId(feedId),
								_unreadOnly(unreadOnly) {
}

GetHeadlines::~GetHeadlines() {
}

void GetHeadlines::handleSuccess(QVariant reply) {
	QList<QVariant> lReply = reply.toList();
	for (QList<QVariant>::ConstIterator it = lReply.constBegin(), end = lReply.constEnd(); it != end; ++it) {
		QMap<QString, QVariant> mHeadline = it->toMap();
		Feed* feed = getManager()->getFeed(_feedId);
		if (feed) {
			// Article(unsigned int id, QString title, QList<QString> labels, bool unread, bool marked, bool published, QString content = "", bool loaded = false);
			QList<QString> labels;
			QList<QVariant> vLabels = mHeadline.value("labels").toList();
			for (QList<QVariant>::ConstIterator it = vLabels.constBegin(), end = vLabels.constEnd(); it != end; ++it)
				labels.append(it->toString());
			Article* article = new Article(	mHeadline.value("id").toUInt(),
											mHeadline.value("title").toString(),
											labels,
											mHeadline.value("unread").toBool(),
											mHeadline.value("marked").toBool(),
											mHeadline.value("published").toBool());
			feed->addArticle(article);
		} else {
			qDebug() << "Received article for unknown feed" << _feedId;
		}
	}
}

void GetHeadlines::handleError(QVariant /*reply*/) {
	qDebug() << "GetHeadlines::error";
}

QVariantMap GetHeadlines::getRequestDataImpl() const {
	QVariantMap packet;
	packet["op"] = "getHeadlines";
	packet["feed_id"] = _feedId;
	packet["view_mode"] = _unreadOnly ? "unread" : "all_articles";
	return packet;
}