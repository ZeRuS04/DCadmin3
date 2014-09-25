import QtQuick 2.2


Rectangle { // background
    id: container
    color: "white";

    property bool orientation: true; // true=Vertical, false=Horizontal
    property var flickableArea

    visible:{
        if(orientation)
            flickableArea.contentHeight < flickableArea.height ? false : true;
        else
            flickableArea.contentWidth < flickableArea.width ? false : true;
    }


    Rectangle {
        id: indicator// viewport indicator
        y: flickableArea.visibleArea.yPosition * container.height
        x: flickableArea.visibleArea.xPosition * container.width
        width: {
            if(orientation)
                parent.width;
            else
                flickableArea.visibleArea.widthRatio * container.width;
        }
        height: {
            if(orientation)
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
            drag.maximumX: container.width - indicator.width;
            drag.maximumY: container.height - indicator.height;
        }
        onXChanged: flickableArea.x = x;!!!!!!!!!!!!!!!!
        onYChanged: flickableArea.y = y;!!!!!!!!!!!

    }
}
