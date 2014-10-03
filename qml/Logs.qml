import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Rectangle{
    id: tabsField;
    color: "white";
    Row{
        id: rowL
        anchors.left: parent.left;
        anchors.bottom: parent.bottom;
        Btn{
            id: localLogs;
            width: 100;
            height: 19;
            txt: qsTr("Local log")
            border.width: {
                if((logTabs.currentIndex == 0)&&(tabsField.state == "open"))
                    2
                else
                    0
            }
            border.color: "gray"
            MouseArea{
                anchors.fill: parent;
                onClicked: {
                    logTabs.currentIndex = 0;
                    tabsField.state = "open";
                    clearLogs.visible = true;
                }
            }
        }
        Btn{
            id: serverLogs;
            width: 100;
            height: 19;
            txt: qsTr("Server log")
            border.width: {
                if((logTabs.currentIndex == 1)&&(tabsField.state == "open"))
                    2
                else
                    0
            }
            border.color: "gray"
            MouseArea{
                anchors.fill: parent;
                onClicked: {
                    logTabs.currentIndex = 1;
                    tabsField.state = "open";
                    clearLogs.visible = true;
                }
            }
        }

    }
    Row{
            id: rowR
            anchors.right: parent.right;
            anchors.bottom: parent.bottom;
            Btn{
                id: settings;
                width: 80;
                height: 19;
                txt: qsTr("Settings");
    //            visible: (logTabs.currentIndex === 0)||(logTabs.currentIndex === 1)
                MouseArea{
                    anchors.fill: parent;
                    onClicked: {
                        logTabs.currentIndex = 2;
                        tabsField.state = "open";
                        clearLogs.visible = false;

                    }
                }
            }
            Btn{
                id: clearLogs;
                width: 50;
                height: 19;
                txt: qsTr("Clear");
    //            visible: (logTabs.currentIndex === 0)||(logTabs.currentIndex === 1)
                MouseArea{
                    anchors.fill: parent;
                    onClicked: {
                            logTabs.getTab(logTabs.currentIndex).txt = "";
                    }
                }

            }
            Btn{
                id: hideTab;
                width: 50;
                height: 19;

                txt: "Hide"
                MouseArea{
                    anchors.fill: parent;
                    onClicked: (tabsField.state == "open") ? (tabsField.state = "hide") : (tabsField.state = "open");
                }


            }

        }

    function addStrToLLog(str)
    {
        var text = logTabs.getTab(0).txt+"\n"+str;
        logTabs.getTab(0).txt = text;
    }
    function addStrToSLog(str)
    {
        var text = logTabs.getTab(0).txt+"\n"+str;
        logTabs.getTab(0).txt = text;
    }

    TabView{
        id: logTabs;
        anchors.top:parent.top
        anchors.bottom: rowR.top;
        anchors.left: parent.left
        anchors.right: parent.right
        tabsVisible: false
        Tab {
            title: qsTr("Local log")
            property string txt:"Local Logs..."
            TextArea{
                id: locLog
//                anchors.fill: parent;
                readOnly: true;
                text: txt
            }
        }
        Tab{

            title: qsTr("Server log")
            property string txt:"Server Logs...";
            TextArea{
                id: servLog
//                anchors.fill: parent;
                readOnly: true;
                text: txt
            }
        }

        Tab {
            title: qsTr("Settings")
            Settings{
                anchors.fill: parent;/*
                border.width: 1;
                border.color: "gray"*/
            }
        }

    }

    state:  "open"
    states:[
        State {
            name: "open"
            PropertyChanges {
                target: hideTab;
                txt: "Hide"
            }
            PropertyChanges {
                target: tabsField;
                Layout.maximumHeight: 500;
                Layout.minimumHeight: 150;
            }
        },
        State {
            name: "hide"
            PropertyChanges {
                target: hideTab;
                txt: "Open"
            }
            PropertyChanges {
                target: clearLogs;
                visible: false;
            }
            PropertyChanges {
                target: logTabs;
                visible: false;
            }
            PropertyChanges {
                target: tabsField;
                height: 20;
                Layout.maximumHeight: 20;
            }
        }
    ]

}


