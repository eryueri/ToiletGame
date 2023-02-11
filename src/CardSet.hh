#pragma once

#include "Card.hh"

namespace TG {
	class CardSet {
	public:
		CardSet();
		~CardSet();
		bool empty();
		size_t size() const;
        void pushCards(std::vector<Card*>::iterator start, std::vector<Card*>::iterator end);
		void pushCards(Card** array, size_t length);
		void pushCards(CardSet cs);
		Card* popCard();
		void eraseCards(std::vector<Card*>::iterator start, std::vector<Card*>::iterator end);
		void insert(Card* c);
		
		std::vector<Card*>::iterator begin();
		std::vector<Card*>::iterator end();
		std::vector<Card*>::reverse_iterator rbegin();
		std::vector<Card*>::reverse_iterator rend();
		std::vector<Card*>::const_iterator begin() const;
		std::vector<Card*>::const_iterator end() const;
		std::vector<Card*>::const_reverse_iterator rbegin() const;
		std::vector<Card*>::const_reverse_iterator rend() const;
	private:
		std::vector<Card*> _cards;
	};
}