#ifndef __ARTICLE_HPP__
#define __ARTICLE_HPP__

#include <QtCore/QList>
#include <QtCore/QString>
#include <QtCore/QUrl>

class Article {
public:
	// TODO: complete attributes
	Article(unsigned int id, QString title, QList<QString> labels, bool unread, bool marked, bool published, QString content);
	virtual ~Article();

	unsigned int getId() const;
	QString getTitle() const;
	QList<QString> getLabels() const;
	bool isUnread() const;
	void setUnread(bool unread);
	bool isMarked() const;
	void setMarked(bool marked);
	bool isPublished() const;
	void setPublished(bool published);
	QString getComments() const;
	QString getContent() const;
	QString getAuthor() const;
	unsigned int getUpdated() const;
	QUrl getLink() const;

private:
	unsigned int _id;
	QString _title;
	QUrl _link;
	QList<QString> _labels;
	bool _unread;
	bool _marked;
	bool _published;
	QString _comments;
	QString _author;
	unsigned int _updated;
	QString _content;
	// TODO: feed_id
	// TODO: attachments
};

inline unsigned int Article::getId() const {
	return _id;
}

inline QString Article::getTitle() const {
	return _title;
}

inline QUrl Article::getLink() const {
	return _link;
}

inline QList<QString> Article::getLabels() const {
	return _labels;
}

inline bool Article::isUnread() const {
	return _unread;
}

inline void Article::setUnread(bool unread) {
	_unread = unread;
}

inline bool Article::isMarked() const {
	return _marked;
}

inline void Article::setMarked(bool marked) {
	_marked = marked;
}

inline bool Article::isPublished() const {
	return _published;
}

inline void Article::setPublished(bool published) {
	_published = published;
}

inline QString Article::getComments() const {
	return _comments;
}

inline QString Article::getAuthor() const {
	return _author;
}

inline unsigned int Article::getUpdated() const {
	return _updated;
}

inline QString Article::getContent() const {
	return _content;
}

#endif // __ARTICLE_HPP__
