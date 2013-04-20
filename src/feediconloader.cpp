#include "feediconloader.hpp"

#include "data/feed.hpp"

namespace ttrss {
	FeedIconLoader::FeedIconLoader(const QString &imageUrl, data::Feed* feed, QObject* parent): ImageLoader(imageUrl, parent), _feed(feed) {
		connect(this, SIGNAL(loadingChanged()), this, SLOT(handleLoadChange()));
	}

	FeedIconLoader::~FeedIconLoader() {
	}

	void FeedIconLoader::handleLoadChange() {
		if (!loading()) {
			_feed->setIcon(image());
			deleteLater();
		}
	}
}
