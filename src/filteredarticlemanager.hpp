#ifndef __FILTERED_ARTICLE_MANAGER_HPP__
#define __FILTERED_ARTICLE_MANAGER_HPP__

#include "modelfilter.hpp"

namespace ttrss {
	class FilteredArticleManager: public ModelFilter {

		Q_OBJECT

	public:
		FilteredArticleManager(bb::cascades::DataModel *sourceModel, QObject *parent = 0);
		virtual ~FilteredArticleManager();

		Q_INVOKABLE void filterOnFeed(int feedId);
		Q_INVOKABLE void resetFeedFilter();

	protected:
	    virtual bool isSourceIndexFiltered(const QVariantList& sourceIndexPath) const;

	private:
	    int	_filteredFeed;
	};
}

#endif // __FILTERED_ARTICLE_MANAGER_HPP__
