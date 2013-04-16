import bb.cascades 1.0

Page {
    property variant article
    
    titleBar: TitleBar {
        title: article.title
        visibility: ChromeVisibility.Visible
    } // titleBar
    
    Container {
        TextArea {
            editable: false
            text: article.content
            textFormat: TextFormat.Html
        }
    }
}
