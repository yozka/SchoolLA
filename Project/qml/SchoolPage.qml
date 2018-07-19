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

import "qrc:/grade"

Page 
{
	id: school

	
	//индификатор школы
	property int schoolID : 1

	


	header: ToolBar 
	{
        Label 
		{
			text: qsTr("School")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }

	ColumnLayout 
	{
        anchors.fill: parent
 

      	GradesList
		{
			id: gradesList
			Layout.fillWidth: true
            Layout.fillHeight: true

			schoolID : school.schoolID

			onSelect : function(gradeID)
			{
				//выбрали урок
				//покажем его
				console.log("SHow grade page " + gradeID);
				school.StackView.view.push("qrc:/grade/GradePage.qml", {gradeID:gradeID});
			}
		}

    }

	footer: ToolBar 
	{
        Label 
		{
			text: qsTr("Footer School")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }
}

