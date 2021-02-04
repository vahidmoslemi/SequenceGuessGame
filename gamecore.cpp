#include "gamecore.h"

GameCore::~GameCore()
{

}

void GameCore::StartNewGame()
{
    m_random_sequence.clear();
    m_random_sequence = m_random_sequence_generator(m_random_sequence_length);

#ifdef DEBUG_ENABLED
    PrintVector(m_random_sequence,"Randomly Generated Sequence is : ");
#endif
}

void GameCore::handleEvent(std::string event, std::unordered_map<std::string,std::string> params)
{
    if(event=="EvaluateUserGuess")
    {
        std::string guessed_seq = params.at("GuessedSequence");
        m_user_guessed_sequence = CharSequence(guessed_seq.begin(),guessed_seq.end());

        CharSequence guess_result = GetGuessResult();
        std::unordered_map<std::string,std::string> params;
        params.insert(std::pair<std::string,std::string>("GuessResult",std::string(guess_result.begin(),guess_result.end())));
        notify("GuessResultCalculated",params);
    }
    else if(event=="StartNewGame")
    {
        StartNewGame();
    }
}
