/* programmer name: Genevieve Kochel
* Date:
file purpose: this file contains the function defintions for methods in the Game class */

#include "game.hpp"

/* description: runs the main game loop
accepts/returns: void, void */

void Game::runGame()
{
	// init necessary game vars
	int decision = 0,
		playerIndex = -1;

	bool playing = true;

	while (playing)
	{
		// user selects from the main menu 
		decision = getMenuInput();

		switch (decision)
		{
		
		// game rules
		case 1:

			system("clear");
			displayRules();
			break;
		
		// play game
		case 2:

			system("clear");
			game(-1);
			backToMenu();

			break;

		// load previous game
		case 3:

			system("clear");

			// search and load previous game
			playerIndex = loadPreviousGame();

			system("clear");
			game(playerIndex);

			backToMenu();

			break;

		// add command
		case 4:

			system("clear");
			addCommand();
			break;

		// remove command 
		case 5:

			system("clear");
			removeCommand();
			break;

		// exit
		case 6:
			
			system("clear");

			playing = false; // will break out of main loop and exit program
			
			// save data and print exit mssg
			exit();

			break;
		};
	}

	// load game info and update points/commands .csv files
}

/* description: reads and parses all lines from commands.csv and stores data in 
* linux commands list.
accepts/returns: void, returns a bool indicating success or non-sucess of opening and reading
from file */

bool Game::loadCommands()
{
	bool success = false;

	string line,
		description,
		command;

	// create ifstream obj and open file
	fstream infile("src/commands.csv");
	
	if (infile.is_open())
	{
		// successfully opened the file!
		success = true; 

		// read and parse each line while not at end of file
		while (getline(infile, line))
		{
			// read the description after the first quote, remove the second quote from end of string
			description = line.substr(line.find('"') + 1);
			description.pop_back(); 

			// read the command substring of line up until the ',' delimeter
			command = line.substr(0, line.find(','));

			// insert command and description pair into list
			mLinuxCommands.insertAtFront(command, description);
		}

		// close the file after using it
		infile.close();
	}

	return success;
}


/* description: loads the existing player profiles from profiles.csv into the front of the 
* Profiles array contained in the Game class. returns a bool indicating if the file was opened
* successfully.
accepts/returns: void, a bool indicating true if opened file; false otherwise */

/* NOTE: this will load the information from the file contained in the build directory/where executable
is located, not from the files contained in the main program */

bool Game::loadProfiles()
{
	bool success = false;

	string line,
		name,
		score;

	// create ifstream obj and open file
	fstream infile("src/profiles.csv");

	if (infile.is_open())
	{
		// indicate opened success
		success = true;

		// read line by line until at the end of the file
		while (getline(infile, line))
		{
			// parse each line into name and score substrings
			// format: name, points
			name = line.substr(0, line.find(','));

			score = line.substr(line.find(',') + 2); // read score (occurs 2 positions after comma ,)

			// insert profile into front of array
			insertNewProfile(name, stoi(score));
		

		}

		// close file
		infile.close();
	}

	return success;
}

/* description: displays the main menu and gets the user's choice selection
accepts/returns: void, returns the user's selection (int) */

int Game::getMenuInput()
{
	int userChoice = 0;
	string input = "";
	bool flag = false; // indicates if non-numeric string entered

	do {

		// reset at the beginning of each iteration
		flag = false;

		cout << "Please select an option listed below:\n"
			<< "1. Game Rules\n"
			<< "2. Play Game\n"
			<< "3. Load Previous Game\n"
			<< "4. Add Command\n"
			<< "5. Remove Command\n"
			<< "6. Exit\n\n"
			<< "Enter your selection here: ";

		// safely get user input
		getline(cin, input);
		
		// make sure string is numeric before using stoi()
		if (isNumericStr(input))
		{
			// convert to integer for comparison
			userChoice = stoi(input);
		}
		else
		{
			flag = true;
		}


		// indicate invalid input and clear screen
		if (userChoice < 1 || userChoice > 6 || flag)
		{
			system("clear");
			cout << "*** Invalid selection, please try again! ***\n\n";
		}
			

	} while (userChoice < 1 || userChoice > 6 || flag);

	return userChoice;

}

