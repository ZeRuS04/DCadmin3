import QtQuick 2.1

Rectangle {
    id: fld
    border.width: 1;
    color: Qt.rgba(1,1,1,0.8);
    property string txt: "";
    property color colorTxt: "black";
    property int fntSize: 14

    Text{
        id: buttonText
        anchors.fill: parent;
        text: parent.txt;
        color: parent.colorTxt;
        horizontalAlignment: Text.AlignHCenter;
        verticalAlignment: Text.AlignVCenter;
        font.pixelSize: parent.fntSize;
        wrapMode: Text.WordWrap;
    }
}
