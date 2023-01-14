#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>


typedef struct Position {

    int x;
    int y;

} Position;



typedef struct Room {
    Position position;
    int height;
    int width;
    // Monster ** monsters; 
    // Item ** items;

} Room;


typedef struct Player {
    Position position;
    int health;
    // Room * room;
} Player;


int screenSetUp();
 int drawRoom(Room *room);
Room ** mapSetup();
int handleInput(int input, Player * user);
int playerMove(int y, int x, Player * user);
int checkPosition(int newY, int newX, Player * user);
Player * playerSetup(); // create function to setup the player, returning struct


// room functions

Room * createRoom(int x, int y, int height, int width);


int main(void) {

Player * user; // create a user
int ch;

screenSetUp();

mapSetup();
user = playerSetup(); // make it equal to struct returned



// main game loop

while ((ch = getch()) != 'q') {

        handleInput(ch, user);
}


    endwin();
    return 0;
}




int screenSetUp() {

    initscr();
    printw("Hello World");
    noecho();
    refresh();

    return 0;



}


Room ** mapSetup() {
    Room ** rooms;
    rooms = malloc(sizeof(Room)*6);

    // mvprintw(13, 13, "--------"); // move cursor to draw (y,x,string)
    // mvprintw(14, 13, "|......|");
    // mvprintw(15, 13, "|......|");
    // mvprintw(16, 13, "|......|");
    // mvprintw(17, 13, "|......|");
    // mvprintw(18, 13, "--------");

    rooms[0] = createRoom(13, 13, 6, 8);
    drawRoom(rooms[0]);

    // mvprintw(2, 40,  "--------"); 
    // mvprintw(3, 40, "|......|");
    // mvprintw(4, 40, "|......|");
    // mvprintw(5, 40, "|......|");
    // mvprintw(6, 40, "|......|");
    // mvprintw(7, 40, "--------");

    rooms[1] = createRoom(40, 2, 6, 8);
    drawRoom(rooms[1]);


    // mvprintw(10, 40, "------------"); 
    // mvprintw(11, 40, "|..........|");
    // mvprintw(12, 40, "|..........|");
    // mvprintw(13, 40, "|..........|");
    // mvprintw(14, 40, "|..........|");
    // mvprintw(15, 40, "------------");

    rooms[2] = createRoom(40, 10, 6, 12);
    drawRoom(rooms[2]);

    return rooms;
}





   Room * createRoom(int x, int y, int height, int width) {
        Room * newRoom;
        newRoom = malloc(sizeof(Room));

        newRoom->position.x = x;
        newRoom->position.y = y;
        newRoom->height = height;
        newRoom->width = width;


        return newRoom;
   }


    int drawRoom(Room *room) {
        int x;
        int y;

        // draw the top and bottom
        for (x = room->position.x; x < room->position.x + room->width; x++) {
            mvprintw(room->position.y, x, "-"); // top
            mvprintw(room->position.y + room->height - 1, x, "-"); // add room height to go to bottom

        }

        // now draw the floors and walls

        for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++) {
            mvprintw(y, room->position.x, "|");
            mvprintw(y, room->position.x + room->width - 1 , "|");
            for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++) {
                mvprintw(y, x, ".");
            }

        }



        return 0;
    }




Player * playerSetup() {


    Player * newPlayer;
    newPlayer = malloc(sizeof(Player));

    newPlayer->position.x = 14;
    newPlayer->position.y = 14;
    newPlayer->health = 20;

playerMove(14, 14, newPlayer);


    return newPlayer;
}



int handleInput(int input, Player * user) {

    int newY;
    int newX;
    switch(input) {
        case 'w':
        case 'W':
        newY = user->position.y - 1;
        newX = user->position.x;
            break;

        case 'a':
        case 'A':
        newY = user->position.y;
        newX = user->position.x - 1;
            break;

        case 's':
        case 'S':
        newY = user->position.y + 1;
        newX = user->position.x;
            break; 

        case 'd':
        case 'D':
        newY = user->position.y;
        newX = user->position.x + 1;
            break;


        default: break;       





    }

    checkPosition(newY, newX, user);


}


// check next position, only call playerMove if it's allowed
int checkPosition(int newY, int newX, Player * user) {
int space;

    switch(mvinch(newY, newX)) { 
    case '.': 
        playerMove(newY, newX, user); 
    break;


    default:
        move(user->position.y, user->position.x);
     break;
    }

}




int playerMove(int y, int x, Player * user) {

    mvprintw(user->position.y, user->position.x, "."); // replace last position

    user->position.x = x;
    user->position.y = y;

    mvprintw(user->position.y, user->position.x, "@"); // redraw after updating
    move(user->position.y, user->position.x);


}