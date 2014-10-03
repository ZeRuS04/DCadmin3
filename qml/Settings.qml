import QtQuick 2.2
import QtQuick.Controls 1.2

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
