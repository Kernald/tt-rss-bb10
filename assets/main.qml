import bb.cascades 1.0
import bb.system 1.0
import "CategoryTab"
import "FeedsListPage"
import "SubscriptionSheet"

TabbedPane {
    id: tabPane
    Menu.definition: MenuDefinition {
        settingsAction: SettingsActionItem {
            onTriggered: {
                displaySettings();
            }
        }
        helpAction: HelpActionItem {
            onTriggered: {
                displayHelp();
            }
        }
        /*actions: [
            ActionItem {
                title: qsTr("Subscribe")
                imageSource: "asset:///images/subscribe.png"
                onTriggered: {
                    displaySubscriptionPage();
                }
            }
        ]*/
    } // Menu.definition
    
    showTabsOnActionBar: false
    activePane: NavigationPane {
        id: nav
        peekEnabled: false
        FeedsListPage {
            id: feedsPage
            onFeedClicked: {
                var page = articlesListPageDefinition.createObject();
                page.feed = feed;
                nav.push(page)
            }
        }
    } // NavigationPane
    
    onActiveTabChanged: {
        feedsPage.titleBar.title = activeTab.title;
        if (activeTab.category) {
            _feedModel.filterOnCategory(activeTab.category.id);
        } else {
            _feedModel.resetCategoryFilter();
        }
    }
    
    attachedObjects: [
        ComponentDefinition {
            id: settingsPageDefinition
            source: "SettingsPage/SettingsPage.qml"
        }, // Settings page
        ComponentDefinition {
            id: articlesListPageDefinition
            source: "ArticlesListPage/ArticlesListPage.qml"
        }, // Articles list page
        ComponentDefinition {
            id: newTabDefinition
            content: CategoryTab {}
        }, // New tab
        SystemToast {
            id: errorToast
            body: "Error"
        }, // Error toast
        Sheet {
            id: subscriptionSheet
            SubscriptionSheet {
                id: subscribe
                onCancel: {
                    subscriptionSheet.close();
                }
                onAccept: {
                    _manager.subscribe(feedUrl);
                    subscriptionSheet.close();
                }
            }
        } // Subscription page
    ] // attachedObjects

    function displaySettings() {
        var page = settingsPageDefinition.createObject();
        nav.push(page)
    }

    function displayHelp() {
        // TODO: display help
        console.log("Help not implemented yet");
    }
    function displaySubscriptionPage() {
        subscriptionSheet.open();
    }
    
    function displayError(text) {
        errorToast.body = text;
        errorToast.show();
    }
    
    function addCategory(category) {
        var tab = newTabDefinition.createObject();
        tab.category = category;
        tabPane.add(tab);
    }
    
    Tab {
        title: qsTr("All feeds")
        imageSource: "asset:///images/all_categories.png"
    }
} // TabbedPane
