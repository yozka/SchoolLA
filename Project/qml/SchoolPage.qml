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


    SwipeView
    {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        GradesForm
        {
            schoolID : school.schoolID

            onSelect : function(gradeID)
            {
                //выбрали урок
                //покажем его
                console.log("SHow grade page " + gradeID);
                school.StackView.view.push("qrc:/grade/GradePage.qml", {gradeID:gradeID});
            }
        }

        TeachersForm
        {
        }

        StudentsForm
        {

        }
    }

    footer: TabBar
    {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton
        {
            text: qsTr("Grades")
        }
        TabButton
        {
            text: qsTr("Teachers")
        }
        TabButton
        {
            text: qsTr("Students")
        }
    }


}

