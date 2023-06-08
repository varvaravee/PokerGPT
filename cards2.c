#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include "cards2.h"

CARD *NewCard(int CC, int Value)
{
    CARD *c;
    c = malloc(sizeof(CARD));
    if(!c)
    {
        perror("Out of Memory!\n");
        exit(10);
    }
    c->CC = CC;
    c->Value = Value;
    return c;
}

void MakeDeck(DECK D)
{
    int y = 1;
    for(int x = 0; x < 52; x++)
    {
        if(x<13)
        {
            CARD *c;
            c = NewCard(Club,y);
            D[x] = c;
        }
        else if(x<26)
        {
            CARD *c;
            c = NewCard(Spade,y);
            D[x] = c;
        }
        else if(x<39)
        {
            CARD *c;
            c = NewCard(Heart,y);
            D[x] = c;    
        }
        else
        {
            CARD *c;
            c = NewCard(Diamond,y);
            D[x] = c;
        }
        
        if(y < 13)
        {
            y++;
        }
        else
        {
            y = 1;
	}
    }
}

void ShuffleDeck(DECK D)
{
    srand(time(NULL));
    CARD *c;
    for (int i = 0; i < 52; i ++)
    {
        
        int newIndex = rand() % 52;
        c = D[i];
        D[i] = D[newIndex];
        D[newIndex] = c;
        
    }
}
int CardType(PlayerDECK P,int card){
	return P[card]->CC;
}
int CardValue(PlayerDECK P,int card){
	return P[card]->Value;
}
void PrintCardsValues(DECK D)
{
    for(int i = 0; i < 52; i++)
    {
        if(D[i] == NULL) continue;
        else printf("CardType:%d  Value:%d\n", D[i]->CC,D[i]->Value);
    }
}

void PrintPlayerCards(PlayerDECK P) //rint player hand
{
    for(int i = 0; i < 2; i++)
    {
        printf("CardType:%d Value:%d\n", P[i]->CC,P[i]->Value);
    }
}

void PrintHouseCards(HouseDECK H) //print common cards
{
    for (int i = 0; i < 5; i++)
    {
        if (!H[i]) continue;
        else printf("CardType:%d Value:%d\n", H[i]->CC,H[i]->Value);
    }
}

void Give2Cards(DECK D, DECK C, PlayerDECK P) //generates 2 cards from 2 decks for player hand and stores in P 
{
    int i = 0;
    for (int a = 0; a < 52; a++){
        if (D[a]==NULL){
            continue;
        }
        else{
            P[i] = D[a];
            D[a] = NULL;
            break;
        }
    }
    i++;
    for (int b = 0; b < 52; b++){
        if (C[b]==NULL){
            continue;
        }
        else{
            P[i] = C[b];
            C[b] = NULL;
            break;
        }
    } 
}

void HouseStarter(DECK D, DECK C, HouseDECK H)
{
    int i = 0;

    for (int a = 0; a < 52; a++){
        if (D[a]==NULL){
            continue;
        }
        else{
            H[i] = D[a];
            D[a] = NULL;
            break;
        }
    }
    i++;
    for (int b = 0; b < 52; b++){
        if (C[b]==NULL){
            continue;
        }
        else{
            H[i] = C[b];
            C[b] = NULL;
            break;
        }
    }
    i++;
    for (int j = 0; j < 52; j++){
        if (D[j]==NULL){
            continue;
        }
        else{
            H[i] = D[j];
            D[j] = NULL;
            break;
        }
    }
}

char enumtocharP(PlayerDECK P,int index){
    if(P[index]->CC == Club){
        return 'C';
    }
    else if(P[index]->CC == Spade){
        return 'S';
    }
    else if(P[index]->CC == Heart){
        return 'H';
    }
    else if(P[index]->CC == Diamond){
        return 'D';
    }
    else return 'Z';
}

char enumtocharH(HouseDECK P,int index){
    if(P[index]->CC == Club){
        return 'C';
    }
    else if(P[index]->CC == Spade){
        return 'S';
    }
    else if(P[index]->CC == Heart){
        return 'H';
    }
    else if(P[index]->CC == Diamond){
        return 'D';
    }
    else return 'Z';
}

char cardnumberP(PlayerDECK P, int index){
    if(P[index]->Value == 1) return 'A';
    else if (P[index]-> Value == 2) return '2';
    else if (P[index]-> Value == 3) return '3';
    else if (P[index]-> Value == 4) return '4';
    else if (P[index]-> Value == 5) return '5';
    else if (P[index]-> Value == 6) return '6';
    else if (P[index]-> Value == 7) return '7';
    else if (P[index]-> Value == 8) return '8';
    else if (P[index]-> Value == 9) return '9';
    else if (P[index]-> Value == 10) return 'X';
    else if (P[index]-> Value == 11) return 'J';
    else if (P[index]-> Value == 12) return 'Q';
    else if (P[index]-> Value == 13) return 'K';
    else return 'Z';
}

char cardnumberH( HouseDECK P, int index){
    if(P[index]->Value == 1) return 'A';
    else if (P[index]-> Value == 2) return '2';
    else if (P[index]-> Value == 3) return '3';
    else if (P[index]-> Value == 4) return '4';
    else if (P[index]-> Value == 5) return '5';
    else if (P[index]-> Value == 6) return '6';
    else if (P[index]-> Value == 7) return '7';
    else if (P[index]-> Value == 8) return '8';
    else if (P[index]-> Value == 9) return '9';
    else if (P[index]-> Value == 10) return 'X';
    else if (P[index]-> Value == 11) return 'J';
    else if (P[index]-> Value == 12) return 'Q';
    else if (P[index]-> Value == 13) return 'K';
    else return 'Z';
}

char *CardsHouse(HouseDECK H){ //converts the common cards into char array
    char house[20];
    char *s = house;
    int loc;
    for (int i = 0; i < 20; i++){
        house[i] = ' ';
    }
    //printf("for");
    if (H[0]){
        house[0] = enumtocharH(H,0);
        house[1] = cardnumberH(H,0);
        loc = 2;
    }
    //printf("0");
    if (H[1]){
        house[3] = enumtocharH(H,1);
        house[4] = cardnumberH(H,1);
        loc = 5;
    }
   // printf("1");
    if (H[2]){
        house[6] = enumtocharH(H,2);
        house[7] = cardnumberH(H,2);
        loc = 8;
    }
   // printf("2");
    if (H[3]){
        house[9] = enumtocharH(H,3);
        house[10] = cardnumberH(H,3);
        loc = 11;
    }
    //printf("3");
    if (H[4]){
        house[12] = enumtocharH(H,4);
        house[13] = cardnumberH(H,4);
        loc = 14;
    }
    //printf("4");
    house[loc] = '\000';
    return s;
}

char *CardsPlayer(PlayerDECK P){ // converts player hand into char array
    char player[20];
    char *s = player;
    int loc;
    for (int i = 0; i < 20; i++){
        player[i] = ' ';
    }
    
    if (P[0]){
        player[0] = enumtocharP(P,0);
        player[1] = cardnumberP(P,0);
        loc = 2;
    }
    if (P[1]){
        player[3] = enumtocharP(P,1);
        player[4] = cardnumberP(P,1);
        loc = 5;
    } 
    player[loc] = '\000';
    return s;
}

void StartCards(DECK D, DECK C, HouseDECK H)
{   
    MakeDeck(D);
    ShuffleDeck(D);
    MakeDeck(C);
    
    ShuffleDeck(C); 
    ShuffleDeck(C);
    
    HouseStarter(D,C,H);
}













