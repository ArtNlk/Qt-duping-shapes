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
    state: "DEAD"

    signal click(int numSides)
    signal death(int index)

    states: [
        State {
            name: "ALIVE"
            PropertyChanges { target: shape; opacity: 1}
        },
        State {
            name: "DEAD"
            PropertyChanges { target: shape; opacity: 0}
        },
        State {
            name: "CLICKED"
            PropertyChanges { target: shape; opacity: 0}
        }
    ]

    transitions: [
        Transition {
            from: "ALIVE"
            to: "DEAD"
            NumberAnimation {properties: "opacity"; easing.type: Easing.InOutCubic; duration: 1000}
            onRunningChanged: {
                        if ((state == "DEAD") && (!running))
                            shape.death(index);
                    }
        },
        Transition {
            from: "DEAD"
            to: "ALIVE"
            NumberAnimation {properties: "opacity"; easing.type: Easing.InOutCubic; duration: 250}
        },
        Transition {
            from: "ALIVE"
            to: "CLICKED"
            NumberAnimation {properties: "opacity"; easing.type: Easing.InOutCubic; duration: 250}
            onRunningChanged: {
                        if ((state == "CLICKED") && (running))
                            shape.click(model.vertexCount);
                    }
        }
        ]

    Timer {
            interval: model.lifetime; running: true; repeat: false
            onTriggered: parent.state = "DEAD"
        }

    ListModel {
            id: positions
    }

    ShapePath {
        id: shapePath
        strokeWidth: 1
        strokeColor: "black"
        strokeStyle: ShapePath.SolidLine
        startX: 0; startY: 0
        property color startColor: Qt.hsva(randF(0,1),randF(0.7,1),randF(0.7,1))
        property color endColor: Qt.hsva(startColor.hsvHue,startColor.hsvSaturation,startColor.hsvValue-0.2)
        SequentialAnimation on fillColor {
                    loops: Animation.Infinite
                    ColorAnimation { from: shapePath.startColor; to: shapePath.endColor; duration: 1000 }
                    ColorAnimation { from: shapePath.endColor; to: shapePath.startColor; duration: 1000 }
                }
    }

    MouseArea{
        anchors.fill: parent
        onClicked:(event) =>
                  {
                      if(shape.contains(Qt.point(event.x,event.y)))
                      {
                        shape.state = "CLICKED"
                        enabled = false;
                      }
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

    function randF(min, max) {
            return Math.random() * (max - min) + min;
        }

    function randInt(min, max) {
            min = Math.ceil(min);
            max = Math.floor(max);
            return Math.floor(randF(max,min));
        }

    Component.onCompleted: {
        var vertexCount = model.vertexCount
        var rotation = randF(0,2)*Math.PI
        for(let i = 0; i <= vertexCount; i++)
        {
            positions.append({"x":Math.sin(((2*Math.PI*i)+rotation)/vertexCount)*shape.width/2 + shape.width/2,
                                 "y":Math.cos(((2*Math.PI*i)+rotation)/vertexCount)*shape.height/2 + shape.height/2})
            shapePath.startX = positions.get(0).x
            shapePath.startY = positions.get(0).y
        }
        shape.x = randInt(0,mainWindow.width-shape.width)
        shape.y = randInt(0,mainWindow.height-shape.height)
        state = "ALIVE"
    }
}
