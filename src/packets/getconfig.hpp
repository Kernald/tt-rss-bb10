#ifndef __GET_CONFIG_HPP__
#define __GET_CONFIG_HPP__

#include "apacket.hpp"

namespace ttrss {
	namespace packets {
		class GetConfig: public APacket {
		public:
			GetConfig(TTRSSManager* manager, unsigned long long id);
			virtual ~GetConfig();

			virtual void handleSuccess(QVariant reply);
			virtual void handleError(QVariant reply);

		protected:
			virtual QVariantMap getRequestDataImpl() const;
		};
	}
}

#endif // __GET_CONFIG_HPP__
