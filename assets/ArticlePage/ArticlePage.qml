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
        ActionItem {
            title: article.unread ? qsTr("Mark as read") : qsTr("Keep unread")
            imageSource: article.unread ? "asset:///images/mark_as_read.png" : "asset:///images/keep_unread.png"
            ActionBar.placement: ActionBarPlacement.OnBar

            onTriggered: {
                article.unread = !article.unread
            }
        }, // Keep unread
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
