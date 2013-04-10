#ifndef __APACKET_HPP__
#define __APACKET_HPP__

class TTRSSManager;

#include <QtCore/QByteArray>
#include <QtCore/QMap>
#include <QtCore/QVariant>
#include <QtCore/QVariantMap>

class APacket {
public:
	APacket(TTRSSManager* manager, unsigned long long id);
	virtual ~APacket();

	virtual QByteArray getRequestData() const;
	unsigned long long getId() const;

	void handleReply(QMap<QString, QVariant> reply);
	virtual void handleSuccess(QVariant reply) = 0;
	virtual void handleError(QVariant reply) = 0;

protected:
	TTRSSManager* getManager() const;
	virtual QVariantMap getRequestDataImpl() const = 0;

private:
	TTRSSManager*		_manager;
	unsigned long long	_id;
};

inline unsigned long long APacket::getId() const {
	return _id;
}

inline TTRSSManager* APacket::getManager() const {
	return _manager;
}

#endif // __APACKET_HPP__
