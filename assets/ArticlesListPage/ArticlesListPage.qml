import bb.cascades 1.0

Page {
    titleBar: TitleBar {
        title: currentFeed.title
        visibility: ChromeVisibility.Visible
    } // titleBar
    
    Container {
        ListView {
        } // ListView
    }
}
