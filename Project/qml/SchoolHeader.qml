import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.11

Label
{
    property string     schoolName//имя школы
    property string     title
    property var        menu

    Label
    {
        id:lbSchoolName
        text: schoolName
        padding: 10;
        horizontalAlignment : Text.AlignRight

        Layout.fillWidth: true
        anchors.fill: parent
    }

    Label
    {
        id:lbTitle
        text: title
        padding: 10;

        font.pixelSize: Qt.application.font.pixelSize * 2
        Layout.fillWidth: true
        anchors.top: lbSchoolName.bottom
        anchors.left: lbSchoolName.left
    }
    ToolButton
    {
        text: qsTr("⋮")
        onClicked: menu.open()
        anchors.top: lbSchoolName.bottom
        anchors.right: lbSchoolName.right
    }
}
