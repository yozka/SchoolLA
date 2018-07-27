import QtQuick 2.9
import QtQuick.Controls 2.2

import com.sla.jsonlistmodel 1.0
import QtGraphicalEffects 1.0


Page
{
    title:qsTr("Students")



    AJsonListModel
    {
        id: studentsModel
        api: serviceAPI


        parameters: {'gradeID': grade.gradeID}
        onParametersChanged:
        {
            //listView.rebound();
            reload();
        }

        idField: 'id'

        requests
        {
            get: "1.0/school/grade/student"
        }

        Component.onCompleted: { console.log(pagination.perPage);}
    }


    ListView
    {
        id: listView
        anchors.fill: parent
        topMargin: 48
        leftMargin: 0
        bottomMargin: 48
        rightMargin: 0
        spacing: 10

        /*
        snapMode: ListView.SnapToItem
        headerPositioning: ListView.OverlayHeader
        header: Label
        {
            height: 50
            z: 2

            leftPadding : 10

            text:qsTr("Students")
            font.pixelSize: 18
        }*/


        model: studentsModel
        delegate: ItemDelegate
        {
            text: name
            font.pixelSize: 16
            width: listView.width - listView.leftMargin - listView.rightMargin
            height: avatar.height + 16
            leftPadding: avatar.width + 32


            Image
            {
                id: avatar
                width: 64
                height:64
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: 10

                source: "https://sla.tigraha.com/files/avatar/" + avatarID + ".jpg"
                cache: true

                fillMode: Image.PreserveAspectCrop
                layer.enabled: true
                layer.effect: OpacityMask { maskSource: mask}
            }

            Rectangle
            {
                id: mask
                width: avatar.width
                height: avatar.height
                radius: avatar.width * 0.5
                visible: false
            }

            //список ачивок
            ListView
            {
                id:listViewAchivments
                anchors.fill: parent
                spacing: 10

                width:              parent.width * 0.5
                anchors.leftMargin: parent.width * 0.5
                contentWidth: width
                clip: true


                flickableDirection: Flickable.AutoFlickDirection


                orientation: ListView.Horizontal

                model: achivments
                delegate:ItemDelegate
                {
                    text: modelData.img
                    height:parent.height
                    width:parent.height
                }

                onCountChanged:
                {
                    listViewAchivments.positionViewAtBeginning();
                    listViewAchivments.currentIndex = 0
                }

            }


            onClicked:
            {
                //onSelect(gradeID);
            }

        }//delegate

    }//listview



}//page


