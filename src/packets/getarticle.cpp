#include "getarticle.hpp"

#include "data/article.hpp"

#include <QtCore/QDebug>

namespace ttrss {
	namespace packets {
		GetArticle::GetArticle(data::Article* article, TTRSSManager* manager, unsigned long long id) :	APacket(manager, id),
																										_article(article) {
		}

		GetArticle::~GetArticle() {
		}

		void GetArticle::handleSuccess(QVariant reply) {
			QList<QVariant> lReply = reply.toList();
			for (QList<QVariant>::ConstIterator it = lReply.constBegin(), end = lReply.constEnd(); it != end; ++it) {
				QMap<QString, QVariant> data = it->toMap();
				if (data.value("id").toUInt() == _article->getId())
					_article->setContent(data.value("content").toString());
			}
		}

		void GetArticle::handleError(QVariant /*reply*/) {
			qDebug() << "GetArticle::error";
		}

		QVariantMap GetArticle::getRequestDataImpl() const {
			QVariantMap packet;
			packet["op"] = "getArticle";
			packet["article_id"] = _article->getId();
			return packet;
		}
	}
}
