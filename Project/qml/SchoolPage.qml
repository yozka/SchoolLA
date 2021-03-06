﻿/****************************************************************************
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
    property string schoolName: "Фаблаб" //имя школы


    header:SchoolHeader
    {
        id:schoolHeader
        schoolName:school.schoolName
        title:swipeView.currentItem.title
    }


    SwipeView
    {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        SchoolFormGrades
        {
        }

        SchoolFormTeachers
        {
        }

        SchoolFormStudents
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

