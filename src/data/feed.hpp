#ifndef __FEED_HPP__
#define __FEED_HPP__

class Article;

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QUrl>

class Feed {
public:
	Feed(QString title, QUrl feedUrl, QList<Article*> articles);
	virtual ~Feed();

	QString getTitle() const;
	QUrl getUrl() const;
	QList<Article*> getArticles() const;

	bool hasUnreadArticles() const;
	unsigned int unreadArticlesCount() const;
	QList<Article*> unreadArticles() const;

private:
	QString			_title;
	QUrl			_feedUrl;
	QList<Article*>	_articles;
};

inline QString Feed::getTitle() const {
	return _title;
}

inline QUrl Feed::getUrl() const {
	return _feedUrl;
}

inline QList<Article*> Feed::getArticles() const {
	return _articles;
}

#endif // __FEED_HPP__
