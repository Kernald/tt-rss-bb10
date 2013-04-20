import bb.cascades 1.0

StandardListItem {
    property variant feed
    
    title: feed.title
    status: feed.unreadArticlesCount
    image: feed.icon
}
