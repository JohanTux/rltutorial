#ifndef DOOR_H
#define DOOR_H


enum DoorState {CLOSED, OPEN};
struct Position{
    int x;
    int y;
};

class Door
{
public:


  Position doorLocation;
  DoorState doorState;
  Door(Position p, DoorState s=OPEN);
};

#endif // DOOR_H
