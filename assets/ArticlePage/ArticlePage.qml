import bb.cascades 1.0

Page {
    titleBar: TitleBar {
        title: currentArticle.title
        visibility: ChromeVisibility.Visible
    } // titleBar
    
    Container {
        TextArea {
            editable: false
            text: currentArticle.content
            textFormat: TextFormat.Html
        }
    }
}
