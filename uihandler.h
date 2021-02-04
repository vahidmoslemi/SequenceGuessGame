#ifndef UIHANDLER_H
#define UIHANDLER_H

#include <QQmlApplicationEngine>
#include <QObject>
#include <QQmlContext>
#include <QQuickItem>
#include <memory>
#include <QDebug>
#include <unordered_map>
#include <string>
#include <memory>

#include "eventlistenerinterface.h"
#include "eventsourceinterface.h"

#define DEFAULT_INDICATOR_COLOR "#E8E8E8"

class UIHandler : public QObject , public EventSource , public EventListenerInterface
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

    void handleEvent(std::string event, std::unordered_map<std::string, std::string> params) override;


signals:
//    Signal names cannot begin with an upper case letter in Qt
    void userGuessedSuccessfully();
public slots:
private:
    //qml related data models and ui context
    QQmlContext* m_app_ui_context;
    QVariantList m_guess_result_data_model;
    QVariantList m_user_guess_data_model;
    QString m_user_guessed_sequence;
    QVariantList m_current_item_model;
    int m_steps_count;
    int m_current_item_index;

    //TODO: indicator colors list could be changed in the future to support application
    //development and strategy change
    std::vector<std::string> m_result_indicator_colors {"red","orange","green"};

    void reset_game();
};

#endif // UIHANDLER_H
