#include <ncurses.h>
#include "room.h"

Room::Room(int x, int y, int height, int width)
{
    this->origin = {x,y};
    this->height = height;
    this->width = width;
}

int Room::drawRoom() {
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

