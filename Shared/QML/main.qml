import QtQuick 2.6
import QtQuick.Controls 2.0

import com.sla.serviceapi 1.0

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
        authToken: "Bearer 8aef452ee3b32466209535b96d456b06"

        Component.onCompleted: console.log("completed!");
    }


    StackView 
	{
        id: stackView
        anchors.fill: parent
        initialItem: GradePage{}


	}
}
