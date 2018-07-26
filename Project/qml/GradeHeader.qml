import QtQuick 2.9
import QtQuick.Controls 2.2

ToolBar
{
    ToolButton
    {
        text: qsTr("Back")
        anchors.left: parent.left
        anchors.leftMargin: 10
        anchors.verticalCenter: parent.verticalCenter
        onClicked: stackView.pop()
    }

    Label
    {
        id: pageTitle
        text: "Grade id " + gradeID
        font.pixelSize: 20
        anchors.centerIn: parent
    }
}
