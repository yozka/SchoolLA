/****************************************************************************
**
** Copyright (C) 2018 Andreev AN.
** Contact: alex@tigraha.com
**
**
****************************************************************************/

import QtQuick 2.9
import QtQuick.Controls 2.2
import com.sla.jsonlistmodel 1.0

Page 
{
	id: grade

	property int gradeID

	/*
	AJsonListModel 
	{
		id: gradeModel
        api: serviceAPI


		parameters: {'schoolID': 1}


        idField: 'id'

        requests 
		{
            get: "1.0/grade"
        }

        Component.onCompleted: { console.log(pagination.perPage); reload(); }
	}*/



	header: ToolBar 
	{
        ToolButton 
		{
            text: qsTr("Back")
            anchors.left: parent.left
            anchors.leftMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            onClicked: grade.StackView.view.pop()
        }

        Label 
		{
            id: pageTitle
            text: "Grade id " + gradeID
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }



	footer: ToolBar 
	{
        Label 
		{
			text: qsTr("Footer grade")
            font.pixelSize: 20
            anchors.centerIn: parent
        }
    }
}

