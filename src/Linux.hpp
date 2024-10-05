#pragma once

/* programmer name: Genevieve Kochel
* Date:
file purpose: this file contains all commonly used #includes, using statements and utility functions that don't 
need to belong to a class */

constexpr int MAX_PROFILES = 1000; // max # user profiles that can be created

#include <iostream>
#include <string> // for getline()
#include <stdlib.h> // to clear screen
#include <random>
#include <algorithm> // for random_shuffle()
#include <vector>
#include <cctype> // to_upper(), to_lower()
#include <fstream>
#include <stdexcept> // for exception handling

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::getline;
using std::stoi;
using std::shuffle;
using std::vector;
using std::find;
using std::transform;
using std::ifstream;
using std::istream;
using std::getline;
using std::ofstream;
using std::ostream;
using std::fstream;
using std::exception;
using std::invalid_argument; // exceptions for stoi() 
using std::out_of_range;

// simple Profile struct - no class needed since no complicated methods or 
// inheritance/polymorhism not needed to be used!
typedef struct profile {
	
	string mUsername;
	int mScore;

} Profile;


// utility function(s)
void nextQuestionMssg(void);
bool isNumericStr(const string& str);