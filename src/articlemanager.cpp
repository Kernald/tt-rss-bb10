#include "articlemanager.hpp"

#include "settings.hpp"

namespace ttrss {
	ArticleManager::ArticleManager(TTRSSManager* mainManager) : bb::cascades::GroupDataModel(QStringList() << "updatedDate" << "updated" << "title"), _mainManager(mainManager) {
		setSortedAscending(Settings::getValueFor("articlesOldestFirst", true).toBool());
	}

	ArticleManager::~ArticleManager() {
	}
}
