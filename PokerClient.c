#include <stdio.h>
#include <gtk/gtk.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>

char SendBuf[256];	/* message buffer for sending a message */
//variables to hold rec buffer message
int length;
/*
*/
//main menu user input button functions 
void varGame()
{
	char *var="POKER";
	strncpy(SendBuf,var,10);
}
void varBye() //closing client
{
	char *var="BYE";
	strncpy(SendBuf,var,10);
}
void varShut() //closing server
{
	char *var="SHUTDOWN";
	strncpy(SendBuf,var,10);
}
//void varGarbage() //send buff test 
//{
//	char *var="GARBAGE";
//	strncpy(SendBuf,var,10);
//}
//turn menu button functions
void varCall()
{
	char *var="CALL";
	strncpy(SendBuf,var,10);
}
void varRaise()
{
	char *var="RAISE";
	strncpy(SendBuf,var,10);
}
void varCheck()
{
	char *var="CHECK";
	strncpy(SendBuf,var,10);
}
void varFold()
{
	char *var="FOLD";
	strncpy(SendBuf,var,10);
}
void varAllin()
{
	char *var="ALLIN";
	strncpy(SendBuf,var,10);
}


//additional info sent to client
void varTurn()
{
	char *var="TURN";
	strncpy(SendBuf,var,10);
}

void varHouseCards()
{
	char *var="HCARDS";
	strncpy(SendBuf,var,10);
}

void varPlayerHand()
{
	char *var="PHAND";
	strncpy(SendBuf,var,10);
}

void varNumPlayers()
{
	char *var="PNUM";
	strncpy(SendBuf,var,10);
}
void varPot()
{
	char *var="POT";
	strncpy(SendBuf,var,10);
}


//other player's info send to client

void var1Bet()
{
	char *var="1BET";
	strncpy(SendBuf,var,10);
}
void var2Bet()
{
	char *var="2BET";
	strncpy(SendBuf,var,10);
}
void var3Bet()
{
	char *var="3BET";
	strncpy(SendBuf,var,10);
}
void var4Bet()
{
	char *var="4BET";
	strncpy(SendBuf,var,10);
}
void var5Bet()
{
	char *var="5BET";
	strncpy(SendBuf,var,10);
}



void var1Bank()
{
	char *var="1BANK";
	strncpy(SendBuf,var,10);
}
void var2Bank()
{
	char *var="2BANK";
	strncpy(SendBuf,var,10);
}
void var3Bank()
{
	char *var="3BANK";
	strncpy(SendBuf,var,10);
}
void var4Bank()
{
	char *var="4BANK";
	strncpy(SendBuf,var,10);
}
void var5Bank()
{
	char *var="5BANK";
	strncpy(SendBuf,var,10);
}
//end user input button functs


//GUI STUFF

#define bg_width 1000
#define bg_height 750
#define button_width 75
#define button_height 50
#define button_space 50

GtkWidget *main_window;
GtkWidget *main_menu;
  GtkWidget *b_play, *b_quit, *b_serverClose, *b_login, *b_register;    
  //images
  GtkWidget *i_bg, *i_monkey; 
  
GtkWidget *option_window;
GtkWidget *option_menu;
  GtkWidget *b_seatNum, *b_tableNum, *in_name, *b_joinGame, *i_bg2;
  GtkWidget *txt; 
   
  
GtkWidget *game_window;
GtkWidget *game_menu;  
  GtkWidget *b_check, *b_call, *b_raise, *b_allin, *b_fold, *b_leaveGame, *i_bg3;
  
GtkWidget *gameOver_window;
///////////////////////////
// Prototypes
///////////////////////////

void init_window(GtkWidget* window);
void copy_text(GtkWidget* wid, gpointer *ptr);
void show_mainMenu(GtkWidget *wid, gpointer *ptr);
void show_optionMenu(GtkWidget *wid, gpointer *ptr);
void show_game(GtkWidget *wid, gpointer *ptr);
void show_gameOver(GtkWidget *wid, gpointer *ptr);


