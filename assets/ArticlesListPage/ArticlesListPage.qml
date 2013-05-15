import bb.cascades 1.0

Page {
    property variant feed
    titleBar: TitleBar {
        title: feed.title
        visibility: ChromeVisibility.Visible
    } // titleBar
    
    Container {
        ListView {
            dataModel: _articleModel
            listItemComponents: [
                ListItemComponent {
                    type: "item"
                    
                    ArticleListComponent {
                        article: ListItemData

                        contextActions: [
                            ActionSet {
                                title: article.title
                                ActionItem {
                                    title: article.unread ? qsTr("Mark as read") : qsTr("Keep unread")
                                    imageSource: article.unread ? "asset:///images/mark_as_read.png" : "asset:///images/keep_unread.png"

                                    onTriggered: {
                                        article.unread = !article.unread
                                    }
                                }
                            }
                        ]
                    }
                },
                ListItemComponent {
                    type: "header"
                    Header {
                        title: Qt.formatDate(ListItemData, Qt.DefaultLocaleLongDate)
                    }
                }
            ]
            onTriggered: {
                if (indexPath.length > 1) {
                    var page = articlePageDefinition.createObject();
                    var article = dataModel.data(indexPath);
                    article.unread = false;
                    page.article = article;
                    nav.push(page);
                }
            }
            attachedObjects: [
                ComponentDefinition {
                    id: articlePageDefinition
                    source: "../ArticlePage/ArticlePage.qml"
                } // Article page
            ]
        } // ListView
    }
}
