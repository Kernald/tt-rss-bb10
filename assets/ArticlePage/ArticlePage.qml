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
    } // Container
    
    actions: [
        InvokeActionItem {
            query {
                mimeType: "text/plain"
                invokeActionId: "bb.action.SHARE"
            }
            onTriggered: {
                data = article.link.toString();
            }
        } // Share
    ] // Actions
}
