import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15
import DupingShapes 1.0
import "qrc:/forms/"
import "qrc:/components/"

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Множащиеся фигуры. R - рестарт, S - настройки")

    property SettingsDialog settings: SettingsDialog{
        id: settingsDialog
        onSettingsChanged: (count, sidesMin, sidesMax, lifetime) =>
                           {
                                dataModel.changeSettings(count,sidesMin,sidesMax,lifetime)
                           }
    }

    Shortcut {
            sequence: "R"
            onActivated: dataModel.reset()
        }

    Shortcut {
            sequence: "S"
            onActivated: settings.open()
        }

    DupingShapesModel{
        id: dataModel
        Component.onCompleted:
        {
            dataModel.reset()
        }
    }

    Repeater{
        model: dataModel
        delegate: DupingShapeDelegate{
        onClick:(numSides) => dataModel.spawn(numSides)
        onDeath:(index) => dataModel.deleteAt(index)
        }
    }

    Component.onCompleted: {
        dataModel.reset()
    }
}
