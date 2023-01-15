#ifndef ROGUE_H
#define ROGUE_H


#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <time.h>

typedef struct Position
{

    int x;
    int y;

} Position;

typedef struct Room
{
    Position position;
    int height;
    int width;

    Position **doors;

    // Monster ** monsters;
    // Item ** items;

} Room;

typedef struct Player
{
    Position position;
    int health;
    // Room * room;
} Player;

int screenSetUp();
int drawRoom(Room *room);
Room **mapSetup();
int handleInput(int input, Player *user);
int playerMove(int y, int x, Player *user);
int checkPosition(int newY, int newX, Player *user);
Player *playerSetup(); // create function to setup the player, returning struct

// room functions

Room *createRoom(int x, int y, int height, int width);
int connectDoors(Position *doorOne, Position *doorTwo);


#endif
