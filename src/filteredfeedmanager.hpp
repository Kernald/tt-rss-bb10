#ifndef __FILTERED_FEED_MANAGER_HPP__
#define __FILTERED_FEED_MANAGER_HPP__

#include <bb/cascades/DataModel>
#include <QtCore/QHash>

namespace ttrss {
	class FilteredFeedManager: public bb::cascades::DataModel {

		Q_OBJECT

	public:
		FilteredFeedManager(bb::cascades::DataModel *sourceModel, QObject *parent = 0);
		virtual ~FilteredFeedManager();

	    int childCount(const QVariantList& proxyIndexPath) const;
	    virtual int childCount(const QVariantList& proxyIndexPath);
	    virtual bool hasChildren(const QVariantList& proxyIndexPath);
	    virtual QVariant data(const QVariantList& proxyIndexPath);
	    virtual QString itemType(const QVariantList& proxyIndexPath);

		Q_INVOKABLE void filterOnCategory(int categoryId);
		Q_INVOKABLE void resetCategoryFilter();

	private Q_SLOTS:
		void handleAdd(const QVariantList& sourceIndexPath);
		void handleUpdate(const QVariantList& sourceIndexPath);
		void handleRemove(const QVariantList& sourceIndexPath);

	private:
	    bool isSourceIndexFiltered(const QVariantList& sourceIndexPath) const;
	    int childCount_impl(const QVariantList& proxyIndexPath) const;
	    void fillMapping();
	    QVariantList proxyToSource(const QVariantList& proxyIndexPath, bool& ok) const;
	    QVariantList sourceToProxy(const QVariantList& sourceIndexPath) const;

	    bb::cascades::DataModel*			_sourceDataModel;
	    int									_filteredCategory;
	    bool								_filtered;
	    QHash<QVariantList, QVariantList>	_filterMapping;
	};

	inline int FilteredFeedManager::childCount(const QVariantList& proxyIndexPath) const {
		return childCount_impl(proxyIndexPath);
	}

	inline int FilteredFeedManager::childCount(const QVariantList& proxyIndexPath) {
		return childCount_impl(proxyIndexPath);
	}
}

inline uint qHash(const QVariantList& key) {
	uint res = 0;
	foreach (QVariant v, key) {
		res ^= qHash(v.toInt());
	}
	return res;
}

#endif // __FILTERED_FEED_MANAGER_HPP__
