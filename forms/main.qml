import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15
import DupingShapes 1.0
import "../components"

Window {
    id: mainWindow
    width: 640
    height: 480
    visible: true
    title: qsTr("Duplicating shapes")

    DupingShapesModel{
        id: dataModel
        Component.onCompleted:
        {
            dataModel.addShape(3,300)
            dataModel.addShape(5,500)
            dataModel.addShape(7,700)
        }
    }

    Repeater{
        model: dataModel
        delegate: DupingShapeDelegate{
        onClick:(index) => dataModel.clicked(index)
        }
    }
}