///////////////////////////
// Functions
///////////////////////////

void end_program(GtkWidget* window, gpointer ptr)
{
  gtk_main_quit();
  varBye();
}

void end_server(GtkWidget* window, gpointer ptr)
{
  gtk_main_quit();
  varShut();
}


void init_window(GtkWidget* window)
{
  gtk_window_set_title(GTK_WINDOW(window), "Poker GPT");
  gtk_window_set_default_size(GTK_WINDOW(window), 290, 200);
  gtk_window_set_position(GTK_WINDOW(window), TRUE);
  gtk_window_set_resizable(GTK_WINDOW(window), TRUE);
  g_signal_connect(window, "delete_event", G_CALLBACK(end_program), NULL);
}

void copy_text(GtkWidget* wid, gpointer *ptr)
{
  const char *input = gtk_entry_get_text(GTK_ENTRY (txt));
  gtk_label_set_text(GTK_LABEL (ptr), input);

}
void show_mainMenu(GtkWidget *wid, gpointer *ptr)
{
  gtk_widget_show_all(main_window);
  gtk_widget_hide(option_window);
  gtk_widget_hide(game_window);
  gtk_widget_hide(gameOver_window);
  
}
void show_optionMenu(GtkWidget *wid, gpointer *ptr)
{
  gtk_widget_hide(main_window);
  gtk_widget_show_all(option_window);
  gtk_widget_hide(game_window);
  gtk_widget_hide(gameOver_window);
  
}
void show_game(GtkWidget *wid, gpointer *ptr)
{
  gtk_widget_hide(main_window);
  gtk_widget_hide(option_window);
  gtk_widget_hide(gameOver_window);
  gtk_widget_show_all(game_window);
  varGame();
}
void show_gameOver(GtkWidget *wid, gpointer *ptr)
{
  gtk_widget_hide(main_window);
  gtk_widget_hide(game_window);
  gtk_widget_hide(option_window);
  gtk_widget_show_all(gameOver_window);
}
///////////////////////////
// main
///////////////////////////

//END OF GUI STUFF


/* #define DEBUG */	/* be verbose */

/*** global variables ****************************************************/

const char *Program	/* program name for descriptive diagnostics */
	= NULL;

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

