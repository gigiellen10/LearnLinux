#pragma once

/* programmer name: Genevieve Kochel
* Date:
file purpose: this file contains the class definition for the Game class */

#include "list.hpp" // List class

class Game {

public:

	Game() {

		mRecords = new Profile[MAX_PROFILES]; // dynamically allocated array
		mNumProfiles = 0;
	}

	~Game() {
		delete[] mRecords;
	}


	// public method(s)
	void runGame();
	bool loadCommands();
	bool loadProfiles();

private:
	
	// private methods
	int getMenuInput();
	void displayRules();
	void removeCommand();
	void addCommand();
	void game(int playerProfile);
	int findPlayer(string& name);
	int loadPreviousGame();
	int generateQuestions(int numQuestions);
	bool insertNewProfile(string& name, int pointsEarned);
	bool saveCommands();
	bool saveProfiles();
	void exit();

	
	// utility functions
	int message(int foundOrDuplicate);
	void backToMenu();

	// private data members
	List<string, string> mLinuxCommands;
	Profile* mRecords;
	unsigned int mNumProfiles; // current # profiles saved
	
};