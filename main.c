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
        mvprintw(13,13, "--------");
        mvprintw(14,13, "|......|");
        mvprintw(15,13, "|......|");
        mvprintw(16,13, "|......|");
        mvprintw(17,13, "|......|");
        mvprintw(18,13, "--------");

        mvprintw(2,40, "--------");
        mvprintw(3,40, "|......|");
        mvprintw(4,40, "|......|");
        mvprintw(5,40, "|......|");
        mvprintw(6,40, "|......|");
        mvprintw(7,40, "--------");

        mvprintw(12,40, "-----------");
        mvprintw(13,40, "|.........|");
        mvprintw(14,40, "|.........|");
        mvprintw(15,40, "|.........|");
        mvprintw(16,40, "|.........|");
        mvprintw(17,40, "-----------");
}
