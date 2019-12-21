#ifndef GAMECORE_H
#define GAMECORE_H

//Game core class
//This class is main part of the game app alongside UI
//it is initialized by giving 2 lambda functions (Sequence Generator and Result Processor)
//and one integer value indicating random English Alphabet sequence length
//example:
//
//  GameCore game_core (StrategyFunctions::GetSequenceGenerator(),
//                      ksequence_length,StrategyFunctions::GetResultProcessor());
//  game_core.StartNewGame();
//
//See StrategyFunctions class as a sample for required lambda functions

#include<vector>
#include<memory>
#include<algorithm>
#include<functional>
#include<iostream>
#include <string>
#include <map>

using namespace std;

#include "eventlistenerinterface.h"
#include "eventsourceinterface.h"

//Alias type GameResultProcessor: funtion/lamda which gets 2 English Alphabets vectors and
// process their values and return a vector of int as result
typedef std::function<vector<char>(vector<char>&,vector<char>&)> GameResultProcessor;

//Alias type GameRandomSequenceGenerator: funtion/lamda which gets length of sequence and returns one
// randomly generated vector of English Alphabets
typedef std::function<vector<char>(int)> GameRandomSequenceGenerator;


template<typename T>
void PrintVector(T items,string msg)
{
    cout<<msg<<endl;
    for(auto& item:items)
    {
        cout<<", "<<item;
    }
    cout<<endl;
}

class GameCore : public EventListenerInterface, public EventSourceInterface
{
public:
    GameCore() {}
    ~GameCore();
    GameCore(GameRandomSequenceGenerator sequence_generator, int sequence_len,GameResultProcessor result_processor):
        random_sequence_length_{sequence_len}, result_processor_{result_processor},random_sequence_generator_{sequence_generator} {
#ifdef DEBUG_ENABLED
        cout<<"Game Core initialized with sequence len of "<<sequence_len<<endl;
#endif
    }

    void StartNewGame();

    void UserGuessed(const vector<char>& guessed_sequence){ user_guessed_sequence_ = guessed_sequence;}
    vector<char> GetGuessResult(){ return result_processor_(random_sequence_,user_guessed_sequence_);}

    void HandleEvent(string event,map<string,string> params);

private:
    vector<char> random_sequence_;
    vector<char> user_guessed_sequence_;
    vector<char> user_guess_result_;

    int random_sequence_length_;
    /**
     * @brief result_processor_
     * function object which calc game result. could be set from outside the game core
     * Simply implementing so called Strategy Design Pattern
     * The GameResultProcessor method will get 2 vectors of char (random and guessed sequences)
     * and will return result in type of vector of integers.
     * example as lambda:
     *          [](vector<char>& random_seq,vector<char>& guessed_seq){return std::generate()};
     */
    GameResultProcessor result_processor_;
    /**
     * @brief random_sequence_generator_
     * function object which generate random string to be guessed by the user.
     * Could be set from outside the game core
     * Simply implementing so called Strategy Design Pattern
     */
    GameRandomSequenceGenerator     random_sequence_generator_;
};

#endif // GAMECORE_H
