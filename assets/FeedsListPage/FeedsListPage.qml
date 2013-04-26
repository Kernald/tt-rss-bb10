import bb.cascades 1.0

Page {
    signal articleClicked(variant article)

    id: root

    titleBar: TitleBar {
        title: qsTr("All feeds")
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
                        feed: ListItemData
                    }
                }
            ]
            //visible: !_manager.working

            onTriggered: {
                if (indexPath.length > 1) {
                    root.articleClicked(dataModel.data(indexPath));
                }
            }
        } // ListView
        
        /*ActivityIndicator {
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
            running: _manager.working
        }*/
    } // Root container
} // Page
