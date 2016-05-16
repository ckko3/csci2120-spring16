/*
' CSCI2120 Introduction to Software Engineering
'
' Assignment 1
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
' Date: 2/2/2016
*/

#include <iostream>
#include <string>	// for getline, length, etc
#include <cctype>	// for isalpha, isdigit
#include <cstdlib>	// for srand
#include <ctime>	// for time
#include <algorithm>	// for random_shuffle
#define numDigits 4	// number of digits = 4
#define numTrials 6	// number of trials = 6
using namespace std;

class Player {
public:
	// set player name
	void setName(string name) {
		playerName = name;
	}
	// get player name
	string getName() const {
		return playerName;
	}
private:
	string playerName;
};

class PasswordPanel {
public:
	// constructor to generate a 4-digit password
	PasswordPanel() {
		int digits[] = {0,1,2,3,4,5,6,7,8,9};
		srand(time(0));
		random_shuffle(digits, digits + 10);
		for (int i = 0; i < numDigits; i++)
			password += to_string(digits[i]);
	}
	// check whether guess bingo
	bool checkPassword(string pw) {
		return pw == password;
	}
	// give hint
	string giveHint(string pw) {
		char tmp[numDigits];
		/*
		O: correct number in correct position
		.: correct number but in wrong position
		X: wrong number
		*/
		for (int i = 0; i < numDigits; i++) {
			if (pw[i] == password[i]) {
				tmp[i] = 'O';
			}
			else {
				tmp[i] = 'X';
				for (int j = 0; j < numDigits; j++)
					if (pw[i] == password[j])
						tmp[i] = '.';
			}
		}
		
		// convert char array to string object
		string hint(tmp, numDigits);
		return hint;
	}
	// get password
	string getPassword() {
		return password;
	}
private:
	string password;
};

class PasswordGuessingGame {
public:
	/* start game */
	void start() {
		string nameOfPlayer, guessOfPlayer;
		bool validName = false;
		bool validGuess;
		bool bingo = false;
	
		// ask for name
		do {
			cout << "Please enter your name: ";
			getline(cin, nameOfPlayer);
			
			// check whether valid
			for (int i = 0; i < nameOfPlayer.length(); i++) {
				if (isalpha(nameOfPlayer[i])) {
					validName = true;
					break;
				}
			}
			// print the message of invalid name
			if (!validName)
				cout << "Your input has to contain at least one alphabet character." << endl;
		} while (!validName);

		// now there is a valid name, then set it accordingly
		player.setName(nameOfPlayer);
		// print the message
		cout << player.getName() << ", you have to crack a 4-digit password in 6 trials!" << endl;

		/* game flow */
		// track the number of trials
		int trial = numTrials;
		
		// the following line is for debugging, which should be commented befor submission
		// cout << passwordpanel.getPassword() << endl;
		
		/* game loop */
		do {
			// assume guess is valid
			validGuess = true;
			
			// ask for guess
			cout << "Make a guess:" << endl;
			getline(cin, guessOfPlayer);
		
			// check whether guess is valid 
			if (guessOfPlayer.length() == numDigits) {	// check if it is 4-digit
				for (int i = 0; i < numDigits; i++){
					if (!isdigit(guessOfPlayer[i])) {	// check if it is 4-digit
							validGuess = false;
					}
					else {
						for (int j = i + 1; j < numDigits; j++)
							if (guessOfPlayer[i] == guessOfPlayer[j])	// check if it has duplicate digits
								validGuess = false;
					}
				}
			}
			else
				validGuess = false;
			
			// print the message of invalid guess
			if (!validGuess) {
				cout << "Your guess should be a 4-digit number with no duplicate digits." << endl;
			}
			// now there is a valid guess, then check whether bingo or not
			else {
				trial--;
				// guess bingo
				if (passwordpanel.checkPassword(guessOfPlayer)) {
					bingo = true;
					break;
				}
				// guess not bingo
				else {
					cout << passwordpanel.giveHint(guessOfPlayer);
					cout << " ";
					cout << "(Number of trials left: " << trial << ")" << endl;
				}
			}
		} while (!validGuess || trial > 0);
	
		if (bingo)
			// print the message of winning the game
			cout << player.getName() << ", you have cracked the password! Congratulations!" << endl;
		else
			// print the message of losing the game
			cout << player.getName() << ", you have used up all trials! The password is " << passwordpanel.getPassword() << "! Game Over!" << endl;
	}
	
private:
	// Player object
	Player player;
	// PasswordPanel object
	PasswordPanel passwordpanel;
};

int main() {
	PasswordGuessingGame game;
	game.start();
	return 0;
}


