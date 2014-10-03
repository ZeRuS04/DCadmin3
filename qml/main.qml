import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

ApplicationWindow {
    id: aplWindow;
    visible: true
    width: 800
    height: 540
    minimumWidth: 400;
    minimumHeight: 300;
    title: qsTr("Admin Tools")

    Rectangle{//Внешняя подложка окна
        id: outField;
        anchors.fill: parent
        color: "white"


        Rectangle{//Внутренняя "Подложка" окна
            id: inField;
            width: parent.width/20*19;
            height: parent.height/20*19
            anchors.centerIn: parent;

            SplitView{//Вертикальный сплит (Гориз.Сплит/Логи)
                anchors.fill: parent
                orientation: Qt.Vertical;

                SplitView{//Горизонтальный сплит(Дерево/Главное окно)
                    id: horizSplit
                    orientation: Qt.Horizontal;
                    Layout.fillHeight : true;
                    Layout.fillWidth : true;
                    Rectangle{//"Подкладка" дерева
                        anchors.top: parent.top;
                        anchors.bottom: parent.bottom;
                        width: parent.width;
                        Layout.minimumWidth: 220;
                        Layout.fillWidth: true;

                        Tree{//Дерево серверов и сервисов
                            id: tree
                            anchors.top:{
                                if(serverAdd.visible)
                                    serverAdd.bottom;
                                else
                                    addServButton.bottom;
                            }
                            anchors.bottom: parent.bottom;
                            width: parent.width;
                            model: serverAdd.model;

//===============================================================
//Обработка сигналов клика по элементам дерева(высокий уровень):
                            onItemClicked: {
                                logs.addStrToLLog(admin.itemClicked(item.name));
                            }
                            onItemDoubleClicked: {
                                logs.addStrToLLog(admin.itemDoubleClicked(item.name));
                                mainLoader.setSource("ServerInfo.qml",{"model": item})
                            }
//                            onItemRightClicked: {
//                                contextMenu.isOpen = true;
//                                contextMenu.x = x;
//                                contextMenu.y = y;
//                                contextMenu.name = name;
//                            }

//===============================================================
                        }
                        Btn{//Кнопка "Добавить сервер"
                            id: addServButton;
                            anchors.top: parent.top;
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

                        AddServer{//Поле добавления сервера в список
                            id: serverAdd;
                            width: 200;
                            color: "white";
                            visible: false;
                            anchors.top: parent.top;
                            anchors.horizontalCenter: parent.horizontalCenter;
                        }

                    }
                    Rectangle{//Главное окно программы
                        id: mainWindow;
                        width: 2000;
                        height: inField.height-20;
                        color: "white"
                        Loader{
                            id: mainLoader;
                        }
                    }
                }
                Logs{//Вкладки логов(и настроек)
                    id: logs;
                    width: parent.width;
                    height: 200;
                    Layout.fillWidth : true;
                    Layout.fillHeight : true;
                    Layout.minimumHeight: 20;
//                    Layout.maximumHeight: inField.height-20;

                }


            }
        }
    }
    ContextMenu{//Контекстное  меню для дерева
        id: contextMenu
        property string name;

        onMenuSelected: {
            switch (index){
            case 1:
                logs.addStrToLLog(admin.itemClicked(name));
                break
            case 2:
                admin.removeServer(name);
                tree.model = admin.getTree();
                break
            }


        }

    }
}
