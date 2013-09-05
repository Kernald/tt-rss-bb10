import bb.cascades 1.0

Page {
    signal cancel
    signal accept (string feedUrl)
    
    titleBar: TitleBar {
        id: titleBar
        title: qsTr("Subscribe")
        visibility: ChromeVisibility.Visible

        dismissAction: ActionItem {
            title: qsTr("Cancel")
            onTriggered: {
                cancel();
            }
        }

        acceptAction: ActionItem {
            title: qsTr("OK")
            // TODO: enable only when input is validated
            enabled: true
            onTriggered: {
                accept(feedUrl.text);
            }
        }
    }
    
    Container {
        leftPadding: 20
        rightPadding: 20
        
        Label {
            text: qsTr("Feed url")
        }
        TextField {
            id: feedUrl
            inputMode: TextFieldInputMode.Url
        }
    }
}
