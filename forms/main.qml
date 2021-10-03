import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Shapes 1.15

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello Worldss")

    ListModel{
        id: dataModel
        property list<PathLine> shape: [
            PathLine { x: 0; y: 0 },
            PathLine { x: 0; y: 10 },
            PathLine { x: 10; y: 10 },
            PathLine { x: 10; y: 0 }
        ]
    }

    Repeater {
        model: dataModel
        delegate: Item {
            height: parent.height
            width: parent.width

            Shape {
                width: 20
                height: 20
                x: model.x
                y: model.y
                ShapePath {
                    strokeWidth: 4
                    strokeColor: "red"
                    fillGradient: LinearGradient {
                        x1: 20; y1: 20
                        x2: 180; y2: 130
                        GradientStop { position: 0; color: "blue" }
                        GradientStop { position: 0.2; color: "green" }
                        GradientStop { position: 0.4; color: "red" }
                        GradientStop { position: 0.6; color: "yellow" }
                        GradientStop { position: 1; color: "cyan" }
                    }
                    strokeStyle: ShapePath.DashLine
                    dashPattern: [ 1, 4 ]
                    startX: 20; startY: 20
                    PathLine { x: 36; y: 36 }
                    PathLine { x: 36; y: 36 }
                    PathLine { x: 36; y: 36 }
                    PathLine { x: 36; y: 36 }
                }
            }
        }
    }
}
