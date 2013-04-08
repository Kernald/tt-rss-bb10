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
                        objectName: "serverAddress"
                        inputMode: TextFieldInputMode.Url
                        text: _settings.getValueFor(objectName, "")
                        onTextChanged: {
                            _settings.saveValueFor(serverAddress.objectName, text);
                        }
                    }
                } // Address
                Container {
                    leftPadding: 40
                    Label {
                        text: qsTr("Login")
                    }
                    TextField {
                        id: serverLogin
                        objectName: "serverLogin"
                        text: _settings.getValueFor(objectName, "")
                        onTextChanged: {
                            _settings.saveValueFor(serverLogin.objectName, text);
                        }
                    }
                } // Login
                Container {
                    leftPadding: 40
                    Label {
                        text: qsTr("Password")
                    }
                    TextField {
                        id: serverPassword
                        objectName: "serverPassword"
                        inputMode: TextFieldInputMode.Password
                        text: _settings.getValueFor(objectName, "")
                        onTextChanged: {
                            _settings.saveValueFor(serverPassword.objectName, text);
                        }
                    }
                } // Address
            } // Server settings
            Divider {}
        } // Main scrollview container
    } // ScrollView
} // Page
