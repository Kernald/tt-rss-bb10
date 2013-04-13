#ifndef __FEED_MANAGER_HPP__
#define __FEED_MANAGER_HPP__

class TTRSSManager;

#include <bb/cascades/GroupDataModel>

class FeedManager : public bb::cascades::GroupDataModel {

	Q_OBJECT

public:
	FeedManager(TTRSSManager* mainManager);
	virtual ~FeedManager();

	Q_INVOKABLE void filterOnCategory(int categoryId);
	Q_INVOKABLE void resetCategoryFilter();

private:
	TTRSSManager*	_mainManager;
};

#endif // __FEED_MANAGER_HPP__
