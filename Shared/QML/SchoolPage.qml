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
		}

		Label 
		{
			anchors.top: gradesList.bottom

			Layout.fillWidth: true
			text: qsTr("Grade1")
            font.pixelSize: 20
        }

		/*
		Label 
		{
			Layout.fillWidth: true
			text: qsTr("Grade2")
        }

		Label 
		{
			Layout.fillWidth: true
			text: qsTr("Grade3")
            font.pixelSize: 20

        }*/
    }


}

