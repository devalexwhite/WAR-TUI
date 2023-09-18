#include <string>

using namespace std;

enum Face {
	Heart,
	Spade,
	Club,
	Diamond,
};

class Card {
public:
	Card() {}

	Card(Face face, int value)
	{
		this->face = face;
		this->value = value;
	}

	int operator >(Card b)
	{
		return this->value > b.value;
	}

	int operator <(Card b)
	{
		return this->value < b.value;
	}

	int operator ==(Card b)
	{
		return this->value == b.value;
	}

	int operator >=(Card b)
	{
		return this->value >= b.value;
	}

	int operator  <=(Card b)
	{
		return this->value <= b.value;
	}

	string label()
	{
		string label = this->get_value_string();
		label += " of " + this->get_face_string();

		return label;
	}

	void draw_front(int x, int y)
	{
		WINDOW *win = newwin(12, 15, y, x);
		refresh();
		box(win, 0, 0);

		mvwprintw(win, 1, 1, this->get_value_string().c_str());
		mvwprintw(win, 10, 14 - this->get_value_string().length(), this->get_value_string().c_str());
		mvwprintw(win, 6, 8 - floor(this->get_face_string().length()/2), this->get_face_string().c_str());

		wrefresh(win);
	}

	void draw_back(int x, int y)
	{
		WINDOW *win = newwin(12, 15, y, x);
		refresh();
		box(win, 0, 0);

		for (int x = 1; x < 14; ++x)
		{
			for (int y = 1; y < 11; ++y) {
				if (x % 2 == 0)
				{
					mvwprintw(win, y, x, "X");
				}
			}
		}

		wrefresh(win);
	}
private:
	Face face;
	int value;

	string get_face_string()
	{
		string label;
		if (this->face == Heart) label = "Hearts";
		else if (this->face == Spade) label = "Spades";
		else if (this->face == Club) label = "Clubs";
		else if (this->face == Diamond) label = "Diamonds";

		return label;
	}

	string get_value_string()
	{
		string value;
		if (this->value == 14) value = "Ace";
		else if (this->value == 13) value = "King";
		else if (this->value == 12) value = "Queen";
		else if (this->value == 11) value = "Jack";
		else value = to_string(this->value);

		return value;
	}
};