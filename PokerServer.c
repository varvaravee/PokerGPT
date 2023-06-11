/* PokerServer.c
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <assert.h>
#include "cards2.h"

/* #define DEBUG */	/* be verbose */

/*** global variables ****************************************************/

const char *Program	/* program name for descriptive diagnostics */ 
	= NULL;
int Shutdown		/* keep running until Shutdown == 1 */
	= 0;
char ComCards[10]= "";	/* current common cards in printable format */

//GAME INTS
const int SmallBlind=5;

const int BigBlind=10;

int Player1Bet=0;
int Player2Bet=0;
int Player3Bet=0;
int Player4Bet=0;
int Player5Bet=0;
int PlayerBet=0;

int P1Bank=1000;
int P2Bank=1000;
int P3Bank=1000;
int P4Bank=1000;
int P5Bank=1000;
int PlayerBank=0;
int pot=0;
int difference=0;
int startingBet=0;

int turn=0;
int cardsGiven=0;

int CurrentBet=0;
//number of players
int NumPlayers=0;

//initialize data structures for cards2.c and cards2.h
 DECK D;
 DECK C;
 HouseDECK H;
 PlayerDECK P1,P2,P3,P4,P5;



/*** global functions ****************************************************/


void FatalError(		/* print error diagnostics and abort */
	const char *ErrorMsg)
{
    fputs(Program, stderr);
    fputs(": ", stderr);
    perror(ErrorMsg);
    fputs(Program, stderr);
    fputs(": Exiting!\n", stderr);
    exit(20);
} /* end of FatalError */

int MakeServerSocket(		/* create a socket on this server */
	uint16_t PortNo)
{
	//generate decks
	StartCards(D, C, H);
	//generate house cards
	HouseStarter(D, C, H);

   
    int ServSocketFD;
    struct sockaddr_in ServSocketName;

    /* create the socket */
    ServSocketFD = socket(PF_INET, SOCK_STREAM, 0);
    if (ServSocketFD < 0)
    {   FatalError("service socket creation failed");
    }
    /* bind the socket to this server */
    ServSocketName.sin_family = AF_INET;
    ServSocketName.sin_port = htons(PortNo);
    ServSocketName.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(ServSocketFD, (struct sockaddr*)&ServSocketName,
		sizeof(ServSocketName)) < 0)
    {   FatalError("binding the server to a socket failed");
    }
    /* start listening to this socket */
    if (listen(ServSocketFD, 5) < 0)	/* max 5 clients in backlog */
    {   FatalError("listening on socket failed");
    }
    return ServSocketFD;
} /* end of MakeServerSocket */

void DisplayHouseCards()	/*  print/update current common cards array */
{
	printf("\rHouse Cards: %s", CardsHouse(H)); //prints house cards on server
	
	fflush(stdout);

} /* end of DisplayComCards */

void DisplayTurn()//display turn
{
	printf("|Turn: %d", turn); //prints current players bet on server
	
	fflush(stdout);

}


void DisplayPlayer1Bet() //display player's bet
{
	
	printf("|P1 Bet: %d", Player1Bet); //prints current players bet on server
	
	fflush(stdout);
}
void DisplayPlayer2Bet() //display player's bet
{
	
	printf("|P2 Bet: %d", Player2Bet); //prints current players bet on server
	
	fflush(stdout);
}
void DisplayPlayer3Bet() //display player's bet
{
	
	printf("|P3 Bet: %d", Player3Bet); //prints current players bet on server
	
	fflush(stdout);
}

void DisplayPlayer4Bet() //display player's bet
{
	
	printf("|P4 Bet: %d", Player4Bet); //prints current players bet on server
	
	fflush(stdout);
}
void DisplayPlayer5Bet() //display player's bet
{
	
	printf("|P5 Bet: %d", Player5Bet); //prints current players bet on server
	
	fflush(stdout);
}


//void DisplayPlayerHand() //display player hand
//{
//	printf(" | Player's Hand: %s", CardsPlayer(P));//print current player's hand on server
//	fflush(stdout);
//}


