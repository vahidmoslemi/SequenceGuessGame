#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlContext>
#include <QQuickItem>
#include <memory>
#include <QDebug>
#include <map>
#include <string>
#include <memory>

#include "eventlistenerinterface.h"
#include "eventsourceinterface.h"

#define DEFAULT_INDICATOR_COLOR "#E8E8E8"

using namespace std;

class UIHandler : public QObject , public EventSourceInterface , public EventListenerInterface
{
    Q_OBJECT
public:
    //initialize applicatoin IU context in order to access qml elements and
    //interaction qml with cpp part.
    /**
     * @brief UIHandler
     * @param ctxt
     * @param parent
     */
    explicit UIHandler(std::unique_ptr<QQmlApplicationEngine>& engine, int steps_count=3, QObject *parent = nullptr);
    ~UIHandler() override;

    //invokable method to be accessed from qml to inform cpp part of qml ui changes
    //Tells cpp logic that user guessed one char and ui should be changed according user sellection
    //changes to ui is managed using QVariantList DataModels (user_guess_data_model_,current_item_model_)

    //method name must starts with lowercase caused by Qt and Qml restrictions
    /**
     * @brief gotoNextStep
     * @param selected_char
     */
    Q_INVOKABLE void gotoNextStep(QString selected_char);
    Q_INVOKABLE void evaluateUserGuess();

    void handleEvent(string event, map<string, string> params) override;


signals:
//    Signal names cannot begin with an upper case letter in Qt
    void userGuessedSuccessfully();
public slots:
private:
    QQmlContext* app_ui_context_;
    QVariantList guess_result_data_model_;
    QVariantList user_guess_data_model_;
    QString user_guessed_sequence_;
    QVariantList current_item_model_;
    int steps_count_;
    int current_item_index_;

    //TODO: indicator colors list could be changed in the future to support application
    //development and strategy change
    vector<string> result_indicator_colors_ {"red","orange","green"};

    void reset_game();
};

#endif // UIHANDLER_H
