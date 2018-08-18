#include <ncurses.h>

int screenSetUp();
int mapSetUp();

int main(int argc, char *argv[])
{
        screenSetUp();

        mapSetUp();
        
        getch();
        endwin();
        
        return 0;
}

int screenSetUp()
{
        initscr();
        printw("Hello, world!");
        noecho();
        refresh();
        return 0;
}

int mapSetUp()
{
        
}