int main(int argc, char *argv[])
{
    
    //GUI STUFF//

    gtk_init (&argc, &argv);
  
  //windows
  main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  option_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  game_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gameOver_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  
  init_window(main_window);
  init_window(option_window);
  init_window(game_window);
  init_window(gameOver_window);
  
  /////////////////
  // main window
  /////////////////
  /*
  Buttons:
  Play, Quit
  
  */
  
  
   //main menu ----------------------------------------------------------------------------------------------
  b_play = gtk_button_new_with_label("Play");
  b_serverClose = gtk_button_new_with_label("Shutdown Server");
  b_quit = gtk_button_new_with_label("Quit");
  b_login = gtk_button_new_with_label("Login");
  b_register = gtk_button_new_with_label("Register");
  
  gtk_widget_set_size_request(GTK_WIDGET(b_play), button_width, button_height);
  gtk_widget_set_size_request(GTK_WIDGET(b_serverClose), button_width + 20, button_height);
  gtk_widget_set_size_request(GTK_WIDGET(b_quit), button_width, button_height);
  gtk_widget_set_size_request(GTK_WIDGET(b_login), button_width, button_height);
  gtk_widget_set_size_request(GTK_WIDGET(b_register), button_width, button_height);
  
  //images
  i_bg = gtk_image_new_from_file("/users/ugrad2/2017/winter/team9/vanessa/images/Main Menu Background.png");
  //gtk_image_set_pixel_size (GtkImage* image, gint pixel_size);

  
  //puts buttons on main window
  main_menu = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(main_menu), i_bg, 0, 0);
  
  gtk_fixed_put(GTK_FIXED(main_menu), b_play, bg_width/2 - button_width/2, bg_height/2);
  gtk_fixed_put(GTK_FIXED(main_menu), b_quit, bg_width/2 - button_width/2, bg_height/2 + button_space);
  gtk_fixed_put(GTK_FIXED(main_menu), b_login, bg_width/2 - button_width/2, bg_height/2 + 2*button_space);
  gtk_fixed_put(GTK_FIXED(main_menu), b_register, bg_width/2 - button_width/2, bg_height/2 + 3*button_space); 
  gtk_fixed_put(GTK_FIXED(main_menu), b_serverClose, bg_width/2 - button_width/2, bg_height/2 + 4*button_space); 
  
  gtk_container_add(GTK_CONTAINER(main_window), main_menu);
  //gtk_widget_show_all(main_window);
  //--------------------------------------------------------------------------------------------------------

  //////////////////
  // option menu
  //////////////////
  
  //
  
  b_seatNum = gtk_combo_box_text_new();
  b_tableNum = gtk_combo_box_text_new();
  in_name = gtk_entry_new(); 
  b_joinGame = gtk_button_new_with_label("Join Game");
  
  // set widget size
  gtk_widget_set_size_request(GTK_WIDGET(b_tableNum), button_width + 20, button_height);
  gtk_widget_set_size_request(GTK_WIDGET(b_seatNum), button_width + 20, button_height);
  gtk_widget_set_size_request(GTK_WIDGET(in_name), button_width + 20, button_height);
  gtk_widget_set_size_request(GTK_WIDGET(b_joinGame), button_width + 20, button_height);
  
  gtk_combo_box_append_text(GTK_COMBO_BOX(b_tableNum), "Table 1"); //0
  gtk_combo_box_append_text(GTK_COMBO_BOX(b_tableNum), "Table 2"); //1
  
  gtk_combo_box_append_text(GTK_COMBO_BOX(b_seatNum), "Seat 1"); //0
  gtk_combo_box_append_text(GTK_COMBO_BOX(b_seatNum), "Seat 2"); //1
  gtk_combo_box_append_text(GTK_COMBO_BOX(b_seatNum), "Seat 3"); //2
  gtk_combo_box_append_text(GTK_COMBO_BOX(b_seatNum), "Seat 4"); //3
  
  gtk_combo_box_set_active(GTK_COMBO_BOX(b_tableNum), 0);
  gtk_combo_box_set_active(GTK_COMBO_BOX(b_seatNum), 0);
  
  // set widget location
  option_menu = gtk_fixed_new();
  // !!! problem here: --------------- fixed_put not working
  i_bg2 = gtk_image_new_from_file("/users/ugrad2/2017/winter/team9/varvara/Test/images/Main Menu Background.png");
  
  gtk_fixed_put(GTK_FIXED(option_menu), i_bg2, 0, 0);
  
  //GtkWidget *table;
  
  gtk_fixed_put(GTK_FIXED(option_menu), b_joinGame, bg_width/2 - button_width/2, bg_height/2);
  
  gtk_fixed_put(GTK_FIXED(option_menu), i_bg2, 0, 0);
  gtk_fixed_put(GTK_FIXED(option_menu), b_seatNum, bg_width/2 - button_width/2, bg_height/2);
  gtk_fixed_put(GTK_FIXED(option_menu), b_tableNum, bg_width/2 - button_width/2, bg_height/2 + button_space);
  gtk_fixed_put(GTK_FIXED(option_menu), in_name, bg_width/2 - button_width/2, bg_height/2 + (2*button_space));
  gtk_fixed_put(GTK_FIXED(option_menu), b_joinGame, bg_width/2 - button_width/2, bg_height/2 + (3*button_space));
  //*/
  
  
  
 gtk_container_add(GTK_CONTAINER(option_window), option_menu);

