#pragma once

#include "pch.hh"

namespace TG {
	enum class Figure {
		TWO = 0, THREE = 1, FOUR = 2, FIVE = 3, SIX = 4, SEVEN = 5, EIGHT = 6, NINE = 7, 
		TEN = 8, JACK = 9, QUEEN = 10, KING = 11, ACE = 12, JOKER = 13, 
	};
	enum class Pattern {
		NONE = 0, SPADE = 1, HEART = 2, DIAMOND = 3, CLUB = 4, RED_JOKER = 5, BLACK_JOKER = 6,  
	};
	struct Card {
		Figure figure;
		Pattern pattern;
		Card() = delete;
		Card(const Figure& f, const Pattern& p);
	};
	
	std::ostream& operator<<(std::ostream& os, Figure f);
	std::ostream& operator<<(std::ostream& os, Pattern f);
	
	std::ostream& operator<<(std::ostream& os, Card c);
	std::ostream& operator<<(std::ostream& os, Card* c);
};
