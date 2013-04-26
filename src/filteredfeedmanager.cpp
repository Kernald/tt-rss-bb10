#include "filteredfeedmanager.hpp"

#include "data/feed.hpp"

namespace ttrss {
	FilteredFeedManager::FilteredFeedManager(bb::cascades::DataModel *sourceModel, QObject *parent):	ModelFilter(sourceModel, parent),
																										_filteredCategory(0) {
	}

	FilteredFeedManager::~FilteredFeedManager() {
	}

	void FilteredFeedManager::filterOnCategory(int categoryId) {
		_filteredCategory = categoryId;
		setFilterStatus(true);
	}

	void FilteredFeedManager::resetCategoryFilter() {
		setFilterStatus(false);
	}

	bool FilteredFeedManager::isSourceIndexFiltered(const QVariantList& sourceIndexPath) const {
		if (!getFilterStatus() || sourceIndexPath.size() == 0)
			return false;
		if (sourceIndexPath.size() == 1)
			return childCount(sourceToProxy(sourceIndexPath)) == 0;
		return qobject_cast<data::Feed*>(getSourceDataModel()->data(sourceIndexPath).value<QObject*>())->getCategory()->getId() != _filteredCategory;
	}
}
