import QtQuick 2.0
import QtQuick.Controls 1.2
Rectangle {
    id: contextMenuItem
    signal menuSelected(int index) // index{1: Select All, 2: Remove Selected}
    property bool isOpen: false
    width: 150
    height: menuHolder.height+6
    visible: isOpen
    focus: isOpen
    border { width: 1; color: "#BEC1C6" }

    function updateMenu(){
        if(select.hovered || removeSelected.hovered)
            isOpen = true;
        else
            isOpen = false;
    }

//    MouseArea{
//        anchors.fill: parent
//        hoverEnabled: true;
//        onExited: {
//            parent.isOpen = false;
//        }
//    }

    Column {
        id: menuHolder
        spacing: 1
        width: parent.width
        height: children.height * children.length
        anchors { verticalCenter: parent.verticalCenter; left: parent.left; leftMargin: 3 }

        ContextButton {
            id: select
            button_text: "Select"
            index: 1
            onButtonClicked: menuSelected(index);
            onCursorExited:updateMenu();

        }

        ContextButton {
            id: removeSelected
            button_text: "Remove Selected"
            index: 2
            onButtonClicked: menuSelected(index);
            onCursorExited:updateMenu();
        }
    }

}
