#include "Card.h"

void swap(int& a, int& b)
{
	int c = a;
	a = b;
	b = c;
}

void shuffleCards(int deck[])
{
	srand(time(NULL));
	
	int swapPos;

	for (int i = 0; i < 51; i++)
	{
		swapPos = rand() % 52;
		swap(deck[i], deck[swapPos]);
	}

}

void printCardsShuffling(int deck[], string cards[])
{
	for (int i = 0; i < 52; i++)
		cout << "(" << cards[deck[i]] << ")" << "\n";
}

void dealingForHand(int deck[], int hand[])
{
	for (int i = 0; i < 5; i++)
		hand[i] = deck[51 - i];
}

void printHand(int hand[], string cards[])
{
	for (int i = 0; i < 5; i++)
		cout << "(" << cards[hand[i]] << ")" << "\n";
}

int findSuit(string s, string suits[])
{
	string rank;
	int d = 0;

	d = s.find(',');

	for (int i = 0; i < d; i++)
		rank += s[i];

	for (int j = 0; j < 4; j++)
	{
		string test = suits[j];
		if (test.compare(rank) == 0)
			return j;
	}
}

int findFace(string s, string faces[])
{
	string rank;
	int d = 0;

	d = s.find(' ');

	for (int i = d; i < s.length(); i++)
		rank += s[i + 1];
	rank.pop_back();

	for (int j = 0; j < 13; j++)
	{
		string test = faces[j];
		if (test.compare(rank) == 0)
			return j;
	}
}

void arrOfRank(int a[], string cards[], string faces[], int hand[])
{
	for (int i = 0; i < 5; i++)
		a[i] = findFace(cards[hand[i]], faces);
}

void arrOfSuit(int a[], string cards[], string suits[], int hand[])
{
	for (int i = 0; i < 5; i++)
		a[i] = findSuit(cards[hand[i]], suits);
}

void sortHand(int a[])
{
	for (int i = 0; i < 4; i++)
		for (int j = i + 1; j < 5; j++)
			if (a[i] > a[j])
				swap(a[i], a[j]);
}

bool checkSameSuit(int suit[])
{
	if (suit[0] == suit[1] && suit[1] == suit[2] && suit[2] == suit[3] && suit[3] == suit[4])
		return 1;
	return 0;
}

bool checkSequentialRank(int rank[])
{
	int count = 0;
	sortHand(rank);
	if (rank[0] == 0 && rank[4] == 12)
	{
		rank[4] = -1;
		for (int j = 4; j > 0; j--)
			swap(rank[j], rank[j - 1]);
	}
	for (int k = 4; k > 0; k--)
		if (rank[k] - rank[k - 1] != 1)
			return 0;
		else count++;
	if (count == 4)
		return 1;
	return 0;
}

bool isFourOfAKind(card hand)
{
	if (!checkSameSuit(hand.suit))
	{
		int count;
		for (int i = 0; i < 2; i++)
		{
			count = 0;
			for (int j = i + 1; j < 5; j++)
			{
				if (hand.rank[i] == hand.rank[j])
					count++;
			}
			if (count == 3)
				return 1;
		}
	}
	return 0;
}

int isFullHouse(card hand)
{
	if (!checkSameSuit(hand.suit))
	{
		if (((hand.rank[0] == hand.rank[1]) && (hand.rank[1] == hand.rank[2]) && (hand.rank[2] != hand.rank[3]) && (hand.rank[3] == hand.rank[4])) || ((hand.rank[0] == hand.rank[1]) && (hand.rank[1] = hand.rank[2]) && (hand.rank[2] == hand.rank[3]) && (hand.rank[3] == hand.rank[4])))
			return 1;
	}
	return 0;
}

bool isStraightFlush(card hand)
{
	if (checkSameSuit(hand.suit) && checkSequentialRank(hand.rank))
		return 1;
	return 0;
}

bool isFlush(card hand)
{
	if (checkSameSuit(hand.suit) && !checkSequentialRank(hand.rank))
		return 1;
	return 0;
}

