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
	    preferredHeight: 120
	
	    /*ImageView {
	        id: image
	        preferredHeight: 120
	        preferredWidth: 120
	        verticalAlignment: VerticalAlignment.Center
	    }*/
	    
	    Container {
	        layout: StackLayout {}
            horizontalAlignment: HorizontalAlignment.Fill
            leftPadding: 20
            rightPadding: 10

            Container {
                layout: StackLayout {
                    orientation: LayoutOrientation.LeftToRight
                }
                layoutProperties: StackLayoutProperties {
                    spaceQuota: -1
                }

				Container {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: 1
                    }
                    verticalAlignment: VerticalAlignment.Fill
                    
                    Label {
	                    id: title
	                    textStyle {
	                        fontSize: FontSize.Large
	                        fontWeight: FontWeight.W400
	                    }
	
	                    text: article.title
	
	                }
	            }

				Container {
                    layoutProperties: StackLayoutProperties {
                        spaceQuota: -1
                    }
                    verticalAlignment: VerticalAlignment.Bottom
                    bottomPadding: 5
                    
                    Label {
	                    id: updated
	                    textStyle {
	                        color: Color.create("#ff585858")
	                        fontWeight: FontWeight.W100
	                        fontSize: FontSize.Small
	                    }

                        text: Qt.formatTime(article.updated, "hh:mm")
	                }
	            }
            }

			Container {
                layoutProperties: StackLayoutProperties {
                    spaceQuota: 1
                }
                
                Label {
	                id: excerpt
	                textStyle {
	                	color: Color.create("#ff585858")
	                    fontWeight: FontWeight.W400
	                    fontSize: FontSize.Small
	                }
	                verticalAlignment: VerticalAlignment.Top
	
	                text: article.excerpt
	            }
	        }
        }
    }

    Divider {
        verticalAlignment: VerticalAlignment.Bottom
        horizontalAlignment: HorizontalAlignment.Center
    }
}
