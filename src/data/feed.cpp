#include "feed.hpp"

#include "article.hpp"

Feed::Feed(int id, QString title, QUrl feedUrl, QList<Article*> articles) :	_id(id),
																			_title(title),
																			_feedUrl(feedUrl),
																			_articles(articles) {
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

void Feed::addArticle(Article* article) {
	_articles.append(article);
}
