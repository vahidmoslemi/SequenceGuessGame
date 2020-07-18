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
#include<algorithm>
#include<functional>
#include<iostream>
#include <string>
#include <map>

#include "eventlistenerinterface.h"
#include "eventsourceinterface.h"

//define CharSequence as alias for vector of characters
using CharSequence = std::vector<char>;

//Alias type GameResultProcessor: funtion/lamda which gets 2 English Alphabets vectors and
// process their values and return a vector of int as result
typedef std::function<CharSequence(CharSequence&,CharSequence&)> GameResultProcessor;

//Alias type GameRandomSequenceGenerator: funtion/lamda which gets length of sequence and returns one
// randomly generated vector of English Alphabets
typedef std::function<CharSequence(unsigned int)> GameRandomSequenceGenerator;

template<typename T>
void PrintVector(T items,std::string msg)
{
    using namespace std;
    cout<<msg<<endl;
    std::for_each(std::begin(items),std::end(items),[](auto item){cout<<item;});
    cout<<endl;
}

class GameCore : public EventListenerInterface, public EventSource
{
public:
    GameCore(): m_random_sequence_length{1}{std::cout<<"random sequence default length: "<<m_random_sequence_length<<std::endl;}
    GameCore(GameRandomSequenceGenerator sequence_generator, unsigned int t_sequence_len,GameResultProcessor result_processor):
        m_random_sequence_length{t_sequence_len}, m_result_processor{result_processor},
        m_random_sequence_generator{sequence_generator}
    {
#ifdef DEBUG_ENABLED
        std::cout<<"Game Core initialized with sequence len of "<<t_sequence_len<<std::endl;
#endif
    }
    ~GameCore() override;

    void StartNewGame();

    void UserGuessed(const CharSequence& t_guessed_sequence){ m_user_guessed_sequence = t_guessed_sequence;}
    CharSequence GetGuessResult(){ return m_result_processor(m_random_sequence,m_user_guessed_sequence);}

    void handleEvent(std::string event,std::map<std::string,std::string> params) override;

private:
    CharSequence m_random_sequence;
    CharSequence m_user_guessed_sequence;
    CharSequence m_user_guess_result;

    const unsigned int m_random_sequence_length;
    /**
     * @brief result_processor_
     * function object which calc game result. could be set from outside the game core
     * Simply implementing so called Strategy Design Pattern
     * The GameResultProcessor method will get 2 vectors of char (random and guessed sequences)
     * and will return result in type of vector of integers.
     * example as lambda:
     *          [](vector<char>& random_seq,vector<char>& guessed_seq){return std::generate()};
     */
    GameResultProcessor m_result_processor;
    /**
     * @brief random_sequence_generator_
     * function object which generate random string to be guessed by the user.
     * Could be set from outside the game core
     * Simply implementing so called Strategy Design Pattern
     */
    GameRandomSequenceGenerator m_random_sequence_generator;
};

#endif // GAMECORE_H
