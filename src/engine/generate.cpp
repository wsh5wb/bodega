/*
* Code to generate rooms for Hell or Highwater
* Still unfinished, need to set positions of rooms and integrate
* with the rest of engine code somehow
*
* Also need to implement a slightly more efficient algorithm if time allows
*/

#define NUM_ROOMS 10
#define GRID_SIZE 20

// room definitions
#define START_ROOM 2
#define REG_ROOM   1

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

#include <stdio.h> 
#include <stdlib.h> 
#include <random>
#include <iostream>
#include <time.h> 
#include <map>
#include <string>

using namespace std;

struct position{
    int x;
    int y;
    position(){}
    position(int x, int y){
        this->x = x;
        this->y = y;
    }

    string to_str(){
        return "("+to_string(x)+","+to_string(y)+")";
    }
}; typedef struct position pos_t;

struct room{
	struct room* doors[4];
	int size[2] = {5,5};
	pos_t pos;
	int availableDoors = 0;

}; typedef struct room room_t;

struct floor{
	map<string, room_t*> rooms;
	// spawn room
	room_t* startRoom;
	// "boss" room
	room_t* bossRoom;

}; typedef struct floor floor_t;

floor_t level;
char grid[GRID_SIZE][GRID_SIZE];

int adjacentRooms(int x, int y, room_t** arr){
    int directions[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};
    int i = 0;
    int rooms = false;
    
    for(int* dir : directions){
        if(x+dir[0] >= 0 && x+dir[0] < GRID_SIZE
            && y+dir[1] >= 0 && y+dir[1] < GRID_SIZE
            && grid[x+dir[0]][y+dir[1]]){
            rooms++;
            pos_t pos(dir[0],dir[1]);
            arr[i] = level.rooms[pos.to_str()];
        } else arr[i] = NULL;
        i++;
    }

    return rooms;
}

void generate(){
	random_device rd;
    mt19937 e(rd());
	uniform_int_distribution<int> dist(0, GRID_SIZE-1);

    room_t *startRoom = new room_t;
    startRoom->pos.x = dist(e); startRoom->pos.y = dist(e);
    grid[startRoom->pos.x][startRoom->pos.y] = START_ROOM;
    level.rooms[startRoom->pos.to_str()] = startRoom;

    // cout << "Making room @ " << startRoom->pos.to_str() << endl;
    unsigned int numRooms = 1;

    while(numRooms < NUM_ROOMS){
        int x = dist(e);
        int y = dist(e);
        pos_t pos(x,y);


        // if room already in the generated position
        if(level.rooms.count(pos.to_str()) > 0)
            continue;

        room_t* adjRooms[4];
        int adjacent = adjacentRooms(x,y,adjRooms);
        if(adjacent < 2 && adjacent > 0){
            // cout << "Making room @ " << pos.to_str() << endl;
            room_t* room = new room_t;
            numRooms++;
            grid[x][y] = REG_ROOM;
            // if there is a room above the new room
            if(adjRooms[NORTH]){
                room->doors[NORTH] = adjRooms[NORTH];
                adjRooms[NORTH]->doors[SOUTH] = room;
                room->availableDoors++;
                adjRooms[NORTH]->availableDoors++;
            }
            if(adjRooms[SOUTH]){
                room->doors[SOUTH] = adjRooms[SOUTH];
                adjRooms[SOUTH]->doors[NORTH] = room;
                room->availableDoors++;
                adjRooms[SOUTH]->availableDoors++;
            }
            if(adjRooms[EAST]){
                room->doors[EAST] = adjRooms[EAST];
                adjRooms[EAST]->doors[WEST] = room;
                room->availableDoors++;
                adjRooms[EAST]->availableDoors++;
            }
            if(adjRooms[WEST]){
                room->doors[WEST] = adjRooms[WEST];
                adjRooms[WEST]->doors[EAST] = room;
                room->availableDoors++;
                adjRooms[WEST]->availableDoors++;
            }

            level.rooms[pos.to_str()] = room;
        }
    }

}

void print_map(){
    bool first_seen = false;
    bool not_seen = true;
    for(int i = 0; i < GRID_SIZE; i++){
        not_seen = true;
        for(int j = 0; j < GRID_SIZE; j++){
            if(grid[i][j] == 0){
                if(!first_seen)
                    continue;
                cout << " ";
            }
            else{
                if(!first_seen){
                    first_seen = true;
                    for(int k = 0; k < j; k++)
                        cout << " ";
                }
                not_seen = false;
                cout << "o";
            }
        }
        if(!not_seen && first_seen)
            cout << "\n";
    }
    cout << "\n-------------------------------------------------------------------\n";
}

void clear_grid(){
    for(int i = 0; i < GRID_SIZE; i++){
        for(int j = 0; j < GRID_SIZE; j++){
            grid[i][j] = 0;
        }
    }
}

/* int main(){
    for(int i = 0; i < 5; i++){
        generate();
        print_map();
        level.rooms.clear();
        clear_grid();
    }
	return 0;
} */
