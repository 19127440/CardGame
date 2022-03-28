#ifndef _CARD_H_
#define _CARD_H_
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

struct card
{
	int card[5];
	int rank[5];
	int suit[5];
	int rankOfPlayer;
	int score = 0;
};

void swap(int& a, int& b);
//1a
void shuffleCards(int deck[]);
//1b
void printCardsShuffling(int deck[], string cards[]);
//2a
void dealingForHand(int deck[], int hand[]);
//2b
void printHand(int hand[], string cards[]);
int findSuit(string s, string suits[]);
int findFace(string s, string faces[]);
void arrOfRank(int a[], string cards[], string faces[], int hand[]);
void arrOfSuit(int a[], string cards[], string suits[], int hand[]);
void sortHand(int a[]);
bool checkSameSuit(int suit[]);
bool checkSequentialRank(int rank[]);
//2d
bool isFourOfAKind(card hand);
//2e
int isFullHouse(card hand);
//2h
bool isStraightFlush(card hand);
//2f
bool isFlush(card hand);
//2g
bool isStraight(card hand);
//2i
bool isThreeOfAKind(card hand);
int countPairs(int a[]);
//2j
bool isTwoPairs(card hand);
//2k
bool isPair(card hand);
//2l
int getHighestCard(card hand);
//3a
void dealingForHands(int deck[], card hand[], int player);
//3b
int getStatusOfHand(card hand);
void countDifferentElement(int a[], int n, int b[], int& x);
//3c
int rankingHands(card hand[], int player);
//3d
void evaluateHands(card hand[], int player);
#endif
