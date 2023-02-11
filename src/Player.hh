#pragma once

#include "CardSet.hh"

namespace TG {
    using CallbackFunc = std::function<void()>;

    class Player {
    public:
        Player();
        ~Player();
        bool empty();
        size_t number() const;
        void getCards(std::vector<Card*>::iterator start, std::vector<Card*>::iterator end);
        void getCards(Card** src, size_t length);
        void getCards(CardSet src);
        Card* putCard(CardSet& dst);
    private:
        CardSet _cards;
    };
}