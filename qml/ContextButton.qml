import QtQuick 2.0

Item {
    id: contextButtonItem
    property string button_text;
    property bool clicked;
    property int index;
    property string target;
    property bool hovered: false;
    property bool enable: true;
    signal buttonClicked;
//    signal cursorEntered();
    signal cursorExited();
    height: 14
    width: parent.width - 5

    function viewButtonHovered() {

        viewButton.state = "hovered";
    }

    function viewButtonExited() {
//        cursorExited();
        if(clicked == false) {
            viewButton.state = "";
        } else {
            viewButton.state = "clicked"
        }
    }
    Rectangle {
        id: viewButton;
        height: vButton.height + 4
        width: parent.width

        Text {
            id: vButton
            text: qsTr(button_text)
            width: parent.width
            anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 10 }
            font { pixelSize: 12 }
        }
        MouseArea {
            hoverEnabled: enable
            anchors.fill: parent
            enabled: enable
            onClicked: buttonClicked();
            onEntered: viewButtonHovered();
            onExited: viewButtonExited();
        }
        states: [
            State {
                name: "clicked";
                PropertyChanges { target: vButton; color: "#286E1E"; }
                PropertyChanges { target: contextButtonItem; hovered: false; }
            },
            State {
                name: "hovered";
                PropertyChanges { target: vButton; color: "#BEA1C6"; }
                PropertyChanges { target: contextButtonItem; hovered: true; }
            },
            State {
                name: "normal";
                PropertyChanges { target: vButton; color: "#232323"; }
                PropertyChanges { target: contextButtonItem; hovered: false; }
            }
        ]
    }
}
