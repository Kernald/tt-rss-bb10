#include "imageloader.hpp"

#include "settings.hpp"

#include <bb/ImageData>

#include <QtCore/QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#include <QtCore/QDebug>

namespace ttrss {
	ImageLoader::ImageLoader(const QString& imageUrl, QObject* parent): QObject(parent), _loading(false), _imageUrl(imageUrl) {
	}

	ImageLoader::~ImageLoader() {
	}

	void ImageLoader::load() {
		_loading = true;
		emit loadingChanged();

		QNetworkAccessManager* netManager = new QNetworkAccessManager(this);

		const QUrl url(_imageUrl);
		QNetworkRequest request(url);

		QNetworkReply* reply = netManager->get(request);
		if (Settings::getValueFor("ignoreSslErrors", QVariant(false)).toBool())
			reply->ignoreSslErrors();
		connect(reply, SIGNAL(finished()), this, SLOT(onReplyFinished()));
	}

	void ImageLoader::onReplyFinished() {
		QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

		QString response;
		if (reply) {
			if (reply->error() == QNetworkReply::NoError) {
				const int available = reply->bytesAvailable();
				if (available > 0) {
					const QByteArray data(reply->readAll());
					QImage image;
					image.loadFromData(data);
					image = image.scaled(120, 120, Qt::KeepAspectRatioByExpanding);
					const QImage swappedImage = image.rgbSwapped();
					const bb::ImageData imageData = bb::ImageData::fromPixels(swappedImage.bits(), bb::PixelFormat::RGBA_Premultiplied, swappedImage.width(), swappedImage.height(), swappedImage.bytesPerLine());

					_image = bb::cascades::Image(imageData);
					emit imageChanged();

					_loading = false;
					emit loadingChanged();

					reply->deleteLater();
					return;
				}
			}
			reply->deleteLater();
		}

		// TODO: handle error: set default icon
	}

	QVariant ImageLoader::image() const {
		return QVariant::fromValue(_image);
	}

	bool ImageLoader::loading() const {
		return _loading;
	}
}