void ProcessRequest(		/* process a request by a client */
	int DataSocketFD)
{

    int  l, n;
    char RecvBuf[256];	/* message buffer for receiving a message */
    char SendBuf[256];	/* message buffer for sending a response */
    char ClientOutput[100];

    memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
    memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
    memset(ClientOutput,0,sizeof(ClientOutput)); //clear client output

    n = read(DataSocketFD, RecvBuf, sizeof(RecvBuf)-1);
    if (n < 0) 
    {   FatalError("reading from data socket failed");
    }
    RecvBuf[n] = 0;
#ifdef DEBUG
    printf("%s: Received message: %s\n", Program, RecvBuf);
#endif
    //handles different client requests and updates SendBuf with needed info from server
    if (0 == strcmp(RecvBuf, "POKER"))
    {   
	NumPlayers+=1;
	//char *placeholderP="";
	
	if(NumPlayers==1)
	{
		Player1Bet=SmallBlind;
		P1Bank-=Player1Bet;
		PlayerBank=P1Bank;
		PlayerBet=Player1Bet;
		CurrentBet=Player1Bet;
		Give2Cards(D, C, P1);
		//placeholderP=CardsPlayer(P1); //char ptr that holds player hand

	}
	else if (NumPlayers==2)
	{
		Player2Bet=SmallBlind;
		P2Bank-=Player2Bet;
		PlayerBank=P2Bank;
		PlayerBet=Player2Bet;
		CurrentBet=Player2Bet;
		Give2Cards(D, C, P2);
		//placeholderP=CardsPlayer(P2); //char ptr that holds player hand

	}
	else if (NumPlayers==3)
	{
		Player3Bet=SmallBlind;
		P3Bank-=Player3Bet;
		PlayerBank=P3Bank;
		PlayerBet=Player3Bet;
		CurrentBet=Player3Bet;
		Give2Cards(D, C, P3);
		//placeholderP=CardsPlayer(P3); //char ptr that holds player hand

	}
	else if (NumPlayers==4)
	{
		Player4Bet=SmallBlind;
		P4Bank-=Player4Bet;
		PlayerBank=P4Bank;
		PlayerBet=Player4Bet;
		CurrentBet=Player4Bet;
		Give2Cards(D, C, P4);
		//placeholderP=CardsPlayer(P4); //char ptr that holds player hand

	}
	else if (NumPlayers==5)
	{
		Player5Bet=SmallBlind;
		P5Bank-=Player5Bet;
		PlayerBank=P5Bank;
		PlayerBet=Player5Bet;
		CurrentBet=Player5Bet;
		Give2Cards(D, C, P5);
		//placeholderP=CardsPlayer(P5); //char ptr that holds player hand

	}

	fflush(stdout);
	
	
	char sPlayerBet[10]; //creates char array to hold player bet
	memset(sPlayerBet,0,sizeof(sPlayerBet));

	sprintf(sPlayerBet, "%d", PlayerBet); //converts int bet to char array bet

	
	//char ClientOutput[100]; //placeholder var to hold output to client
	//char *placeholderP=CardsPlayer(P); //char ptr that holds player hand
	//strcpy(ClientOutput,placeholderP); //copies char of player hand to array
	
	if (turn == 0)
		turn+=1;

	//strcat(ClientOutput," | "); //separates turn from player bet
	strcat(ClientOutput,sPlayerBet); //concatenates common cards and player bet to one char array
	

	//sends player's hand and player bet concat. array to client
	strncpy(SendBuf, "\nPlayer's Bet:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	printf("%s\n",ClientOutput);
	


    }	
    else if (0 == strcmp(RecvBuf, "PHAND"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	char *placeholderP1=CardsPlayer(P1);//char ptr that holds the house cards
	char *placeholderP2=CardsPlayer(P2);//char ptr that holds the house cards
	char *placeholderP3=CardsPlayer(P3);//char ptr that holds the house cards
	char *placeholderP4=CardsPlayer(P4);//char ptr that holds the house cards
	char *placeholderP5=CardsPlayer(P5);//char ptr that holds the house cards
	if (NumPlayers==1)
	{	
	   
	    strcat(ClientOutput,placeholderP1); //copies char of housecards to output array  
	}
	else if (NumPlayers==2)
	{	
	   
	    strcat(ClientOutput,placeholderP2); //copies char of housecards to output array  
	}
	else if (NumPlayers==3)
	{	
	    
	    strcat(ClientOutput,placeholderP3); //copies char of housecards to output array  
	}
	else if (NumPlayers==4)
	{	
	    
	    strcat(ClientOutput,placeholderP4); //copies char of housecards to output array  
	}
	else if (NumPlayers==5)
	{	
	    
	    strcat(ClientOutput,placeholderP5); //copies char of housecards to output array  
	}
	//sends common cards array to client
	strncpy(SendBuf, "\nPlayer's Hand:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));    
	    
	    
	    
    }
    else if (0 == strcmp(RecvBuf, "HCARDS"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char *placeholderH=CardsHouse(H);//char ptr that holds the house cards 
	strcat(ClientOutput,placeholderH); //copies char of housecards to output array  
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nHouse Cards:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));

    }
	
    else if (0 == strcmp(RecvBuf, "TURN"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sTurn[10];//char ptr that holds the house cards 
	sprintf(sTurn, "%d", turn); //copies char of housecards to output array  
	strcat(ClientOutput,sTurn);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nCurrent Turn:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));


    }
	
    else if (0 == strcmp(RecvBuf, "PNUM"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sNumPlayers[10];//char ptr that holds the house cards 
	sprintf(sNumPlayers, "%d", NumPlayers); //copies char of housecards to output array  
	strcat(ClientOutput,sNumPlayers);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nNumber of Players:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));


    }
    else if (0 == strcmp(RecvBuf, "POT"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	pot=Player1Bet+Player2Bet+Player3Bet+Player4Bet+Player5Bet;
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sPot[10];//char ptr that holds the house cards 
	sprintf(sPot, "%d", pot); //copies char of housecards to output array  
	strcat(ClientOutput,sPot);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nCurrent Pot:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));

    }
	
	
	
    //SENDS PLAYER'S BANKS TO CLIENTS
    else if (0 == strcmp(RecvBuf, "1BANK"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sP1Bank[10];//char ptr that holds the house cards 
	sprintf(sP1Bank, "%d", P1Bank); //copies char of housecards to output array  
	strcat(ClientOutput,sP1Bank);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nPlayer1's Bank:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	
    }
    else if (0 == strcmp(RecvBuf, "2BANK"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sP2Bank[10];//char ptr that holds the house cards 
	sprintf(sP2Bank, "%d", P2Bank); //copies char of housecards to output array  
	strcat(ClientOutput,sP2Bank);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nPlayer2's Bank:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	

    }
    else if (0 == strcmp(RecvBuf, "3BANK"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sP3Bank[10];//char ptr that holds the house cards 
	sprintf(sP3Bank, "%d", P3Bank); //copies char of housecards to output array  
	strcat(ClientOutput,sP3Bank);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nPlayer3's Bank:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	
    }
    else if (0 == strcmp(RecvBuf, "4BANK"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sP4Bank[10];//char ptr that holds the house cards 
	sprintf(sP4Bank, "%d", P4Bank); //copies char of housecards to output array  
	strcat(ClientOutput,sP4Bank);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nPlayer4's Bank:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	

    }
    else if (0 == strcmp(RecvBuf, "5BANK"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sP5Bank[10];//char ptr that holds the house cards 
	sprintf(sP5Bank, "%d", P5Bank); //copies char of housecards to output array  
	strcat(ClientOutput,sP5Bank);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nPlayer5's Bank:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	

    }
	
	
	
    //SENDS BETS TO CLIENT
    else if (0 == strcmp(RecvBuf, "1BET"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sPlayer1Bet[10];//char ptr that holds the house cards 
	
	sprintf(sPlayer1Bet, "%d", Player1Bet); //copies char of housecards to output array  
	strcat(ClientOutput,sPlayer1Bet);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nPlayer1's Bet:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	

    }
    else if (0 == strcmp(RecvBuf, "2BET"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sPlayer2Bet[10];//char ptr that holds the house cards 
	sprintf(sPlayer2Bet, "%d", Player2Bet); //copies char of housecards to output array  
	strcat(ClientOutput,sPlayer2Bet);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nPlayer2's Bet:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	

    }
    else if (0 == strcmp(RecvBuf, "3BET"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sPlayer3Bet[10];//char ptr that holds the house cards 
	sprintf(sPlayer3Bet, "%d", Player3Bet); //copies char of housecards to output array  
	strcat(ClientOutput,sPlayer3Bet);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nPlayer3's Bet:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	

    }	
    else if (0 == strcmp(RecvBuf, "4BET"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sPlayer4Bet[10];//char ptr that holds the house cards 
	sprintf(sPlayer4Bet, "%d", Player4Bet); //copies char of housecards to output array  
	strcat(ClientOutput,sPlayer4Bet);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nPlayer4's Bet:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	

    }
    else if (0 == strcmp(RecvBuf, "5BET"))
    {
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	//char ClientOutput[100]; //placeholder var to hold output to client
	char sPlayer5Bet[10];//char ptr that holds the house cards 
	sprintf(sPlayer5Bet, "%d", Player5Bet); //copies char of housecards to output array  
	strcat(ClientOutput,sPlayer5Bet);
	    
	//sends common cards array to client
	strncpy(SendBuf, "\nPlayer5's Bet:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	

    }
//END OF BETS TO CLIENT
	
	
	
	
    else if (0 == strcmp(RecvBuf, "SHUTDOWN"))
    {   PlayerBet=0;
	Shutdown = 1;
	strncpy(SendBuf, "OK SHUTDOWN", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
    }
	
    else if (0 == strcmp(RecvBuf, "CALL"))
    {
	if (turn==1)
	{
		difference=CurrentBet-Player1Bet;
		Player1Bet=CurrentBet;
		P1Bank-=difference;
		PlayerBank=P1Bank;
		PlayerBet=Player1Bet;
	}
	else if (turn==2)
	{
		difference=CurrentBet-Player2Bet;
		Player2Bet=CurrentBet;
		P2Bank-=difference;
		PlayerBank=P2Bank;
		PlayerBet=Player2Bet;
	}
	else if (turn==3)
	{
		difference=CurrentBet-Player3Bet;
		Player3Bet=CurrentBet;
		P3Bank-=difference;
		PlayerBank=P3Bank;
		PlayerBet=Player3Bet;
	}
	else if (turn==4)
	{
		difference=CurrentBet-Player4Bet;
		Player4Bet=CurrentBet;
		P4Bank-=difference;
		PlayerBank=P4Bank;
		PlayerBet=Player4Bet;
	}
	else
	{
		difference=CurrentBet-Player5Bet;
		Player5Bet=CurrentBet;
		P5Bank-=difference;
		PlayerBank=P5Bank;
		PlayerBet=Player5Bet;
	}
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	char sPlayerBet[10]; //creates char array to hold player bet
	memset(sPlayerBet,0,sizeof(sPlayerBet));
	sprintf(sPlayerBet, "%d", PlayerBet); //converts int bet to char array bet
	//char ClientOutput[100]; //placeholder var to hold output to client


	//control turn 
	if (turn==NumPlayers)
	{	
		Give1CardtoHouse(D, C, H);
		cardsGiven+=1; //update cards given var
		turn=1;
	}
	else 
		turn+=1;

	
	strcat(ClientOutput,sPlayerBet); //concatenates player bet into client output
	strncpy(SendBuf, "\nPlayer's Bet:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer



    }
    else if (0 == strcmp(RecvBuf, "ALLIN"))
    {
	if (turn==1)
	{
		Player1Bet+=P1Bank;
		P1Bank=0;
		PlayerBank=P1Bank;
		PlayerBet=Player1Bet;
	}
	else if (turn==2)
	{
		Player2Bet+=P2Bank;
		P2Bank=0;
		PlayerBank=P2Bank;
		PlayerBet=Player2Bet;
	}
	else if (turn==3)
	{
		Player3Bet+=P3Bank;
		P3Bank=0;
		PlayerBank=P3Bank;
		PlayerBet=Player3Bet;
	}
	else if (turn==4)
	{
		Player4Bet+=P4Bank;
		P4Bank=0;
		PlayerBank=P4Bank;
		PlayerBet=Player4Bet;
	}
	else
	{
		Player5Bet+=P5Bank;
		P5Bank=0;
		PlayerBank=P5Bank;
		PlayerBet=Player5Bet;

	}
	
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer

	char sPlayerBet[10]; //creates char array to hold player bet
	memset(sPlayerBet,0,sizeof(sPlayerBet));
	sprintf(sPlayerBet, "%d", PlayerBet); //converts int bet to char array bet
	//char ClientOutput[100]; //placeholder var to hold output to client

	//control turn 
	if (turn==NumPlayers)
	{
		Give1CardtoHouse(D, C, H);
		cardsGiven+=1; //update cards given var
		turn=1;
	}
	else 
		turn+=1;

	strcat(ClientOutput,sPlayerBet); //concatenates common cards and player bet to one char array
	//sends player bet concat. array to client
	strncpy(SendBuf, "\nPlayer's Bet:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer



    }


    else if (0 == strcmp(RecvBuf, "RAISE"))
    {
	if (turn==1)
	{
		startingBet=Player1Bet;
		Player1Bet+=10;
		difference=Player1Bet-startingBet;
		P1Bank-=difference;
		PlayerBank=P1Bank;
		PlayerBet=Player1Bet;
	}
	else if (turn==2)
	{
		startingBet=Player2Bet;
		Player2Bet+=10;
		difference=Player2Bet-startingBet;
		P2Bank-=difference;
		PlayerBank=P2Bank;	
		PlayerBet=Player2Bet;
	}
	else if (turn==3)
	{
		startingBet=Player3Bet;
		Player3Bet+=10;
		difference=Player3Bet-startingBet;
		P3Bank-=difference;
		PlayerBank=P3Bank;
		PlayerBet=Player3Bet;
	}
	else if (turn==4)
	{
		startingBet=Player4Bet;
		Player4Bet+=10;
		difference=Player4Bet-startingBet;
		P4Bank-=difference;
		PlayerBank=P4Bank;
		PlayerBet=Player4Bet;
	}
	else
	{
		startingBet=Player5Bet;
		Player5Bet+=10;
		difference=Player5Bet-startingBet;
		P1Bank-=difference;
		PlayerBank=P5Bank;
		PlayerBet=Player5Bet;
	}
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	CurrentBet=PlayerBet;
	char sPlayerBet[10]; //creates char array to hold player bet
	memset(sPlayerBet,0,sizeof(sPlayerBet));
	sprintf(sPlayerBet, "%d", PlayerBet); //converts int bet to char array bet
	//char ClientOutput[100]; //placeholder var to hold output to client
	

	//control turn 
	if (turn==NumPlayers)
	{
		Give1CardtoHouse(D, C, H);
		cardsGiven+=1; //update cards given var
		turn=1;
	}
	else 
		turn+=1;

	strcat(ClientOutput,sPlayerBet); //concatenates common cards and player bet to one char array
	strncpy(SendBuf, "\nPlayer's Bet:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer

	


    }
    else if (0 == strcmp(RecvBuf, "CHECK"))
    {

	if (turn==1)
	{
		difference=CurrentBet-Player1Bet;
		Player1Bet=CurrentBet;
		P1Bank-=difference;
		PlayerBank=P1Bank;
		PlayerBet=Player1Bet;
	}
	else if (turn==2)
	{
		difference=CurrentBet-Player2Bet;
		Player2Bet=CurrentBet;
		P2Bank-=difference;
		PlayerBank=P2Bank;
		PlayerBet=Player2Bet;
	}
	else if (turn==3)
	{
		difference=CurrentBet-Player3Bet;
		Player3Bet=CurrentBet;
		P3Bank-=difference;
		PlayerBank=P3Bank;
		PlayerBet=Player3Bet;
	}
	else if (turn==4)
	{
		difference=CurrentBet-Player4Bet;
		Player4Bet=CurrentBet;
		P4Bank-=difference;
		PlayerBank=P4Bank;
		PlayerBet=Player4Bet;
	}
	else
	{
		difference=CurrentBet-Player5Bet;
		Player5Bet=CurrentBet;
		P5Bank-=difference;
		PlayerBank=P5Bank;
		PlayerBet=Player5Bet;
	}
	memset(SendBuf,0,sizeof(SendBuf)); //clear send buffer
	char sPlayerBet[10]; //creates char array to hold player bet
	memset(sPlayerBet,0,sizeof(sPlayerBet));
	sprintf(sPlayerBet, "%d", PlayerBet); //converts int bet to char array bet
	//char ClientOutput[100]; //placeholder var to hold output to client

	//control turn 
	if (turn==NumPlayers)
	{
		Give1CardtoHouse(D, C, H);
		cardsGiven+=1; //update cards given var
		turn=1;
	}
	else 
		turn+=1;

	strcat(ClientOutput,sPlayerBet); //concatenates common cards and player bet to one char array
	//sends common cards and player bet concat. array to client
	strncpy(SendBuf, "\nPlayer's Bet:  \n", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, ClientOutput, sizeof(SendBuf)-1-strlen(SendBuf));
	//memset(SendBuf,0,sizeof(RecvBuf)); //clear send buffer



    }
    else
    {   strncpy(SendBuf, "ERROR unknown command ", sizeof(SendBuf)-1);
	SendBuf[sizeof(SendBuf)-1] = 0;
	strncat(SendBuf, RecvBuf, sizeof(SendBuf)-1-strlen(SendBuf));
    }
   
    l = strlen(SendBuf);
#ifdef DEBUG
    printf("%s: Sending response: %s.\n", Program, SendBuf);
#endif
    n = write(DataSocketFD, SendBuf, l);
   
    if (n < 0)
    {   FatalError("writing to data socket failed");
    }
} /* end of ProcessRequest */

void ServerMainLoop(		/* simple server main loop */
	int ServSocketFD,		/* server socket to wait on */
	int Timeout)			/* timeout in micro seconds */
{
   	

    int DataSocketFD;	/* socket for a new client */
    socklen_t ClientLen;
    struct sockaddr_in
	ClientAddress;	/* client address we connect with */
    fd_set ActiveFDs;	/* socket file descriptors to select from */
    fd_set ReadFDs;	/* socket file descriptors ready to read from */
    struct timeval TimeVal;
    int res, i;


    FD_ZERO(&ActiveFDs);		/* set of active sockets */
    FD_SET(ServSocketFD, &ActiveFDs);	/* server socket is active */
    while(!Shutdown)
    {   ReadFDs = ActiveFDs;
	TimeVal.tv_sec  = Timeout / 1000000;	/* seconds */
	TimeVal.tv_usec = Timeout % 1000000;	/* microseconds */
	/* block until input arrives on active sockets or until timeout */
	res = select(FD_SETSIZE, &ReadFDs, NULL, NULL, &TimeVal);
	if (res < 0)
	{   FatalError("wait for input or timeout (select) failed");
	}
	if (res == 0)	/* timeout occurred */
	{
#ifdef DEBUG
	    printf("%s: Handling timeout...\n", Program);
#endif
	 
	  DisplayHouseCards();
	  DisplayTurn();
	  DisplayPlayer1Bet();
	  DisplayPlayer2Bet();
	  DisplayPlayer3Bet();
	  DisplayPlayer4Bet();
	  DisplayPlayer5Bet();
	  
	
	}
	else		/* some FDs have data ready to read */
	{   for(i=0; i<FD_SETSIZE; i++)
	    {   if (FD_ISSET(i, &ReadFDs))
		{   if (i == ServSocketFD)
		    {	/* connection request on server socket */
#ifdef DEBUG
			printf("%s: Accepting new client %d...\n", Program, i);
#endif
			ClientLen = sizeof(ClientAddress);
			DataSocketFD = accept(ServSocketFD,
				(struct sockaddr*)&ClientAddress, &ClientLen);
			if (DataSocketFD < 0)
			{   FatalError("data socket creation (accept) failed");
			}
#ifdef DEBUG
			printf("%s: Client %d connected from %s:%hu.\n",
				Program, i,
				inet_ntoa(ClientAddress.sin_addr),
				ntohs(ClientAddress.sin_port));
#endif
			FD_SET(DataSocketFD, &ActiveFDs);
		    }
		    else
		    {   /* active communication with a client */
#ifdef DEBUG
			printf("%s: Dealing with client %d...\n", Program, i);
#endif
			ProcessRequest(i);

		    }
		}
	    }
	}
    }
} /* end of ServerMainLoop */

/*** main function *******************************************************/

int main(int argc, char *argv[])
{
    int ServSocketFD;	/* socket file descriptor for service */
    int PortNo;		/* port number */

    Program = argv[0];	/* publish program name (for diagnostics) */
#ifdef DEBUG
    printf("%s: Starting...\n", Program);
#endif
    if (argc < 2)
    {   fprintf(stderr, "Usage: %s port\n", Program);
	exit(10);
    }
    PortNo = atoi(argv[1]);	/* get the port number */
    if (PortNo <= 2000)
    {   fprintf(stderr, "%s: invalid port number %d, should be >2000\n",
		Program, PortNo);
        exit(10);
    }
#ifdef DEBUG
    printf("%s: Creating the server socket...\n", Program);
#endif
    ServSocketFD = MakeServerSocket(PortNo);
    printf("%s: Serving poker at port %d...\n", Program, PortNo);

    ServerMainLoop(ServSocketFD, 250000);
    printf("\n%s: Shutting down.\n", Program);
    close(ServSocketFD);
    return 0;
}

/* EOF PokerServer.c */
