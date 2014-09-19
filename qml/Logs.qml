import QtQuick 2.2
import QtQuick.Controls 1.2

Rectangle{
    id: tabsField;
    color: "lightblue";

    Row{
        anchors.right: parent.right;
        anchors.top: parent.top;
        Button{
            id: clearLogs;
            width: 100;
            height: 19;
            text: "Clear"
            visible: (logTabs.currentIndex === 0)||(logTabs.currentIndex === 1)
            onClicked: {
                //clearLog()
            }
        }
        Button{
            id: hideTab;
            width: 19;
            height: width;

            text: "-"

        }

    }



    TabView{
        id: logTabs;
        anchors.fill: parent
        frameVisible: false
        Tab{

            title: qsTr("Server log")
            TextArea{
                id: servLog
                anchors.fill: parent;
                readOnly: true;
            }
        }
        Tab {

            title: qsTr("Local log")
            TextArea{
                id: locLog
                anchors.fill: parent;
                readOnly: true;
            }
        }
        Tab {
            id: settings
            title: qsTr("Settings")
            Rectangle{
                anchors.fill: parent;
                Flow{
                    anchors.fill: parent;
                    anchors.margins: 10
                    spacing: 10
                    Row{
                        Text{
                            text: qsTr("Language: ")
                        }
                        ComboBox{
                            id: lang
                            width: 200;
                            model: [];

                        }
                    }
                    Row{
                        Text{
                            text: qsTr("Code Table: ")
                        }
                        ComboBox{
                            id: codeTable
                            width: 200;
                            model: [];
                        }
                    }
                    Row{
                        Text{
                            text: qsTr("Debug level: ")
                        }
                        SpinBox{
                            id: debugLevel
                            width: 50;
                            minimumValue: 0;
                            maximumValue: 12;
                            stepSize: 1;
                            value: 7;
                        }
                    }
                    Row{
                        Text{
                            text: qsTr("Ask while delete ")
                        }
                        CheckBox{
                            id: deleteAsk
                            checked:  true;
                        }
                    }
                    Row{
                        Text{
                            text: qsTr("Info as error add server ")
                        }
                        CheckBox{
                            id: infoErrServ
                            checked:  true;
                        }
                    }
                }
            }
        }
    }


}


