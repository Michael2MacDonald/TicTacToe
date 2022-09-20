/**
 * Michael MacDonald
 * 
 * 
 * A simple tty tic-tac-toe game. Play with two players.
 * 
 * 
 * 
 */

#include <iostream>
#include <iomanip>
//#include <cstring>
#include <climits>

int check(int board[][3], int player);

void printBoard(int board[][3]) {
	for (int i=0; i<3; i++) { // print each row
		for (int j=0; j<3; j++) { // print the column of each row
			char value = '?';
			if (board[i][j] == 1) { value = 'x'; }
			else if (board[i][j] == 2) { value = 'o'; }
			std::cout << " " << value << " ";
			// Column divider after first and second columns
			if (j<2) { std::cout << "|"; }
			else { std::cout << "\n"; } // Else go to the next line
		}
		// Print the row divider after the first and second rows
		if (i<2) { std::cout << "---+---+---\n"; }
	}
	//std::cout << 
}

int main() {
	int board[][3] = { {0,0,0}, {0,0,0}, {0,0,0} };
	int turn = 1;

	std::cout << "=======================\n";
	std::cout << "Welcome to Tic-Tac-Toe!\n";
	std::cout << "=======================\n";

	while (true) { // Game loop
		std::cout << "\nPlayer " << turn <<"'s turn:\n";
		printBoard(board);
		
		char input[3]; // getline() stores 'n' characters plus the delimiting character so we need (2+1) 3 chars
		std::cin.getline(input, 3); // Get the cords from user
		
		/* getline() fetches n=2 characters plus the newline
		 * So, if you enter more than 2 characters, it won't see the
		 * '\n' in the 3rd places where it expects it to be. This breaks
		 * the program and causes enexpected behavior such as loops. The
		 * technical term we use for situations like this is "It went BRRRRRRR"
		 * It will throw an error so we clear the error and clear any
		 * remaining characters in the cin buffer so we can get a new
		 * user input.
		 */
		if (std::cin.fail()) {
			std::cout << "\n===== ERROR: FAILBIT! =====\n";
			std::cout << "Please enter a valid [row, column] input! Ex: '00'\n\n";
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			continue;
		}

//		std::cin.clear();
//		std::cin.ignore(INT_MAX, '\n');

		//std::cout << std::cin.gcount() << " characters read: " << input << '\n';

//		for (int i=0; i<4; i++) {
//			std::cin.getline(input, 3); // Get the cords from user
//			std::cout << input << '\n';		
//		}
		//return 0;
		
		// Ascii numbers to ints (only single digit)
		int r = (int)input[0] - 48;
		int c = (int)input[1] - 48;
		
		if (r<0 || r>2 || c<0 || c>2) {
			std::cout << "This space is invalid! Pick a new space!\n";
			continue;
		}
		else if (board[r][c] != 0) {
			std::cout << "This space is taken! Pick a new space!\n";
			continue;
		}
		
		if (turn==1) { board[r][c] = 1; } else { board[r][c] = 2; }

		// TODO: Check for wins and tie
		int win = check(board, turn);
		if (win == 1) { std::cout << "===== Player 1 Wins! =====\n"; return 0; }
		else if (win == 2) { std::cout << "===== Player 2 Wins! =====\n"; return 0; }
		else if (win == 3) { std::cout << "===== Tie! =====\n"; return 0; }
		else if (win == 0) { /* game is not over */ }

		if (turn==1) { turn = 2; } else  { turn = 1; } // Switch turns
	}

	return 0;
}


int check(int board[][3], int player) {
	// Check for tie
	bool tie = true;
	for (int i=0; i<3 && tie; i++) {
		for (int j=0; j<3 && tie; j++) {
			if (board[i][j] == 0) { tie = false; }
		}
	}
	if (tie) { return 3; }

	// check rows
	for (int i=0; i<3; i++) {
		int count = 0;
		for (int j=0; j<3; j++) {
			if (board[i][j] == player) { count++; }
		}
		if (count == 3) { return player; } // win
	}

	// check columns
	for (int i=0; i<3; i++) {
		int count = 0;
		for (int j=0; j<3; j++) {
			if (board[j][i] == player) { count++; }
		}
		if (count == 3) { return player; } // win
	}

	// check diaganal (top left to bottom right)
	int count = 0;
	if (board[0][0] == player) { count++; }
	if (board[1][1] == player) { count++; }
	if (board[2][2] == player) { count++; }
	if (count == 3) { return player; } // win

	// check diaganal (bottom left to top right)
	count = 0;
	if (board[2][0] == player) { count++; }
	if (board[1][1] == player) { count++; }
	if (board[0][2] == player) { count++; }
	if (count == 3) { return player; } // win

	return 0; // no win

}