///////////////////
  // game window
  ///////////////////
  
  b_check = gtk_button_new_with_label("Check");
  b_call = gtk_button_new_with_label("Call");
  b_raise = gtk_button_new_with_label("Raise");
  b_allin = gtk_button_new_with_label("All-In");
  b_fold = gtk_button_new_with_label("Fold");
  b_leaveGame = gtk_button_new_with_label("Leave Game");
  
  gtk_widget_set_size_request(GTK_WIDGET(b_check), button_width + 20, button_height);
  gtk_widget_set_size_request(GTK_WIDGET(b_call), button_width + 20, button_height);
  gtk_widget_set_size_request(GTK_WIDGET(b_raise), button_width + 20, button_height);
  gtk_widget_set_size_request(GTK_WIDGET(b_allin), button_width + 20, button_height);
  gtk_widget_set_size_request(GTK_WIDGET(b_fold), button_width + 20, button_height);
  gtk_widget_set_size_request(GTK_WIDGET(b_leaveGame), button_width + 20, button_height);
  
  game_menu = gtk_fixed_new();
  
  i_bg3 = gtk_image_new_from_file("/users/ugrad2/2017/winter/team9/vanessa/images/Main Menu Background.png");
  gtk_fixed_put(GTK_FIXED(game_menu), i_bg3, 0, 0);
  
  gtk_fixed_put(GTK_FIXED(game_menu), b_check, bg_width/6 - button_width/6, bg_height/2 + 250);
  gtk_fixed_put(GTK_FIXED(game_menu), b_call, bg_width/6 - button_width/6 + (2*button_space), bg_height/2 + 250);
  gtk_fixed_put(GTK_FIXED(game_menu), b_raise, bg_width/6 - button_width/6 + (4*button_space), bg_height/2 + 250);
  gtk_fixed_put(GTK_FIXED(game_menu), b_allin, bg_width/6 - button_width/6 + (6*button_space), bg_height/2 + 250);
  gtk_fixed_put(GTK_FIXED(game_menu), b_fold, bg_width/6 - button_width/6 + (8*button_space), bg_height/2 + 250);
  gtk_fixed_put(GTK_FIXED(game_menu), b_leaveGame, bg_width/6 - button_width/6 + (10*button_space), bg_height/2 + 250);

  gtk_container_add(GTK_CONTAINER(game_window), game_menu);


  //////// button connections
  g_signal_connect(b_quit, "clicked", G_CALLBACK(end_program), main_window);
  
  g_signal_connect(b_serverClose, "clicked", G_CALLBACK(end_server), main_window);

  
  g_signal_connect(b_play, "clicked", G_CALLBACK(show_optionMenu), option_window);
  
  g_signal_connect(b_joinGame, "clicked", G_CALLBACK(show_game), game_window);

  //g_signal_connect(b_check, "clicked", G_CALLBACK(varCheck), game_window);
  //g_signal_connect(b_call, "clicked", G_CALLBACK(varCall), game_window);
  //g_signal_connect(b_raise, "clicked", G_CALLBACK(varRaise), game_window);
  //g_signal_connect(b_allin, "clicked", G_CALLBACK(show_game), game_window);
  //g_signal_connect(b_fold, "clicked", G_CALLBACK(varFold), game_window);
  //g_signal_connect(b_leaveGame, "clicked", G_CALLBACK(end_program), game_window);






  show_mainMenu(NULL, NULL);
  gtk_widget_show_all(main_window);

  gtk_main();	

	//END OF GUI STUFF



char Turn[5]="";
char HouseCards[25]="";
char PlayerHand[15]="";
char NumPlayers[5]="";
char Pot[10]="";
char P1Bet[5]="";
char P2Bet[5]="";
char P3Bet[5]="";
char P4Bet[5]="";
char P5Bet[5]="";
char P1Bank[5]="";
char P2Bank[5]="";
char P3Bank[5]="";
char P4Bank[5]="";
char P5Bank[5]="";




    int l, n, x, z;
    int SocketFD,	/* socket file descriptor */
	PortNo;		/* port number */
    struct sockaddr_in
	ServerAddress;	/* server address we connect with */
    struct hostent
	*Server;	/* server host */
    //char SendBuf[256];	/* message buffer for sending a message */
    char RecvBuf[256];	/* message buffer for receiving a response */


    Program = argv[0];	/* publish program name (for diagnostics) */
