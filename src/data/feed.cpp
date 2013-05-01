#include "feed.hpp"

#include "article.hpp"

namespace ttrss {
	namespace data {
		Feed::Feed(int id, QString title, QUrl feedUrl, QList<Article*> articles, Category* category) :	_id(id),
																										_title(title),
																										_feedUrl(feedUrl),
																										_articles(articles),
																										_category(category) {
		}

		Feed::Feed(const Feed& other) : QObject() {
			_id = other.getId();
			_title = other.getTitle();
			_feedUrl = other.getUrl();
			// TODO: _articles
			_icon = other.getIcon();
			_category = other.getCategory();
		}

		Feed::~Feed() {
			for (QList<Article*>::Iterator it = _articles.begin(), end = _articles.end(); it != end; ++it)
				delete *it;
		}

		bool Feed::hasUnreadArticles() const {
			return unreadArticles().size() > 0;
		}

		unsigned int Feed::unreadArticlesCount() const {
			return unreadArticles().size();
		}

		QList<Article*> Feed::unreadArticles() const {
			QList<Article*> ret;
			for (QList<Article*>::ConstIterator it = _articles.constBegin(), end = _articles.constEnd(); it != end; ++it)
				if ((*it)->isUnread())
					ret << *it;

			return ret;
		}

		bool Feed::addArticle(Article* article) {
			// Don't add the same article twice
			QListIterator<data::Article*> i(_articles);
			while (i.hasNext())
				if (i.next()->getId() == article->getId())
					return false;

			unsigned int unread = unreadArticlesCount();
			_articles.append(article);
			if (article->isUnread()) {
				emit unreadArticlesChanged(true);
				emit unreadArticlesCountChanged(unread + 1);
			}
			return true;
		}
	}
}
