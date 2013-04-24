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

	bool FilteredFeedManager::isSourceIndexFiltered(const QVariantList& indexPath) const {
		if (!_filtered || indexPath.size() == 0)
			return false;
		if (indexPath.size() == 1)
			return childCount(sourceToProxy(indexPath)) == 0;
		return qobject_cast<data::Feed*>(_sourceDataModel->data(indexPath).value<QObject*>())->getCategory()->getId() != _filteredCategory;
	}

	int FilteredFeedManager::childCount_impl(const QVariantList& indexPath) const {
		int result = 0;
		for (unsigned int i = 0, j = _sourceDataModel->childCount(proxyToSource(indexPath)); i < j; ++i) {
			QVariantList path = indexPath;
			path << i;
			if (!isSourceIndexFiltered(proxyToSource(path)))
				++result;
		}

		return result;
	}

	bool FilteredFeedManager::hasChildren(const QVariantList& indexPath) {
		if (isSourceIndexFiltered(proxyToSource(indexPath)) || !_sourceDataModel->hasChildren(proxyToSource(indexPath)))
			return false;

		return childCount(indexPath) > 0;
	}

	QVariant FilteredFeedManager::data(const QVariantList& indexPath) {
		return _sourceDataModel->data(proxyToSource(indexPath));
	}

	QString FilteredFeedManager::itemType(const QVariantList& indexPath) {
	    return _sourceDataModel->itemType(proxyToSource(indexPath));
	}

	void FilteredFeedManager::filterOnCategory(int categoryId) {
		_filteredCategory = categoryId;
		_filtered = true;
		fillMapping();
		emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove);
	}

	void FilteredFeedManager::resetCategoryFilter() {
		_filtered = false;
		emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove);
	}

	void FilteredFeedManager::fillMapping() {
		_filterMapping.clear();
		int currentProxySectionIndex = 0;
		for (int sourceSectionIndex = 0, sourceSectionCount = _sourceDataModel->childCount(QVariantList()); sourceSectionIndex < sourceSectionCount; ++sourceSectionIndex) {
			bool usedIndex = false;
			QVariantList currentSourceSection;
			currentSourceSection << sourceSectionIndex;
			int currentProxyIndex = 0;
			for (int childIndex = 0, childCount = _sourceDataModel->childCount(currentSourceSection); childIndex < childCount; ++childIndex) {
				QVariantList path = QVariantList() << sourceSectionIndex << childIndex;
				bool filtered = isSourceIndexFiltered(path);
				if (!filtered) {
					if (!usedIndex) {
						usedIndex = true;
						_filterMapping.insert(QVariantList() << currentProxySectionIndex, currentSourceSection);
					}
					_filterMapping.insert(QVariantList() << currentProxySectionIndex << currentProxyIndex, QVariantList() << sourceSectionIndex << childIndex);
					++currentProxyIndex;
				}
			}

			if (usedIndex)
				++currentProxySectionIndex;
		}
	}

	QVariantList FilteredFeedManager::proxyToSource(const QVariantList& indexPath) const {
		if (!_filtered)
			return indexPath;
		QHash<QVariantList, QVariantList>::ConstIterator it = _filterMapping.find(indexPath);
		if (it == _filterMapping.constEnd())
			return QVariantList();
		else
			return *it;
	}

	QVariantList FilteredFeedManager::sourceToProxy(const QVariantList& indexPath) const {
		if (!_filtered)
			return indexPath;
		return _filterMapping.key(indexPath);
	}
}
