#ifndef __CATEGORY_HPP__
#define __CATEGORY_HPP__

namespace ttrss {
	namespace data {
		class Feed;
	}
}

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QVariant>
namespace ttrss {
	namespace data {
		class Category : public QObject {

			Q_OBJECT

			Q_PROPERTY(int id READ getId CONSTANT);
			Q_PROPERTY(QString title READ getTitle CONSTANT);
			Q_PROPERTY(bool hasUnreadArticles READ hasUnreadArticles NOTIFY unreadArticlesChanged);
			Q_PROPERTY(unsigned int unreadArticlesCount READ unreadArticlesCount NOTIFY unreadArticlesCountChanged);

		public:
			Category(int id = -1, QString title = "", QList<Feed*> feeds = QList<Feed*>());
			Category(const Category& other);
			virtual ~Category();

			int getId() const;
			QString getTitle() const;
			QList<Feed*> getFeeds() const;

			bool hasUnreadArticles() const;
			unsigned int unreadArticlesCount() const;

			void addFeed(Feed* feed);

		Q_SIGNALS:
			void unreadArticlesChanged(bool hasUnreadArticles);
			void unreadArticlesCountChanged(unsigned int unreadArticlesCount);

		private:
			int				_id;
			QString			_title;
			QList<Feed*>	_feeds;
		};

		inline int Category::getId() const {
			return _id;
		}

		inline QString Category::getTitle() const {
			return _title;
		}

		inline QList<Feed*> Category::getFeeds() const {
			return _feeds;
		}
	}
}

Q_DECLARE_METATYPE(ttrss::data::Category);
Q_DECLARE_METATYPE(ttrss::data::Category*);

#endif // __CATEGORY_HPP__
