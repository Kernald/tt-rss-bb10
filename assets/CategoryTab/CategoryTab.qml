import bb.cascades 1.0

Tab {
    property variant category
    title: category ? category.title : ""
    //newContentAvailable: category ? category.hasUnreadArticles : false
    unreadContentCount: category ? category.unreadArticlesCount : 0
    imageSource: "asset:///images/category.png"
}
