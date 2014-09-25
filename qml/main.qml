import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    visible: true
    width: 800
    height: 540
    title: qsTr("Admin Tools")

//    menuBar: MenuBar {
//        Menu {
//            title: qsTr("File")
//            MenuItem {
//                text: qsTr("&Open")
//                onTriggered: console.log("Open action triggered");
//            }
//            MenuItem {
//                text: qsTr("Exit")
//                onTriggered: Qt.quit();
//            }
//        }
//    }
    Rectangle{
        id: outField;
        anchors.fill: parent
        color: "white"


        Rectangle{
            id: inField;
            width: parent.width/20*19;
            height: parent.height/20*19
            anchors.centerIn: parent;


            SplitView{
                anchors.fill: parent
                orientation: Qt.Vertical;
                SplitView{
                    id: horizSplit
                    orientation: Qt.Horizontal;

                    Column{
                        spacing: 5;
                        anchors.top: parent.top;
                        anchors.bottom: parent.bottom;
                        Layout.minimumWidth: 100;
                        Layout.fillWidth: true;
                        Btn{
                            id: addServButton;
                            width: parent.width-outField.width/40;
                            height: 30;
                            txt: qsTr("Add server");
                            visible: !serverAdd.visible;
                            MouseArea{
                                anchors.fill: parent;

                                onClicked: {
                                    serverAdd.visible = true;
                                }
                            }
                        }

                        AddServer{
                            id: serverAdd;
                            width: 200;
                            color: "white";
                            visible: false;
                            anchors.horizontalCenter: parent.horizontalCenter;
                        }

                        Tree{
                            id: tree
                            height: {
                                if(serverAdd.visible)
                                    horizSplit.height - serverAdd.height;
                                else
                                    horizSplit.height - addServButton.height-10;
                            }
                            width: parent.width;
                            model: serverAdd.model;

                        }

                    }
                    Rectangle{
                        id: mainWindow;
                        width: 600;

                        color: "white"


                    }
                }
        //        Column{
        ////            Button{
        ////                id: hideTab;
        ////                width: parent.width;
        ////                height: 20;
        ////                property bool tabState: true
        ////                text: tabState ? "▼" : "▲"
        ////                onClicked: {
        ////                    tabState = !tabState;
        ////                }

        ////            }
        //            Logs{
        //                id: logs;
        //                width: parent.width;
        ////                visible: hideTab.tabState;
        //            }
        //        }


            }
        }
    }




}
