#include "MazeGenerator.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int MazeGenerator::adjacentRooms(int x, int y, room_t **arr) {
	int directions[4][2] = { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 } };
	int i = 0;
	int rooms = false;

	for (int *dir : directions) {
		if (x + dir[0] >= 0 && x + dir[0] < GRID_SIZE && y + dir[1] >= 0
				&& y + dir[1] < GRID_SIZE && grid[x + dir[0]][y + dir[1]]) {
			rooms++;
			pos_t pos(dir[0], dir[1]);
			arr[i] = level.rooms[pos.to_str()];
		} else
			arr[i] = NULL;
		i++;
	}

	return rooms;
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

	room_t *startRoom = new room_t;
	startRoom->pos.x = dist(e);
	startRoom->pos.y = dist(e);
	grid[startRoom->pos.x][startRoom->pos.y] = START_ROOM;
	level.rooms[startRoom->pos.to_str()] = startRoom;

	// cout << "Making room @ " << startRoom->pos.to_str() << endl;
	unsigned int numRooms = 1;
	cerr << "adding rooms0\n";
	while (numRooms < NUM_ROOMS) {
		int x = dist(e);
		int y = dist(e);
		pos_t pos(x, y);

		// if room already in the generated position
		if (level.rooms.count(pos.to_str()) > 0)
			continue;

		room_t *adjRooms[4];
		int adjacent = adjacentRooms(x, y, adjRooms);
		if (adjacent < 2 && adjacent > 0) {
			// cout << "Making room @ " << pos.to_str() << endl;
			room_t *room = new room_t;
			numRooms++;
			grid[x][y] = REG_ROOM;
			// if there is a room above the new room
			if (adjRooms[NORTH]) {
				room->doors[NORTH] = adjRooms[NORTH];
				adjRooms[NORTH]->doors[SOUTH] = room;
				room->availableDoors++;
				adjRooms[NORTH]->availableDoors++;
			}
			if (adjRooms[SOUTH]) {
				room->doors[SOUTH] = adjRooms[SOUTH];
				adjRooms[SOUTH]->doors[NORTH] = room;
				room->availableDoors++;
				adjRooms[SOUTH]->availableDoors++;
			}
			if (adjRooms[EAST]) {
				room->doors[EAST] = adjRooms[EAST];
				adjRooms[EAST]->doors[WEST] = room;
				room->availableDoors++;
				adjRooms[EAST]->availableDoors++;
			}
			if (adjRooms[WEST]) {
				room->doors[WEST] = adjRooms[WEST];
				adjRooms[WEST]->doors[EAST] = room;
				room->availableDoors++;
				adjRooms[WEST]->availableDoors++;
			}

			level.rooms[pos.to_str()] = room;
		}
	}
	cerr << "adding rooms0\n";

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
