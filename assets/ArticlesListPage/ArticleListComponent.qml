import bb.cascades 1.0

Container {
    property variant article
    
    id: root
    layout: DockLayout {}
    horizontalAlignment: HorizontalAlignment.Fill

    Container {
        id: main
	    layout: StackLayout {
	        orientation: LayoutOrientation.LeftToRight
	    }
	    horizontalAlignment: HorizontalAlignment.Fill
	    preferredHeight: 110
	
	    /*ImageView {
	        id: image
	        preferredHeight: 110
	        preferredWidth: 110
	        verticalAlignment: VerticalAlignment.Center
	    }*/
	    
	    Container {
	        layout: StackLayout {}
            horizontalAlignment: HorizontalAlignment.Fill
            leftPadding: 20
            
            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                
                Label {
                    textStyle {
                        base: SystemDefaults.TextStyles.TitleText
                    }
                    
                    text: article.title
                }
                
                Label {                    
                    text: Qt.formatTime(article.updated, "hh:mm")
                }
            }
            
            Label {
                textStyle {
                    base: SystemDefaults.TextStyles.BodyText
                    color: Color.create("#ff585858")
                }
                verticalAlignment: VerticalAlignment.Top
                
                text: article.excerpt
            }
        }
	}

    Divider {
        verticalAlignment: VerticalAlignment.Bottom
        horizontalAlignment: HorizontalAlignment.Center
    }
}