#ifdef DEBUG
    printf("%s: Starting...\n", argv[0]);
#endif
    if (argc < 3)
    {   fprintf(stderr, "Usage: %s hostname port\n", Program);
	exit(10);
    }
    Server = gethostbyname(argv[1]);
    if (Server == NULL)
    {   fprintf(stderr, "%s: no such host named '%s'\n", Program, argv[1]);
        exit(10);
    }
    PortNo = atoi(argv[2]);
    if (PortNo <= 2000)
    {   fprintf(stderr, "%s: invalid port number %d, should be >2000\n",
		Program, PortNo);
        exit(10);
    }
    ServerAddress.sin_family = AF_INET;
    ServerAddress.sin_port = htons(PortNo);
    ServerAddress.sin_addr = *(struct in_addr*)Server->h_addr_list[0];
    
    //main menu
    do
    {	printf("%s: Enter a command to send to the poker server:\n"
		"         'POKER' to play poker game,\n"
		"         'BYE' to quit this client, or\n"
		"         'SHUTDOWN' to terminate the server\n"
		"command: ", argv[0]);

	//gets input from user

	//show_mainMenu(NULL, NULL);
  	//gtk_widget_show_all(main_window);
 	//gtk_main();

	fgets(SendBuf, sizeof(SendBuf), stdin);
	l = strlen(SendBuf);
	if (SendBuf[l-1] == '\n')
	{   SendBuf[--l] = 0;
	}
	if (0 == strcmp("BYE", SendBuf))
	{   break;
	}
	//CONNECTION CODE
	while (0 != strcmp("BYE", SendBuf))
	{   SocketFD = socket(AF_INET, SOCK_STREAM, 0);
	    if (SocketFD < 0)
	    {   FatalError("socket creation failed");
	    }
	    printf("%s: Connecting to the server at port %d...\n",
			Program, PortNo);
	    //connect one time
	    if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
			sizeof(ServerAddress)) < 0)
	    {   FatalError("connecting to server failed");
	    }
	    printf("%s: Sending message '%s'...\n", Program, SendBuf);
	    n = write(SocketFD, SendBuf, l);
	    if (n < 0)
	    {   FatalError("writing to socket failed");
	    }
#ifdef DEBUG
	    printf("%s: Waiting for response...\n", Program);
