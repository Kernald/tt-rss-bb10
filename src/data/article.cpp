#include "article.hpp"

#include "ttrssmanager.hpp"

namespace ttrss {
	namespace data {
		Article::Article(	TTRSSManager* manager,
							unsigned int id,
							QString title,
							QList<QString> labels,
							bool unread,
							bool marked,
							bool published,
							unsigned int updated,
							QString excerpt,
							QString content,
							bool loaded,
							QUrl link) :
								_manager(manager),
								_id(id),
								_title(title),
								_labels(labels),
								_unread(unread),
								_marked(marked),
								_published(published),
								_updated(QDateTime::fromTime_t(updated)),
								_excerpt(excerpt),
								_content(content),
								_loaded(loaded),
								_link(link) {
		}

		Article::Article(const Article& other) : QObject() {
			_manager = other._manager;
			_id = other.getId();
			_title = other.getTitle();
			_labels = other.getLabels();
			_unread = other.isUnread();
			_marked = other.isMarked();
			_published = other.isPublished();
			_updated = other.getUpdated();
			_excerpt = other.getExcerpt();
			_content = other._content;
			_loaded = other.isLoaded();
			_comments = other.getComments();
			_author = other.getAuthor();
			_link = other.getLink();
		}

		Article::~Article() {
		}


		QString Article::getContent() {
			if (!_loaded)
				load();
			return _content;
		}

		void Article::setContent(QString content) {
			_content = content;
			_loaded = true;
			emit contentChanged(_content);
		}

		void Article::load() {
			if (!_loaded && _manager)
				_manager->requestArticleDetails(this);
		}
	}
}
