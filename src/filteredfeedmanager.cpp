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
					SLOT(handleAdd(QVariantList)));
		connect(
				_sourceDataModel,
					SIGNAL(itemUpdated(QVariantList)),
				this,
					SLOT(handleUpdate(QVariantList)));
		connect(
				_sourceDataModel,
					SIGNAL(itemRemoved(QVariantList)),
				this,
					SLOT(handleRemove(QVariantList)));
	}

	FilteredFeedManager::~FilteredFeedManager() {
	}


	void FilteredFeedManager::handleAdd(const QVariantList& sourceIndexPath) {
		if (!isSourceIndexFiltered(sourceIndexPath))
			emit itemAdded(sourceToProxy(sourceIndexPath));
	}

	void FilteredFeedManager::handleUpdate(const QVariantList& sourceIndexPath) {
		if (!isSourceIndexFiltered(sourceIndexPath))
			emit itemUpdated(sourceToProxy(sourceIndexPath));
	}

	void FilteredFeedManager::handleRemove(const QVariantList& sourceIndexPath) {
		if (!isSourceIndexFiltered(sourceIndexPath))
			emit itemRemoved(sourceToProxy(sourceIndexPath));
	}

	bool FilteredFeedManager::isSourceIndexFiltered(const QVariantList& sourceIndexPath) const {
		if (!_filtered || sourceIndexPath.size() == 0)
			return false;
		if (sourceIndexPath.size() == 1)
			return childCount(sourceToProxy(sourceIndexPath)) == 0;
		return qobject_cast<data::Feed*>(_sourceDataModel->data(sourceIndexPath).value<QObject*>())->getCategory()->getId() != _filteredCategory;
	}

	int FilteredFeedManager::childCount_impl(const QVariantList& proxyIndexPath) const {
		int result = 0;
		bool ok;
		QVariantList sourceBasePath = proxyToSource(proxyIndexPath, ok);
		if (!ok)
			return result;

		for (unsigned int i = 0, j = _sourceDataModel->childCount(sourceBasePath); i < j; ++i) {
			QVariantList proxyPath = proxyIndexPath;
			proxyPath << i;
			bool res;
			QVariantList sourcePath = proxyToSource(proxyPath, res);
			if (res && !isSourceIndexFiltered(sourcePath)) {
				++result;
			}
		}

		return result;
	}

	bool FilteredFeedManager::hasChildren(const QVariantList& proxyIndexPath) {
		bool ok;
		QVariantList sourcePath = proxyToSource(proxyIndexPath, ok);
		if (!ok || isSourceIndexFiltered(sourcePath) || !_sourceDataModel->hasChildren(sourcePath))
			return false;

		return childCount(proxyIndexPath) > 0;
	}

	QVariant FilteredFeedManager::data(const QVariantList& proxyIndexPath) {
		bool ok;
		return _sourceDataModel->data(proxyToSource(proxyIndexPath, ok));
	}

	QString FilteredFeedManager::itemType(const QVariantList& proxyIndexPath) {
		bool ok;
	    return _sourceDataModel->itemType(proxyToSource(proxyIndexPath, ok));
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

	QVariantList FilteredFeedManager::proxyToSource(const QVariantList& proxyIndexPath, bool& ok) const {
		ok = true;
		if (!_filtered)
			return proxyIndexPath;
		if (proxyIndexPath == QVariantList())
			return QVariantList();
		QHash<QVariantList, QVariantList>::ConstIterator it = _filterMapping.find(proxyIndexPath);
		if (it == _filterMapping.constEnd()) {
			ok = false;
			return QVariantList();
		} else
			return *it;
	}

	QVariantList FilteredFeedManager::sourceToProxy(const QVariantList& sourceIndexPath) const {
		if (!_filtered)
			return sourceIndexPath;
		return _filterMapping.key(sourceIndexPath);
	}
}
