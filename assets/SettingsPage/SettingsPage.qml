import bb.cascades 1.0

Page {
    titleBar: TitleBar {
        title: qsTr("Settings")
        visibility: ChromeVisibility.Visible
    } // titleBar
    ScrollView {
        horizontalAlignment: HorizontalAlignment.Fill
        Container {
            Container {
                leftPadding: 20
                rightPadding: 20
                horizontalAlignment: HorizontalAlignment.Fill
                Label {
                    text: qsTr("Server")
                }
                Container {
                    leftPadding: 40
                    Label {
                        text: qsTr("Address")
                    }
                    TextField {
                        id: serverAddress
                        inputMode: TextFieldInputMode.Url
                    }
                } // Address
                Container {
                    leftPadding: 40
                    Label {
                        text: qsTr("Login")
                    }
                    TextField {
                        id: serverLogin
                    }
                } // Login
                Container {
                    leftPadding: 40
                    Label {
                        text: qsTr("Password")
                    }
                    TextField {
                        id: serverPassword
                        inputMode: TextFieldInputMode.Password
                    }
                } // Address
            } // Server settings
            Divider {}
        } // Main scrollview container
    } // ScrollView
} // Page
