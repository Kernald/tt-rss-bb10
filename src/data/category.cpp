#include "category.hpp"

#include "feed.hpp"

Category::Category(QString title, QList<Feed*> feeds) : _title(title), _feeds(feeds) {
}

Category::~Category() {
	for (QList<Feed*>::Iterator it = _feeds.begin(), end = _feeds.end(); it != end; ++it)
		delete *it;
}
