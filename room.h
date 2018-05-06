#ifndef ROOM_H
#define ROOM_H
#include <vector>
#include "door.h"

class Room
{
public:
    Position origin;
    int height;
    int width;
    std::vector<Door> doors;

    Room(int x, int y, int height, int width);
    int drawRoom();

};

#endif // ROOM_H
