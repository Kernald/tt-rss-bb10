#ifndef __CATEGORY_HPP__
#define __CATEGORY_HPP__

class Feed;

#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>

class Category : public QObject {

	Q_OBJECT

	Q_PROPERTY(QString title READ getTitle CONSTANT);

public:
	Category(QString title, QList<Feed*> feeds);
	virtual ~Category();

	QString getTitle() const;
	QList<Feed*> getFeeds() const;

private:
	QString			_title;
	QList<Feed*>	_feeds;
};

inline QString Category::getTitle() const {
	return _title;
}

inline QList<Feed*> Category::getFeeds() const {
	return _feeds;
}

#endif // __CATEGORY_HPP__
