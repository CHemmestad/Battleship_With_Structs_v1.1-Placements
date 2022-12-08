#include <iostream>
#include <iomanip>

using namespace std;

struct ShipInfo {
	int shipSize = 0;
	string shipName = "\0" ;
	bool destroyed = false;

	void check() {
		if (shipSize == 0) {
			destroyed = true;
		}
		if (destroyed == true) {
			cout << shipName << " was destroyed!" << endl;
		}
		else
			cout << shipName << " is coooooool! X)" << endl;
	}
};

typedef char GRID[10][10][3];

enum placement { up = 1, down = 2, right = 3, left = 4 };

void intializeGrids(GRID player);

ShipInfo setShipInfo(ShipInfo ship, int size, string name);

void printBoards(GRID ocean, int layers);

void placeShip(GRID player, ShipInfo ship, bool user);

void setEqual(GRID temp, GRID player);

bool validPlacement(GRID player, ShipInfo ship, string direction, int x_axis, int y_axis);


int main() {

	GRID playerOne;
	GRID playerCom;

	intializeGrids(playerOne);
	intializeGrids(playerCom);

	ShipInfo carrier;
	ShipInfo battleship;
	ShipInfo cruiser;
	ShipInfo submarine;
	ShipInfo destroyer;

	carrier = setShipInfo(carrier, 5, "Carrier");
	battleship = setShipInfo(battleship, 4, "Battleship");
	cruiser = setShipInfo(cruiser, 3, "Cruiser");
	submarine = setShipInfo(submarine, 3, "Submarine");
	destroyer = setShipInfo(destroyer, 2, "Destroyer");

	ShipInfo carrierCom = carrier;
	ShipInfo battleshipCom = battleship;
	ShipInfo cruiserCom = cruiser;
	ShipInfo submarineCom = submarine;
	ShipInfo destroyerCom = destroyer;

	placeShip(playerOne, carrier, 1);
	placeShip(playerOne, battleship, 1);
	placeShip(playerOne, cruiser, 1);
	placeShip(playerOne, submarine, 1);
	placeShip(playerOne, destroyer, 1);
	
	printBoards(playerOne, 2);

	carrier.check();
	carrier.shipSize = 0;
	carrier.check();

	//printBoards(playerCom, 2);

	return 0;
}

void placeShip(GRID player, ShipInfo ship, bool user) { // 1 for user 0 for com

	GRID temp;
	intializeGrids(temp);
	setEqual(temp, player);

	bool check = false;
	int x_axis = NULL;
	int y_axis = NULL;
	string direction;

	if (user) {
		do {
			printBoards(temp, 2);
			cout << "Pick a place to put your " << ship.shipName << endl;

			do {
				cout << "Enter a number on the x axis " << endl;
				cin >> x_axis;
			} while ((x_axis < 1) || (x_axis > 10));

			for (int x = 0; x < 10; x++) {
				temp[x_axis - 1][x][1] = '|';
			}
			printBoards(temp, 2);

			do {
				cout << "Enter a number on the y axis " << endl;
				cin >> y_axis;
			} while ((y_axis < 1) || (y_axis > 10));

			for (int x = 0; x < 10; x++) {
				temp[x][y_axis - 1][1] = '-';
			}
			printBoards(temp, 2);
			intializeGrids(temp);
			setEqual(temp, player);

			do {
				cout << "Type up, down, right, or left" << endl;
				cin >> direction;
			} while ((direction != "up") && (direction != "down") && (direction != "left") && (direction != "right"));
			check = validPlacement(player, ship, direction, x_axis, y_axis);
		} while (!check);
		//printBoards(player, 2);
	}
	else {
		// do com stuff
	}
}

void setEqual(GRID temp, GRID player) {
	for (int z = 0; z < 3; z++) {
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				temp[x][y][z] = player[x][y][z];
			}
		}
	}
}

bool validPlacement(GRID player, ShipInfo ship, string direction, int x_axis, int y_axis) {
	GRID temp;
	intializeGrids(temp);
	setEqual(temp, player);
	int size = ship.shipSize;
	bool valid = true;
	if (direction == "up") {
		for (int x = 0; x < size; x++) {
			if (temp[x_axis - 1][y_axis - 1 - x][1] == '#') {
				valid = false;
			}
			if (y_axis - 1 - x < 0) {
				valid = false;
			}
		}
		if (valid) {
			for (int x = 0; x < size; x++) {
				temp[x_axis - 1][y_axis - 1 - x][1] = '#';
			}
			setEqual(player, temp);
		}
	}
	if (direction == "down") {
		for (int x = 0; x < size; x++) {
			if (temp[x_axis - 1][y_axis - 1 + x][1] == '#') {
				valid = false;
			}
			if (y_axis - 1 + x > 9) {
				valid = false;
			}
		}
		if (valid) {
			for (int x = 0; x < size; x++) {
				temp[x_axis - 1][y_axis - 1 + x][1] = '#';
			}
			setEqual(player, temp);
		}
	}
	if (direction == "right") {
		for (int x = 0; x < size; x++) {
			if (temp[x_axis - 1 + x][y_axis - 1][1] == '#') {
				valid = false;
			}
			if (x_axis - 1 + x > 9) {
				valid = false;
			}
		}
		if (valid) {
			for (int x = 0; x < size; x++) {
				temp[x_axis - 1 + x][y_axis - 1][1] = '#';
			}
			setEqual(player, temp);
		}
	}
	if (direction == "left") {
		for (int x = 0; x < size; x++) {
			if (temp[x_axis - 1 - x][y_axis - 1][1] == '#') {
				valid = false;
			}
			if (x_axis - 1 - x < 0) {
				valid = false;
			}
		}
		if (valid) {
			for (int x = 0; x < size; x++) {
				temp[x_axis - 1 - x][y_axis - 1][1] = '#';
			}
			setEqual(player, temp);
		}
	}
	return valid;
}

void printBoards(GRID ocean, int layers) {
	system("cls");
	cout << "\n";
	for (int z = 0; z < layers; z++) {
		cout << "Y\\ 1 2 3 4 5 6 7 8 9 10 - X" << endl;
		for (int y = 0; y < 10; y++) {
			cout << setw(2) << y+1;
			for (int x = 0; x < 10; x++) {
				cout << setw(2) << ocean[x][y][z];
			}
			cout << endl;
		}
		cout << endl;
	}
	system("pause");
}

ShipInfo setShipInfo(ShipInfo ship, int size, string name) {
	ship.shipSize = size;
	ship.shipName = name;

	return ship;
}

void intializeGrids( GRID player ) {
	for (int z = 0; z < 3; z++) {
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				player[x][y][z] = '~';
			}
		}
	}
}