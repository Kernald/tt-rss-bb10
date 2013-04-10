import bb.cascades 1.0
import bb.system 1.0
import "FeedsListPage"

TabbedPane {
    id: tabPane
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
        ComponentDefinition {
            id: newTabDefinition
            content: Tab {}
        }, // New tab
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
    
    function addCategory(category) {
        var tab = newTabDefinition.createObject();
        tab.title = category;
        tabPane.add(tab);
    }
    
    Tab {
        title: qsTr("All feeds")
    }
} // TabbedPane
