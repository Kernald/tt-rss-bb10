import bb.cascades 1.0
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
        }
    ] // attachedObjects

    function displaySettings() {
        var page = settingsPageDefinition.createObject();
        nav.push(page)
    }

    Tab {
        title: qsTr("All feeds")
    }

    Tab {
        title: qsTr("Test")
    }
} // TabbedPane
