#ifndef __ARTICLE_MANAGER_HPP__
#define __ARTICLE_MANAGER_HPP__

namespace ttrss {
	class TTRSSManager;
}

#include <bb/cascades/GroupDataModel>

namespace ttrss {
	class ArticleManager : public bb::cascades::GroupDataModel {

		Q_OBJECT

	public:
		ArticleManager(TTRSSManager* mainManager);
		virtual ~ArticleManager();

	private:
		TTRSSManager*	_mainManager;
	};
}

#endif // __ARTICLE_MANAGER_HPP__
