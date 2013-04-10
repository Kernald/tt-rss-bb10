#include "article.hpp"

Article::Article(	unsigned int id,
					QString title,
					QList<QString> labels,
					bool unread,
					bool marked,
					bool published,
					QString content,
					bool loaded) :
						_id(id),
						_title(title),
						_labels(labels),
						_unread(unread),
						_marked(marked),
						_published(published),
						_content(content),
						_loaded(loaded) {
}

Article::~Article() {
}
