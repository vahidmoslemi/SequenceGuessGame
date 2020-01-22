import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.3
import QtQuick.Dialogs 1.2

ApplicationWindow {
    id:mainwindow
    visible: true
    width: 300
    height: 300
    title: qsTr("Guess Game")

//    ListModel {id:currentItemIndicatorModel}
//    ListModel {id:guessResultModel}
//    ListModel {id:userGuessListModel}


    signal userGuessedSuccessfully;
    onUserGuessedSuccessfully: {
        console.log("You Successfully Guessed the right sequence.\nTry to guess a new Sequence ;-)")
//        alert("You Successfully Guessed the right sequence.\nTry to guess a new Sequence ;-)")

        //Comment to run in android: needs to be checked
//        msgDialog.open();
    }

    GridView{
        id: result_leds
        width: 300
        height: 100
        y:20
        model: guessResultModel
        delegate: Column
        {
            GuessIndicator{
                result_color: modelData
            }
        }
    }

    GridView{
        id: currentItemIndicator
        anchors.top:result_leds.bottom
        width: 300
        height: 5
        model: currentItemIndicatorModel
        delegate: Column
        {
            CurrentItemToGuessIndicator{
                isActive: modelData
            }
        }
    }

    GridView{
        id: userGuessView
        anchors.verticalCenter : result_leds.verticalCenter
        width: 300
        height: 20
        model: userGuessListModel
        delegate: Column
        {
            Text{
                width: 100
                height: 20
                font.pixelSize: 20
                wrapMode: Text.Wrap
                text: modelData
            }
        }
    }

    ListModel{
        id: buttonsList
        ListElement{
            btn_label:"A"
        }
        ListElement{
            btn_label:"B"
        }
        ListElement{
            btn_label:"C"
        }
    }


    GridView{
        id: guessButtons
        anchors.top:currentItemIndicator.bottom
        width: 300
        height: 100
        anchors.topMargin: 20
        model: buttonsList
        delegate: Column
        {
            UserGuessButton{
                label_text: btn_label
                onClicked: {
//                    console.log("UI: button clicked: " + btn_label)
                    uihandler.gotoNextStep(btn_label);
                }
            }
        }
    }

    Dialog {
        id: msgDialog
        title: "Congratulation!!!"
        standardButtons: Dialog.Ok
        modality: Qt.ApplicationModal
        width: mainwindow.width/2
        height: mainwindow.height/2

        Label {
            text:"You Successfully Guessed the right sequence.\nTry to guess a new Sequence ;-)"
        }
    }

    /*
    //We can add a dedicated button to invoke result calculation
    //commented in order to serve exact project senario
    Button
    {
        width: 250
        height: 30
        highlighted:true
        anchors.horizontalCenter:guessButtons.horizontalCenter
        anchors.top: guessButtons.bottom
        anchors.topMargin: 10
        text: "Evaluate Guessed Sequence"
        onClicked: {
            console.log("UserGussed");
            uihandler.evaluateUserGuess();
        }
    }
    */

}
