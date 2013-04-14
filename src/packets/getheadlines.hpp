#ifndef __GET_HEADLINES_HPP__
#define __GET_HEADLINES_HPP__

#include "apacket.hpp"

namespace ttrss {
	namespace packets {
		class GetHeadlines: public APacket {
		public:
			GetHeadlines(int feedId, bool unreadOnly, TTRSSManager* manager, unsigned long long id);
			virtual ~GetHeadlines();

			virtual void handleSuccess(QVariant reply);
			virtual void handleError(QVariant reply);

		protected:
			virtual QVariantMap getRequestDataImpl() const;

		private:
			int		_feedId;
			bool	_unreadOnly;
		};
	}
}

#endif // __GET_HEADLINES_HPP__
