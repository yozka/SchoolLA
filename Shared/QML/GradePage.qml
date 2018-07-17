﻿/****************************************************************************
**
** Copyright (C) 2018 Andreev AN.
** Contact: alex@tigraha.com
**
**
****************************************************************************/

import QtQuick 2.6
import QtQuick.Controls 2.1

Page 
{
    id: root







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
        model: ["Albert Einstein", "Ernest Hemingway", "Hans Gude"]
        delegate: ItemDelegate 
		{
            text: modelData
            width: listView.width - listView.leftMargin - listView.rightMargin
            height: avatar.implicitHeight
            leftPadding: avatar.implicitWidth + 32
            onClicked: root.StackView.view.push("qrc:/main/ConversationPage.qml", { inConversationWith: modelData })

			/*
            Image {
                id: avatar
                source: "qrc:/" + modelData.replace(" ", "_") + ".png"
            }*/
        }
    }
}

