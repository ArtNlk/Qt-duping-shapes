import QtQuick 2.0
import QtQuick.Shapes 1.12
import DupingShapes 1.0

Rectangle{
    id: control
    color: "green"
    x: model.vertexCount/5
    y: model.vertexCount/5
    height: 20
    width: 40
    Text{
        text: model.vertexCount
    }

    MouseArea
    {
        anchors.fill: parent
        onClicked:
        {
            console.log("Tick clicked")
            dataModel.tick()
        }
    }
}