/* description: displays the game rules to the screen
accepts/returns: void, void */
void Game::displayRules()
{
	cout << "Welcome to the Linux Command Matching Game!\n\n"
		<< "The object of the game is to match a given Linux command to its corresponding\n"
		<< "description. Before the game starts, the player may add or remove existing commands.\n"
		<< "When the game starts, the user will be given a command and 3 answers. The player must\n"
		<< "select from 3 choices. For each correct answer, a point is added to the player's score\n"
		<< "and a point will be subtracted from the total score if answered incorrectly. The game will\n"
		<< "continue until all the commands have been used. A player may then save thier profile before\n"
		<< "exiting the game. Good luck!!\n\n";

	// display a message before clearing screen and going back to main menu
	backToMenu();
		
}

/* description: basic utility function to display a message telling the user to select 
any key to return to the main menu.
accepts/returns: void, void */
void Game::backToMenu()
{
	string trash;

	cout << "Press enter to go back to the main menu...";

	getline(cin, trash);

	system("clear");

}

/* description: prompts the user to exit or continue searching for the command to delete. input validation loop filters
* input.
accepts/returns: an integer indicating the type of message to display, 
an integer indicating if user wants to exit or continue searching */
int Game::message(int foundOrDuplicate)
{
	int decision = -1;
	string decisionStr;
	bool flag = false;

	do 
	{
		// reset flag each iteration
		flag = false;

		// prompt user to enter number
		if (foundOrDuplicate == 1)
		{
			cout << "The command you searched for is not found! Would you like to exit or continue searching?\n";
		}
		else
		{
			cout << "The command you entered already exists! Would you like to exit or enter another command?\n";
		}

		cout << "Enter 0 for exit, or 1 to try again: ";

		getline(cin, decisionStr);

		// validate that input can be converted using stoi()
		if (isNumericStr(decisionStr))
		{
			decision = stoi(decisionStr);
		}
		else
		{
			// non-numeric string encountered
			flag = true;
		}
		
		if ((decision != 0 && decision != 1) || flag)
		{
			system("clear");
			cout << "That input is invalid. Please enter 0 or 1.\n\n";
		}

	} while ((decision != 0 && decision != 1) || flag);

	return decision;
}

/* description: prompts the user for the command to remove; uses the removeNode() method of the 
list to search for and remove the node containing the data searched for.
accepts/returns: void, void */
void Game::removeCommand()
{
	bool found = false,
		keepTrying = true;
	string command;

	do
	{
		// prompt for a command to remove
		cout << "Please enter the Linux command from commands.csv that you would like to delete: ";

		// get input string
		getline(cin, command);

		// search and rem if found
		found = mLinuxCommands.removeNode(command);

		// indicate that the command was not found, prompt for exit or continue
		if (!found)
		{
			system("clear");
			keepTrying = message(1); // see if user wants to exit, change notFound to false if the case
		}

		system("clear");

	} while (!found && keepTrying);

	// if the command was found and deleted, indicate this
	if (found)
	{
		cout << "Your command was successfully deleted!\n";
	}

}

/* description: prompts the user for the command to remove; uses the insertAtFront() method of the
list to insert the command and description into the list if the data is not a duplicate command.
accepts/returns: void, void */
void Game::addCommand()
{
	bool tryAgain = true, 
		duplicate = false;

	string command, // strings containing unique Linux command and its description to insert
		description;

	do
	{
		// part 1: prompt for a command to remove
		cout << "Please enter the Linux command you would like to add: ";

		// get the command and check if it's already in the list
		getline(cin, command);

		// check for duplicate command in the list
		duplicate = mLinuxCommands.checkDuplicate(command);

		// if duplicate found, notify user and ask if wants to enter another command
		if (duplicate)
		{
			tryAgain = message(2);
		}
		// no duplicate is found, continue to part 2: entering description
		else
			tryAgain = false;

	} while (tryAgain);

	/* if no duplicate was found above,
	continue to part 2: prompting for the description and insert in the list */
	if (!duplicate)
	{
		cout << "Please enter the corresponding description for this command: ";

		getline(cin, description);

		mLinuxCommands.insertAtFront(command, description);

		system("clear");

		cout << "Your Linux command has been successfully saved!\n\n";

	}

	backToMenu();

	
}

/* description: finds the profile of the player searched for in the profiles array.
accepts/returns: a string containing the player's name to search for in profiles arr, 
an integer of the index of the profile's array that the player was found at (if found), -1 otherwise */
int Game::findPlayer(string& name)
{
	// search the array for the Profile containing name string, O(n) worst case
	for (int i = 0; i < mNumProfiles; ++i)
	{
		// if player is found in the array, return the index
		if (mRecords[i].mUsername == name)
			return i;
	}

	// player was not found
	return -1;
}

