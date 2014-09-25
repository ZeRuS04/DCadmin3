import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

Rectangle{
    id: addServ;
    height: column.height;
    color: "white"
    property var model;
    function changeModel()
    {
        var str;
        str = admin.getTree();
        model = Qt.createQmlObject(str, addServ);
    }
    Column{
        id: column;
        spacing: 3;
        anchors.verticalCenter: parent.verticalCenter

        TextField{
            id: name;
            width: parent.width;
            placeholderText: qsTr("Name");
        }

        Row{
            spacing: 5

            TextField{
                id: ip;
                width: addServ.width-port.width - parent.spacing;
                horizontalAlignment: TextInput.AlignHCenter;
                verticalAlignment: TextInput.AlignVCenter;

                validator: RegExpValidator{regExp: /^(([01]?[0-9]?[0-9]|2([0-4][0-9]|5[0-5]))\.){3}([01]?[0-9]?[0-9]|2([0-4][0-9]|5[0-5]))$/}
                inputMask: "000.000.000.000;0";
                placeholderText: "IP";

            }
            TextField{
                id: port
                width: 50
                placeholderText: qsTr("Port");

                horizontalAlignment: TextInput.AlignHCenter;
                verticalAlignment: TextInput.AlignVCenter;
                validator: RegExpValidator { regExp: /[0-9]+/; }
                maximumLength: 5;
            }

        }
        Row{
            Text{
                width: 160;
                height: 30;
                verticalAlignment: Text.AlignVCenter;
                text: qsTr("Choose color:");
                color: "gray"
            }

            Rectangle{
                id: color
                width: 30;
                height: 30;
                color: curColor;
                border.width: 2;
                property color curColor: "black";

                MouseArea{
                    anchors.fill: parent;
                    onClicked: selectColor.open();

                }
                ColorDialog{
                    id: selectColor;
                    title: qsTr("Please choose a color");
                    onAccepted: {
                        color.curColor = selectColor.color;
                        selectColor.close();
                    }
                    onRejected: {
                        selectColor.close();
                    }
                }
            }
        }


        Row{
            Btn{
                id: addButton
                width: addServ.width/2
                height: 20
                txt: qsTr("Add Server");

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        //Проверка на корректность должна быть здесь.
                        admin.addServer(name.text, ip.text, port.text, color.curColor);
                        addServ.changeModel();
                        addServ.visible = false;
                    }
                }
            }
            Btn{
                id: cancelButton
                width: addServ.width/2
                height: 20
                txt: qsTr("Cancel");

                MouseArea{
                    anchors.fill: parent
                    onClicked: {
                        addServ.visible = false;
                    }
                }
            }

        }
    }


    Component.onCompleted: changeModel();

}

