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
            visible: !_manager.working && !_feedModel.empty

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
        
        Label {
            text: qsTr("Nothing to read")
            visible: !_manager.working && _feedModel.empty
            textStyle.textAlign: TextAlign.Center
            verticalAlignment: VerticalAlignment.Center
            horizontalAlignment: HorizontalAlignment.Center
            textStyle.fontStyle: FontStyle.Italic
            textStyle.fontWeight: FontWeight.W400
            textStyle.fontSize: FontSize.Large
            textStyle.color: Color.LightGray
        } // Empty indicator
    
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