/* description: prompts the user for a name to search for, and displays the player's points if they 
are found in the records. If they are not found, a flag is returned and a message is displayed to indicate this
accepts/returns: void, an integer index of the player record searched for */
int Game::loadPreviousGame()
{
	string name, 
	trash;

	int playerIndex = -1;

	// prompt and get the name to search
	cout << "To load a previous score, enter the name of the player: ";

	getline(cin, name);

	// clear screen before displaying message 
	system("clear");


	// convert name to all lowercase for easy searching/comparison
	transform(name.begin(), name.end(), name.begin(), ::tolower);

	// find the index of player searched for
	playerIndex = findPlayer(name);

	// if we found the player in the records, display score 
	if (playerIndex != -1)
	{
		cout << "PLAYER NAME: " << mRecords[playerIndex].mUsername << 
			", PREVIOUS SCORE: " << mRecords[playerIndex].mScore << "\n\n";
	}
	// did not find the player
	else
	{
		cout << "Sorry, that player does not exist in the game records.\n";
	}

	cout << "\nSelect enter to continue with gameplay...";

	getline(cin, trash);

	return playerIndex;
}

/* description: runs through the main gameplay. updates the point count of the player at the index indicated by
* the param "playerProfile" if != -1. Otherwise, (if don't have max # profiles) adds a new profile to the profiles 
array with the name of the new player, and increments the number of profiles counter. 
accepts/returns: an integer index of the player profile that should be updated upon game finishing (this param will 
be -1 if a new player), void */

void Game::game(int playerProfile)
{
	string name, // player name and # questions as a string
		questionStr;

	int questions = 0,  // # questions to be generated
		netPoints = 0, // net point gain/loss after questions answered
		totalScore = 0,
		playerIndex = -1;

	bool newRecord = false, 
		flag = false;

	// prompt for name and get from user
	cout << "To begin the game, please enter your name: ";

	getline(cin, name);

	// convert name to all lowercase for easy searching/comparison
	transform(name.begin(), name.end(), name.begin(), ::tolower);

	cout << "\n"; // newline for formatting

	// prompt for number of questions to generate, convert to integer
	do
	{
		// reset flag each iteration
		flag = false;

		cout << "How many questions would you like to answer? (5 - 30): ";

		getline(cin, questionStr);

		// verify stoi() valid input - string needs to be fully numeric
		if (isNumericStr(questionStr))
		{
			questions = stoi(questionStr);
		}
		else
		{
			flag = true;
		}

		
		if (questions < 5 || questions > 30 || flag)
		{
			system("clear");

			cout << "That input is invalid. Please enter a number within the range 5 - 30.\n";
		}

	} while (questions < 5 || questions > 30 || flag);


	// if there are more or an equal amount of commands to ask in the list, generate questions
	if (questions <= mLinuxCommands.getNumItems())
	{

		// generate # questions in random order
		netPoints = generateQuestions(questions);

		// previous game was not loaded, determine if current player has a profile already
		if (playerProfile == -1)
		{
			playerIndex = findPlayer(name);
		}
		// previous game was loaded, save value of playerProfile as index
		else
		{
			playerIndex = playerProfile;
		}

		// display and compute total score
		if (playerIndex != -1)
		{
			// if player already in system, add netPoints to prev score
			totalScore = netPoints + mRecords[playerIndex].mScore;

			// save prev score to existing profile
			mRecords[playerIndex].mScore = totalScore;

			cout << "Your total score is " << totalScore << ". Your new score will be saved to your existing profile upon Exit (6).\n";
		}
		// if not already in profiles, save the name and score to records array
		else
		{
			newRecord = insertNewProfile(name, netPoints);

			// if record could be successfully inserted into records array
			if (newRecord)
			{
				cout << "Your total score is " << totalScore << ". Your score will be saved to a new profile upon Exit (6) and can be "
					"accessed later!\n";
			}
			else // could not be inserted, limit memory of arr reached 
			{
				cout << "Your total score is " << totalScore << ". Max # of profiles reached in storage. Your profile "
					"could not be saved!\n";
			}
		}
	}
	// there were not enough commands to generate the requested # of questions
	else
	{
		system("clear");

		cout << "Sorry, there are not enough commands to generate that # of questions to answer!\n";
	}
}


