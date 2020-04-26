/*
* Code to generate rooms for Hell or Highwater
* Still unfinished, need to set positions of rooms and integrate
* with the rest of engine code somehow
*
* Also need to implement a slightly more efficient algorithm if time allows
*/
#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#define NUM_ROOMS 25
#define GRID_SIZE 8


// room definitions
#define REG_ROOM   	1
#define START_ROOM 	2
#define BOSS_ROOM	100

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
        return "("+to_string(y)+","+to_string(x)+")";
    }
}; typedef struct position pos_t;

struct room{
	unsigned char doors = 0;
	int size[2] = {5,5};
	pos_t pos;
	int availableDoors = 0;
	int distFromBoss = 0;

}; typedef struct room room_t;

struct floor{
	map<string, room_t*> rooms;
	// spawn room
	room_t startRoom;
	// "boss" room
	room_t bossRoom;

}; typedef struct floor floor_t;


class MazeGenerator{

public:
	MazeGenerator();
	int adjacentRooms(int x, int y, room_t** arr);
	bool generate();
	void generateNoBoss();
	void print_map();
	void clear_grid();
	int** getLayout();
	int** getLayoutNoBoss();
	floor_t getLevel();

private:
	void generateBossRoom(uniform_int_distribution<int>& dist, mt19937 &e);
	void setStartRoom();
	bool checkPossible(int x, int y);
	floor_t level;
	int** grid;
	int failCount = 0;

};

#endif




