import bb.cascades 1.0

StandardListItem {
    property variant updated
    property alias excerpt: root.description
    
    id: root
    status: Qt.formatTime(updated, "hh:mm")
}
