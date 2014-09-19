import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Dialogs 1.2
Rectangle {
    id: serv
    width: 400
    height: 400
    color: "gray"
    function changeModel()
    {
           var str;
           str = admin.getTree();
           tree.model = Qt.createQmlObject(str, serv);
    }
    Column{
       anchors.fill: parent;

       Tree{
           id: tree
           height: parent.height-addServ.height;
           width:parent.width
       }
       Rectangle{
           id: addServ;
           width:parent.width
           height: column.height;
           Column{
               id: column;
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

               Rectangle{
                   id: color
                   width: addServ.width;
                   height: 30;
                   color: curColor;
                   border.width: 2;
                   property color curColor: "black";
                   Text{
                       anchors.fill: parent
                       horizontalAlignment: Text.AlignHCenter;
                       verticalAlignment: Text.AlignVCenter;
                       text: qsTr("Choose color");
                       color: "white"
                   }

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

               Button{
                   id: addButton
                   width: addServ.width
                   text: qsTr("Add Server");
                   onClicked: {
                       //Проверка на корректность должна быть здесь.
                        admin.addServer(name.text, ip.text, port.text, color.curColor);
                        serv.changeModel();
                   }
               }
           }

       }
   }

}
