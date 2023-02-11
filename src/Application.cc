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
        int i = 0;
        for (auto c : _cardPool) {
            std::cout << c << " ";
            ++i;
            if (i % 13 == 0) {
                std::cout << "\n";
            }
        }
        std::cout << std::endl;
        dispatchCards();
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
                // exam players' cards, if empty the player lose
                std::cout << temp << " ";
                if (cardPairs(temp)) {
                    std::cout << " player 0 collects ";
                    // std::cout << " player 1 "<< _players[1].number() << " remain";
                    auto pos = getSliptPos(temp);
                    eraseCardSignal(pos, _cardsOnDesk.end());
                    _players[0].getCards(pos, _cardsOnDesk.end());
                    _cardsOnDesk.eraseCards(pos, _cardsOnDesk.end());
                    _currentPlayer = !_currentPlayer;
                }
                if (_players[0].empty()) {
                    _terminate = true;
                    std::cout << "\nplayer 0 loses!\n";
                }
            } else {
                Card* temp = _players[1].putCard(_cardsOnDesk);
                std::cout << temp << " ";
                if (cardPairs(temp)) {
                    std::cout << " player 1 collects ";
                    // std::cout << " player 0 "<< _players[0].number() << " remain";
                    auto pos = getSliptPos(temp);
                    eraseCardSignal(pos, _cardsOnDesk.end());
                    _players[1].getCards(pos, _cardsOnDesk.end());
                    _cardsOnDesk.eraseCards(pos, _cardsOnDesk.end());
                    _currentPlayer = !_currentPlayer;
                }
                if (_players[1].empty()) {
                    _terminate = true;
                    std::cout << "\nplayer 1 loses!\n";
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
    
    void Application::eraseCardSignal(std::vector<Card*>::iterator pos, std::vector<Card*>::iterator end)
    {
        for (auto it = pos; it != end; ++it) {
            size_t i = static_cast<std::underlying_type<Figure>::type>((*it)->figure);
            _cardPairs[i] = !_cardPairs[i];
        }
    }
    
    std::vector<Card*>::iterator Application::getSliptPos(Card* c)
    {
        std::cout << std::endl;
        for (auto it = _cardsOnDesk.begin(); it != _cardsOnDesk.end(); ++it) {
            if ((*it)->figure != c->figure) {
                std::cout << (*it) << " ";
            } else {
                return it;
            }
        }
        throw std::runtime_error("should not happen that cards dont pair!");
    }
}
