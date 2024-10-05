/* programmer name: Genevieve Kochel
Date: 
file: this file contains utility functions used throughout the program that don't belong to a particular class */


#include "Linux.hpp"

/* description: utility function to pause the game and get one character
from the user before continuing with program.
accepts/returns: void, void */
void nextQuestionMssg(void)
{
	string trash;

	cout << "Press any key to continue..." << endl;

    // ignore input
	getline(cin, trash);

}

/* description: checks if a string contains all numeric characters. used for 
stoi() error checking so user cannot enter a string with letters or special characters
accepts/returns: a string to be checked, returns true if str is only numbers false otherwise */

bool isNumericStr(const string& str)
{
	if (str.empty()) return false;
	
	for (char n : str)
	{
		// check if every character in str is a digit and not whitespace
		if (!isdigit(n) || n == '\n')
		{
			return false;
		}
	}

	return true;
}