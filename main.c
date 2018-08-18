#include <ncurses.h>
#include <stdlib.h>

struct player_t
{
        int x_pos;
        int y_pos;
        int health;
};
typedef struct player_t player;

player* player_setup();

int screen_setup();
int map_setup();

int main(int argc, char *argv[])
{
        player* user;
        int ch;
        screen_setup();
        map_setup();

        user = player_setup();

        while ((ch = getch()) != 'q') {
                
        }

        endwin();
        return 0;
}

int screen_setup()
{
        initscr();
        printw("Hello, world!");
        noecho();
        refresh();
        return 0;
}

int map_setup()
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

player* player_setup()
{
        player* new_player;
        new_player = malloc(sizeof(player));

        new_player->x_pos = 14;
        new_player->y_pos = 14;
        new_player->health = 20;

        mvprintw(new_player->y_pos, new_player->x_pos, "@");
        move(new_player->y_pos, new_player->x_pos);
        return new_player;
}
