import QtQuick 2.0
import QtQuick.Controls 2.5
import QtQuick.Dialogs 1.2
import QtQuick.Layouts 1.15

import "qrc:/components"

Dialog {
        title: qsTr("Настройки")
        standardButtons: StandardButton.Ok | StandardButton.Cancel
        signal settingsChanged(int quantity, int minSides, int maxSides, int lifespan)

        onAccepted:
        {
            settingsChanged(initialCountSpinbox.value,minSidesSpinbox.value,maxSidesSpinbox.value,lifetimeSpinbox.value)
        }

        GridLayout {
            id: grid
            columns: 2

            Label{
                text: qsTr("Начальное число фигур: ")
            }


            TextSpinbox{
                id: initialCountSpinbox
                from: 1
                to: 1000
            }

            Label{
                text: qsTr("Минимум сторон: ")
            }

            SpinBox{
                id: minSidesSpinbox
                from: 3
                to: 1000
                onValueModified:
                {
                    maxSidesSpinbox.from = minSidesSpinbox.value
                }
                Component.onCompleted: {
                    value = 3
                }
            }

            Label{
                text: qsTr("Максимум сторон: ")
            }

            SpinBox{
                id: maxSidesSpinbox
                from: 3
                to: 1000
                onValueModified:
                {
                    minSidesSpinbox.to = maxSidesSpinbox.value
                }
                Component.onCompleted: {
                    value = 15
                }
            }

            Label{
                text: qsTr("Время жизни (мкс): ")
            }

            TextSpinbox{
                id: lifetimeSpinbox
                from: 1
                to: 100000000
                Component.onCompleted: {
                    value = 2000
                }
            }
        }
    }
