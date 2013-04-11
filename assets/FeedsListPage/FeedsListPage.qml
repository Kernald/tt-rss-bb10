import bb.cascades 1.0

Page {
    titleBar: TitleBar {
        title: qsTr("Feeds")
        visibility: ChromeVisibility.Visible
    } // titleBar
    
    Container {
        layout: DockLayout {
        }
        
        Label {
            text: "Feeds list"
        }

        ActivityIndicator {
            verticalAlignment: VerticalAlignment.Fill
            horizontalAlignment: HorizontalAlignment.Fill
            running: _manager.working
        }
    } // Root container
} // Page
