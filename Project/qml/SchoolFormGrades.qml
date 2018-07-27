import QtQuick 2.9
import QtQuick.Controls 2.2


import com.sla.jsonlistmodel 1.0


Page
{
    title:qsTr("Grades")

    AJsonListModel
    {
        id: gradesModel
        api: serviceAPI


        parameters: {'schoolID': school.schoolID}
        onParametersChanged: reload()

        idField: 'id'

        requests
        {
            get: "1.0/school/grade"
        }

        Component.onCompleted: { console.log(pagination.perPage);}
    }


    ListView
    {
        id: listView
        anchors.fill: parent
        topMargin: 48
        leftMargin: 48
        bottomMargin: 48
        rightMargin: 48
        spacing: 10
        model: gradesModel
        delegate: ItemDelegate
        {
            text: name
            font.pixelSize: 16
            width: listView.width - listView.leftMargin - listView.rightMargin
            height: 40
            onClicked:
            {
                grade.show(gradeID);
            }
        }
    }
}
