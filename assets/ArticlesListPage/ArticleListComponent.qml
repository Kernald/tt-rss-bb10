import bb.cascades 1.0

Container {
    property variant article
    
    id: root
    layout: DockLayout {}
    horizontalAlignment: HorizontalAlignment.Fill
    
    ListItem.onSelectionChanged: {
        if (selected)
        	setSelected.play();
        else 
        	setUnselected.play();
    }
    
    Container {
        id: highlight
        layout: DockLayout {}
        horizontalAlignment: HorizontalAlignment.Fill
        verticalAlignment: VerticalAlignment.Fill
        opacity: 0.0
        background: Color.create("#00A7DE")
        topPadding: 4
        bottomPadding: 4
        leftPadding: 4
        rightPadding: 4
        
        animations: [
            FadeTransition {
                id: setSelected
                fromOpacity: 0.0
                toOpacity: 1.0
                duration: 200
            },
            FadeTransition {
                id: setUnselected
                fromOpacity: 1.0
                toOpacity: 0.0
                duration: 200
            }
        ]

        Container {
            id: innerHighlight
            horizontalAlignment: HorizontalAlignment.Fill
            verticalAlignment: VerticalAlignment.Fill
            //opacity: 0.0
            background: Color.create("#99DCF2")
        }
    }

    Container {
        id: main
	    layout: StackLayout {
	        orientation: LayoutOrientation.LeftToRight
	    }
	    horizontalAlignment: HorizontalAlignment.Fill
	    preferredHeight: 120
	
	    ImageView {
	        id: image
	        preferredHeight: 120
	        preferredWidth: 120
	        verticalAlignment: VerticalAlignment.Center
	        image: article.icon

            layoutProperties: StackLayoutProperties {
                spaceQuota: -1
            }

        }
	    
	    Container {
	        layout: StackLayout {}
            horizontalAlignment: HorizontalAlignment.Fill

            layoutProperties: StackLayoutProperties {
                spaceQuota: 1
            }

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
	                        fontWeight: article.unread ? FontWeight.W400 : FontWeight.W100
	                    }
	
	                    text: article.title
                        textFormat: TextFormat.Html

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
                    textFormat: TextFormat.Html
                }
	        }
        }
    }

    Divider {
        verticalAlignment: VerticalAlignment.Bottom
        horizontalAlignment: HorizontalAlignment.Center
    }
}