#endif
	    n = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
	    if (n < 0) 
	    {   FatalError("reading from socket failed");
	    }
	    RecvBuf[n] = 0;
	    printf("%s: Received response: %s\n", Program, RecvBuf);
	    memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
            //END CONNECTION CODE
	 	
		
		//send player hand 
	 	varPlayerHand();
		length=sizeof(PlayerHand)-1;//calculate length of array
		memset(PlayerHand, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{ printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(PlayerHand,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}
		
	   // TurnChoice
	while(0 != strcmp("FOLD", SendBuf))
	{
		printf("%s: Enter a command to send to the poker server:\n"
			"         'CALL' to to not raise the current bet,\n"
			"         'RAISE' to raise the current bet, \n"
			"         'CHECK' to match the current bet, or\n"
			"	  'FOLD' to quit the game\n"
			"turn command: ", argv[0]);
	
		//gets input from user

		fgets(SendBuf, sizeof(SendBuf), stdin);
		x = strlen(SendBuf);
		if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (0 == strcmp("FOLD", SendBuf))
		{   break;
		}

		
		//CONNECTION CODE
		if (x) 
		{   SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		    if (SocketFD < 0)
	 	   {   FatalError("socket creation failed");
	 	   }
	   	 printf("%s: Connecting to the server at port %d...\n",
				Program, PortNo);
	    	//establish connection
	    	if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
				sizeof(ServerAddress)) < 0)
	   	 {   FatalError("connecting to server failed");
	   	 }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
	   	 z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		

	  	  z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
	   	 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer

		}


	
		//
		//SEND/REC ADDITIONAL INFO ABOUT OTHER PLAYERS
		//send request for house cards
		varHouseCards();
		length=sizeof(HouseCards)-1;//calculate length of array
		memset(HouseCards, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{ printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(HouseCards,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}

		//send player hand 
	 	varPlayerHand();
		length=sizeof(PlayerHand)-1;//calculate length of array
		memset(PlayerHand, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{ printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(PlayerHand,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}

		
		 
	        //send request for current turn
	        varTurn();
		length=sizeof(Turn)-1;//calculate length of array
		memset(Turn, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(Turn,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}
		 
		//send request for number of players
		varNumPlayers();
		length=sizeof(NumPlayers)-1;//calculate length of array
		memset(NumPlayers, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(NumPlayers,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}
		 
		//send request for pot
		varPot();
		length=sizeof(Pot)-1;//calculate length of array
		memset(Pot, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(Pot,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}
	       
		//player info
		var1Bet();
		length=sizeof(P1Bet)-1;//calculate length of array
		memset(P1Bet, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(P1Bet,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}

		var2Bet();
		length=sizeof(P2Bet)-1;//calculate length of array
		memset(P2Bet, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(P2Bet,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}

 
		 
		var3Bet();
		length=sizeof(P3Bet)-1;//calculate length of array
		memset(P3Bet, 0, length); //set all bytes in array to 0
	        x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(P3Bet,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}

		 
		var4Bet();
		length=sizeof(P4Bet)-1;//calculate length of array
		memset(P4Bet, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(P4Bet,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}

		

		var5Bet();
		length=sizeof(P5Bet)-1;//calculate length of array
		memset(P5Bet, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(P5Bet,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}


		var1Bank();
		length=sizeof(P1Bank)-1;//calculate length of array
		memset(P1Bank, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(P1Bank,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}

		 
		var2Bank();
		length=sizeof(P2Bank)-1;//calculate length of array
		memset(P2Bank, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(P2Bank,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}


		var3Bank();
		length=sizeof(P3Bank)-1;//calculate length of array
		memset(P3Bank, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(P3Bank,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}


		var4Bank();
		length=sizeof(P4Bank)-1;//calculate length of array
		memset(P4Bank, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(P4Bank,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}


		var5Bank();
		length=sizeof(P5Bank)-1;//calculate length of array
		memset(P5Bank, 0, length); //set all bytes in array to 0
		x = strlen(SendBuf);
	        if (SendBuf[x-1] == '\n')
		{   SendBuf[--x] = 0;
		}
		if (x) 
		{  // SocketFD = socket(AF_INET, SOCK_STREAM, 0);
		   // if (SocketFD < 0)
	 	  // {   FatalError("socket creation failed");
	 	  // }
	   	 //printf("%s: Connecting to the server at port %d...\n",
			//	Program, PortNo);
	    	//establish connection
	    	//if (connect(SocketFD, (struct sockaddr*)&ServerAddress,
		//		sizeof(ServerAddress)) < 0)
	   	// {   FatalError("connecting to server failed");
	   	// }
	   	 printf("%s: Sending message '%s'...\n", Program, SendBuf);
		z = write(SocketFD, SendBuf, x);
	   	 if (z < 0)
	    	{   FatalError("writing to socket failed");
	    	}
		#ifdef DEBUG
	    	printf("%s: Waiting for response...\n", Program);
		#endif
		z = read(SocketFD, RecvBuf, sizeof(RecvBuf)-1);
		 if (z < 0) 
	   	 {   FatalError("reading from socket failed");
	   	 }
	    	RecvBuf[z] = 0;
	    	printf("%s: Received response: %s\n", Program, RecvBuf);
		strcat(P5Bank,RecvBuf);
		memset(RecvBuf,0,sizeof(RecvBuf)); //clear receive buffer
		}

            	//END CONNECTION CODE
		
	}
 	    
#ifdef DEBUG
	    printf("%s: Closing the connection...\n", Program);
#endif
	    close(SocketFD);
	}
	
    } while(0 != strcmp("SHUTDOWN", SendBuf));
    printf("%s: Exiting...\n", Program);
    return 0;
}

/* EOF PokerClient.c */
