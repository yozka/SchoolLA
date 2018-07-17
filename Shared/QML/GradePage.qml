/****************************************************************************
**
** Copyright (C) 2018 Andreev AN.
** Contact: alex@tigraha.com
**
**
****************************************************************************/

import QtQuick 2.6
import QtQuick.Controls 2.1
import com.sla.jsonlistmodel 1.0

Page 
{
	id: root



	AJsonListModel 
	{
		id: gradeModel
        api: serviceAPI


		parameters: {'schoolID': 1, 'test' : 2}


        idField: 'id'

        requests 
		{
            get: "grade"
        }

        Component.onCompleted: { console.log(pagination.perPage); reload(); }
	}



    header: ToolBar 
	{
        Label 
		{
			text: qsTr("Занятия")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

    ListView 
	{
        id: listView
        anchors.fill: parent
        topMargin: 48
        leftMargin: 48
        bottomMargin: 48
        rightMargin: 48
        spacing: 20
        model: gradeModel
        delegate: ItemDelegate 
		{
            text: name
            width: listView.width - listView.leftMargin - listView.rightMargin
            height: avatar.implicitHeight
            leftPadding: avatar.implicitWidth + 32
            onClicked: 
			{
				root.StackView.view.push("qrc:/main/ConversationPage.qml", { inConversationWith: name })
				gradeModel.parameters = {'test3' : 3}
			}

			/*
            Image {
                id: avatar
                source: "qrc:/" + modelData.replace(" ", "_") + ".png"
            }*/
        }
    }
}

