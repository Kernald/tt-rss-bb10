import bb.cascades 1.0
import bb.system 1.0
import "FeedsListPage"

TabbedPane {
    Menu.definition: MenuDefinition {
        settingsAction: SettingsActionItem {
            onTriggered: {
                displaySettings();
            }
        }
    } // Menu.definition
    
    showTabsOnActionBar: false
    activePane: NavigationPane {
        id: nav
        FeedsListPage {}
    } // NavigationPane
    
    attachedObjects: [
        ComponentDefinition {
            id: settingsPageDefinition
            source: "SettingsPage/SettingsPage.qml"
        }, // Settings Page
        SystemToast {
            id: errorToast
            body: "Error"
        } // Error toast
    ] // attachedObjects
    
    function displaySettings() {
        var page = settingsPageDefinition.createObject();
        nav.push(page)
    }
    
    function displayError(text) {
        errorToast.body = text;
        errorToast.show();
    }
    
    Tab {
        title: qsTr("All feeds")
    }
    
    Tab {
        title: qsTr("Test")
    }
} // TabbedPane
