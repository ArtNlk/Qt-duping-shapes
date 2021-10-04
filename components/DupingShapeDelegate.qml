import QtQml 2.3
import QtQuick 2.0
import QtQuick.Shapes 1.12
import DupingShapes 1.0

Shape {
    id: shape
    height: 100
    width: 100
    x: 0
    y: 0
    containsMode: Shape.FillContains
    signal click(int index)
    ListModel {
            id: positions
    }

    function randInt(min, max) {
            min = Math.ceil(min);
            max = Math.floor(max);
            return Math.floor(Math.random() * (max - min + 1)) + min;
        }

    ShapePath {
        id: shapePath
        strokeWidth: 1
        strokeColor: "black"
        strokeStyle: ShapePath.SolidLine
        startX: 0; startY: 0
    }

    MouseArea{
        anchors.fill: parent
        onClicked:(event) =>
                  {
                    click(index)
                  }
    }

    Instantiator {
            model: positions
            onObjectAdded:(index, object) => {
                shapePath.pathElements.push(object)
            }
            PathLine {
                x: model.x
                y: model.y
            }
        }
    //Math.sin((2*Math.PI*i)/vertexCount)
    Component.onCompleted: {
        var vertexCount = model.vertexCount
        for(let i = 0; i <= vertexCount; i++)
        {
            positions.append({"x":Math.sin((2*Math.PI*i)/vertexCount)*shape.width/2 + shape.width/2,
                                 "y":Math.cos((2*Math.PI*i)/vertexCount)*shape.height/2 + shape.height/2})
            shapePath.startX = positions.get(0).x
            shapePath.startY = positions.get(0).y
        }
        shape.x = randInt(0,mainWindow.width-shape.width)
        shape.y = randInt(0,mainWindow.height-shape.height)
    }
}
