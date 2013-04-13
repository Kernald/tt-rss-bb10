import bb.cascades 1.0

Page {
    titleBar: TitleBar {
        title: qsTr("Feeds")
        visibility: ChromeVisibility.Visible
    } // titleBar
    
    // TODO: scroll issues with dock layout? 
    Container {
        ListView {
            dataModel: _feedModel
            listItemComponents: [
                ListItemComponent {
                    type: "item"
                    
                    FeedListComponent {
                        title: ListItemData.title
                        unreadArticlesCount: ListItemData.unreadArticlesCount
                    }
                }
            ]
            //visible: !_manager.working
        } // ListView
        
        /*ActivityIndicator {
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
            running: _manager.working
        }*/
    } // Root container
} // Page
