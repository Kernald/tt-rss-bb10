#include "applicationui.hpp"

#include <bb/cascades/AbstractPane>
#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>

namespace ttrss {
	ApplicationUI::ApplicationUI(bb::cascades::Application *app) :	QObject(app),
																	_articleManager(&_manager),
																	_feedManager(&_manager),
																	_filteredArticleManager(&_articleManager, this),
																	_filteredFeedManager(&_feedManager, this) {
		bb::cascades::QmlDocument *qml = bb::cascades::QmlDocument::create("asset:///main.qml").parent(this);
		qml->setContextProperty("_manager", &_manager);
		qml->setContextProperty("_settings", &_settings);
		qml->setContextProperty("_articleModel", &_filteredArticleManager);
		qml->setContextProperty("_feedModel", &_filteredFeedManager);

		bb::cascades::AbstractPane *root = qml->createRootObject<bb::cascades::AbstractPane>();
		connect(&_manager, SIGNAL(networkError(QVariant)), root, SLOT(displayError(QVariant)));
		connect(&_manager, SIGNAL(categoryAdded(QVariant)), root, SLOT(addCategory(QVariant)));
		connect(&_manager, SIGNAL(articleAdded(QObject*)), &_articleManager, SLOT(insert(QObject*)));
		connect(&_manager, SIGNAL(feedAdded(QObject*)), &_feedManager, SLOT(insert(QObject*)));
		app->setScene(root);
	}
}