bool isStraight(card hand)
{
	if (!checkSameSuit(hand.suit) && checkSequentialRank(hand.rank))
		return 1;
	return 0;
}

bool isThreeOfAKind(card hand)
{
	int check = isFullHouse(hand);
	if (check == -1)
		return 1;
	return 0;
}

int countPairs(int a[])
{
	sortHand(a);
	int count = 0;
	for (int i = 0; i < 4; i++)
		if (a[i] == a[i + 1])
			count++;
	return count;
}

bool isTwoPairs(card hand)
{
	if(!isThreeOfAKind(hand) && !checkSameSuit(hand.suit))
	{
		if (countPairs(hand.rank) == 2)
			return 1;
	}
	return 0;
}

bool isPair(card hand)
{
	if (!checkSameSuit(hand.suit))
	{
		if (countPairs(hand.rank) == 1)
			return 1;
	}
	return 0;
}

int getHighestCard(card hand)
{
	if (!checkSameSuit(hand.suit) && !checkSequentialRank(hand.rank) && countPairs(hand.rank) == 0)
	{
		int max = hand.rank[0];
		for (int i = 1; i < 5; i++)
			if (max < hand.rank[i])
				max = hand.rank[i];
		return max;
	}
	return -1;
}

void dealingForHands(int deck[], card hand[], int player)
{
	int n = 51;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < player; j++)
		{
			hand[j].card[i] = deck[n - j];
		}
		n -= player;
	}
}

int getStatusOfHand(card hand)
{
	if (isStraightFlush(hand))
		return 8;
	if (isFourOfAKind(hand))
		return 7;
	if (isFullHouse(hand))
		return 6;
	if (isFlush(hand))
		return 5;
	if (isStraight(hand))
		return 4;
	if (isThreeOfAKind(hand))
		return 3;
	if (isTwoPairs(hand))
		return 2;
	if (isPair(hand))
		return 1;
	return 0;
}

void countDifferentElement(int a[], int n, int b[], int &x) 
{
	x = 1;
	b[0] = a[0];

	for (int i = 1; i < n; i++) 
	{
		int count = 0;
		for (int j = 0; j < x; j++) 
		{
			if (a[i] == b[j])
				count++;
		}
		if (count == 0) {
			b[x] = a[i];
			x++;
		}
	}
}

int rankingHands(card hand[], int player)
{
	int* status = new int[player];
	for (int a = 0; a < player; a++)
		status[a] = getStatusOfHand(hand[a]);
	int* ranks = new int[player];
	int totalRanks;

	countDifferentElement(status, player, ranks, totalRanks);

	if (ranks[totalRanks - 1] == 0) 
	{
		for (int k = 0; k < player; k++)
			status[k] = getHighestCard(hand[k]);

		countDifferentElement(status, player, ranks, totalRanks);

		for (int i = 0; i < totalRanks; i++)
		{
			for (int j = i + 1; j < totalRanks; j++)
				if (ranks[i] > ranks[j])
					swap(ranks[i], ranks[j]);
		}
	}

	for (int m = 0; m < totalRanks; m++)
	{
		for (int n = 0; n < player; n++)
		{
			if (status[n] == ranks[m])
				hand[n].rankOfPlayer = ranks[m];
		}
	}

	int highestRank = ranks[totalRanks - 1];
	delete[] ranks;
	delete[] status;

	return highestRank;
}

void evaluateHands(card hand[], int player)
{
	for (int i = 0; i < player; i++)
	{
		cout << "SCORES :" << endl;
		cout << "	PLayer " << i + 1 <<": " << hand[i].score << endl;
	}
	int max = hand[0].score;
	int count;
	for (int j = 1; j < player; j++)
	{
		count = 0;
		if (max < hand[j].score)
			max = hand[j].score;
		if (max == hand[j].score)
			count++;
	}
	if (count == (player - 1))
		cout << "TIE !" << endl;
	else
	{
		for (int k = 0; k < player; k++)
		{
			if (hand[k].score == max)
				cout << "Congratulations player " << k + 1 << " ! You are the WINNER !" << endl;
		}
	}
}