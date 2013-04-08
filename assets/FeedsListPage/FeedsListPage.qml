import bb.cascades 1.0

Page {
    titleBar: TitleBar {
        title: qsTr("Feeds")
        visibility: ChromeVisibility.Visible
    } // titleBar
    
    Container {
        Label {
            text: "Feeds list"
        }
    } // Root container
} // Page
