#include "gamecore.h"

GameCore::~GameCore()
{

}

void GameCore::StartNewGame()
{
    random_sequence_.clear();
    random_sequence_ = random_sequence_generator_(random_sequence_length_);

#ifdef DEBUG_ENABLED
    PrintVector(random_sequence_,"Randomly Generated Sequence is : ");
#endif
}

void GameCore::handleEvent(string event, map<string,string> params)
{
    if(event=="EvaluateUserGuess")
    {
        string guessed_seq = params.at("GuessedSequence");
        user_guessed_sequence_ = vector<char>(guessed_seq.begin(),guessed_seq.end());

        vector<char> guess_result = GetGuessResult();
        map<string,string> params;
        params.insert(pair<string,string>("GuessResult",string(guess_result.begin(),guess_result.end())));
        notify("GuessResultCalculated",params);
    }
    else if(event=="StartNewGame")
    {
        StartNewGame();
    }
}
