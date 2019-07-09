#ifndef MARKOV_CHAINS_H
#define MARKOV_CHAINS_H

#include <string>
#include <map>
#include <vector>
#include <random>


class MarkovChains
{
public:
    MarkovChains(unsigned int depth);
    
    void seed(const std::u32string& s);
    void addLearning(const std::u32string& s);
    std::u32string getNext(std::mt19937_64& random_engine);
private:
    class Chain
    {
    public:
        void add(const std::u32string& data);
        std::u32string getRandom(std::mt19937_64& random_engine);
    private:
        unsigned int total = 0;
        std::map<std::u32string, unsigned int> entries;
    };
    
    unsigned int max_depth;
    std::map<std::u32string, Chain> chains;
    std::vector<std::u32string> history;
};

#endif//MARKOV_CHAINS_H
