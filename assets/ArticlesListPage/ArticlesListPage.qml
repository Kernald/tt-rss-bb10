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
        } // ListView
    }
}