/* description: generates "numQuestions" # of commands and 3 possible answers from the linux commands list. prompts
* the user to select an answer and displays message if user got the answer correct/incorrect. 
accepts/returns: an integer containing the # questions to generate, an integer of the total net points gained
or lost (can be negative) which will be added to the player's point count */

int Game::generateQuestions(int numQuestions)
{
	bool point = false; // indicates if player won or lost a point for that Q

	int netPoints = 0;

	// for shuffle() function
	std::random_device rd;
    std::mt19937 g(rd());

	// create a vector of #'s 0 - n (where n is number nodes in list)
	// this will be how we ensure the selection of a command to ask is random
	vector<int> positions;

	for (int i = 0; i < mLinuxCommands.getNumItems(); ++i)
		positions.push_back(i);

	// randomly order the #'s in the vector
	shuffle(positions.begin(), positions.end(), g);

	// loop while we have not generated the correct # of questions
	for (int count = numQuestions, i = 0; count > 0; --count, ++i)
	{
		cout << '\n';

		// quiz user on linux command located at random position in list
		point = mLinuxCommands.askQuestion(positions[i], positions);

		// add or subtract from points earned for this round if correct/incorrect
		if (point)
		{
			++netPoints;
		}
		else
		{
			--netPoints;
		}

		// print total points earned/lost
		cout << "Your point total for this round is " << netPoints << ".\n\n";

		// pause then clear screen for next Q
		 nextQuestionMssg();

		 system("clear");
	}

	return netPoints;
}

/* description: inserts a new record in the front of the array of Profiles called mRecords. if the maximum # of 
* records are already contained in the array, returns a bool indicating non success (false). returns true if
* successfully inserted.
accepts: a string containing the new username, an integer containing the points earned for that player
returns: a bool indicating if the record was successfully inserted, true if inserted false if couldn't be inserted */

bool Game::insertNewProfile(string& name, int pointsEarned)
{
	// if still room in the array for another profile, insert at front
	if (mNumProfiles != MAX_PROFILES)
	{
		// create new profile and update info
		Profile p;
		p.mUsername = name;
		p.mScore = pointsEarned;

		int i = mNumProfiles - 1; // set index to the end of array

		// shift all elements over 1 position to make room for new record
		for (; i >= 0; --i)
		{
			mRecords[i + 1] = mRecords[i];
		}

		// insert new profile at index 0
		mRecords[0] = p;

		// increment the # profiles stored
		++mNumProfiles;

		return true;
	}

	// ran out of storage in array, could not insert
	return false;
}

/* description: uses list method saveData() to save list information to commands.csv in the 
format: command, "description"
accepts/returns: void, a bool indicating if the file was opened successfully or not */

bool Game::saveCommands()
{
	return mLinuxCommands.saveData();
}

/* description: saves all Profile array information to profiles.csv in the format: name, score
accepts/returns: void, a bool indicating if the file was opened successfully or not */

bool Game::saveProfiles()
{
	bool success = false;

	// create ofstream obj and open file
	ofstream outfile("src/profiles.csv");

	// read each entry in Profiles array and write to the file
	if (outfile.is_open())
	{
		success = true; // opened file!

		for (int i = 0; i < mNumProfiles; ++i)
		{
			outfile << mRecords[i].mUsername << ", " << mRecords[i].mScore << '\n';
		}

		// close file once done processing
		outfile.close();
	}

	return success;

}

/* description: saves all list information to commands.csv and all array Profiles information to profiles.csv.
* prints a success and exiting message to screen.
accepts/returns: void, void */

void Game::exit()
{
	bool commands = false,
		profiles = false;

	// save commands and profiles
	commands = saveCommands();
	profiles = saveProfiles();

	// print mssgs
	if (commands)
	{
		cout << "Saving current commands to \"commands.csv\"...\n";
	}
	else
	{
		cout << "Could not open file! Updated commands were NOT saved to \"commands.csv\"...\n";
	}

	if (profiles)
	{
		cout << "Saving current profiles to \"profiles.csv\"...\n";
	}
	else
	{
		cout << "Could not open file! Updated user profiles were NOT saved to \"profiles.csv\"...\n";
	}

	cout << "Exiting program...Goodbye!" << '\n';
}