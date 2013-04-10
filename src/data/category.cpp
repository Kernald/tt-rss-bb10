#include "category.hpp"

#include "feed.hpp"

Category::Category(int id, QString title, QList<Feed*> feeds) : _id(id), _title(title), _feeds(feeds) {
}

Category::Category(const Category& other) : QObject() {
	_id = other.getId();
	_title = other.getTitle();
	_feeds = other.getFeeds();
}

Category::~Category() {
	for (QList<Feed*>::Iterator it = _feeds.begin(), end = _feeds.end(); it != end; ++it)
		delete *it;
}

bool Category::hasUnreadArticles() const {
	bool res = false;
	for (QList<Feed*>::ConstIterator it = _feeds.constBegin(), end = _feeds.constEnd(); it != end && !res; ++it)
		if ((*it)->hasUnreadArticles())
			res = true;

	return res;
}

unsigned int Category::unreadArticlesCount() const {
	unsigned int count = false;
	for (QList<Feed*>::ConstIterator it = _feeds.constBegin(), end = _feeds.constEnd(); it != end; ++it)
		count += (*it)->unreadArticlesCount();

	return count;
}

void Category::addFeed(Feed* feed) {
	unsigned int unread = unreadArticlesCount();
	_feeds.append(feed);
	if (feed->hasUnreadArticles()) {
		emit unreadArticlesChanged(true);
		emit unreadArticlesCountChanged(unread + feed->unreadArticlesCount());
	}
}
