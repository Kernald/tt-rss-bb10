import bb.cascades 1.0

Page {
    property variant article
    
    titleBar: TitleBar {
        title: article.title
        visibility: ChromeVisibility.Visible
    } // titleBar
    
    ScrollView {
        scrollViewProperties {
            scrollMode: ScrollMode.Both
            pinchToZoomEnabled: true
            minContentScale: 0.75
            maxContentScale: 5
        }
        
        onContentScaleChanged: {
            webView.settings.viewport = {
                "initial-scale": scale
            }
        }
        
        WebView {
            id: webView
            html: article.content
            settings.viewport: {
                "initial-scale": 1.0
            }
        } // Web view
    } // Scroll view
    
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
