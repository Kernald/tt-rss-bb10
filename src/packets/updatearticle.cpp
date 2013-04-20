#include "updatearticle.hpp"

#include "ttrssmanager.hpp"

#include <QtCore/QDebug>

namespace ttrss {
	namespace packets {
		UpdateArticle::UpdateArticle(	unsigned int articleId,
										E_Field field,
										bool status,
										QString data,
										TTRSSManager* manager,
										unsigned long long id) :
											APacket(manager, id),
											_articleId(articleId),
											_field(field),
											_status(status),
											_data(data) {
		}

		UpdateArticle::~UpdateArticle() {
		}

		void UpdateArticle::handleSuccess(QVariant reply) {
			qDebug() << reply;
		}

		void UpdateArticle::handleError(QVariant /*reply*/) {
			qDebug() << "UpdateArticle::error";
		}

		QVariantMap UpdateArticle::getRequestDataImpl() const {
			QVariantMap packet;
			packet["op"] = "updateArticle";
			packet["article_ids"] = _articleId;
			packet["mode"] = _status ? 1 : 0;
			packet["field"] = static_cast<unsigned int>(_field);
			if (_field == NOTE)
				packet["data"] = _data;
			return packet;
		}
	}
}
