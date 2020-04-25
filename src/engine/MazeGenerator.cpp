#include "MazeGenerator.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int MazeGenerator::adjacentRooms(int x, int y, room_t **arr) {
	int directions[4][2] = { { -1, 0 }, { 0, 1 }, { 1, 0 }, { 0, -1 } };
	int i = 0;
	int rooms = false;

	for (int *dir : directions) {
		if (x + dir[1] >= 0 && x + dir[1] < GRID_SIZE && y + dir[0] >= 0
				&& y + dir[0] < GRID_SIZE && grid[y + dir[0]][x + dir[1]]) {
			if(grid[y+dir[0]][x+dir[1]] == BOSS_ROOM){
				// printf("Boss room at (%x,%x)\n", y+dir[0],x+dir[1]);
				return 0;
			}
			rooms++;
			pos_t pos(x+dir[1], y+dir[0]);
			arr[i] = level.rooms[pos.to_str()];
			// printf("room (%d,%d) is adj to (%d,%d), %d\n",x,y,x+dir[1],y+dir[0],i);
			// printf("Adj addr: %x\n", arr[i]);
		} else
			arr[i] = NULL;
		i++;
	}

	return rooms;
}

void MazeGenerator::generateNoBoss() {

	cerr << "making grid0\n";
	grid = new int*[GRID_SIZE];
	for (int i = 0; i < GRID_SIZE; i++) {
		grid[i] = new int[GRID_SIZE];
		for (int j = 0; j < GRID_SIZE; j++) {
			grid[i][j] = 0;
		}
	}
	cerr << "making grid1\n";
	random_device rd;
	mt19937 e(rd());
	uniform_int_distribution<int> dist(0, GRID_SIZE - 1);

	room_t *startRoom = new room_t;
	startRoom->pos.x = dist(e);
	startRoom->pos.y = dist(e);
	grid[startRoom->pos.y][startRoom->pos.x] = START_ROOM;
	level.rooms[startRoom->pos.to_str()] = startRoom;

	// cout << "Making room @ " << startRoom->pos.to_str() << endl;
	unsigned int numRooms = 1;
	cerr << "adding rooms0\n";
	while (numRooms < NUM_ROOMS) {
		int x = dist(e);
		int y = dist(e);
		pos_t pos(x,y);

		// if room already in the generated position
		if (level.rooms.count(pos.to_str()) > 0)
			continue;

		room_t* adjRooms[4];
		int adjacent = adjacentRooms(x, y, adjRooms);
		// printf("adjecent rooms %d\n", adjacent);
		if (adjacent == 1) {
			// cout << "Making room @ " << pos.to_str() << endl;
			room_t* room = new room_t;
			numRooms++;
			grid[y][x] = REG_ROOM;

			// layout is WSEN
			//			 0000
			if (adjRooms[NORTH]) {
				// printf("Adding N-S connection b/w (%d,%d) and (%d,%d)\n", x,y,x,y-1);
				room->doors |= (1<<NORTH);
				adjRooms[NORTH]->doors |= (1<<SOUTH);
				room->availableDoors++;
				adjRooms[NORTH]->availableDoors++;
			}
			if (adjRooms[EAST]) {
				// printf("Adding E-W connection b/w (%d,%d) and (%d,%d)\n", x,y,x+1,y);
				room->doors |= (1<<EAST);
				adjRooms[EAST]->doors |= (1<<WEST);
				room->availableDoors++;
				adjRooms[EAST]->availableDoors++;
			}
			if (adjRooms[SOUTH]) {
				// printf("Adding S-N connection b/w (%d,%d) and (%d,%d)\n", x,y,x,y+1);
				room->doors |= (1<<SOUTH);
				adjRooms[SOUTH]->doors |= (1<<NORTH);
				room->availableDoors++;
				adjRooms[SOUTH]->availableDoors++;
			}
			if (adjRooms[WEST]) {
				// printf("Adding W-E connection b/w (%d,%d) and (%d,%d)\n", x,y,x-1,y);
				room->doors |= (1<<WEST);
				adjRooms[WEST]->doors |= (1<<EAST);
				room->availableDoors++;
				adjRooms[WEST]->availableDoors++;
			}

			level.rooms[pos.to_str()] = room;
			// delete [] adjRooms;
		}
	}
	cerr << "adding rooms0\n";

}


