#include <algorithm>
#include <array>
#include <random>
#include <vector>

#include "card.cpp"

using namespace std;

class Deck {
public:
	Deck()
	{
		for (int i = 0; i <= 8; i++)
		{
			int suit = floor(i / 13);
			int value = i - (suit * 13) + 2;

			Card* card = new Card(static_cast<Face>(suit), value);
			this->cards.push_back(*card);
		}

		this->shuffle();
	}

	bool has_cards()
	{
		return !this->cards.empty();
	}

	int count()
	{
		return this->cards.size();
	}

	Card draw_card()
	{
		Card card = this->cards.back();
		this->cards.pop_back();

		return card;
	}

	void insert_card(Card card)
	{
		this->cards.insert(this->cards.begin(),card);
	}

private:
	vector<Card> cards;

	void shuffle()
	{
		random_device rd;
		mt19937 g(rd());

		::shuffle(this->cards.begin(), this->cards.end(), g);
	}
};