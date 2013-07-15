import bb.cascades 1.0

Page {
    property variant feed
    titleBar: TitleBar {
        title: feed.title
        visibility: ChromeVisibility.Visible
    } // titleBar
    
    Container {
        ListView {
            dataModel: _articleModel
            id: listView
            
            multiSelectAction: MultiSelectActionItem {
            }
            
            multiSelectHandler {
                status: qsTr("None selected")
                actions: [
                    ActionItem {
                        title: qsTr("Mark as read")
                        imageSource: "asset:///images/mark_as_read.png"
                        
                        onTriggered: {
                            var selectionList = listView.selectionList();
                            listView.clearSelection();
                            for (var i = 0; i < selectionList.length; ++i)
                            	_articleModel.data(selectionList[i]).unread = false;
                        }
                    },
                    ActionItem {
                        title: qsTr("Keep unread")
                        imageSource: "asset:///images/keep_unread.png"

                        onTriggered: {
                            var selectionList = listView.selectionList();
                            listView.clearSelection();
                            for (var i = 0; i < selectionList.length; ++ i)
                            	_articleModel.data(selectionList[i]).unread = true;
                        }
                    },

                    ActionItem {
                        title: qsTr("Publish")
                        imageSource: "asset:///images/publish.png"

                        onTriggered: {
                            var selectionList = listView.selectionList();
                            listView.clearSelection();
                            for (var i = 0; i < selectionList.length; ++ i)
                            	_articleModel.data(selectionList[i]).published = true;
                        }
                    },
                    ActionItem {
                        title: qsTr("Unpublish")
                        imageSource: "asset:///images/unpublish.png"

                        onTriggered: {
                            var selectionList = listView.selectionList();
                            listView.clearSelection();
                            for (var i = 0; i < selectionList.length; ++ i)
                            	_articleModel.data(selectionList[i]).published = false;
                        }
                    },

                    ActionItem {
                        title: qsTr("Star")
                        imageSource: "asset:///images/star.png"

                        onTriggered: {
                            var selectionList = listView.selectionList();
                            listView.clearSelection();
                            for (var i = 0; i < selectionList.length; ++ i)
                            	_articleModel.data(selectionList[i]).marked = true;
                        }
                    },
                    ActionItem {
                        title: qsTr("Unstar")
                        imageSource: "asset:///images/unstar.png"

                        onTriggered: {
                            var selectionList = listView.selectionList();
                            listView.clearSelection();
                            for (var i = 0; i < selectionList.length; ++ i)
                            	_articleModel.data(selectionList[i]).marked = false;
                        }
                    }
                ]
            }
            
            onSelectionChanged: {
                if (selectionList().length > 1) {
                    multiSelectHandler.status = qsTr("%1 items selected").arg(selectionList().length);
                } else if (selectionList().length == 1) {
                    multiSelectHandler.status = qsTr("1 item selected");
                } else {
                    multiSelectHandler.status = qsTr("None selected");
                }
            }
            
            listItemComponents: [
                ListItemComponent {
                    type: "item"
                    
                    ArticleListComponent {
                        article: ListItemData
                        
                        contextActions: [
                            ActionSet {
                                title: article.title
                                ActionItem {
                                    title: article.unread ? qsTr("Mark as read") : qsTr("Keep unread")
                                    imageSource: article.unread ? "asset:///images/mark_as_read.png" : "asset:///images/keep_unread.png"
                                    
                                    onTriggered: {
                                        article.unread = !article.unread
                                    }
                                }
                                
                                ActionItem {
                                    title: article.published ? qsTr("Unpublish") : qsTr("Publish")
                                    imageSource: article.published ? "asset:///images/unpublish.png" : "asset:///images/publish.png"
                                    
                                    onTriggered: {
                                        article.published = !article.published
                                    }
                                }
                                
                                ActionItem {
                                    title: article.marked ? qsTr("Unstar") : qsTr("Star")
                                    imageSource: article.marked ? "asset:///images/unstar.png" : "asset:///images/star.png"
                                    
                                    onTriggered: {
                                        article.marked = !article.marked
                                    }
                                }
                            }
                        ]
                    }
                },
                ListItemComponent {
                    type: "header"
                    Header {
                        title: Qt.formatDate(ListItemData, Qt.DefaultLocaleLongDate)
                    }
                }
            ]
            onTriggered: {
                if (indexPath.length > 1) {
                    var page = articlePageDefinition.createObject();
                    var article = dataModel.data(indexPath);
                    article.unread = false;
                    page.article = article;
                    nav.push(page);
                }
            }
            attachedObjects: [
                ComponentDefinition {
                    id: articlePageDefinition
                    source: "../ArticlePage/ArticlePage.qml"
                } // Article page
            ]
        } // ListView
    }
}
