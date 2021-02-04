#include "uihandler.h"

UIHandler::UIHandler(std::unique_ptr<QQmlApplicationEngine>& engine, int steps_count, QObject *parent) : QObject(parent)
{
    //initialze UI: access to qml ui context
    m_app_ui_context = engine->rootContext();
    m_steps_count = steps_count;
    m_app_ui_context->setContextProperty("uihandler",this);

    QObject* viewObject = engine->rootObjects()[0];
    connect(this,SIGNAL(userGuessedSuccessfully()),viewObject,SIGNAL(userGuessedSuccessfully()));

    //init ui with default values to start guess new random sequence
    reset_game();
}

UIHandler::~UIHandler()
{
    delete m_app_ui_context;
}

void UIHandler::gotoNextStep(QString selected_char)
{
    m_user_guess_data_model[m_current_item_index] = "      "+selected_char+"      ";
//    qDebug()<<Q_FUNC_INFO<<" selected chars:" <<user_guess_data_model_;
    m_app_ui_context->setContextProperty("userGuessListModel", m_user_guess_data_model);
    m_current_item_model[m_current_item_index]=0;
    m_user_guessed_sequence[m_current_item_index] = selected_char.at(0);
    ++m_current_item_index;

    if(m_current_item_index==m_steps_count)
    {
        //We can add a dedicated button to invoke result calculation
        //but I have commented it in main.qml last part, in order to serve exact project senario
        //and evaluateUserGuess in invoked automaically after 3 button presses and result will shown on top
        evaluateUserGuess();
        m_current_item_index = 0;
    }
    m_current_item_model[m_current_item_index]=1;
    m_app_ui_context->setContextProperty("currentItemIndicatorModel", m_current_item_model);
}


void UIHandler::reset_game()
{
    m_current_item_index=0;
    m_user_guess_data_model.clear();
    m_current_item_model.clear();
    m_guess_result_data_model.clear();

    //default initlaization of user_guess_data_model_
    for(int ctr=0;ctr<m_steps_count;ctr++)
    {
        //last color element in result_indicator_colors_ vector is DEFAULT_INDICATOR_COLOR
        m_guess_result_data_model.append(DEFAULT_INDICATOR_COLOR);
        m_user_guess_data_model.append("      ?      ");
        m_current_item_model.append(static_cast<int>(m_current_item_index == ctr));
        m_user_guessed_sequence.append('?');
    }
    m_current_item_model[0]=1;
    m_app_ui_context->setContextProperty("userGuessListModel", m_user_guess_data_model);
    m_app_ui_context->setContextProperty("currentItemIndicatorModel", m_current_item_model);
    m_app_ui_context->setContextProperty("guessResultModel", m_guess_result_data_model);
}

void UIHandler::evaluateUserGuess()
{
    std::unordered_map<std::string,std::string> params;
    //automatic type inference in modern c++
    params.insert({"GuessedSequence",m_user_guessed_sequence.toStdString()});
    notify("EvaluateUserGuess",params);
}


void UIHandler::handleEvent(std::string event, std::unordered_map<std::string, std::string> params)
{
    if(event=="GuessResultCalculated")
    {
        auto str_result_seq = params.at("GuessResult");
        m_guess_result_data_model.clear();
        char result_sum = 0;
        for(auto& result_code: str_result_seq)
        {
            m_guess_result_data_model.append(QString::fromStdString(m_result_indicator_colors[static_cast<unsigned long>(result_code)]));
            result_sum+= result_code;
        }
        m_app_ui_context->setContextProperty("guessResultModel", m_guess_result_data_model);

        //if user guessed correct sequence
        if(result_sum==6)
        {
            emit(userGuessedSuccessfully());
            reset_game();
            notify("StartNewGame",{});
        }
    }
}
