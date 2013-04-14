#ifndef __ARTICLE_HPP__
#define __ARTICLE_HPP__

#include <QtCore/QDate>
#include <QtCore/QDateTime>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QUrl>
#include <QtCore/QVariant>

namespace ttrss {
	namespace data {
		class Article : public QObject {

			Q_OBJECT

			Q_PROPERTY(QString title READ getTitle CONSTANT);
			Q_PROPERTY(QString content READ getContent CONSTANT);
			Q_PROPERTY(QString author READ getAuthor CONSTANT);
			Q_PROPERTY(QDateTime updated READ getUpdated CONSTANT);
			Q_PROPERTY(QDate updatedDate READ getUpdatedDate CONSTANT);

		public:
			// TODO: complete attributes
			Article(unsigned int id = 0,
					QString title = "",
					QList<QString> labels = QList<QString>(),
					bool unread = false,
					bool marked = false,
					bool published = false,
					unsigned int updated = 0,
					QString content = "",
					bool loaded = false);
			Article(const Article& other);
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
			QDateTime getUpdated() const;
			QDate getUpdatedDate() const;
			QUrl getLink() const;

		private:
			unsigned int	_id;
			QString			_title;
			QUrl			_link;
			QList<QString>	_labels;
			bool			_unread;
			bool			_marked;
			bool			_published;
			QString			_comments;
			QString			_author;
			QDateTime		_updated;
			QString			_content;
			bool			_loaded;
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

		inline QDateTime Article::getUpdated() const {
			return _updated;
		}

		inline QDate Article::getUpdatedDate() const {
			return _updated.date();
		}

		inline QString Article::getContent() const {
			// TODO: if not loaded, load first
			return _content;
		}
	}
}

Q_DECLARE_METATYPE(ttrss::data::Article);
Q_DECLARE_METATYPE(ttrss::data::Article*);

#endif // __ARTICLE_HPP__
