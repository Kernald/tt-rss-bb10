#ifndef __FEED_ICON_LOADER_HPP__
#define __FEED_ICON_LOADER_HPP__

namespace ttrss {
	namespace data {
		class Feed;
	}
}

#include "imageloader.hpp"

namespace ttrss {
	class FeedIconLoader: public ttrss::ImageLoader {

		Q_OBJECT

	public:
		FeedIconLoader(const QString &imageUrl, data::Feed* feed, QObject* parent = 0);
		virtual ~FeedIconLoader();

	private Q_SLOTS:
		void handleLoadChange();

	private:
		data::Feed*	_feed;
	};
}

#endif // __FEED_ICON_LOADER_HPP__
