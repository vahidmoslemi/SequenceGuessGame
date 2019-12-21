#include "uihandler.h"

UIHandler::UIHandler(QQmlApplicationEngine* engine, int steps_count, QObject *parent) : QObject(parent)
{
    //initialze UI: access to qml ui context
    app_ui_context_ = engine->rootContext();
    steps_count_ = steps_count;
    app_ui_context_->setContextProperty("uihandler",this);

    QObject* viewObject = engine->rootObjects()[0];
    connect(this,SIGNAL(userGuessedSuccessfully()),viewObject,SIGNAL(userGuessedSuccessfully()));

    //init ui with default values to start guess new random sequence
    reset_game();
}

UIHandler::~UIHandler()
{
    delete app_ui_context_;
}

void UIHandler::gotoNextStep(QString selected_char)
{
    user_guess_data_model_[current_item_index_] = "      "+selected_char+"      ";
//    qDebug()<<Q_FUNC_INFO<<" selected chars:" <<user_guess_data_model_;
    app_ui_context_->setContextProperty("userGuessListModel", user_guess_data_model_);
    current_item_model_[current_item_index_]=0;
    user_guessed_sequence_[current_item_index_] = selected_char.at(0);
    ++current_item_index_;

    if(current_item_index_==steps_count_)
    {
        //We can add a dedicated button to invoke result calculation
        //but I have commented it in main.qml last part, in order to serve exact project senario
        //and evaluateUserGuess in invoked automaically after 3 button presses and result will shown on top
        evaluateUserGuess();
        current_item_index_ = 0;
    }
    current_item_model_[current_item_index_]=1;
    app_ui_context_->setContextProperty("currentItemIndicatorModel", current_item_model_);
}


void UIHandler::reset_game()
{
    current_item_index_=0;
    user_guess_data_model_.clear();
    current_item_model_.clear();
    guess_result_data_model_.clear();

    //default initlaization of user_guess_data_model_
    for(int ctr=0;ctr<steps_count_;ctr++)
    {
        //last color element in result_indicator_colors_ vector is DEFAULT_INDICATOR_COLOR
        guess_result_data_model_.append(DEFAULT_INDICATOR_COLOR);
        user_guess_data_model_.append("      ?      ");
        current_item_model_.append(static_cast<int>(current_item_index_ == ctr));
        user_guessed_sequence_.append('?');
    }
    current_item_model_[0]=1;
    app_ui_context_->setContextProperty("userGuessListModel", user_guess_data_model_);
    app_ui_context_->setContextProperty("currentItemIndicatorModel", current_item_model_);
    app_ui_context_->setContextProperty("guessResultModel", guess_result_data_model_);
}

void UIHandler::evaluateUserGuess()
{
    map<string,string> params;
    params.insert(pair<string,string>("GuessedSequence",user_guessed_sequence_.toStdString()));
    notify("EvaluateUserGuess",params);
}


void UIHandler::HandleEvent(string event, map<string, string> params)
{
    if(event=="GuessResultCalculated")
    {
        string str_result_seq = params.at("GuessResult");
        guess_result_data_model_.clear();
        char result_sum = 0;
        for(auto& result_code: str_result_seq)
        {
            guess_result_data_model_.append(QString::fromStdString(result_indicator_colors_[static_cast<unsigned long>(result_code)]));
            result_sum+= result_code;
        }
        app_ui_context_->setContextProperty("guessResultModel", guess_result_data_model_);

        //if user guessed correct sequence
        if(result_sum==6)
        {
            emit(userGuessedSuccessfully());
            reset_game();
            notify("StartNewGame",map<string,string>());
        }
    }
}
