#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

// Few variables
char player='@';
char food='o';
int px=3,py=3;
int fx,fy;
int alive=1;
int dirx=1,diry=0;
int my,mx;
int ch;
int score=1;  //score starts at 1, don't really know why but it works else it acts weird... 
int segs[MAX][2];
int idk=0;

//Function declarations.
void eatfood();
void death(); //head at that position.
void screenborder();
void outofborder();
void posrec();
void prsegs();

int main(){

    srand(time(NULL));
    initscr();
    noecho();
    cbreak();
    keypad(stdscr,TRUE);
    nodelay(stdscr,TRUE);
    curs_set(0);

    getmaxyx(stdscr,my,mx);

    fx=(1 + rand() % (mx-2));
    fy=(1 + rand() % (my-2));

    do{
        clear();
	screenborder();
	mvprintw(0,0,"Score:%d",score-1);
        ch=getch();
        posrec();
	prsegs();
        mvprintw(py,px,"%c",player);
        mvprintw(fy,fx,"%c",food);
        refresh();

        if (ch==KEY_LEFT && dirx!=1){
            dirx=-1;
            diry=0;
        }
        else if (ch==KEY_RIGHT && dirx!=-1){
            dirx=1;
            diry=0;
        }
        else if (ch==KEY_UP && diry!=1){
            dirx=0;
            diry=-1;
        }
        else if (ch==KEY_DOWN && diry!=-1){
            dirx=0;
            diry=1;
        }

        px+=dirx;
        py+=(diry);

        refresh();

        if (px>=mx-2 || py>=my-2 || px<1 || py<1) outofborder();
	if (px==fx && py==fy) eatfood();
	if (score>0) ++idk;
	if (dirx) napms(150);
        else napms(175);
    	if (score==MAX) death();
    }while((ch!='q') && (alive));

    endwin();
    printf("You Died With Scrore of %d\n",score-1);
    printf("Credits : Sumit\n");
    return 0;

}

void eatfood(){
    mvprintw(fy,fx," ");
    fx=(1 + rand() % (mx-2));
    fy=(1 + rand() % (my-2));
    ++score;
    napms(500);
}

void death(){
alive=0;
}

void screenborder(){
    mvhline(0,0,'-',mx);
    mvhline(my-1,0,'-',mx);
    mvvline(0,0,'|',my);
    mvvline(0,mx-1,'|',my);
    mvaddch(0,0,'+');
    mvaddch(my-1,0,'+');
    mvaddch(0,mx-1,'+');
    mvaddch(my-1,mx-1,'+');
}

void posrec(){
    if (score){
        segs[idk%score][0]=px;
        segs[idk%score][1]=py;
    }
}

void prsegs(){
    for (int i=0;i<(score);i++){
        mvprintw(segs[i][1],segs[i][0],"@");
	if (px +dirx == segs[i][0] && py +diry == segs[i][1]) death();
}
}

void outofborder(){
    if (px>mx-2) px=1;
    else if (py>my-2) py=1;
    else if (px<1) px=mx-2;
    else if (py<1) py=my-2;
}
