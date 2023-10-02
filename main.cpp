#include <iostream>
#include <cmath>
#include <string>
#include <ncurses.h>
#include <chrono>
#include <thread>
#include <exception>

#include "deck.cpp"

using namespace std;

void handle_game_over(Deck& player_deck, Deck& cpu_deck)
{
	clear();
	refresh();

	if (!player_deck.has_cards())
	{
		mvprintw(4,2, "You are the loser, tough luck.");
	}
	else
	{
		mvprintw(4,2, "You are the winner, great job mashing that spacebar!");
	}

	refresh();
	getch();
}

bool draw_cards(Deck& player_deck, Deck& cpu_deck, bool is_tie = false)
{
	clear();
	refresh();

	Card player_card = player_deck.draw_card();
	Card cpu_card = cpu_deck.draw_card();

	mvprintw(4,2, ("Your deck: " + to_string(player_deck.count()) + " cards").c_str());

	try
	{
		player_card.draw_back(2,5);
		player_card.draw_back(4,5);
		player_card.draw_back(6,5);

		cpu_card.draw_back(31,25);
		cpu_card.draw_back(29,25);
		cpu_card.draw_back(27,25);		
	}
	catch (const std::exception& ex)
	{
		handle_game_over(player_deck, cpu_deck);
	}

	mvprintw(37,25, ("CPU deck: " + to_string(cpu_deck.count()) + " cards").c_str());

	try
	{
		player_card.draw_back(8,5);
		cpu_card.draw_back(25,25);	
	}
	catch (const std::exception& ex)
	{
		handle_game_over(player_deck, cpu_deck);
	}

	refresh();

	std::this_thread::sleep_for(std::chrono::milliseconds(300));

	if (is_tie)
	{
		try
		{
			player_card.draw_back(30,5);
			player_card.draw_back(32,5);
			player_card.draw_back(34,5);	
		}
		catch (const std::exception& ex)
		{
			handle_game_over(player_deck, cpu_deck);
		}
		
	}
	
	try
	{
		player_card.draw_front(8,5);
		cpu_card.draw_front(25,25);
	}
	catch (const std::exception& ex)
	{
		handle_game_over(player_deck, cpu_deck);
	}


	refresh();

	bool won = player_card > cpu_card;

	if (player_card == cpu_card)
	{
		// Handle draw
		vector<Card> on_hand = { player_deck.draw_card(), player_deck.draw_card(), player_deck.draw_card(), cpu_deck.draw_card(), cpu_deck.draw_card(), cpu_deck.draw_card() };

		mvprintw(20, 12, "Tie!");
		mvprintw(22, 12, "Press a key to draw continue...");
		getch();

		if (draw_cards(player_deck, cpu_deck, true))
		{
			// Player won draw
			won = true;

			for (std::vector<Card>::iterator i = on_hand.begin(); i != on_hand.end(); ++i)
			{
				player_deck.insert_card(*i);
			}
		}
		else
		{
			// CPU won draw
			won = false;

			for (std::vector<Card>::iterator i = on_hand.begin(); i != on_hand.end(); ++i)
			{
				cpu_deck.insert_card(*i);
			}
		}
	}
	
	if (won)
	{
		// Player won
		player_deck.insert_card(player_card);
		player_deck.insert_card(cpu_card);

		if (is_tie)
		{
			mvprintw(18, 12, "You won the tie!");	
		}
		else
		{
			mvprintw(20, 12, "You won!");	
		}
	}
	else
	{
		// Player lost
		cpu_deck.insert_card(cpu_card);
		cpu_deck.insert_card(player_card);

		if (is_tie)
		{
			mvprintw(18, 12, "You lost the tie!");
		}
		else
		{
			mvprintw(20, 12, "You lost!");	
		}
	}

	mvprintw(22, 12, "Press a key to draw again...");

	refresh();
	getch();

	return won;
}

void game_loop()
{
	Deck player_deck;
	Deck cpu_deck;

	clear();
	refresh();
	mvprintw(23, 20, "Press any key to draw!");
	getch();

	while (player_deck.has_cards() && cpu_deck.has_cards())
	{
		try
		{
			draw_cards(player_deck, cpu_deck);
		}
		catch (const std::exception& ex)
		{
			handle_game_over(player_deck, cpu_deck);
		}
	}
}

void title_screen()
{
	clear();
	Card* card = new Card(Heart, 14);
	card->draw_back(10,10);
	card->draw_front(30,10);
	card->draw_front(10,25);
	card->draw_back(30,25);

	mvprintw(23, 20, "WAR! By Alex White");
	mvprintw(24, 18, "Press any key to start.");

	refresh();
	getch();

	game_loop();
}

int main(int argc, char const *argv[])
{
	initscr();
	
	title_screen();

	endwin();

	return 0;
}

