import QtQuick 2.0


Flow{
    anchors.fill: parent;
    anchors.margins: 10
    spacing: 10
    property var model;
    Text{
        text: qsTr("Name: "+model.text);
    }
    Text{
        text: qsTr("ID: "+model.sid);
    }



}
