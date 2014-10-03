import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2

Rectangle{
    id: addServ;
    height: column.height;
    color: "white"
    property var model;
    function changeModel(){
        var str;
        str = admin.getTree();
        model = Qt.createQmlObject(str, addServ);
    }

    function validateHostParam(name, ip, port){
        // Проверяем параметры хоста введенные пользователем.
        // Если проблема в имени возвращаем 1
        // Если проблема в ip адресе взвращаем 2
        // Если проблема в порте возвращаем 4
        // Проблема во всем 7, проблем нет - 0
        // Порт и адрес 6, имя и порт 5, имя и адрес - 3
        var retErr = 0;
        if(port >= 65535)
            retErr |= 4;
        retErr |= admin.validateHostParam(name, ip, port);
        return retErr;
    }

    Column{
        id: column;
        spacing: 3;
        anchors.verticalCenter: parent.verticalCenter
        Label{
            id: errLabel
            width: name.width;
            height: 30;
            text: "";
            color: "darkred"
            visible: false
        }

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
//                inputMask: "000.000.000.000;0";
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
                        errLabel.visible = true;
                        var errors = addServ.validateHostParam(name.text, ip.text, port.text);
                        if(!errors)
                        {
                            errLabel.visible = false;
                            admin.addServer(name.text, ip.text, port.text, color.curColor);
                            addServ.changeModel();
                            addServ.visible = false;
                        }
                        else
                        {
                            errLabel.text = qsTr("Check these fields: ")
                            errLabel.visible = true;
                            if(errors & 1)
                                errLabel.text += "Name, "
                            if(errors & 2)
                                errLabel.text += "IP, "
                            if(errors & 4)
                                errLabel.text += "Port"
                        }
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
                        errLabel.visible = false;
                        addServ.visible = false;
                    }
                }
            }
        }
    }


    Component.onCompleted: changeModel();

}

