#ifndef CARDS2_H
#define CARDS2_H

enum CarType{Club,Spade,Heart,Diamond};

typedef struct Card CARD;

typedef CARD *DECK[52];
typedef CARD *PlayerDECK[2];
typedef CARD *HouseDECK[5];

struct Card{
	int CC;
	int Value;
};

CARD *NewCard(int CC, int Value);

void MakeDeck(DECK D);

void ShuffleDeck(DECK D);

int CardType(PlayerDECK P,int card);

int CardValue(PlayerDECK P, int card);

void PrintCardsValues(DECK D);

void PrintPlayerCards(PlayerDECK P);

void PrintHouseCards(HouseDECK H);

void Give2Cards(DECK D, DECK C, PlayerDECK P);

void HouseStarter(DECK D, DECK C, HouseDECK H);

char enumtocharP(PlayerDECK P, int index);

char enumtocharH(HouseDECK P, int index);

char cardnumberP(PlayerDECK P, int index);

char cardnumberH(HouseDECK P, int index);

char *CardsHouse(HouseDECK H);

char *CardsPlayer(PlayerDECK P);

void StartCards(DECK D, DECK C, HouseDECK H);








#endif

