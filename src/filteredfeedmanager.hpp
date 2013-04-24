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

	    int childCount(const QVariantList& indexPath) const;
	    virtual int childCount(const QVariantList& indexPath);
	    virtual bool hasChildren(const QVariantList& indexPath);
	    virtual QVariant data(const QVariantList& indexPath);
	    virtual QString itemType(const QVariantList& indexPath);

		Q_INVOKABLE void filterOnCategory(int categoryId);
		Q_INVOKABLE void resetCategoryFilter();

	private:
	    bool isSourceIndexFiltered(const QVariantList& indexPath) const;
	    int childCount_impl(const QVariantList& indexPath) const;
	    void fillMapping();
	    QVariantList proxyToSource(const QVariantList& indexPath) const;
	    QVariantList sourceToProxy(const QVariantList& indexPath) const;

	    bb::cascades::DataModel*			_sourceDataModel;
	    int									_filteredCategory;
	    bool								_filtered;
	    QHash<QVariantList, QVariantList>	_filterMapping;
	};

	inline int FilteredFeedManager::childCount(const QVariantList& indexPath) const {
		return childCount_impl(indexPath);
	}

	inline int FilteredFeedManager::childCount(const QVariantList& indexPath) {
		return childCount_impl(indexPath);
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
