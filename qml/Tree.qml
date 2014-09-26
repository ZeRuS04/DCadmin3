import QtQuick 2.2
import QtQuick.Controls 1.2

Rectangle{
        id: view

        property var model
        property int rowHeight: 19
        property int columnIndent: 22
        property var currentNode
        property var currentItem

        property Component delegate:
            Label {
            id: label
            text: model.text ? model.text : 0
            color: currentNode === model ? "white" : (!!model.color ? model.color : "black")
        }
        function openMainWindow(){

        }


        //    frameVisible: false
        implicitWidth: 250
        implicitHeight: 300

        Flickable {
            id:flickable
//            anchors.fill: parent
            anchors.top: parent.top;
            anchors.left: parent.left;
            anchors.right: scrollBarV.left;
            anchors.bottom: scrollBarH.top;
            contentHeight: content.item.height;
            contentWidth: content.width;
        /*contentItem:*/ Loader {
            id: content

            onLoaded: item.isRoot = true
            sourceComponent: treeBranch
            property var elements: model

            Component {
                id: treeBranch
                Item {
                    id: root
                    property bool isRoot: false
                    implicitHeight: column.implicitHeight
                    implicitWidth: column.implicitWidth
                    Column {
                        id: column
                        x: 2
                        Item { height: isRoot ? 0 : rowHeight; width: 1}
                        Repeater {
                            model: elements
                            Item {
                                id: filler
                                width: loader.expanded ? (Math.max(loader.width + columnIndent, row.width + columnIndent)) : (row.width + columnIndent)
                                //                                Math.max(loader.width + columnIndent, row.width + columnIndent)
                                height: Math.max(row.height, loader.height)
                                property var _model: model
                                Rectangle {
                                    id: rowfill
                                    x: /*view.mapToItem(rowfill, 0, 0).x*/0
                                    width: filler.width
                                    height: rowHeight
                                    visible: currentNode === model
                                    color: "#37f"
                                }
                                MouseArea {
                                    anchors.fill: rowfill
                                    onPressed: {
                                        currentNode = model
                                        currentItem = loader
                                        forceActiveFocus()

                                        //view.openMainWindow();

                                    }
                                }
                                Row {
                                    id: row
                                    Item {
                                        width: rowHeight
                                        height: rowHeight
                                        opacity: !!model.elements ? 1 : 0
                                        Image {
                                            id: expander
                                            source: "../resource/expander.png"
                                            opacity: mouse.containsMouse ? 1 : 0.7
                                            anchors.centerIn: parent
                                            rotation: loader.expanded ? 90 : 0
                                            Behavior on rotation {NumberAnimation { duration: 120}}
                                        }
                                        MouseArea {
                                            id: mouse
                                            anchors.fill: parent
                                            hoverEnabled: true
                                            onClicked: loader.expanded = !loader.expanded
                                        }
                                    }
                                    Loader {
                                        property var model: _model
                                        sourceComponent: delegate
                                        anchors.verticalCenter: parent.verticalCenter

                                    }
                                }
                                Loader {
                                    id: loader
                                    x: columnIndent
                                    height: expanded ? implicitHeight : 0
                                    property var node: model
                                    property bool expanded: true
                                    property var elements: model.elements
                                    property var text: model.text
                                    sourceComponent: (expanded && !!model.elements) ? treeBranch : undefined
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    ScrollBar {
      id: scrollBarV
      anchors.right: parent.right; y: flickable.y
      width: 8; height: flickable.height-8
      orientation: true;
      flickableArea: flickable

    }
    ScrollBar {
      id: scrollBarH
      anchors.bottom: parent.bottom; x: flickable.x
      width: flickable.width-8; height: 8
      orientation: false;
      flickableArea: flickable
    }
}
