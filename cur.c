#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#define MAX 10

// Few variables
char player='@';
char food='o';
int px=3,py=3;
int fx,fy;
int alive=1;
int dirx=0,diry=0;
int my,mx;
int ch;
int score=1;  //score starts at 1, don't really know why but it works else it acts weird... 
int segs[MAX][2];
int idk=0;
int segnum=0;

//Function declarations.
void eatfood();
void showdebug();
void death(); //head at that position.
void screenborder();
void outofborder();
void posrec();
void prsegs();

//struct
typedef struct {
    int partnum;
    //char piece;

}parts;

//__main__
int main(int nargs,char* vargs[] ){
    /*
    char player='o';
    char food='*';
    float px=0,py=0;
    int fx,fy;
    int alive=1;
    int dirx=0,diry=0;
    int my,mx;
    */
    srand(time(NULL));
    initscr();
    noecho();
    cbreak();
    keypad(stdscr,TRUE);
    nodelay(stdscr,TRUE);
    curs_set(0);
    getmaxyx(stdscr,my,mx);
    //int ch;
    fx=rand() % mx;
    fy=rand() % my;
    //printf("%d %d",fx,fy)

    if (nargs>1) showdebug();
    //int x=0;

    do{
        clear();
        screenborder();
        ch=getch();
        posrec();
        prsegs();
        mvprintw(py,px,"%c",player);
        mvprintw(fy,fx,"%c",food);
        refresh();

        if (ch==KEY_LEFT){
            dirx=-1;
            diry=0;
        }
        else if (ch==KEY_RIGHT){
            dirx=1;
            diry=0;
        }
        else if (ch==KEY_UP){
            dirx=0;
            diry=-1;
        }
        else if (ch==KEY_DOWN){
            dirx=0;
            diry=1;
        }

        px+=dirx;
        py+=(diry);

        //segs[idk%MAX][0]=px;
        //segs[idk%MAX][1]=py;

        if (px==fx && py==fy){
            eatfood();
        }
        if (px>mx || py>my || px<0 || py<0) outofborder(); //kill?
        //mvprintw(0,10,"%d %d",px,py);
        if (score>0){
            ++idk;
        }

        if (dirx){
            napms(150);
        }
        else{
            napms(175);
        }
        //clear();
    }while((ch!='q') && (alive));

    endwin();

}

void eatfood(){
    mvprintw(fy,fx," ");
    fx=rand() % mx;
    fy=rand() % my;
    ++score;
    napms(500);
    // for segmetnts...
    //mvprintw(segs[score-1][1],segs[score-1][0],"@");
}

void showdebug(){
    mvprintw(3,0,"score: %d",score);
    mvprintw(0,0,"screen sizen %d,%d",mx,my);
    mvprintw(1,0,"Food: %d,%d",fx,fy);
    mvprintw(2,0,"Player:%d %d",px,py);
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

void outofborder(){
    if (px>mx){
    px=0;
}
else if (py>my){
    py=0;
}
else if (px<0){
    px=mx;
}
else if (py<0){
    py=my;
}
}

void posrec(){
    if (score){
        segs[idk%score][0]=px;
        segs[idk%score][1]=py;
        //printf("%d %d\n",px,py);
    }
}

void prsegs(){
    for (int i=0;i<(score);i++){
        mvprintw(segs[i][1],segs[i][0],"@");
    }
}
