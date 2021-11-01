#include<iostream>
#include<vector>
#include<string>
#include<random>
#include<math.h>

//The using directive
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::random_device;
using std::default_random_engine;
using std::uniform_int_distribution;
using std::to_string;

//Prototypes
void dataValidation(int& vectorSize, int& maxNum);
void secretCombination(vector<string>& secretNumber, int size, int max);
void allZeroCombination(string& combination, string& zeroCombination, vector<string>& secretNumber, int size, int max);
void randomNumber(vector<string>& secretNumber, int size, int max);
void userGuessCombination(vector<string>& userGuess, vector<string>& secretNumber, string zeroCombination, int size, int max, int& count);
void validateUserGuess(vector<string>& userGuess, vector<string>& secretNumber, string zeroCombination, int size, int max, int& count);
void game(vector<string>& userGuess, vector<string>& secretNumber, string zeroCombination, int size, int max, int& count);

//Random indentifiers
random_device rd;
default_random_engine engine(rd());

int main() {
	//vector that contain the secret number
	vector<string> secretNumber;
	//vector that will hold the user guess
	vector<string> userGuess;
	//variables that contain the vector size and maximum value of nnumber to be guessed
	int vectorSize, maxNum;
	//input the values from the user
	cin >> vectorSize >> maxNum;
	//function to validate the range of numbers inside of the vector
	dataValidation(vectorSize, maxNum);
	//output the values
	cout << "Playing Mastermind with " << vectorSize << " numbers (1-" << maxNum << ")." << endl;

	//Ask User for Secret Combination he wants to input, if they put all Zero's the computer
	//will assign a random number
	secretCombination(secretNumber, vectorSize, maxNum);
	/*Once we have the secretCombination we have to do Data Validation to see if the numbers they put
	are all 0. If so the computer will asign a random number. This function contains the "randomNumber function within
	it. If the numbers are not 0 we will use that as the combination*/
	//function to check if numbers are all O
	string combination;
	string zeroCombination;
	allZeroCombination(combination, zeroCombination, secretNumber, vectorSize, maxNum);
	//It will keep counting of guess attempts
	int count = 1;
	//Now the we have the secretCombination we want in our program we need to ask the user their guess
	userGuessCombination(userGuess, secretNumber, zeroCombination, vectorSize, maxNum, count);
	////Once we got the number we can Validate it to check if it meats our requirements.
	validateUserGuess(userGuess, secretNumber, zeroCombination, vectorSize, maxNum, count);
	//Now that we have validated our guess we can start the game.
	game(userGuess, secretNumber, zeroCombination, vectorSize, maxNum, count);
	return 0;
}

void dataValidation(int& vectorSize, int& maxNum)
{
	//range condition for vectorSize
	if (vectorSize < 2) {
		vectorSize = 2;
	}
	else
	{
		if (vectorSize > 8){
			vectorSize = 8;
			}
	}
	//range condition for the maximum number
	if (maxNum < 6) {
		maxNum = 6;
	}
	else {
		if (maxNum > 20) {
			maxNum = 20;
		}
	}
}

void secretCombination(vector<string>& secretNumber, int size, int max) {

	//variable that will hold the list of values from the user
	string value;

	while (secretNumber.size() < size) {


		cin >> value;
		//insert the string values inputed by the user in the vector
		secretNumber.push_back(value);
	}
}

void allZeroCombination(string& combination, string& zeroCombination, vector<string>& secretNumber, int size, int max) {
	for (int i = 0; i < size; i++) {
		combination += secretNumber.at(i);
	}
	for (int i = 0; i < size; i++)
	{
		zeroCombination += "0";
	}
	//the user select the random combination secret
	if (zeroCombination == combination) {
		//random number function
		randomNumber(secretNumber, size, max);
		cout << "Using random secret." << endl << endl;
	}
	else {
		//cout the given secret number message
		cout << "Using given secret." << endl << endl;
	}
}

void randomNumber(vector<string>& secretNumber, int size, int max) {
	//Delete all values in vector
	for (int i = 0; i < size; i++) {
		secretNumber.pop_back();
	}
	//add random numbers to the vector
	for (int i = 0; i < size; i++) {
		uniform_int_distribution<int> random(1, max);
		int number = random(engine);
		secretNumber.push_back(to_string(number));
	}
}

