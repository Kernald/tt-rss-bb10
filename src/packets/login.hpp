#ifndef __LOGIN_HPP__
#define __LOGIN_HPP__

#include "apacket.hpp"

namespace ttrss {
	namespace packets {
		class Login : public APacket {
		public:
			Login(QString login, QString password, TTRSSManager* manager, unsigned long long id);
			virtual ~Login();

			virtual void handleSuccess(QVariant reply);
			virtual void handleError(QVariant reply);

		protected:
			virtual QVariantMap getRequestDataImpl() const;

		private:
			QString	_login;
			QString	_password;
		};
	}
}

#endif // __LOGIN_HPP__
