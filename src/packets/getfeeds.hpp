#ifndef __GET_FEEDS_HPP__
#define __GET_FEEDS_HPP__

#include "apacket.hpp"

namespace ttrss {
	namespace packets {
		class GetFeeds: public APacket {
		public:
			GetFeeds(int categoryId, bool unreadOnly, TTRSSManager* manager, unsigned long long id);
			virtual ~GetFeeds();

			virtual void handleSuccess(QVariant reply);
			virtual void handleError(QVariant reply);

		protected:
			virtual QVariantMap getRequestDataImpl() const;

		private:
			int		_categoryId;
			bool	_unreadOnly;
		};
	}
}

#endif // __GET_FEEDS_HPP__
