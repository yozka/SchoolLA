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
    id: grade

    property int gradeID //индификатор занятий


    function show(id)
    {
        gradeID = id;
        stackView.push(this);
    }



    header:GradeHeader
    {
        id:gradeHeader
    }


    SwipeView
    {
        id: swipeView
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        GradeFormStudents
        {

        }

        GradeFormTeachers
        {
        }


    }


    footer: TabBar
    {
        id: tabBar
        currentIndex: swipeView.currentIndex

        TabButton
        {
            text: qsTr("Students")
        }
        TabButton
        {
            text: qsTr("Teachers")
        }
    }


}

