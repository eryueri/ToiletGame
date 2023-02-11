#include "Player.hh"

namespace TG {
    Player::Player()
    {
        
    }
    
    Player::~Player()
    {
        
    }
    
    bool Player::empty()
    {
        return _cards.empty();
    }
    
    size_t Player::number() const
    {
        return _cards.size();
    }

    void Player::getCards(std::vector<Card*>::iterator start, std::vector<Card*>::iterator end)
    {
        _cards.pushCards(start, end);
    }
    
    void Player::getCards(Card** src, size_t length)
    {
        _cards.pushCards(src, length);
    }
    
    void Player::getCards(CardSet src) 
    {
        _cards.pushCards(src);
    }
    
    Card* Player::putCard(CardSet& dst)
    {
        Card* c = _cards.popCard();
        dst.insert(c);
        return c;
    }
}