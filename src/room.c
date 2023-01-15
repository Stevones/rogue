#include "rogue.h"

Room *createRoom(int x, int y, int height, int width)
{
    Room *newRoom;
    newRoom = malloc(sizeof(Room));

    newRoom->position.x = x;
    newRoom->position.y = y;
    newRoom->height = height;
    newRoom->width = width;

    newRoom->doors = malloc(sizeof(Position) * 4);

    // top door
    newRoom->doors[0] = malloc(sizeof(Position));
    newRoom->doors[0]->x = rand() % (newRoom->width - 2) + newRoom->position.x + 1; // subtract width for right corner, add to x for left corner
    newRoom->doors[0]->y = newRoom->position.y;

    // left door
    newRoom->doors[1] = malloc(sizeof(Position));
    newRoom->doors[1]->y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;
    newRoom->doors[1]->x = newRoom->position.x;

    // bottom door
    newRoom->doors[2] = malloc(sizeof(Position));
    newRoom->doors[2]->x = rand() % (newRoom->width - 2) + newRoom->position.x + 1;
    newRoom->doors[2]->y = newRoom->position.y + newRoom->height - 1;

    // right door
    newRoom->doors[3] = malloc(sizeof(Position));
    newRoom->doors[3]->y = rand() % (newRoom->height - 2) + newRoom->position.y + 1;
    newRoom->doors[3]->x = newRoom->position.x + newRoom->width - 1;

    return newRoom;
}

int drawRoom(Room *room)
{
    int x;
    int y;

    // draw the top and bottom
    for (x = room->position.x; x < room->position.x + room->width; x++)
    {
        mvprintw(room->position.y, x, "-");                    // top
        mvprintw(room->position.y + room->height - 1, x, "-"); // add room height to go to bottom
    }

    // now draw the floors and walls

    for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++)
    {
        mvprintw(y, room->position.x, "|");
        mvprintw(y, room->position.x + room->width - 1, "|");
        for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
        {
            mvprintw(y, x, ".");
        }
    }

    // draw doors

    mvprintw(room->doors[0]->y, room->doors[0]->x, "+");
    mvprintw(room->doors[1]->y, room->doors[1]->x, "+");
    mvprintw(room->doors[2]->y, room->doors[2]->x, "+");
    mvprintw(room->doors[3]->y, room->doors[3]->x, "+");
    return 0;
}

int connectDoors(Position *doorOne, Position *doorTwo)
{

    Position temp;
    Position previous;
    int count = 0;
    temp.x = doorOne->x;
    temp.y = doorOne->y;


    previous = temp;

    while (1)
    {
        // step left
        if (abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x) && (mvinch(temp.y, temp.x - 1) == ' '))
        {
            previous.x = temp.x;
            temp.x = temp.x - 1;
        }
        // step right
        else if (abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x) && (mvinch(temp.y, temp.x + 1) == ' '))
        {
            previous.x = temp.x;
            temp.x = temp.x + 1;
        }
        // step down
        else if (abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y) && (mvinch(temp.y + 1, temp.x) == ' '))
        {
            previous.y = temp.y;
            temp.y = temp.y + 1;
        }
        // step up
        else if (abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y) && (mvinch(temp.y - 1, temp.x) == ' '))
        {
            previous.y = temp.y;
            temp.y = temp.y - 1;
        }
        else
        {
            if (count == 0) {
               
                temp = previous;
                count++;
                continue;

            }
            else {
            return 1;
            }
           
        }
        mvprintw(temp.y, temp.x, "#");

    }

    return 0;
}

