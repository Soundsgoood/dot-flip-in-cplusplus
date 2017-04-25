//Orion Guan
//April 17th, 2017
//Ported from DotFlipGame.java, with implementation handled differently.

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <time.h>
#include <cstdlib>
using namespace std;

//The game itself, with the current state of the dots, the original state, and the goal "ideal" state.
class DotFlipGame
{
private:
	static char const STATE_ONE = '+';
	static char const STATE_TWO = '-';

	vector<bool> gameSetup;
	vector<bool> gameState;
	vector<bool> idealState;
	int moveCounter;

	//Generates dot orientations to begin the game.
	vector<bool> generateGameSetup(int numberOfDots)
	{
		vector<bool> gameSetup(numberOfDots);
		//gameSetup.clear(); //how to prevent larger vectors?
		for (int i = 0; i < numberOfDots; i++)
		{
			if (rand() % 2 == 0)
				gameSetup[i] = true;
			else
				gameSetup[i] = false;
		}
		return gameSetup;
	}

	//Makes the ideal state the dots should be in.
	vector<bool> makeIdealSetup(int numberOfDots)
	{
		vector<bool> idealSetup(numberOfDots);
		//idealSetup.clear();
		for (int i = 0; i < numberOfDots; i++)
		{
			idealSetup[i] = true;
		}
		return idealSetup;
	}

	//Turns a state of the dots into a string of characters.
	string gameStateToString(vector<bool> gameState)
	{
		string gameString = "";
		for (int i = 0; i < gameState.size(); i++)
		{
			if (gameState[i])
				gameString += STATE_ONE;
			else
				gameString += STATE_TWO;
		}
		return gameString;
	}

	//Flips a dot and adjacent dots.
	vector<bool> flip(vector<bool> gameState, int input)
	{
		int stateSize = gameState.size();
		gameState[input] = !gameState[input];
		gameState[(input + stateSize - 1) % stateSize]
			= !gameState[(input + stateSize - 1) % stateSize];
		gameState[(input + 1) % stateSize] = !gameState[(input + 1) % stateSize];
		return gameState;
	}

public:
	//Creates a game.
	DotFlipGame(int numberOfDots)
	{
		idealState = makeIdealSetup(numberOfDots);
		gameSetup = idealState;
		while (gameSetup == idealState)
		{
			gameSetup = generateGameSetup(numberOfDots);
		}
		gameState = gameSetup;
		moveCounter = 0;
	}

	//Creates a game from an existing dot setup.
	DotFlipGame(vector<bool> gameSetup)
	{
		int numberOfDots = gameSetup.size();
		idealState = makeIdealSetup(numberOfDots);
		this->gameSetup = gameSetup;
		while (gameSetup == idealState)
		{
			gameSetup = generateGameSetup(numberOfDots);
		}
		gameState = gameSetup;
		moveCounter = 0;
	}

	//Plays the game, giving the player appropriate prompts.
	void play()
	{
		int gameSize = gameSetup.size();
		stringstream ss;
		for (int i = 1; i <= gameSize; i++)
		{
			ss << (i % 10); //to cut off more significant digits
		}
		string numberGuide = ss.str();

		cout << "Enter a number to flip a dot and surrounding dots. Get all +'s!" << endl;

		while (gameState != idealState)
		{
			int input;
			cout << numberGuide << endl << gameStateToString(gameState) << endl;
			cin >> input;
			if (input >= 1 && input <= gameSize)
			{
				gameState = flip(gameState, input - 1);
				moveCounter++;
			}
			else
			{
				cout << "Pick a number in the range shown!" << endl;
			}
		}

		cout << gameStateToString(gameState) << endl << "You won! It took you "
			<< moveCounter << " moves." << endl;
	}

	//Returns the original setup of the game.
	vector<bool> getGameSetup() const
	{
		return gameSetup;
	}
};

int main()
{
	void srand(unsigned int seed);
	srand(time(NULL));

	static int const NUMBER_OF_DOTS = 8;

	bool playAgain = true;

	cout << "Welcome to DotFlip!" << endl;

	while(playAgain == true)
	{	
		cout << "Generating game . . ." << endl;
		DotFlipGame currentGame(NUMBER_OF_DOTS);
		cout << "Game generated." << endl;
		currentGame.play();

		cout << "Play again? Y/N " << endl;
		char yesOrNo;
		cin >> yesOrNo;
		if (yesOrNo == 'y' || yesOrNo == 'Y')
			playAgain = true;
		else if (yesOrNo == 'n' || yesOrNo == 'N')
			playAgain = false;
		else
		{
			cout << "Invalid input. I assume you don't want to play." << endl;
			playAgain = false;
		}
	}
	cout << "See ya!" << endl;
}