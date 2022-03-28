#include "Card.h"

int main()
{
	string suits[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };
	string faces[13] = { "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace" };

	int deck[52];
	string cards[52];
	int k = 0;
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cards[k] = suits[j] + ", " + faces[i];
			k++;
		}
	}

	for (int i = 0; i < 52; i++)
		deck[i] = i;
	
	while (true)
	{
		int choice, choice1, choice2;
		cout << "1. One-player game" << endl;
		cout << "2. N-player game" << endl;
		cout << "0. Quick game" << endl;
		cout << "Choose an option: ";
		cin >> choice;
		cout << endl;
		switch (choice)
		{
		case 1:
		{
			do
			{
				shuffleCards(deck);

				card hand;
				dealingForHand(deck, hand.card);
				cout << "  Your hand:" << endl;
				printHand(hand.card, cards);
				arrOfRank(hand.rank, cards, faces, hand.card);
				arrOfSuit(hand.suit, cards, suits, hand.card);
				cout << "Rank of your hand is: " << getStatusOfHand(hand) << endl;
				cout << endl;

				do
				{
					cout << "1. Play again" << endl;
					cout << "2. Return to menu" << endl;
					cout << "0. Quick game" << endl;
					cout << "Choose an option: ";
					cin >> choice1;
					cout << endl;

					if (choice1 == 0)
						return 0;
					if (choice1 > 2 || choice1 < 0)
					{
						cout << "Please choose again" << endl;
						choice1 = -1;
					}
				} while (choice1 == -1);
			} while (choice1 == 1);
		}
		break;
		case 2:
		{
			do
			{
				int n;
				cout << "Please input the number of players(maximum is 10): ";
				do
				{
					cin >> n;
					if (n > 10 || n < 2)
						cout << "Please input again: ";
				} while (n > 10);

				int s;
				cout << "Please input the number of games you want to play: ";
				do
				{
					cin >> s;
					if (s < 1)
						cout << "Please input again: ";
				} while (s < 1);

				card hand[10];
				if (s == 1)
				{
					shuffleCards(deck);
					dealingForHands(deck, hand, n);

					int* rankOfPlayer = new int[n];

					for (int i = 0; i < n; i++)
					{
						cout << "  PLayer " << i + 1 << " hand:" << endl;
						printHand(hand[i].card, cards);
						arrOfRank(hand[i].rank, cards, faces, hand[i].card);
						arrOfSuit(hand[i].suit, cards, suits, hand[i].card);
						rankOfPlayer[i] = getStatusOfHand(hand[i]);
						cout << "Rank of your hand is: " << rankOfPlayer[i] << endl;
					}
					int max = rankOfPlayer[0];
					int count;
					for (int j = 1; j < n; j++)
					{
						count = 0;
						if (max < rankOfPlayer[j])
							max = rankOfPlayer[j];
						if (max == rankOfPlayer[j])
							count++;
					}
					if (count == (n - 1))
						cout << "TIE !" << endl;
					else
					{
						for (int k = 0; k < n; k++)
						{
							if(rankOfPlayer[k] == max)
								cout << "Congratulations player " << k + 1 << " ! You are the WINNER !" << endl;
						}
					}
					delete[] rankOfPlayer;
				}
				else
				{
					int* highestRank = new int[s];

					for (int j = 0; j < s; j++)
					{
						shuffleCards(deck);
						dealingForHands(deck, hand, n);
						cout << "ROUND " << j + 1 << ":" << endl;

						for (int i = 0; i < n; i++)
						{
							cout << "  PLayer " << i + 1 << " hand:" << endl;
							printHand(hand[i].card, cards);
							arrOfRank(hand[i].rank, cards, faces, hand[i].card);
							arrOfSuit(hand[i].suit, cards, suits, hand[i].card);
							cout << "Rank of your hand is: " << getStatusOfHand(hand[i]) << endl;
						}

						highestRank[j] = rankingHands(hand, n);

						for (int k = 0; k < n; k++)
						{
							if (hand[k].rankOfPlayer == highestRank[j])
								hand[k].score++;
						}
						cout << endl;
					}

					evaluateHands(hand, n);
					cout << endl;

					delete[] highestRank;
				}
				
				do
				{
					cout << "1. Play again" << endl;
					cout << "2. Return to menu" << endl;
					cout << "0. Quick game" << endl;
					cout << "Choose an option: ";
					cin >> choice2;
					cout << endl;

					if (choice2 == 0)
						return 0;
					if (choice2 > 2 || choice2 < 0)
					{
						cout << "Please choose again" << endl;
						choice2 = -1;
					}
				} while (choice2 == -1);
			} while (choice2 == 1);
		}
		break;
		case 0:
		{
			cout << "You have quit the game" << endl;
			return 0;
		}
		default:
		{
			cout << "Please choose again" << endl;
		}
		break;
		}
	}
	return 0;
} 