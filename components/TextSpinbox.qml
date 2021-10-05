import QtQuick 2.0
import QtQuick.Controls 2.5

SpinBox{
    id: spinbox

    onValueChanged: {
        textInp.text = spinbox.value
    }

    contentItem: TextInput {
            id: textInp
            z: 2

            font: parent.font
            horizontalAlignment: Qt.AlignHCenter
            verticalAlignment: Qt.AlignVCenter

            validator: parent.validator
            inputMethodHints: Qt.ImhFormattedNumbersOnly

            function clamp(value,min,max)
            {
                if(value > max)
                {
                    return max
                }
                if(value < min)
                {
                    return min
                }
                return value
            }

            onTextChanged: {
                if(textInp.text.length == 0){
                    return
                }
                spinbox.value = clamp(textInp.text,spinbox.from,spinbox.to)
            }
        }

    Component.onCompleted: {
        textInp.text = spinbox.value
    }
}
