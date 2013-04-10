#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

ApplicationUI::ApplicationUI(bb::cascades::Application *app) : QObject(app) {
	bb::cascades::QmlDocument *qml = bb::cascades::QmlDocument::create("asset:///main.qml").parent(this);
	qml->setContextProperty("_manager", &_manager);
	qml->setContextProperty("_settings", &_settings);

    bb::cascades::AbstractPane *root = qml->createRootObject<bb::cascades::AbstractPane>();
    connect(&_manager, SIGNAL(networkError(QVariant)), root, SLOT(displayError(QVariant)));
    connect(&_manager, SIGNAL(categoryAdded(QVariant)), root, SLOT(addCategory(QVariant)));
    app->setScene(root);
}
