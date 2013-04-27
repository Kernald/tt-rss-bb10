#include "filteredarticlemanager.hpp"

#include "data/article.hpp"

namespace ttrss {
	FilteredArticleManager::FilteredArticleManager(bb::cascades::DataModel *sourceModel, QObject *parent):	ModelFilter(sourceModel, parent),
																											_filteredFeed(0) {
	}

	FilteredArticleManager::~FilteredArticleManager() {
	}

	void FilteredArticleManager::filterOnFeed(int feedId) {
		_filteredFeed = feedId;
		setFilterStatus(true);
	}

	void FilteredArticleManager::resetFeedFilter() {
		setFilterStatus(false);
	}

	bool FilteredArticleManager::isSourceIndexFiltered(const QVariantList& sourceIndexPath) const {
		if (!getFilterStatus() || sourceIndexPath.size() == 0)
			return false;
		if (sourceIndexPath.size() == 1)
			return childCount(sourceToProxy(sourceIndexPath)) == 0;
		return qobject_cast<data::Article*>(getSourceDataModel()->data(sourceIndexPath).value<QObject*>())->getFeed()->getId() != _filteredFeed;
	}
}
