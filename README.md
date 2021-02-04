# SequenceGuessGame
An example of creating an application using pure modern C++ logic and QtQuick(QML) UI.

## Project Description

Given a system with the following:
● LED 1, LED 2 and LED 3 - which can be {red, green, orange}
● Button A, Button B and Button C

The system implements a game in which the user has to guess a sequence of three
button presses. For each press, the current position being guessed is indicated.
- The sequence can contain any combination, e.g. BAC, CCB, AAA.
- The LEDs should always represent the result of the last 3 button presses.
-
- LED 3 will always represent the most recent button event
- LED 2 the one before that
- LED 1 the one before that
After three presses, if the correct sequence has not been guessed, the user starts
guessing from the first position again.
Red indicates that the button pressed was wrong for this position, and does not appear in a
different position.
Orange indicates that the button pressed was wrong for this position, but it does appear in a
different position



## Solution Brief:
    • Solution is provided using mostly based on two design patterns: Observer  and Strategy
      
    • Game core is initiated with 2 lamda function to serve as RandomSequenceGenerator and GuessResultProcessor.
      So Game strategy could be changed by providing different lambda functions in main.cpp	
      
    • Application UI is based on QtQuick and qml language. UIHandler class is responsible for 
      loading and updating UI elements including: LED indicators, UserGuessedSequence display, 
      Alphabetical Buttons to be pressed, and Current Position to guess Indicator bar.
      
    • UI elements are connected to Qt Data model (here simple QVariantList) and will be updated accordingly.
    • 2 Classes are defined to provide observer design pattern in Pure Modern C++: 
      EventListenerInterface and EventSourceIComponent
    • both GameCore and UIHandler are drived from these classes and connected to each other using 
      RegisterEventListener method. And interact with each other using Notify and HandlerEvent functions

# Fill free to use my codes but please refer to my github page address.