void MazeGenerator::generate() {

	cerr << "making grid0\n";
	grid = new int*[GRID_SIZE];
	for (int i = 0; i < GRID_SIZE; i++) {
		grid[i] = new int[GRID_SIZE];
		for (int j = 0; j < GRID_SIZE; j++) {
			grid[i][j] = 0;
		}
	}
	cerr << "making grid1\n";
	random_device rd;
	mt19937 e(rd());
	uniform_int_distribution<int> dist(0, GRID_SIZE - 1);

	generateBossRoom(dist, e);

	// cout << "Making room @ " << startRoom->pos.to_str() << endl;
	unsigned int numRooms = 2;
	cerr << "adding rooms0\n";
	while (numRooms < NUM_ROOMS) {
		int x = dist(e);
		int y = dist(e);
		pos_t pos(x,y);

		// if room already in the generated position
		if (level.rooms.count(pos.to_str()) > 0)
			continue;

		room_t* adjRooms[4];
		// printf("checking %s\n", pos.to_str().c_str());
		int adjacent = adjacentRooms(x, y, adjRooms);
		// printf("adjecent rooms %d\n", adjacent);
		if (adjacent == 1) {

			// cout << "Making room @ " << pos.to_str() << endl;
			room_t* room = new room_t;
			room->pos.x = x;
			room->pos.y = y;
			numRooms++;
			printf("Generating room at %s\n", pos.to_str().c_str());
			grid[y][x] = REG_ROOM;

			// layout is WSEN
			//			 0000
			if (adjRooms[NORTH]) {
				// printf("Adding N-S connection b/w (%d,%d) and (%d,%d)\n", x,y,x,y-1);
				room->doors |= (1<<NORTH);
				adjRooms[NORTH]->doors |= (1<<SOUTH);
				room->availableDoors++;
				adjRooms[NORTH]->availableDoors++;
				room->distFromBoss = adjRooms[NORTH]->distFromBoss+1;
			}
			if (adjRooms[EAST]) {
				// printf("Adding E-W connection b/w (%d,%d) and (%d,%d)\n", x,y,x+1,y);
				room->doors |= (1<<EAST);
				adjRooms[EAST]->doors |= (1<<WEST);
				room->availableDoors++;
				adjRooms[EAST]->availableDoors++;
				if(!room->distFromBoss)
					room->distFromBoss = adjRooms[EAST]->distFromBoss+1;
			}
			if (adjRooms[SOUTH]) {
				// printf("Adding S-N connection b/w (%d,%d) and (%d,%d)\n", x,y,x,y+1);
				room->doors |= (1<<SOUTH);
				adjRooms[SOUTH]->doors |= (1<<NORTH);
				room->availableDoors++;
				adjRooms[SOUTH]->availableDoors++;
				if(!room->distFromBoss)
					room->distFromBoss = adjRooms[SOUTH]->distFromBoss+1;
			}
			if (adjRooms[WEST]) {
				// printf("Adding W-E connection b/w (%d,%d) and (%d,%d)\n", x,y,x-1,y);
				room->doors |= (1<<WEST);
				adjRooms[WEST]->doors |= (1<<EAST);
				room->availableDoors++;
				adjRooms[WEST]->availableDoors++;
				if(!room->distFromBoss)
					room->distFromBoss = adjRooms[WEST]->distFromBoss+1;
			}

			level.rooms[pos.to_str()] = room;
			// delete [] adjRooms;
		}
	}

	setStartRoom();

	cerr << "adding rooms0\n";

}

