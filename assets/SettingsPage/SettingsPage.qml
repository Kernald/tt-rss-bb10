import bb.cascades 1.0

Page {
    titleBar: TitleBar {
        title: qsTr("Settings")
        visibility: ChromeVisibility.Visible
    } // titleBar
    
    Container {
        Label {
            text: "Settings"
        }
    } // Root container
} // Page
