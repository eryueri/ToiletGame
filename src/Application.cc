#include "Application.hh"

namespace TG {
    static int randInt()
    {
        auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        std::mt19937 gen(seed);
        std::uniform_int_distribution<> dis(0, 53);
        int rand = dis(gen);
        return rand;
    }
    
    static void swap(Card*& a, Card*& b)
    {
        Card* temp = a;
        a = b;
        b = temp;
    }

    Application::Application()
    {
        initCardPool();
        std::cerr << "CardPool inited!\n";
        shuffleCards();
        std::cerr << "Cards Shuffled!\n";
        dispatchCards();
        std::cerr << "Cards Dispatched to players!\n";
    }
    
    Application::~Application()
    {
        for (int i = 0; i < 54; ++i) {
            delete _cardPool[i];
        }
    }
    
    void Application::run()
    {
        while (!_terminate) {
            if (!_currentPlayer) {
                Card* temp = _players[0].putCard(_cardsOnDesk);
                // if collectable, collect the cards
                std::cerr << temp << " ";
                if (cardPairs(temp)) {
                    std::cerr << " player 0 collects ";
                    // std::cerr << " player 1 "<< _players[1].number() << " remain";
                    auto pos = getSliptPos(temp);
                    clearCardPairSignal(pos, _cardsOnDesk.end());
                    _players[0].getCards(pos, _cardsOnDesk.end());
                    _cardsOnDesk.eraseCards(pos, _cardsOnDesk.end());
                    _currentPlayer = !_currentPlayer;
                }
                // exam players' cards, if empty the player lose
                if (_players[0].empty()) {
                    _terminate = true;
                    std::cerr << "\nplayer 0 loses!\n";
                }
            } else {
                Card* temp = _players[1].putCard(_cardsOnDesk);
                std::cerr << temp << " ";
                if (cardPairs(temp)) {
                    std::cerr << " player 1 collects ";
                    // std::cerr << " player 0 "<< _players[0].number() << " remain";
                    auto pos = getSliptPos(temp);
                    clearCardPairSignal(pos, _cardsOnDesk.end());
                    _players[1].getCards(pos, _cardsOnDesk.end());
                    _cardsOnDesk.eraseCards(pos, _cardsOnDesk.end());
                    _currentPlayer = !_currentPlayer;
                }
                if (_players[1].empty()) {
                    _terminate = true;
                    std::cerr << "\nplayer 1 loses!\n";
                    // _player[1] loses
                }
            }
            _currentPlayer = !_currentPlayer;
        }
    }
    
    void Application::initCardPool()
    {
        const std::initializer_list<const Figure> figures{
            Figure::TWO, Figure::THREE, Figure::FOUR, 
            Figure::FIVE, Figure::SIX, Figure::SEVEN, 
            Figure::EIGHT, Figure::NINE, Figure::TEN, 
            Figure::JACK, Figure::QUEEN, Figure::KING, 
            Figure::ACE
        };
        const std::initializer_list<const Pattern> patterns{
            Pattern::SPADE, Pattern::HEART, 
            Pattern::DIAMOND, Pattern::CLUB
        };

        int i = 0;
        for (auto f : figures) {
            for (auto p : patterns) {
                _cardPool[i] = new Card{f, p};
                ++i;
            }
        }
        _cardPool[i] = new Card{Figure::JOKER, Pattern::RED_JOKER};
        _cardPool[i+1] = new Card{Figure::JOKER, Pattern::BLACK_JOKER};
    }

    void Application::logCardPool()
    {
        int i = 0;
        for (auto c : _cardPool) {
            std::cerr << c << " ";
            ++i;
            if (i % 18 == 0) {
                std::cerr << "\n";
            }
        }
        std::cerr << std::endl;
    }
    
    // it makes sence for me to shuffle cards in the cardPool
    // because in this game you're not allowed to shuffle cards
    // so cardSet should not have the functionality to shuffle cards
    // cards are only shuffled in the beginning
    void Application::shuffleCards()
    { 
        for (int i = 0; i < 54; ++i) {
            int rand = randInt();
            swap(_cardPool[i], _cardPool[rand]); 
        }
    }
    
    void Application::dispatchCards()
    {
        _players[0].getCards(_cardPool, 27);
        _players[1].getCards(_cardPool+27, 27);
    }
    
    bool Application::cardPairs(Card* c)
    {
        size_t i = static_cast<std::underlying_type<Figure>::type>(c->figure);
        _cardPairs[i] = !_cardPairs[i];
        if (!_cardPairs[i]) {
            return true;
        }
        return false;
    }
    
    void Application::clearCardPairSignal(std::vector<Card*>::iterator pos, std::vector<Card*>::iterator end)
    {
        for (auto it = pos; it != end; ++it) {
            size_t i = static_cast<std::underlying_type<Figure>::type>((*it)->figure);
            _cardPairs[i] = !_cardPairs[i];
        }
    }
    
    std::vector<Card*>::iterator Application::getSliptPos(Card* c)
    {
        std::cerr << std::endl;
        for (auto it = _cardsOnDesk.begin(); it != _cardsOnDesk.end(); ++it) {
            if ((*it)->figure != c->figure) {
                std::cerr << (*it) << " ";
            } else {
                return it;
            }
        }
        throw std::runtime_error("should not happen that cards dont pair!");
    }
}
