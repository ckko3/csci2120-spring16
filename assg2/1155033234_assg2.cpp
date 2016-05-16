/*
' CSCI2120 Introduction to Software Engineering
'
' Assignment 2
'
'

' I declare that the assignment here submitted is original except for source
' material explicitly acknowledged. I also acknowledge that I am aware of
' University policy and regulations on honesty in academic work, and of the
' disciplinary guidelines and procedures applicable to breaches of such policy
' and regulations, as contained in the following University website:
' http://www.cuhk.edu.hk/policy/academichonesty/.
' Student Name: Ko Chi Keung
' Student ID: 1155033234
' Date: 5/3/2016
*/

#include <iostream>
#include <conio.h>	// for _getch
#include <string>	// for getline, length
#include <cctype>	// for isalpha, isdigit
#include <cstdlib>	// for srand, rand, exit
#include <ctime>	// for time
using namespace std;

class Player {
public:
	Player(string name, string ws) : playerName(name), winningStatement(ws) {}	// constructor
	string getName() const {
		return playerName;
	}
	string getWS() const {
		return winningStatement;
	}
	void setName(string name) {
		playerName = name;
	}
	void setWS(string ws) {
		winningStatement = ws;
	}
	void setGuesture(char g) {
		gesture = g;
	}
	char getGesture() const {
		return gesture;
	}
	// convert gesture to string
	string getGesture_to_s() const {
		switch (gesture) {
			case '1': return "rock"; break;
			case '2': return "paper"; break;
			case '3': return "scissors"; break;
			case '4': return "Spock"; break;
			default: return "lizard"; break;
		}
	}
	// obtain gesture from player, which will be overridden in subclasses
	virtual void nextGuesture() = 0;
	
private:
	string playerName; // player name
	string winningStatement; // winning statement
	char gesture; // gesture
};

class HumanPlayer : public Player {
public:
	HumanPlayer(string name, string ws) : Player(name, ws) {}	// constructor
	// obtain gesture from HumanPlayer
	virtual void nextGuesture() {
		cout << getName() << ", please choose your gesture:" << endl;
		cout << "1. rock" << endl;
		cout << "2. paper" << endl;
		cout << "3. scissors" << endl;
		cout << "4. Spock" << endl;
		cout << "5. lizard" << endl;
		
		// input from player
		char g;
		// ignore invalid input
		do {
			g = _getch();
		} while (!(g == '1' || g == '2' || g == '3' || g == '4' || g == '5'));
		
		setGuesture(g);
		system("cls"); 
	}	
};

class ComputerPlayer : public Player{
public:
	ComputerPlayer(string name, string ws) : Player(name, ws) {}	// constructor
	// obtain gesture from ComputerPlayer
	virtual void nextGuesture() {
		int n = rand() % 5 + 1;	// randomly generate an integer between 1 to 5 inclusively
		switch (n) {
			case 1: setGuesture('1'); break;
			case 2: setGuesture('2'); break;
			case 3: setGuesture('3'); break;
			case 4: setGuesture('4'); break;
			default: setGuesture('5'); break;
		}
	}	
};

class Game {
public:
	/* start game */
	void start() {
		/* step 1: display the game menu */
		cout << "Rock ¡V paper ¡Vscissors ¡V Spock ¡V lizard" << endl;
		cout << "1. Player vs. Computer" << endl;
		cout << "2. Player vs. Player" << endl;
		cout << "3. Exit" << endl;
		// input from player
		char mode;
		// ignore invalid input
		do {
			mode = _getch();
		} while (!(mode == '1' || mode == '2' || mode == '3'));
		
		system("cls"); 
		
		if (mode == '3') {
			// Exit
			exit (0);
		}
		else {
			/* step 2: select the number of rounds */
			cout << "Please select the Number of Rounds:" << endl;
			cout << "1. Three rounds" << endl;
			cout << "2. Five rounds" << endl;
			// input from player
			char round;
			// ignore invalid input
			do {
				round = _getch();
			} while (!(round == '1' || round == '2'));
			
			system("cls");
			
			/* step 3: ask for player information */
			if (mode == '1') {
				// player vs computer
				
				// ask for name
				string name = askPlayerName("", "Computer");
				// ask for winning statement
				string ws = askWinningStatement();
				
				// player 1 is human player
				player1 = new HumanPlayer(name, ws);
				
				// player 2 is computer player
				player2 = new ComputerPlayer("Computer", "You cannot beat a computer!");
				
			}
			else {
				// player vs player
				
				// ask for name for player 1
				string player1_name = askPlayerName("Player 1", "");
				// ask for winning statement for player 1
				string ws = askWinningStatement();
				
				// Player 1 is human player
				player1 = new HumanPlayer(player1_name, ws);
				
				system("cls");
				
				// ask for name for player 2
				string player2_name = askPlayerName("Player 2", player1_name);
				// ask for winning statement for player 2
				ws = askWinningStatement();
				
				// player 2 is human player
				player2 = new HumanPlayer(player2_name, ws);
				
			}
			
			system("cls");
			
			/* step 4: play game */
			play(round);
			 
		}
	}
	
