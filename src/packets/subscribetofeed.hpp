#ifndef __SUBSCRIBE_TO_FEED_HPP__
#define __SUBSCRIBE_TO_FEED_HPP__

#include "apacket.hpp"

namespace ttrss {
	namespace packets {
		class SubscribeToFeed: public APacket {
		public:
			SubscribeToFeed(QString url, TTRSSManager* manager, unsigned long long id);
			virtual ~SubscribeToFeed();

			virtual void handleSuccess(QVariant reply);
			virtual void handleError(QVariant reply);

		protected:
			virtual QVariantMap getRequestDataImpl() const;

		private:
			QString	_url;
		};
	}
}

#endif // __SUBSCRIBE_TO_FEED_HPP__
