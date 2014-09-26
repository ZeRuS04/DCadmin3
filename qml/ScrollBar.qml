import QtQuick 2.2


Rectangle { // background
    id: container
    color: "white";

    property bool orientation: true; // true=Vertical, false=Horizontal
    property var flickableArea
    property double cof: {
        if(container.orientation)
            (height - indicator.height)/(flickableArea.contentHeight - flickableArea.height);
        else
            (width - indicator.width)/(flickableArea.contentWidth - flickableArea.width);
    }

    visible:{
        if(orientation)
            flickableArea.contentHeight < flickableArea.height ? false : true;
        else
            flickableArea.contentWidth < flickableArea.width ? false : true;
    }


    Rectangle {
        id: indicator// viewport indicator
        y: container.orientation ? flickableArea.visibleArea.yPosition * container.height : 0
        x: container.orientation ? 0 : flickableArea.visibleArea.xPosition * container.width
        width: {
            if(container.orientation)
                parent.width;
            else
                flickableArea.visibleArea.widthRatio * container.width;
        }
        height: {
            if(container.orientation)
                flickableArea.visibleArea.heightRatio * container.height;
            else
                parent.height;
        }
        color: "black"
        opacity: 0.7
        MouseArea{
            anchors.fill: parent;
            drag.minimumX: 0;
            drag.minimumY: 0;
            drag.target: indicator;
            drag.axis: container.orientation ? Drag.YAxis : Drag.XAxis;
            drag.maximumX: {
                if(!container.orientation)
                    container.width - indicator.width;
                else
                    0;
            }
            drag.maximumY: {
                if(container.orientation)
                    container.height - indicator.height;
                else
                    0;
            }
            onPositionChanged: {
                if(container.orientation)
                    flickableArea.contentY = indicator.y/container.cof;
                else
                    flickableArea.contentX = indicator.x/container.cof;
            }
        }

    }
}
