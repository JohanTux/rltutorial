#include <QCoreApplication>
#include <ncurses.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <chrono>


using namespace std;

int screenSetup();
enum DoorState {CLOSED, OPEN};
struct Position{
    int x;
    int y;
};

class Door {


public:
  Position doorLocation;
  DoorState doorState;

  Door (Position p, DoorState s=OPEN){
    this->doorLocation = p;
    this->doorState = s;
  }
};



class Room {
    public:
    Position origin;
    int height;
    int width;
    std::vector<Door> doors;

    Room(int x, int y, int height, int width){
        this->origin = {x,y};
        this->height = height;
        this->width = width;
    }

    int drawRoom() {
        int x, y;

        /*draw top and bottom*/
        for (x = this->origin.x; x <= this->origin.x + this->width; x++) {
            mvprintw(this->origin.y, x, "-"); //top
            mvprintw(this->origin.y + this->height - 1, x, "-");  //bottom
        }

        /* draw the side walls & floors*/

        for (x = this->origin.x; x <= this->origin.x + this->width; x++){
            for (y = this->origin.y + 1; y < this->origin.y + this->height - 1; y++){
                if( (x == this->origin.x) || (x == this->origin.x + this->width) ){
                    mvprintw(y,x,"|");      //side walls
                } else {
                  mvprintw(y,x,".");        //floor
                }
            }
        }

        /*place the room's doors*/
        int j = 0;
        for (auto i = this->doors.begin(); i != this->doors.end(); i++){
            bool isOpen = this->doors.at(j).doorState;

            if (isOpen){
                mvprintw( this->doors.at(j).doorLocation.y,doors.at(j).doorLocation.x, "#");
              } else {
                mvprintw( this->doors.at(j).doorLocation.y,doors.at(j).doorLocation.x, "=");
              };
            j++;
          }


        return 1;
    }

};

class Player {
    public:
    Position location;
    int health;

    Player() {
        location = {15,15};
        health = 100;
    }
};
std::vector<Room> mapSetUp();
int handleInput(char, Player&);
int playerMove(int, int, Player&);

int main() {

    Player user;
    int ch;
    screenSetup();

    mapSetUp();
    playerMove(16, 16, user); //init player position

    /*Main game loop */
    while ( (ch = getch()) != 'q') {

        handleInput(ch, user);

    }

    endwin();
    return 0;

}
int handleInput(char input, Player& user){
    int newY=0, newX=0;

    switch(input){
        //move up
        case 'w':
            newY = user.location.y - 1;
            newX = user.location.x;
            break;
        //move left
        case 'a':
            newY = user.location.y;
            newX = user.location.x - 1;
            break;
        //move down
        case 's':
            newY = user.location.y + 1;
            newX = user.location.x;
            break;
        //move right
        case 'd':
            newY = user.location.y;
            newX = user.location.x + 1;
            break;
        default:
            return 0;
            break;
    }

    char newSpace = mvinch(newY, newX);
    if ( newSpace == '.' || newSpace == '#'){   //check for traversable space
        playerMove(newY, newX, user);           // and move there
    } else {
            move(user.location.y, user.location.x);         // or reset the cursor moved in mvinch
        }

    return 1;
}
int playerMove(int y, int x, Player& user){
    mvprintw(user.location.y,user.location.x, ".");     //put a . in the user's previous location
    user.location.y = y;                          //update our Player object y
    user.location.x = x;                          //update our Player object y
    mvprintw(user.location.y,user.location.x, "@");     //move the @ on the board
    move(user.location.y, user.location.x);             //repostion the cursor
    return 1;
}

int screenSetup() {
    initscr();
    noecho();
    refresh();
    return 0;
}

std::vector<Room> mapSetUp() {
    srand(time(NULL));

    std::vector<Room> rooms;

//    mvprintw(13,13,"--------");
//    mvprintw(14,13,"|......|");
//    mvprintw(15,13,"|......|");
//    mvprintw(16,13,"|......|");
//    mvprintw(17,13,"|......|");
//    mvprintw(18,13,"--------");

    rooms.push_back( Room(13, 13, 6, 8) ); // x, y, height, width
//    rooms[0].doors.push_back( Door(Position {16,13} ) );
//    rooms[0].doors.push_back( Door(Position {21,16}, CLOSED ) );
//    rooms[0].doors.push_back( Door(Position {17,18} ) );
//    rooms[0].doors.push_back( Door(Position {13,15} ) );

    /*top door*/
//    int x1, y1;
//    x1 = rand() % rooms.at(0).width + rooms.at(0).origin.x;
//    y1 = rooms.at(0).origin.y;

    for (int i = 0; i < 4; i++ ){
        switch (i) {
          case 0: //top door
            rooms.at(0).doors.push_back( Door(Position {  rand() % rooms.at(0).width + rooms.at(0).origin.x,
                                                          rooms.at(0).origin.y
                                                        }
                                              )
                                         );
            break;
          case 1: //left door
            rooms.at(0).doors.push_back( Door(Position {  rooms.at(0).width + rooms.at(0).origin.x,
                                                          rand() % rooms.at(0).height + rooms.at(0).origin.y
                                                        }
                                              )
                                         );
            break;
          case 2: //bottom door
            rooms.at(0).doors.push_back( Door(Position {  rand() % rooms.at(0).width + rooms.at(0).origin.x,
                                                          rooms.at(0).origin.y + rooms.at(0).height -1
                                                        }
                                              )
                                         );
            break;
          case 3: //right door
            rooms.at(0).doors.push_back( Door(Position {  rooms.at(0).origin.x,
                                                          rand() % rooms.at(0).height + rooms.at(0).origin.y
                                                        }
                                              )
                                         );
            break;

          }

      }

    rooms[0].drawRoom();

//    mvprintw( 9,40,"--------");
//    mvprintw(10,40,"|......|");
//    mvprintw(11,40,"|......|");
//    mvprintw(12,40,"|......|");
//    mvprintw(13,40,"|......|");
//    mvprintw(14,40,"|......|");
//    mvprintw(15,40,"|......|");
//    mvprintw(16,40,"|......|");
//    mvprintw(17,40,"|......|");
//    mvprintw(18,40,"--------");

    rooms.push_back( Room(40, 9, 10, 8) );
    rooms[1].doors.push_back( Door(Position {44,9} ) );
    rooms[1].doors.push_back( Door(Position {40,12}, CLOSED ) );
    rooms[1].doors.push_back( Door(Position {48,16} ) );
    rooms[1].doors.push_back( Door(Position {45,18} ) );
    rooms[1].drawRoom();

//    mvprintw( 3,6,"------13-------");
//    mvprintw( 4,6,"|...........|");
//    mvprintw( 5,6,"|...........|");
//    mvprintw( 6,6,"|...........|");
//    mvprintw( 7,6,"|...........|");
//    mvprintw( 8,6,"---------15----");

    rooms.push_back( Room(6, 3, 6, 12) );
    rooms[2].doors.push_back( Door(Position {13,3}, CLOSED ) ); //T
    rooms[2].doors.push_back( Door(Position {6,6}, CLOSED ) );  //R
    rooms[2].doors.push_back( Door(Position {18,6}, CLOSED ) ); //L
    rooms[2].doors.push_back( Door(Position {16,8}, CLOSED ) ); //B
    rooms[2].drawRoom();

    return rooms;
}
