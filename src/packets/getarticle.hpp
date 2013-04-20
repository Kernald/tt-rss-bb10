#ifndef __GET_ARTICLE_HPP__
#define __GET_ARTICLE_HPP__

namespace ttrss {
	namespace data {
		class Article;
	}
}

#include "apacket.hpp"

namespace ttrss {
	namespace packets {
		class GetArticle: public APacket {
		public:
			GetArticle(data::Article* article, TTRSSManager* manager, unsigned long long id);
			virtual ~GetArticle();

			virtual void handleSuccess(QVariant reply);
			virtual void handleError(QVariant reply);

		protected:
			virtual QVariantMap getRequestDataImpl() const;

		private:
			data::Article*	_article;
		};
	}
}

#endif // __GET_ARTICLE_HPP__
