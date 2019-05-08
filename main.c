#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

struct position_t{
        int x;
        int y;
        /* TILE_TYPE tile; */
};
typedef struct position_t position;

struct room_t
{
        position pos;
        int height;
        int width;

        position** doors;
        /* monster ** monsters; */
        /* item ** items; */
};
typedef struct room_t room;

struct player_t
{
        position pos;
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
        srand(time(NULL));

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

        new_room->pos.x = x;
        new_room->pos.y = y;
        new_room->height = height;
        new_room->width = width;

        new_room->doors = malloc(sizeof(position) * 4);
        
        /* Top door */
        new_room->doors[0] = malloc(sizeof(position));
        new_room->doors[0]->x = rand() % (width - 2) + x + 1;
        new_room->doors[0]->y = y;

        /* bottom door */
        new_room->doors[1] = malloc(sizeof(position));
        new_room->doors[1]->x = rand() % (width - 2) + x + 1;
        new_room->doors[1]->y = y + height - 1;

        /* left door */
        new_room->doors[2] = malloc(sizeof(position));
        new_room->doors[2]->y = rand() % (height - 2) + y + 1;
        new_room->doors[2]->x = x;

        /* left door */
        new_room->doors[3] = malloc(sizeof(position));
        new_room->doors[3]->y = rand() % (height - 2) + y + 1;
        new_room->doors[3]->x = x + width - 1;
        return new_room;
}

int draw_room(room* room)
{
        int x,y;

        /* draw top and bottom */
        for(x = room->pos.x; x < room->pos.x+ room->width; x++){+
                mvprintw(room->pos.y, x, "-"); /* top */
                mvprintw(room->pos.y + room->height - 1, x, "-"); /* bottom */
        }
        /* draw floors and side walls */
        for (y = room->pos.y + 1; y < room->pos.y + room->height - 1; y++)
        {
                /* draw side walls */
                mvprintw(y, room->pos.x, "|");
                mvprintw(y, room->pos.x + room->width - 1, "|");
                /* draw floors */
                for (x = room->pos.x + 1; x < room->pos.x + room->width - 1; x++)
                {
                        mvprintw(y,x,".");
                }
        }

        /* draw doors */
        for (int i = 0; i < 4; i++)
                mvprintw(room->doors[i]->y, room->doors[i]->x,"+");
        return 1;
}

player* player_setup()
{
        player* new_player;
        new_player = malloc(sizeof(player));

        new_player->pos.x = 14;
        new_player->pos.y = 14;
        new_player->health = 20;

        player_move(14, 14, new_player);

        return new_player;
}

int handle_input(int input, player* user)
{
        int new_y, new_x;
        switch (input) {
        case 'k':               /* move up */
                new_y = user->pos.y - 1;
                new_x = user->pos.x;
                break;
        case 'j':               /* move down */
                new_y = user->pos.y + 1;
                new_x = user->pos.x;
                break;
        case 'h':               /* move left */
                new_y = user->pos.y;
                new_x = user->pos.x - 1;
                break;
        case 'l':               /* move right */
                new_y = user->pos.y;
                new_x = user->pos.x + 1;
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
                player_move(user->pos.y, user->pos.x, user);
                break;
        }
}

int player_move(int y, int x, player* user)
{
        mvprintw(user->pos.y, user->pos.x, ".");
        user->pos.x = x;
        user->pos.y = y;
        mvprintw(user->pos.y, user->pos.x, "@");
        move(user->pos.y, user->pos.x);
}
