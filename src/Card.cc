#include "Card.hh"

namespace TG {
    Card::Card(const Figure& f, const Pattern& p)
        : figure(f), pattern(p) {}
    
    std::ostream& operator << (std::ostream& os, Figure f)
    {
        switch(f) {
            case Figure::TWO: {
                os << "2";
            }; break;
            case Figure::THREE: {
                os << "3";
            } break;
            case Figure::FOUR: {
                os << "4";
            } break;
            case Figure::FIVE: {
                os << "5";
            } break;
            case Figure::SIX: {
                os << "6";
            } break;
            case Figure::SEVEN: {
                os << "7";
            } break;
            case Figure::EIGHT: {
                os << "8";
            } break;
            case Figure::NINE: {
                os << "9";
            } break;
            case Figure::TEN: {
                os << "10";
            } break;
            case Figure::JACK: {
                os << "J";
            } break;
            case Figure::QUEEN: {
                os << "Q";
            } break;
            case Figure::KING: {
                os << "K";
            } break;
            case Figure::ACE: {
                os << "A";
            } break;
            case Figure::JOKER: {
                os << "JOKER";
            } break;
            default: {
                throw std::runtime_error("it doesnt make sense that the program reach here");
            } break;
        }
        return os;
    }

    std::ostream& operator << (std::ostream& os, Pattern p)
    {
        switch(p) {
            case Pattern::NONE: {

            } break;
            case Pattern::SPADE: {

            } break;
            case Pattern::HEART: {

            } break;
            case Pattern::DIAMOND: {

            } break;
            case Pattern::CLUB: {

            } break;
            case Pattern::RED_JOKER: {

            } break;
            case Pattern::BLACK_JOKER: {

            } break;
            default: {
                throw std::runtime_error("it doesnt make sense that the program reach here");
            } break;
        }
        return os;
    }
    
    std::ostream& operator << (std::ostream& os, Card c)
    {
        os << c.figure;
        return os;
    }
    std::ostream& operator << (std::ostream& os, Card* c)
    {
        os << c->figure;
        return os;
    }
}
