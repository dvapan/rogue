#include <ncurses.h>
#include <stdlib.h>

struct room_t
{
        int x_pos;
        int y_pos;
        int height;
        int width;
        /* monster ** monsters; */
        /* item ** items; */
};
typedef struct room_t room;

struct player_t
{
        int x_pos;
        int y_pos;
        int health;
        /* room* room; */
};
typedef struct player_t player;

player* player_setup();

int screen_setup();
room** map_setup();
int handle_input(int input, player* user);
int player_move(int y, int x, player* user);
int check_position(int new_y, int new_x, player* user);

/* room functions */
room* create_room(int x, int y, int height, int width);
int draw_room(room* room);

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

room** map_setup()
{
        room** rooms;
        rooms = malloc(sizeof(room)*6);

        /* mvprintw(13,13, "--------"); */
        /* mvprintw(14,13, "|......|"); */
        /* mvprintw(15,13, "|......|"); */
        /* mvprintw(16,13, "|......|"); */
        /* mvprintw(17,13, "|......|"); */
        /* mvprintw(18,13, "--------"); */

        rooms[0] = create_room(13, 13, 6, 8);
        draw_room(rooms[0]);

        /* mvprintw(2,40, "--------"); */
        /* mvprintw(3,40, "|......|"); */
        /* mvprintw(4,40, "|......|"); */
        /* mvprintw(5,40, "|......|"); */
        /* mvprintw(6,40, "|......|"); */
        /* mvprintw(7,40, "--------"); */

        rooms[1] = create_room(40, 2, 6, 8);
        draw_room(rooms[1]);

        /* mvprintw(12,40, "-----------"); */
        /* mvprintw(13,40, "|.........|"); */
        /* mvprintw(14,40, "|.........|"); */
        /* mvprintw(15,40, "|.........|"); */
        /* mvprintw(16,40, "|.........|"); */
        /* mvprintw(17,40, "-----------"); */

        rooms[2] = create_room(40, 10, 6, 12);
        draw_room(rooms[2]);
        return rooms;
}

room* create_room(int x, int y, int height, int width)
{
        room* new_room;
        new_room = malloc(sizeof(room));

        new_room->x_pos = x;
        new_room->y_pos = y;
        new_room->height = height;
        new_room->width = width;

        return new_room;
}

int draw_room(room* room)
{
        int x,y;

        /* draw top and bottom */
        for(x = room->x_pos; x < room->x_pos + room->width; x++){
                mvprintw(room->y_pos, x, "-"); /* top */
                mvprintw(room->y_pos + room->height - 1, x, "-"); /* bottom */
        }
        /* draw floors and side walls */
        for (y = room->y_pos + 1; y < room->y_pos + room->height - 1; y++)
        {
                /* draw side walls */
                mvprintw(y, room->x_pos, "|");
                mvprintw(y, room->x_pos + room->width - 1, "|");
                /* draw floors */
                for (x = room->x_pos + 1; x < room->x_pos + room->width - 1; x++)
                {
                        mvprintw(y,x,".");
                }
        }
        return 1;
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
