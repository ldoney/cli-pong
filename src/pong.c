#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include "racket.c"
#include "ball.c"
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <math.h>

#define abs(n) ((n < 0) ? -n : n)
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define PI 3.14159265

#define DELAY 30000

#define MARGIN 30
#define CENTER "|"

#define MAX_BOUNCE 20*PI/12

#define P1_UP 119
#define P1_DOWN 115

#define P2_UP 111
#define P2_DOWN 108
/*
 _____      ____        __      _      _____   
(  __ \    / __ \      /  \    / )    / ___ \  
 ) )_) )  / /  \ \    / /\ \  / /    / /   \_) 
(  ___/  ( ()  () )   ) ) ) ) ) )   ( (  ____  
 ) )     ( ()  () )  ( ( ( ( ( (    ( ( (__  ) 
( (       \ \__/ /   / /  \ \/ /     \ \__/ /  
/__\       \____/   (_/    \__/       \____/   
                                               
*/
const char *titleText[7] = {
	 "_____      ____        __      _      _____" ,
	"(  __ \\    / __ \\      /  \\    / )    / ___ \\" ,
	" ) )_) )  / /  \\ \\    / /\\ \\  / /    / /   \\_)",
	"(  ___/  ( ()  () )   ) ) ) ) ) )   ( (  ____"  ,
	" ) )     ( ()  () )  ( ( ( ( ( (    ( ( (__  )" ,
	"( (       \\ \\__/ /   / /  \\ \\/ /     \\ \\__/ /" , 
	"/__\\       \\____/   (_/    \\__/       \\____/ " 
                                               
};
//Variable definitions for game
int score1 = 0, score2 = 0;
int max_x = 0, max_y = 0;
struct Racket p1, p2;
struct Ball ball;

int kbhit (void)
{
	struct timeval tv;
	fd_set rdfs;
 
	tv.tv_sec = 0;
	tv.tv_usec = 0;

	FD_ZERO(&rdfs);
	FD_SET (STDIN_FILENO, &rdfs);
 
	select(STDIN_FILENO+1, &rdfs, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &rdfs); 
}

void printBoard(WINDOW *win) {
	for(int i = 0; i < max_y; i++)
	{
		mvwprintw(win, i, max_x / 2, CENTER);
	}
	char p1buf[50];
	char p2buf[50];

	sprintf(p1buf, "%d", score1);
	sprintf(p2buf, "%d", score2);
	mvwprintw(win, 0, (max_x/2)-strlen(p1buf), p1buf);
	mvwprintw(win, 0, (max_x/2) + 1, p2buf);
}

