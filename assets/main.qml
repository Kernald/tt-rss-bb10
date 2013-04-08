import bb.cascades 1.0
import "FeedsListPage"

NavigationPane {
    id: nav
    
    Menu.definition: MenuDefinition {
        settingsAction: SettingsActionItem {
            onTriggered: {
                displaySettings();
            }
        }
    } // Menu.definition
    
    FeedsListPage {}

    attachedObjects: [
        ComponentDefinition {
            id: settingsPageDefinition
            source: "SettingsPage/SettingsPage.qml"
        }
    ] // attachedObjects

    function displaySettings() {
        var page = settingsPageDefinition.createObject();
        nav.push(page)
    }
} // NavigationPane
