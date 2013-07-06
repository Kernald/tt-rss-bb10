#ifndef __FEED_HPP__
#define __FEED_HPP__

namespace ttrss {
	namespace data {
		class Article;
	}
}

#include "data/category.hpp"

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtCore/QVariant>

namespace ttrss {
	namespace data {
		class Feed : public QObject {

			Q_OBJECT

			Q_PROPERTY(int id READ getId CONSTANT);
			Q_PROPERTY(QString title READ getTitle CONSTANT);
			Q_PROPERTY(QUrl url READ getUrl CONSTANT);
			Q_PROPERTY(bool hasUnreadArticles READ hasUnreadArticles NOTIFY unreadArticlesChanged);
			Q_PROPERTY(unsigned int unreadArticlesCount READ unreadArticlesCount NOTIFY unreadArticlesCountChanged);
			Q_PROPERTY(QVariant icon READ getIcon WRITE setIcon NOTIFY iconChanged);

		public:
			Feed(int id = -1, QString title = "", QUrl feedUrl = QUrl(), QList<Article*> articles = QList<Article*>(), Category* category = NULL);
			Feed(const Feed& other);
			virtual ~Feed();

			int getId() const;
			QString getTitle() const;
			QUrl getUrl() const;
			QList<Article*> getArticles() const;
			QVariant getIcon() const;
			void setIcon(QVariant icon);
			Category* getCategory() const;

			bool hasUnreadArticles() const;
			unsigned int unreadArticlesCount() const;
			QList<Article*> unreadArticles() const;

			bool addArticle(Article* article);

		Q_SIGNALS:
			void unreadArticlesChanged(bool hasUnreadArticles) const;
			void unreadArticlesCountChanged(unsigned int unreadArticlesCount) const;
			void iconChanged(QVariant icon) const;

		private Q_SLOTS:
			void notifyUnreadArticlesChanged() const;

		private:
			int				_id;
			QString			_title;
			QUrl			_feedUrl;
			QList<Article*>	_articles;
			QVariant		_icon;
			Category*		_category;
		};

		inline int Feed::getId() const {
			return _id;
		}

		inline QString Feed::getTitle() const {
			return _title;
		}

		inline QUrl Feed::getUrl() const {
			return _feedUrl;
		}

		inline QList<Article*> Feed::getArticles() const {
			return _articles;
		}

		inline QVariant Feed::getIcon() const {
			return _icon;
		}

		inline void Feed::setIcon(QVariant icon) {
			_icon = icon;
			emit iconChanged(icon);
		}

		inline Category* Feed::getCategory() const {
			return _category;
		}
	}
}

Q_DECLARE_METATYPE(ttrss::data::Feed);
Q_DECLARE_METATYPE(ttrss::data::Feed*);

#endif // __FEED_HPP__
