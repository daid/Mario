#include "markovChains.h"


MarkovChains::MarkovChains(unsigned int depth)
: max_depth(depth)
{
}

void MarkovChains::seed(const std::u32string& s)
{
    history.clear();
    for(int n=0; n<max_depth; n++)
        history.push_back(s);
}

void MarkovChains::addLearning(const std::u32string& s)
{
    for(unsigned int n=1; n<=max_depth; n++)
    {
        std::u32string key;
        for(unsigned int m=0; m<n; m++)
            key += history[m];
        chains[key].add(s);
    }
    history.insert(history.begin(), s);
    if (history.size() > max_depth)
        history.pop_back();
}

std::u32string MarkovChains::getNext(std::mt19937_64& random_engine)
{
    for(unsigned int key_size = std::min(max_depth, history.size()); key_size > 0; key_size--)
    {
        std::u32string key;
        for(unsigned int m=0; m<key_size; m++)
            key += history[m];
        auto it = chains.find(key);
        if (it != chains.end())
        {
            std::u32string result = it->second.getRandom(random_engine);
            history.insert(history.begin(), result);
            if (history.size() > max_depth)
                history.pop_back();
            return result;
        }
    }
    return U"";
}

void MarkovChains::Chain::add(const std::u32string& data)
{
    entries[data] += 1;
    total += 1;
}

std::u32string MarkovChains::Chain::getRandom(std::mt19937_64& random_engine)
{
    unsigned int n = std::uniform_int_distribution<>(0, total - 1)(random_engine);
    for(auto it : entries)
    {
        if (n < it.second)
            return it.first;
        n -= it.second;
    }
    return U"";
}
