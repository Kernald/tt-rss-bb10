#ifndef __GET_CATEGORIES_HPP__
#define __GET_CATEGORIES_HPP__

#include "apacket.hpp"

class GetCategories: public APacket {
public:
	GetCategories(bool unreadOnly, bool enableNested, bool includeEmpty, TTRSSManager* manager, unsigned long long id);
	virtual ~GetCategories();

	virtual void handleSuccess(QMap<QString, QVariant> reply);
	virtual void handleError(QMap<QString, QVariant> reply);

protected:
	virtual QVariantMap getRequestDataImpl() const;

private:
	bool	_unreadOnly;
	bool	_enableNested;
	bool	_includeEmpty;
};

#endif // __GET_CATEGORIES_HPP__
