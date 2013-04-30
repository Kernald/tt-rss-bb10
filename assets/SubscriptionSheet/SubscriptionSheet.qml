import bb.cascades 1.0

Page {
    signal cancel
    
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
            enabled: false
            onTriggered: {
                // TODO: get URL from textfield
                _manager.subscribe("http://test");
                // TODO: close
            }
        }
    }
    
    Container {
    }
}
