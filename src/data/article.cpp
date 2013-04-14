#include "article.hpp"

namespace ttrss {
	namespace data {
		Article::Article(	unsigned int id,
							QString title,
							QList<QString> labels,
							bool unread,
							bool marked,
							bool published,
							unsigned int updated,
							QString excerpt,
							QString content,
							bool loaded) :
								_id(id),
								_title(title),
								_labels(labels),
								_unread(unread),
								_marked(marked),
								_published(published),
								_updated(QDateTime::fromTime_t(updated)),
								_excerpt(excerpt),
								_content(content),
								_loaded(loaded) {
		}

		Article::Article(const Article& other) : QObject() {
			// TODO: only attributes from default constructor, add others
			_id = other.getId();
			_title = other.getTitle();
			_labels = other.getLabels();
			_unread = other.isUnread();
			_marked = other.isMarked();
			_published = other.isPublished();
			_updated = other.getUpdated();
			_excerpt = other.getExcerpt();
			_content = other.getContent();
		}

		Article::~Article() {
		}

		QString Article::getContent() const {
			/*if (!_loaded)
				qDebug() << "Need to load";*/
			return _content;
		}
	}
}
