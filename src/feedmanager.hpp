#ifndef __FEED_MANAGER_HPP__
#define __FEED_MANAGER_HPP__

#include <bb/cascades/GroupDataModel>

class FeedManager : public bb::cascades::GroupDataModel {

	Q_OBJECT

public:
	FeedManager();
	virtual ~FeedManager();

public Q_SLOTS:
	void filterOnCategory(int categoryId);
};

#endif // __FEED_MANAGER_HPP__
