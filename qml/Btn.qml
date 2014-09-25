import QtQuick 2.2

Rectangle {
    id: btn
    state: "Normal";
    color: Qt.rgba(1,1,1,0.7);
    property string txt: "";
    property int fntSize: 14;
    property color colorTxt: "gray";
    property color normColor: "white";
    property color pressColor: "lightgray";

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

    states: [
        State{
            name: "Normal"
            PropertyChanges {
                target: btn;
                color: normColor;
                colorTxt: colorTxt;
            }
        },
        State{
                name: "Pressed"
                PropertyChanges {
                    target: btn;
                    color: pressColor;
                    colorTxt: colorTxt;
                }
        }

    ]
    MouseArea{
        anchors.fill: parent;
        hoverEnabled: true;

        onEntered: btn.state = "Pressed"
        onExited: btn.state = "Normal"
        onPressed: btn.state = "Pressed"
    }
}

