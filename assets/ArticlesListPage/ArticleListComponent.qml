import bb.cascades 1.0

StandardListItem {
    property variant updated
    
    id: root
    status: Qt.formatTime(updated, "hh:mm")
}
