import QtQuick 2.9
import QtQuick.Controls 2.2

import com.sla.serviceapi 1.0

import "qrc:/school"

ApplicationWindow 
{
    id: window
    width: 480
    height: 640
    visible: true

	AServiceAPI 
	{
		id: serviceAPI

        baseUrl: "https://sla.tigraha.com/api"

        authTokenHeader: "Authorization"
        authToken: "testToken"

        Component.onCompleted: console.log("completed!");
    }


    StackView 
	{
        id: stackView
        anchors.fill: parent
		

		initialItem: SchoolPage {}
	}
}