void resetBoard(WINDOW *win) {
	int times = 3;
	char buf[5];
	for(int i = times; i >= 0; i--)
	{
		erase();
		printBoard(win);
		if(i != 0)
		{
			sprintf(buf, "%d", i);			
		}else {
			sprintf(buf, "Go!");
		}
		mvprintw(max_y/2, max_x/2, buf);
		refresh();
		usleep(1000000);
	}
	ball.reset(win, &ball);
	p1.m_x = MARGIN;
	p1.m_y = max_y / 2;
	p2.m_x = max_x - MARGIN;
	p2.m_y = max_y / 2;
	mvprintw(max_y/2, max_x/2 - 1, "Go!");
	erase();
	refresh();
}
int isCollision() {
	if((int)ball.m_x == (int)p1.m_x) {
		for(int i = 0; i < p1.m_size; i++) {
			if(((int)p1.m_y - (p1.m_size/2)+i) == (int)ball.m_y)
			{
				return 1;
			}
		}
	}
	if((int)ball.m_x == (int)p2.m_x) {
		for(int i = 0; i < p2.m_size; i++) {
			if(((int)p2.m_y - (p2.m_size/2)+i) == (int)ball.m_y)
			{
				return -1;
			}
		}
	}
	return 0;
}
int main(int argc, char *argv[]) {
	WINDOW *game;
	bool start = false;

    initscr();
    noecho();
	curs_set(FALSE);


	refresh();
	int selected = 0;
	int ch = 0;
	int maxselect = 0;
	char buff[50];

	while(!start){
    	getmaxyx(stdscr, max_y, max_x);
		maxselect = 0;

		attroff(A_STANDOUT);
		for(int i = 0; i < sizeof(titleText)/sizeof(titleText[0]); i++)
		{
			mvwprintw(stdscr, (max_y/2)-15 + i, (max_x/2) - (strlen(titleText[1])/2), titleText[i]);
		}
		
		if(selected == 0)
			attron(A_STANDOUT);
		mvwprintw(stdscr, max_y/2, (max_x/2)-2, "Play");
		attroff(A_STANDOUT);
		maxselect++;

		if(selected == 1)
			attron(A_STANDOUT);
		mvwprintw(stdscr, (max_y/2) + 1, (max_x/2)-2, "Exit");
		attroff(A_STANDOUT);
		maxselect++;

		mvwprintw(stdscr, max_y/2 + 15, (max_x/2)-12, "Created by Lincoln Doney");
		
		if (kbhit()) {
			ch = getch();
			if(ch == P1_UP && selected > 0)
				selected--;
			else if(ch == P1_DOWN && selected < maxselect - 1)
				selected++;
			else if(ch == 10) {
				switch(selected)
				{
					case 0:
						start = true;
						break;
					case 1:
						endwin();
						return 0;
						break;
				}
			}
			else if(ch == '\033')
			{
				getch();
				switch(getch()) {
					case 'A':
						if(selected > 0)
							selected--;
						break;
					case 'B':
						if(selected < maxselect - 1)
							selected++;	
						break;
				}
			}
		}
		refresh();
		erase();
	}

	game = newwin(max_y, max_x, 0, 0);

    getmaxyx(game, max_y, max_x);
	
	ball=Ball.new();
	ball.reset(game, &ball);

	p1=Racket.new("Player 1", MARGIN, max_y / 2);
	p2=Racket.new("Player 2", max_x - MARGIN, max_y / 2);
	

	int collision = 0;

	resetBoard(game);

    while(1) {
   		getmaxyx(stdscr, max_y, max_x);
		if (kbhit()) {
			ch = getch();
			if(ch == P1_UP)
				p1.m_y--;
			else if(ch == P1_DOWN)
				p1.m_y++;
			else if(ch == '\033')
			{
				getch();
				switch(getch()) {
					case 'A':
						p2.m_y--;
						break;
					case 'B':
						p2.m_y++;
						break;
				}
			}
		}
		werase(game);
		printBoard(game);

		ball.draw(game, &ball);
		p1.draw(game, &p1);
		p2.draw(game, &p2);

		if(collision=isCollision() != 0) {
			struct Racket colP = (collision == 1 ? p1 : p2);
			double relIntersectY = (colP.m_y+(colP.m_size/2) - ball.m_y);
			double normalizedRelIntersectY = (relIntersectY/(colP.m_size/2));
			double angle = MIN(normalizedRelIntersectY, MAX_BOUNCE);
			double speed = sqrt(ball.m_v_x * ball.m_v_x + ball.m_v_y * ball.m_v_y);;
			ball.m_v_x = speed * (ball.m_v_x < 0 ? 1 : -1)*cos(angle-(PI/2));
			ball.m_v_y = speed * sin(angle-(PI/2));
		}
		wrefresh(game);
		usleep(DELAY);

		ball.m_x += ball.m_v_x;
		ball.m_y += ball.m_v_y;
		if(ball.m_y <= 0 || ball.m_y >= max_y)
			ball.m_v_y = -ball.m_v_y;
		
		if(ball.m_x <= 0)
		{
			score1++;
			resetBoard(game);
		}
		else if(ball.m_x >= max_x)
		{
			score2++;
			resetBoard(game);
		}
    }
    endwin();
}
