import bb.cascades 1.0

Page {
    titleBar: TitleBar {
        title: currentFeed.title
        visibility: ChromeVisibility.Visible
    } // titleBar
    
    Container {
        ListView {
            dataModel: _articleModel
            listItemComponents: [
                ListItemComponent {
                    type: "item"

                    ArticleListComponent {
                        title: ListItemData.title
                        updated: ListItemData.updatedTime
                        content: ListItemData.content
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
                    currentArticle = dataModel.data(indexPath);
                    var page = articlePageDefinition.createObject();
                    nav.push(page)
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
