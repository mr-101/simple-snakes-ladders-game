#include <iostream>

using namespace std;

#define mp make_pair

int n , g[12][12];
char grid[12][12];

pair<int , int> players[15];
pair<int , int> q[12][12];

void start_grid() {
	for(int i = 0; i < 10; ++i)
		for(int j = 0; j < 10; ++j)
			grid[i][j] = '.';

    int prev = 0;
    for(int i = 10; i > 0; --i , prev++) {
        for(int j = 1 ; j <= 10; ++j) {
            if(!(i%2))
                g[i][j] = prev * 10 + j;
            else
                g[i][j] = prev*10 + (10-j+1);
        }
    }

	grid[9][1] = grid[9][8] = grid[6][4] = grid[4][1] = grid[2][1] = 'L'; // ladders
	grid[7][5] = grid[4][8] = grid[3][0] = grid[3][4] = grid[0][5] = 'S';  //snakes

	// ladders
	q[9][1] = mp(8 , 3);
	q[9][8] = mp(7 , 6);
	q[6][4] = mp(2 , 7);
	q[4][1] = mp(2 , 3);
	q[2][1] = mp(0 , 4);

	//snakes
	q[7][5] = mp(9 , 4);
	q[4][8] = mp(6 , 9);
	q[3][0] = mp(6 , 2);
	q[3][4] = mp(5 , 3);
	q[0][6] = mp(2 , 5);
}

void print_grid() {
    for(int i = 0; i < 10; ++i) {
        for(int j = 0; j < 10; ++j)
        cout << grid[i][j] << " ";
    cout << endl;
    }
    cout << endl;
}

int tie() {
	int x = rand();
	return x % 6 + 1;
}

int main() {
	start_grid();
	cout << "Enter number of players \n";
	cin >> n;
	for(int i = 0; i < n; ++i)
		players[i] = mp(10 , 1);
	while(1) {
        print_grid();
		for(int i = 0; i < n; ++i) {
            cout << endl;
			cout << "player number " << i+1 << " turn\n";
			cout << "please roll the tie\n";
			int posx = players[i].first , posy = players[i].second;
			char e; int t;
			cin >> e;
			t = tie();
			cout << "you get " << t << endl;
			cout << "your previous position was " << g[posx][posy] << endl;
			//int upper = (10 - posx + 1)*10;
			int newy;
			if(posx % 2) {
				newy = posy - t;
				if(newy <= 0) {
					newy--;
					newy *= -1;
					posx--;
				}
				posy = newy;
			}
			else {
				newy = posy + t;
				if(newy > 10) {
					newy -= 10;
					newy = 10 - newy + 1;
					posx--;
				}
				posy = newy;
			}
			if(grid[posx-1][posy-1] == 'L' || grid[posx-1][posy-1] == 'S') {
				int x = q[posx-1][posy-1].first;
				int y = q[posx-1][posy-1].second;
                posx = x+1;  posy = y+1;
			}
			players[i].first = posx;
			players[i].second = posy;

			if((posx == 1 && posy == 1) || posx < 1) {
				cout << "player number " << i+1 << " wins! congratulations\n";
				break;
			}
			cout << "your current postion " << g[posx][posy] << endl;
		}
	}
}
