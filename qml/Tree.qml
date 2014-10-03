import QtQuick 2.2
import QtQuick.Controls 1.2

Rectangle{//Представление дерева серверов/сервисов(Рекурсивная)
        id: view

        property var model
        property int rowHeight: 19
        property int columnIndent: 22
        property var currentNode
        property var currentItem

        property Component delegate://Делегат(Элемент дерева)
            Label {
            id: label
            text: model.text ? model.text : 0
            color: currentNode === model ? "white" : (!!model.color ? model.color : "black")
        }

        implicitWidth: 250
        implicitHeight: 300

        signal itemClicked( var item );
        signal itemDoubleClicked( var item );
        signal itemRightClicked( int sid, int x, int y );


        Flickable {
            id:flickable
            anchors.top: parent.top;
            anchors.left: parent.left;
            anchors.right: scrollBarV.left;
            anchors.bottom: scrollBarH.top;
            contentHeight: content.item.height;
            contentWidth: content.width;
        Loader {
            id: content

            onLoaded: item.isRoot = true
            sourceComponent: treeBranch
            property var elements: model

            Component {//Ветвь дерева
                id: treeBranch
                Item {//Корневой элемент ВЕТВИ
                    id: root
                    property bool isRoot: false
                    implicitHeight: column.implicitHeight
                    implicitWidth: column.implicitWidth
                    Column {
                        id: column
                        x: 2
                        Item { height: isRoot ? 0 : rowHeight; width: 1}

                        Repeater {//Список элементов ветви дерева
                            model: elements
                            Item {//Элемент ветви дерева
                                id: filler
                                width: loader.expanded ? (Math.max(loader.width + columnIndent, row.width + columnIndent)) : (row.width + columnIndent)
                                //                                Math.max(loader.width + columnIndent, row.width + columnIndent)
                                height: Math.max(row.height, loader.height)
                                property var _model: model

                                Rectangle {//Строка выделения элемента
                                    id: rowfill
                                    x: /*view.mapToItem(rowfill, 0, 0).x*/0
                                    width: filler.width
                                    height: rowHeight
                                    visible: currentNode === model
                                    color: "#73b1f7"
                                }
                                MouseArea {
                                    anchors.fill: rowfill
                                    acceptedButtons: Qt.LeftButton | Qt.RightButton
//===============================================================
////Обработка сигналов клика по элементам дерева(низкий уровень):
                                    onClicked: {
                                        if(mouse.button == Qt.LeftButton){
                                            currentNode = model
                                            currentItem = loader
                                            forceActiveFocus()

                                            itemClicked(model);
                                        }
                                        if(mouse.button == Qt.RightButton){
                                            {
                                                var x = mapToItem(inField, mouse.x, mouse.y).x+21;
                                                var y = mapToItem(inField, mouse.x, mouse.y).y+13;
                                                itemRightClicked(model.sid, x, y)
                                            }
                                        }
                                    }
                                    onDoubleClicked:{
                                        if(mouse.button == Qt.LeftButton){
                                            currentNode = model
                                            currentItem = loader
                                            forceActiveFocus()

                                            itemDoubleClicked(model);
                                        }
                                    }
                                    onPressed: {
                                        if(mouse.button == Qt.RightButton){
                                            var x = mapToItem(inField, mouse.x, mouse.y).x+21;
                                            var y = mapToItem(inField, mouse.x, mouse.y).y+13;
                                            itemRightClicked(model.sid, x, y)
                                        }
                                    }
//===============================================================
                                }

                                Row {//Строка элемента дерева
                                    id: row
                                    Item {
                                        width: rowHeight
                                        height: rowHeight
                                        opacity: !!model.elements ? 1 : 0
                                        Image {//Значок треугольника
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
                                            onClicked:{
                                                loader.expanded = !loader.expanded
                                                admin.saveBranchState(model.sid, loader.expanded);
                                            }
                                        }
                                    }
                                    Loader {//Создание делегата
                                        property var model: _model
                                        sourceComponent: delegate
                                        anchors.verticalCenter: parent.verticalCenter

                                    }
                                }
                                Loader {//Создание следующей веви дерева(если есть, если нет то undefined)
                                    id: loader
                                    x: columnIndent
                                    height: expanded ? implicitHeight : 0
                                    property var node: model
                                    property bool expanded: admin.getBranchState(model.sid);
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

    ScrollBar {//Верт.Скроллбар
      id: scrollBarV
      anchors.right: parent.right; y: flickable.y
      width: 8; height: flickable.height-8
      orientation: true;
      flickableArea: flickable

    }
    ScrollBar {//Гориз.Скроллбар
      id: scrollBarH
      anchors.bottom: parent.bottom; x: flickable.x
      width: flickable.width-8; height: 8
      orientation: false;
      flickableArea: flickable
    }
}
