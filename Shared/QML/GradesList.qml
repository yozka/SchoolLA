/****************************************************************************
**
** Copyright (C) 2018 Andreev AN.
** Contact: alex@tigraha.com
**
**
****************************************************************************/

import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3

import com.sla.jsonlistmodel 1.0

Item 
{
	id: gradesList

	
	//индификатор школы
	property int schoolID



	AJsonListModel 
	{
		id: gradesModel
        api: serviceAPI


		parameters: {'schoolID': schoolID}
		onParametersChanged: reload() 

        idField: 'id'

        requests 
		{
            get: "1.0/grade"
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
					root.StackView.view.push("qrc:/page/ConversationPage.qml", { inConversationWith: gradesModel.idField });
					//school.schoolID = 100;
				}

			}
		}



}