void userGuessCombination(vector<string>& userGuess, vector<string>& secretNumber, string zeroCombination, int size, int max, int& count) {

	//variable that will hold the list of values from the user
	string value;
	string guessCombination;


	//Getting the user Guess
	while (userGuess.size() < size) {
		cin >> value;
		//inserting the string values inputed by the user in the vector
		userGuess.push_back(value);
	}


	//Now that we have the user input we can check if the user decided to give up or not by inputing al zeros.
	//first we populate the guessCombination string variable to compare it to a zeroCombination
	for (int i = 0; i < size; i++) {
		guessCombination += userGuess.at(i);
		//count++;
		//cout << count;
	}

	if (guessCombination == zeroCombination) {
		cout << "Guess " << count << ": ";
		for (int i = 0; i < size; i++) {
			cout << userGuess.at(i) + " ";
		}
		cout << endl;
		cout << "You lose." << endl;
		cout << "The secret was: ";
		for (int i = 0; i < size; i++) {
			cout << secretNumber.at(i) + " ";
		}
		cout << endl << endl;
		guessCombination.clear();

	}

}

void validateUserGuess(vector<string>& userGuess, vector<string>& secretNumber, string zeroCombination, int size, int max, int& count) {
	string guess;

	for (int i = 0; i < size; i++) {
		if ((stoi(userGuess.at(i)) < 1 || stoi(userGuess.at(i)) > max))
		{
			//We need this for loop cause it is the only way it works :C
			for (int i = 0; i < size; i++) {
				guess += userGuess.at(i);
			}
			if (zeroCombination == guess) {
				return;
			}
			cout << "Numbers must be between 1 and " << max << "." << endl << endl;
			userGuess.clear();
			userGuessCombination(userGuess, secretNumber, zeroCombination, size, max, count);
			guess.clear();
		}
	}
}

void game(vector<string>& userGuess, vector<string>& secretNumber, string zeroCombination, int size, int max, int& count) {
	string guess, combination;
	//counters for when the user got the right place or wrong place
	int rightPlace = 0;
	int wrongPlace = 0;


	for (int i = 0; i < size; i++) {
		guess += userGuess.at(i);
		combination += secretNumber.at(i);
	}
	if (guess == combination) {
		cout << "Guess " << count << ": ";
		for (int i = 0; i < size; i++) {
			cout << userGuess.at(i) + " ";
		}
		cout << endl;
		cout << "That's right!" << endl;
		cout << "It took you " << count << " guess." << endl;
		return;
	}
	if (guess == zeroCombination) {
		return;
	}
	while (guess != combination) {
		//Print out the guess attempt messages	
		cout << "Guess " << count << ": ";
		for (int i = 0; i < size; i++) {
			cout << userGuess.at(i) + " ";
		}
		vector<string> copySecretNumber;
		copySecretNumber = secretNumber;
		cout << endl;
		//keep adding after each new guess 5attempt 
		count = count++;
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				//finding the number of right places
				if (userGuess.at(j) == copySecretNumber.at(i) && i == j) {
					rightPlace++;
					copySecretNumber.at(i) = "21";
				}
			}
		}
		//finding the number of wrong places
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				//finding the number of wrong places
				if (userGuess.at(j) == copySecretNumber.at(i) && i != j && copySecretNumber.at(j) != "21") {
					wrongPlace++;
					copySecretNumber.at(i) = "21";
				}
			}
		}
		copySecretNumber.clear();
		cout << rightPlace << " right place" << endl;
		cout << wrongPlace << " wrong place" << endl;
		cout << endl;
		//Cleaning the Counter
		rightPlace = 0;
		wrongPlace = 0;

		//then clearing the vector
		userGuess.clear();
		//also clearing the strings 
		guess.clear();
		combination.clear();
		//The user guess another combination
		userGuessCombination(userGuess, secretNumber, zeroCombination, size, max, count);
		//Time to check again the user guess
		validateUserGuess(userGuess, secretNumber, zeroCombination, size, max, count);
		for (int i = 0; i < size; i++) {
			guess += userGuess.at(i);
			combination += secretNumber.at(i);
		}
		if (guess == combination) {
			cout << "That's right!" << endl;
			cout << "It took you " << count << " guesses." << endl;
			return;
		}
		if (guess == zeroCombination) {
			return;
		}
	}
}