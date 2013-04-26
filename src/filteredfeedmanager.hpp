#ifndef __FILTERED_FEED_MANAGER_HPP__
#define __FILTERED_FEED_MANAGER_HPP__

#include "modelfilter.hpp"

namespace ttrss {
	class FilteredFeedManager: public ModelFilter {

		Q_OBJECT

	public:
		FilteredFeedManager(bb::cascades::DataModel *sourceModel, QObject *parent = 0);
		virtual ~FilteredFeedManager();

		Q_INVOKABLE void filterOnCategory(int categoryId);
		Q_INVOKABLE void resetCategoryFilter();

	protected:
	    virtual bool isSourceIndexFiltered(const QVariantList& sourceIndexPath) const;

	private:
	    int	_filteredCategory;
	};
}

#endif // __FILTERED_FEED_MANAGER_HPP__
