#include "articlemanager.hpp"

namespace ttrss {
	ArticleManager::ArticleManager(TTRSSManager* mainManager) : bb::cascades::GroupDataModel(QStringList() << "updatedDate" << "updated" << "title"), _mainManager(mainManager) {
	}

	ArticleManager::~ArticleManager() {
	}
}
