import QtQuick 2.2
import QtQuick.Controls 1.2

ApplicationWindow {
    visible: true
    width: 800
    height: 540
    title: qsTr("Admin Tools")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }
    SplitView{
        anchors.fill: parent
        orientation: Qt.Vertical;
        SplitView{
            orientation: Qt.Horizontal;

            AddServer{
                id: serverAdd;
                width: 200;
                color: "white";
            }
            Rectangle{
                id: mainWindow;
                width: 600;

                color: "green"


            }
        }
        Column{
//            Button{
//                id: hideTab;
//                width: parent.width;
//                height: 20;
//                property bool tabState: true
//                text: tabState ? "▼" : "▲"
//                onClicked: {
//                    tabState = !tabState;
//                }

//            }
            Logs{
                id: logs;
                width: parent.width;
//                visible: hideTab.tabState;
            }
        }


    }



}
