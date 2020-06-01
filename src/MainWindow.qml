import QtQuick 2.10
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.11

ApplicationWindow {
    id: window
    visible: true
    width: 640
    height: 480
    title: qsTr("NetBlocker")


        ColumnLayout {
            id: columnLayout
            anchors.fill: parent

            ComboBox {
                id: comboBox
                Layout.leftMargin: 50
                Layout.minimumWidth: 250
                visible: true
                textRole: qsTr("name")
                model: presenter.get_model()

                onActivated: {
                    if (stop_btn.is_stop)
                    {
                        presenter.on_block_ip(comboBox.currentValue)
                    }
                    else if (model.count === 0) // in order to unblock if we closed application when net was blocked
                    {
                        presenter.on_block_ip("");
                    }
                }
            }
            Button {
                id: stop_btn
                Layout.rightMargin: 50
                Layout.alignment: Qt.AlignRight | Qt.AlignVCenter
                highlighted: true

                property bool is_stop: false

                text: qsTr("Whitelist")
                onClicked:
                {
                    presenter.on_block_ip(stop_btn.is_stop ? "" : comboBox.currentValue);
                    stop_btn.is_stop = !stop_btn.is_stop
                    stop_btn.text = stop_btn.is_stop ? qsTr("Undo") : qsTr("Whitelist")
                }
            }
        }
}

