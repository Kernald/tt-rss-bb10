#include "modelfilter.hpp"

namespace ttrss {
	ModelFilter::ModelFilter(bb::cascades::DataModel *sourceModel, QObject *parent):	bb::cascades::DataModel(parent),
																						_sourceDataModel(sourceModel),
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

	ModelFilter::~ModelFilter() {
	}

	void ModelFilter::setFilterStatus(bool filtered) {
		_filtered = filtered;
		refreshFilter();
	}

	void ModelFilter::refreshFilter() {
		if (_filtered)
			fillMapping();
		emit itemsChanged(bb::cascades::DataModelChangeType::AddRemove);
	}

	void ModelFilter::handleAdd(const QVariantList& sourceIndexPath) {
		if (!isSourceIndexFiltered(sourceIndexPath)) {
			emit itemAdded(sourceToProxy(sourceIndexPath));
			emit emptyChanged(false);
		}
	}

	void ModelFilter::handleUpdate(const QVariantList& sourceIndexPath) {
		if (!isSourceIndexFiltered(sourceIndexPath))
			emit itemUpdated(sourceToProxy(sourceIndexPath));
	}

	void ModelFilter::handleRemove(const QVariantList& sourceIndexPath) {
		if (!isSourceIndexFiltered(sourceIndexPath)) {
			emit itemRemoved(sourceToProxy(sourceIndexPath));
			emit emptyChanged(isEmpty());
		}
	}

	int ModelFilter::childCount_impl(const QVariantList& proxyIndexPath) const {
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

	bool ModelFilter::hasChildren(const QVariantList& proxyIndexPath) {
		bool ok;
		QVariantList sourcePath = proxyToSource(proxyIndexPath, ok);
		if (!ok || isSourceIndexFiltered(sourcePath) || !_sourceDataModel->hasChildren(sourcePath))
			return false;

		return childCount(proxyIndexPath) > 0;
	}

	QVariant ModelFilter::data(const QVariantList& proxyIndexPath) {
		bool ok;
		return _sourceDataModel->data(proxyToSource(proxyIndexPath, ok));
	}

	QString ModelFilter::itemType(const QVariantList& proxyIndexPath) {
		bool ok;
	    return _sourceDataModel->itemType(proxyToSource(proxyIndexPath, ok));
	}

	bool ModelFilter::isEmpty() const {
		return childCount(QVariantList()) == 0;
	}

	void ModelFilter::fillMapping() {
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

	QVariantList ModelFilter::proxyToSource(const QVariantList& proxyIndexPath, bool& ok) const {
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

	QVariantList ModelFilter::sourceToProxy(const QVariantList& sourceIndexPath) const {
		if (!_filtered)
			return sourceIndexPath;
		return _filterMapping.key(sourceIndexPath);
	}
}