void MazeGenerator::generateBossRoom(uniform_int_distribution<int>& dist, mt19937 &e){

	int x = dist(e);
	int y = dist(e);
	if(x+1 >= GRID_SIZE)	x--;
	if(y+1 >= GRID_SIZE) 	y--;
	int coords[4][2] = {{y,x},{y+1,x},{y,x+1},{y+1,x+1}};
	for(int i = 0; i < 4; i++){
		grid[coords[i][0]][coords[i][1]] = BOSS_ROOM;
		room_t* bossRoom = new room_t;
		bossRoom->pos.x = coords[i][1];
		bossRoom->pos.y = coords[i][0];
		bossRoom->distFromBoss = 0;
		level.rooms[bossRoom->pos.to_str()] = bossRoom;
		printf("Added boss room at %s\n", bossRoom->pos.to_str().c_str());
	}

	pos_t pos;
	srand(time(NULL));
	int connect = rand() % 8;
	unsigned char adjRoomDoor = 0;
	int adjRoomLocs[8][2]={{x,y-1},{x+1,y-1},{x-1,y},{x+2,y},{x-1,y+1},{x+2,y+1},{x,y+2},{x+1,y+2}};

	while(!checkPossible(adjRoomLocs[connect][0], adjRoomLocs[connect][1])){
		connect = rand() % 8;
	}
	pos.x = adjRoomLocs[connect][0]; pos.y = adjRoomLocs[connect][1];
	printf("CONNECT IS %d\n", connect);

	if(connect == 0){
		adjRoomDoor = 1<<SOUTH;
		level.rooms["("+to_string(y)+","+to_string(x)+")"]->doors = (1<<NORTH);
	}
	else if(connect == 1){
		adjRoomDoor = 1<<SOUTH;
		level.rooms["("+to_string(y)+","+to_string(x+1)+")"]->doors = (1<<NORTH);
	}
	else if(connect == 2){
		adjRoomDoor = 1<<EAST;
		level.rooms["("+to_string(y)+","+to_string(x)+")"]->doors = (1<<WEST);
	}
	else if(connect == 3){
		adjRoomDoor = 1<<WEST;
		level.rooms["("+to_string(y)+","+to_string(x+1)+")"]->doors = (1<<EAST);
	}
	else if(connect == 4){
		adjRoomDoor = 1<<EAST;
		level.rooms["("+to_string(y+1)+","+to_string(x)+")"]->doors = (1<<WEST);
	}
	else if(connect == 5){
		adjRoomDoor = 1<<WEST;
		level.rooms["("+to_string(y+1)+","+to_string(x+1)+")"]->doors = (1<<EAST);
	}
	else if(connect == 6){
		adjRoomDoor = 1<<NORTH;
		level.rooms["("+to_string(y+1)+","+to_string(x)+")"]->doors = (1<<SOUTH);
	}
	else if(connect == 7){
		adjRoomDoor = 1<<NORTH;
		level.rooms["("+to_string(y+1)+","+to_string(x+1)+")"]->doors = (1<<SOUTH);
	}

	room_t* room = new room_t;
	room->doors = adjRoomDoor;
	room->pos = pos;
	grid[pos.y][pos.x] = REG_ROOM;
	room->availableDoors = 1;
	room->distFromBoss = 1;
	level.rooms[pos.to_str()] = room;

	

}

void MazeGenerator::setStartRoom(){
	for(auto it = level.rooms.begin(); it != level.rooms.end(); ++it){
		if(it->second->distFromBoss >= 7){
			grid[it->second->pos.y][it->second->pos.x] = START_ROOM;
			return;
		}
	}
}

// X,Y is boss's adjacent room's x,y
bool MazeGenerator::checkPossible(int x, int y){
	// x or y out of bounds, not possible
	printf("Checking generation for (%x,%x)\n", y,x);
	if(x<0 || y<0 || x>=GRID_SIZE || y>=GRID_SIZE)
		return false;
	// if room is in top left or bottom right corner area, not possible
	if(x+y==0 || x+y==1 || x+y==2*(GRID_SIZE-1)-1 || x+y==2*(GRID_SIZE-1))
		return false;
	// if room is in bottom left corner area, not possible
	if(x<2 && y>GRID_SIZE-3){
		if(x==1 && y==GRID_SIZE-2)
			return true;
		return false;
	}
	// if room is in top right corner area, not possible
	if(x>GRID_SIZE-3 && y<2){
		if(x==GRID_SIZE-2 && y==1)
			return true;
		return false;
	}

	printf("Generation is possible\n");

	return true;
}

void MazeGenerator::print_map() {
	bool first_seen = false;
	bool not_seen = true;
	for (int i = 0; i < GRID_SIZE; i++) {
		not_seen = true;
		for (int j = 0; j < GRID_SIZE; j++) {
			if (grid[i][j] == 0) {
				if (!first_seen)
					continue;
				cout << " ";
			} else {
				if (!first_seen) {
					first_seen = true;
					for (int k = 0; k < j; k++)
						cout << " ";
				}
				not_seen = false;
				cout << "o";
			}
		}
		if (!not_seen && first_seen)
			cout << "\n";
	}
	cout
			<< "\n-------------------------------------------------------------------\n";
}
void MazeGenerator::clear_grid() {
	for (int i = 0; i < GRID_SIZE; i++) {
		for (int j = 0; j < GRID_SIZE; j++) {
			grid[i][j] = 0;
		}
	}
}
int** MazeGenerator::getLayout() {
	generate();
	return (int**) grid;
}

floor_t MazeGenerator::getLevel(){
	return this->level;
}
