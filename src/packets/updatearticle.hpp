#ifndef __UPDATE_ARTICLE_HPP__
#define __UPDATE_ARTICLE_HPP__

#include "apacket.hpp"

namespace ttrss {
	namespace packets {
		class UpdateArticle: public ttrss::packets::APacket {
		public:
			enum E_Field {
				STARRED = 0,
				PUBLISHED = 1,
				UNREAD = 2,
				NOTE = 3
			};
			UpdateArticle(unsigned int articleId, E_Field field, bool status, QString data, TTRSSManager* manager, unsigned long long id);
			virtual ~UpdateArticle();

			virtual void handleSuccess(QVariant reply);
			virtual void handleError(QVariant reply);

		protected:
			virtual QVariantMap getRequestDataImpl() const;

		private:
			unsigned int	_articleId;
			E_Field			_field;
			bool			_status;
			QString			_data;
		};
	}
}

#endif // __UPDATE_ARTICLE_HPP__
