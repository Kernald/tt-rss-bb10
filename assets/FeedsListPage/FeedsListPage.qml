import bb.cascades 1.0

Page {
    signal feedClicked(variant feed)

    id: root

    titleBar: TitleBar {
        title: qsTr("All feeds")
        visibility: ChromeVisibility.Visible
    } // titleBar
    
    Container {
        layout: DockLayout {}
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
            visible: !_manager.working

            onTriggered: {
                if (indexPath.length > 1) {
                    var feed = dataModel.data(indexPath);
                    if (feed)
                        _articleModel.filterOnFeed(feed.id);
                    root.feedClicked(feed);
                }
            }
        } // ListView
        
        ActivityIndicator {
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
            running: _manager.working
            visible: _manager.working
        }
    } // Root container
    actions: [
        ActionItem {
            title: qsTr("Refresh")
            imageSource: "asset:///images/ic_refresh.png"
            ActionBar.placement: ActionBarPlacement.InOverflow
            enabled: !_manager.working
            onTriggered: {
                _manager.requestCategories();
            }
        } // Refresh
    ] // Actions
} // Page
