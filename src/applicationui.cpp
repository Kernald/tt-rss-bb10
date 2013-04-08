#include "applicationui.hpp"

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

ApplicationUI::ApplicationUI(bb::cascades::Application *app) : QObject(app) {
	bb::cascades::QmlDocument *qml = bb::cascades::QmlDocument::create("asset:///main.qml").parent(this);
    bb::cascades::AbstractPane *root = qml->createRootObject<bb::cascades::AbstractPane>();
    app->setScene(root);
}
