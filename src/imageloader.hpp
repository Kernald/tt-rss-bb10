#ifndef __IMAGE_LOADER_HPP__
#define __IMAGE_LOADER_HPP__

#include <bb/cascades/Image>
#include <QtCore/QByteArray>
#include <QtGui/QImage>

namespace ttrss {
	class ImageLoader : public QObject {

		Q_OBJECT

		Q_PROPERTY(QVariant image READ image NOTIFY imageChanged)

		Q_PROPERTY(bool loading READ loading NOTIFY loadingChanged)

	public:
		ImageLoader(const QString &imageUrl, QObject* parent = 0);
		virtual ~ImageLoader();

		void load();

		QVariant image() const;
		bool loading() const;

	Q_SIGNALS:
		void imageChanged();
		void loadingChanged();

	private Q_SLOTS:
		void onReplyFinished();

	private:

		bb::cascades::Image	_image;
		bool				_loading;
		QString				_imageUrl;
	};
}

#endif // __IMAGE_LOADER_HPP__
