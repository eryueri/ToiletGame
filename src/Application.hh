#pragma once

#include "Player.hh"

namespace TG {
	class Application {
	public:
		Application();
		~Application();
		void run();
	private:
		void initCardPool();
    void logCardPool();
		void shuffleCards();
		void dispatchCards();
	private:
		bool cardPairs(Card* c);
		void clearCardPairSignal(std::vector<Card*>::iterator pos, std::vector<Card*>::iterator end);
		std::vector<Card*>::iterator getSliptPos(Card* c);
	private:
		Player _players[2];
		CardSet _cardsOnDesk;
		Card* _cardPool[54];
	private:
		bool _terminate = false;
		bool _currentPlayer = false;
		bool _cardPairs[14] = {false};
		short _winner = 0;
	};
};
