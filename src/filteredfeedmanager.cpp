#include "filteredfeedmanager.hpp"

#include "data/feed.hpp"

namespace ttrss {
	FilteredFeedManager::FilteredFeedManager(bb::cascades::DataModel *sourceModel, QObject *parent):	bb::cascades::DataModel(parent),
																										_sourceDataModel(sourceModel),
																										_filteredCategory(0),
																										_filtered(false) {
		connect(
				_sourceDataModel,
					SIGNAL(itemAdded(QVariantList)),
				this,
					SIGNAL(itemAdded(QVariantList)));
		connect(
				_sourceDataModel,
					SIGNAL(itemUpdated(QVariantList)),
				this,
					SIGNAL(itemUpdated(QVariantList)));
		connect(
				_sourceDataModel,
					SIGNAL(itemRemoved(QVariantList)),
				this,
					SIGNAL(itemRemoved(QVariantList)));
	}

	FilteredFeedManager::~FilteredFeedManager() {
	}

	bool FilteredFeedManager::isFiltered(const QVariantList& indexPath) const {
		return _filtered && indexPath.size() > 1 && qobject_cast<data::Feed*>(_sourceDataModel->data(indexPath).value<QObject*>())->getCategory()->getId() != _filteredCategory;
	}

	int FilteredFeedManager::childCount(const QVariantList& indexPath) {
		if (isFiltered(indexPath))
			return 0;

		int result = 0;
		for (unsigned int i = 0, j = _sourceDataModel->childCount(indexPath); i < j; ++i) {
			QVariantList path = indexPath;
			path << i;
			if (!isFiltered(path))
				++result;
		}

		return result;
	}

	bool FilteredFeedManager::hasChildren(const QVariantList& indexPath) {
		if (isFiltered(indexPath) || !_sourceDataModel->hasChildren(indexPath))
			return false;

		return childCount(indexPath) > 0;
	}

	QVariant FilteredFeedManager::data(const QVariantList& indexPath) {
		return _sourceDataModel->data(indexPath);
	}

	QString FilteredFeedManager::itemType(const QVariantList& indexPath) {
	    return _sourceDataModel->itemType(indexPath);
	}

	void FilteredFeedManager::filterOnCategory(int categoryId) {
		_filteredCategory = categoryId;
		_filtered = true;
		emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove);
	}

	void FilteredFeedManager::resetCategoryFilter() {
		_filtered = false;
		emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove);
	}
}
