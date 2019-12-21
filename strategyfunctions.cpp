#include "strategyfunctions.h"

GameRandomSequenceGenerator StrategyFunctions::GetSequenceGenerator()
{
    auto random_number_in_range = [](int low, int high)
    {
        auto distribution = std::uniform_int_distribution<int>(low, high);
        auto random_engine = std::mt19937{ std::random_device{}() };
        auto random_function = [&distribution,&random_engine]() mutable
        {
            return distribution(random_engine);
        };
        return random_function;
    };

    auto sequence_generator = [&random_number_in_range](int len) -> vector<char> {
        vector<char> sequence(static_cast<unsigned long>(len));
        std::generate(sequence.begin(),sequence.end(),random_number_in_range(65,65+len-1));
        return sequence;
    };
    return sequence_generator;
}

GameResultProcessor StrategyFunctions::GetResultProcessor()
{
    auto result_processor = [](vector<char>& random_sequence,vector<char>& guessed_sequence) -> vector<char> {
        vector<char> result(random_sequence.size());
        for(unsigned long ctr=0;ctr<random_sequence.size();ctr++)
        {
            if(random_sequence[ctr] == guessed_sequence[ctr])
                result[ctr] = 2;
            else if(std::find(random_sequence.begin(),random_sequence.end(),guessed_sequence[ctr]) != random_sequence.end())
            {
                result[ctr]=1;
            }
            else
            {
                result[ctr]=0;
            }
        }
        return result;
    };
    return result_processor;
}
