#include "game.hpp"

int main(void)
{
	Game myGame;

	bool openedCommands = false,
		openedProfiles = false;

	// load profiles and commands from files
	openedProfiles = myGame.loadProfiles();
	openedCommands = myGame.loadCommands();

	if (openedProfiles && openedCommands)
	{
		// run main game loop
		myGame.runGame();
	}
	
	// notify user of errors opening files
	if (!openedProfiles)
	{
		system("clear");

		cout << "Error opening \"profiles.csv\"! No profiles could be loaded" 
			"and the game cannot be run until fixed.\n";
	}
	if (!openedCommands)
	{
		system("clear");

		cout << "Error opening \"commands.csv\"! No Linux commands and descriptions could be loaded"
			"and the game cannot be run until fixed.\n";
	}

	return 0;
}