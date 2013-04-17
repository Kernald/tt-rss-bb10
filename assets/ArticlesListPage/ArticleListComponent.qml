import bb.cascades 1.0

StandardListItem {
    property variant article
    
    title: article.title
    description: article.excerpt
    status: Qt.formatTime(article.updated, "hh:mm")
}
