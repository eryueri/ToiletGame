#include "CardSet.hh"

namespace TG {
    CardSet::CardSet()
    {
        
    }

    CardSet::~CardSet()
    {

    }
    
    bool CardSet::empty()
    {
        return _cards.empty();
    }
    
    size_t CardSet::size() const 
    {
        return _cards.size();
    }
    
    void CardSet::pushCards(std::vector<Card*>::iterator start, std::vector<Card*>::iterator end)
    {
        _cards.insert(_cards.end(), start, end);
    }
    
    void CardSet::pushCards(Card** array, size_t length)
    {
        _cards.resize(_cards.size() + length);
        std::copy(array, array+length, _cards.begin()); 
    }
    
    void CardSet::pushCards(CardSet cs)
    {
        _cards.insert(_cards.end(), cs.begin(), cs.end());
    }
    
    Card* CardSet::popCard()
    {
        if (_cards.empty()) {
            throw std::runtime_error("the cardSet is empty!");
        }
        Card* result = _cards.front();
        _cards.erase(_cards.begin());
        return result;
    }
    
    void CardSet::eraseCards(std::vector<Card*>::iterator start, std::vector<Card*>::iterator end)
    {
        _cards.erase(start, end);
    }
    
    void CardSet::insert(Card* c)
    {
        _cards.push_back(c);
    }
}

namespace TG {
    std::vector<Card*>::iterator CardSet::begin() { return _cards.begin(); }
    std::vector<Card*>::iterator CardSet::end() { return _cards.end(); }
    std::vector<Card*>::reverse_iterator CardSet::rbegin() { return _cards.rbegin(); }
    std::vector<Card*>::reverse_iterator CardSet::rend() { return _cards.rend(); }
    std::vector<Card*>::const_iterator CardSet::begin() const { return _cards.begin(); }
    std::vector<Card*>::const_iterator CardSet::end() const { return _cards.end(); }
    std::vector<Card*>::const_reverse_iterator CardSet::rbegin() const { return _cards.rbegin(); }
    std::vector<Card*>::const_reverse_iterator CardSet::rend() const { return _cards.rend(); }
}