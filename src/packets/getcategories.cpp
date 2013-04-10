#include "getcategories.hpp"

#include <QtCore/QDebug>

GetCategories::GetCategories(	bool unreadOnly,
								bool enableNested,
								bool includeEmpty,
								TTRSSManager* manager,
								unsigned long long id) :
									APacket(manager, id),
									_unreadOnly(unreadOnly),
									_enableNested(enableNested),
									_includeEmpty(includeEmpty) {
}

GetCategories::~GetCategories() {
}


void GetCategories::handleSuccess(QVariant reply) {
	qDebug() << "GetCategories::success";
}

void GetCategories::handleError(QVariant /*reply*/) {
	qDebug() << "GetCategories::error";
}

QVariantMap GetCategories::getRequestDataImpl() const {
	QVariantMap packet;
	packet["op"] = "getCategories";
	packet["unread_only"] = _unreadOnly;
	packet["enable_nested"] = _enableNested;
	packet["include_empty"] = _includeEmpty;
	return packet;
}