	/* ask for player name */
	string askPlayerName(string whichPlayer, string nameNotAllowed) {
		string name;
		bool validName = false;
		
		do {
			if (whichPlayer.empty())
				cout << "Please input your name:" << endl;
			else
				cout << whichPlayer << ", please input your name:" << endl;
				
			getline(cin, name);
			
			//check whether valid
			for (int i = 0; i < name.length(); i++) {
				if (isalpha(name[i])) {
					validName = true;
					break;
				}
			}
			if (!validName)
				cout << "Invalid player name! Your name should contain at least one alphabet." << endl;
			
			// check whether name is not allowed
			if (!nameNotAllowed.empty())
				if (!name.compare(nameNotAllowed)) {
					validName = false;
					cout << "Invalid player name! Your name should not be \"" << nameNotAllowed << "\"." << endl;
				}
				
		} while (!validName);
		
		return name;
	}
	
	/* ask for winning statement */
	string askWinningStatement() {
		string ws;
		bool validWS = false;
		
		do {
			cout << "Please input your winning statement:" << endl;
			getline(cin, ws);
			
			// check whether valid
			for (int i = 0; i < ws.length(); i++) {
				if (isalpha(ws[i])) {
					validWS = true;
					break;
				}
			}
			if (!validWS)
				cout << "Invalid winning statement! Your statement should contain at least one alphabet." << endl;
				
		} while (!validWS);
		
		return ws;
	}
	
	/* play game */
	void play(int round) {
		int roundnum = 1;
		bool end = false;
		int player1WinRound = 0;
		int player2WinRound = 0;
		
		// loop for each round
		do {
			cout << "Round " << roundnum << endl;	// display round number
			player1->nextGuesture();	// obtain gesture from player1
			player2->nextGuesture();	// obtain gesture from player2
			cout << player1->getName() << ", your gesture is " << player1->getGesture_to_s() << "." << endl;
			cout << player2->getName() << ", your gesture is " << player2->getGesture_to_s() << "." << endl;
			
			/* determine who win, 1 implies player1 wins, 2 implies player2 wins, 0 implies draw game */
			int n = whoWin(player1->getGesture(), player2->getGesture());
			
			if (n) {
				// n = 1 or 2, which implies not draw game
				if (n == 1) {
					// player 1 wins
					player1WinRound++;
					cout << player1->getName() << " wins in this round!" << endl;
				}
				else {
					// n = 2, which implies player 2 wins
					player2WinRound++;
					cout << player2->getName() << " wins in this round!" << endl;
				}
				
				cout << player1->getName() << " wins " << player1WinRound << " round(s)." << endl;
				cout << player2->getName() << " wins " << player2WinRound << " round(s)." << endl;
				cout << endl;
				
				// check whether whole game end
				if ((round == '1' && player1WinRound == 2) || (round == '2' && player1WinRound == 3)) {
					// player 1 wins whole game
					cout << player1->getName() << ": " << player1->getWS() << endl << endl;
					end = true;
				}
				else if ((round == '1' && player2WinRound == 2) || (round == '2' && player2WinRound == 3)) {
					// player 2 wins whole game
					cout << player2->getName() << ": " << player2->getWS() << endl << endl;;
					end = true;
				}
				else {
					// cotinue to next round
					cout << "Press any key to continue...";
					_getch();
					roundnum++;
					system("cls");
				}
			}
			else {
				// n = 0, which implies draw game
				cout << endl << "Draw! Press any key to repeat this round...";
				_getch();
				system("cls");
			}
			
		} while(!end);
		
		// ask whether play again
		cout << "Would you like to play again? (y/n)" << endl;
		
		// input from player
		char playAgain;
		// ignore invalid input
		do {
			playAgain = _getch();
		} while (!(playAgain == 'y' || playAgain == 'n'));
		
		system("cls");
		
		if (playAgain == 'y') {
			// play again
			play(round);
		}
		else {
			// delete player objects
			delete player1;
			delete player2;
			// re-start game
			Game game;
			game.start();
		}
	}
	
	/* determine who wins */
	int whoWin(char a, char b) const {
		if ((a == '1' && (b == '3' || b == '5')) ||
			(a == '2' && (b == '1' || b == '4')) ||
			(a == '3' && (b == '2' || b == '5')) ||
			(a == '4' && (b == '1' || b == '3')) ||
			(a == '5' && (b == '2' || b == '4')))
			return 1;
		else if ((a == '1' && (b == '2' || b == '4')) ||
				 (a == '2' && (b == '3' || b == '5')) ||
				 (a == '3' && (b == '1' || b == '4')) ||
				 (a == '4' && (b == '2' || b == '5')) ||
				 (a == '5' && (b == '1' || b == '3')))
				 return 2;
		else
			return 0;
	}
	
private:
	Player *player1;	// player 1 object
	Player *player2;	// player 2 object
};

int main() {
	srand(time(0)); // initialize the random number sequence, execute once only in the program
	Game game;
	game.start();
	return 0;
}


