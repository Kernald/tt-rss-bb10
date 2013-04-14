#include "articlemanager.hpp"

namespace ttrss {
	ArticleManager::ArticleManager(TTRSSManager* mainManager) : bb::cascades::GroupDataModel(QStringList() << "updated" << "title"), _mainManager(mainManager) {
	}

	ArticleManager::~ArticleManager() {
	}
}
