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
int handle_input(int input, player* user);
int player_move(int y, int x, player* user);
int check_position(int new_y, int new_x, player* user);

int main(int argc, char *argv[])
{
        player* user;
        int ch;
        screen_setup();
        map_setup();

        user = player_setup();

        /* main game loop */
        while ((ch = getch()) != 'q') {
                handle_input(ch, user);
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

        player_move(14, 14, new_player);

        return new_player;
}

int handle_input(int input, player* user)
{
        int new_y, new_x;
        switch (input) {
        case 'k':               /* move up */
                new_y = user->y_pos - 1;
                new_x = user->x_pos;
                break;
        case 'j':               /* move down */
                new_y = user->y_pos + 1;
                new_x = user->x_pos;
                break;
        case 'h':               /* move left */
                new_y = user->y_pos;
                new_x = user->x_pos - 1;
                break;
        case 'l':               /* move right */
                new_y = user->y_pos;
                new_x = user->x_pos + 1;
                break;
        default:
                break;
        }
        check_position(new_y, new_x, user);
}

/* check what is at next position */
int check_position(int y, int x, player* user)
{
        int space;
        switch (mvinch(y,x)) {
        case '.': {
                player_move(y, x, user);
                break;
        }
        default:
                player_move(user->y_pos, user->x_pos, user);
                break;
        }
}

int player_move(int y, int x, player* user)
{
        mvprintw(user->y_pos, user->x_pos, ".");
        user->x_pos = x;
        user->y_pos = y;
        mvprintw(user->y_pos, user->x_pos, "@");
        move(user->y_pos, user->x_pos);
}
