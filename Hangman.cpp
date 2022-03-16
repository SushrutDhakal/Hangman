#include <iostream>
#include <cstring>
#include <cctype>

#include "Utils.h"

using namespace std;

const int IGNORE_CHARS = 256;

const char * INPUT_ERROR_STRING = "Error! Please try again.";

void playGame();
bool playAgain();

int genSecretPhrase(char secretPhrase[], int maxLength);
char * hiddenPhrase(const char* secretPhrase, int secretPhraseLength);
void drawBoard(int guessesLeft, const char * noptrHiddenPhrase);

char playerGuess();

void boardUpdates(char guess,char * noptrHiddenPhrase, const char secretPhrase[], int secretPhraseLength, int & guessesLeft);

bool gameOver(int guessesLeft, const char * noptrHiddenPhrase, int secretPhraseLength);

void resultsDisplay(const char * secretPhrase, int guessesLeft);


int main()
{
	do
	{

		playGame();

	}while(playAgain());


	return 0;
}

void playGame()
{
	const int MAX_LENGTH_OF_SECRET_PHRASE = 256;
	const int MAX_NUMBER_OF_GUESSES = 6;

	char secretPhrase[MAX_LENGTH_OF_SECRET_PHRASE];
	char * optrHiddenPhrase = nullptr;
	int guessesLeft = MAX_NUMBER_OF_GUESSES;

	int secretPhraseLength = genSecretPhrase(secretPhrase, MAX_LENGTH_OF_SECRET_PHRASE);

	optrHiddenPhrase = hiddenPhrase(secretPhrase, secretPhraseLength);

	drawBoard(guessesLeft, optrHiddenPhrase);

	char guess;

	do
	{
		guess = playerGuess();

		boardUpdates(guess, optrHiddenPhrase, secretPhrase, secretPhraseLength, guessesLeft);

		drawBoard(guessesLeft, optrHiddenPhrase);


	}while(!gameOver(guessesLeft, optrHiddenPhrase, secretPhraseLength));

	resultsDisplay(secretPhrase, guessesLeft);

	delete [] optrHiddenPhrase;

}


char playerGuess()
{
	return GetCharacter("Please input your guess: ", INPUT_ERROR_STRING);
}


void boardUpdates(char guess,char * noptrHiddenPhrase, const char secretPhrase[], int secretPhraseLength, int & guessesLeft)
{
	bool found = false;

	for (int i = 0; i < secretPhraseLength; i++)
	{
		if(tolower(secretPhrase[i]) == guess)
		{
			noptrHiddenPhrase[i] = secretPhrase[i];
			found = true;
		}
	}

	if(!found)
	{
		guessesLeft--;
	}

}


bool gameOver(int guessesLeft, const char * noptrHiddenPhrase, int secretPhraseLength)
{
	bool hasDash = false;

	for(int i = 0; i < secretPhraseLength; i++)
	{
		if(noptrHiddenPhrase[i] == '-')
		{
			hasDash = true;
			break;
		}
	}

	return guessesLeft == 0 || !hasDash;
}

void resultsDisplay(const char * secretPhrase, int guessesLeft)
{
	if(guessesLeft > 0)
	{
		cout << "You got it! The phrase was: " << secretPhrase << endl;
	}
	else
	{
		cout << "You didn't get it.... The phrase was: " << secretPhrase << endl;
	}
}


bool playAgain()
{
	const char validInputs[] = {'y', 'n'};

	char response = GetCharacter("Would you like to play again? (y/n) ", INPUT_ERROR_STRING, validInputs, 2);

	return response == 'y';
}

int genSecretPhrase(char secretPhrase[], int maxLength)
{
	bool failure;
	int length;
	do
	{
		failure = false;

		cout << "Please enter the secret phrase: ";
		cin.get(secretPhrase, maxLength);

		if(cin.fail())
		{
			cin.clear();
			cin.ignore(IGNORE_CHARS, '\n');
			cout << INPUT_ERROR_STRING << endl;
			failure = true;
		}
		else
		{
			length = strlen(secretPhrase);

			if(length == 0)
			{
				cout << "You must enter a word that's longer than 0 characters! Try again." << endl;
				failure = true;
			}
		}
	}while(failure);


	return length;
}

char * hiddenPhrase(const char* secretPhrase, int secretPhraseLength)
{
	char* hiddenPhrase = new char[secretPhraseLength + 1];

	for(int i = 0; i < secretPhraseLength; i++)
	{
		if(secretPhrase[i] != ' ')
		{
			hiddenPhrase[i] = '-';
		}
		else
			hiddenPhrase[i] = ' ';
	}

	hiddenPhrase[secretPhraseLength] = '\0';

	return hiddenPhrase;
}

void drawBoard(int guessesLeft, const char * noptrHiddenPhrase)
{

	ClearScreen();

	switch(guessesLeft)
	{
	case 0:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\" << endl;
		cout << " |  / \\" << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 1:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\" << endl;
		cout << " |  /" << endl;
		cout << "-+-" << endl << endl;
	}
	break;

	case 2:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|\\" << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 3:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  /|" << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 4:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |   |" << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 5:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |   O" << endl;
		cout << " |  " << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	case 6:
	{
		cout << " +---+" << endl;
		cout << " |   |" << endl;
		cout << " |  " << endl;
		cout << " |  " << endl;
		cout << " |  " << endl;
		cout << "-+-" << endl << endl;
	}
	break;
	default:
		break;
	}

	cout << "The secret Phrase is: " << noptrHiddenPhrase << endl << endl;
}

