#pragma once

/* programmer name: Genevieve Kochel
* Date:
file purpose: this file contains the class definition for the List class */

#include "Linux.hpp"
#include "listNode.hpp"

template <class T, class U>
class List {

public:
	
	// constructor/destructor
	List() { 
		mpHead = nullptr;
		mNumItems = 0;
	}
	~List();

	// setters/getters if needed
	int getNumItems() const { return mNumItems; }

	// necessary methods
	void insertAtFront(T& command, U& description);
	bool removeNode(const string& remCommand);
	bool checkDuplicate(string& command);
	bool askQuestion(int position, vector<int> randoms);
	ListNode<T, U>* getNodeAtPos(int position);
	bool saveData();

	// helper functions for other List methods
	int getAnswer();

private:

	// private data member of List
	ListNode<T, U>* mpHead;
	int mNumItems; // for random generation of 5-30 questions out of a list with n elements
};

/* description: helper function that prompts the user for an answer choice 1-3. validates that the #
entered is within the valid range and returns the input.
accepts/returns: void, an integer containing the input */

template <class T, class U>
int List<T, U>::getAnswer()
{
	string inputStr;

	int input = 0;

	bool flag = false;

	do {

		// reset flag each iteration
		flag = false;

		cout << "Enter your answer here: ";

		// get input and convert string to integer
		getline(cin, inputStr);

		if (isNumericStr(inputStr))
		{
			input = stoi(inputStr);
		}
		else
		{
			flag = true;
		}
		
		if (input < 1 || input > 3 || flag)
		{
			cout << "That input is invalid. Please enter a selection 1-3.\n";
		}

	} while (input < 1 || input > 3 || flag);


	return input;
}

/* description: deletes all dynamically allocated memory in the list */
template <class T, class U>
List<T, U>::~List()
{
	ListNode<T, U>* next = nullptr,
		*curr = mpHead;

	while (curr != nullptr)
	{
		// save the current node's next ptr
		next = curr->getNext();

		// delete current node
		delete curr;

		// update current node to next for upcoming iteration
		curr = next;
	}
}

/* description: used for adding a command to the list; inserts data containing the 
command and description of a linux command into the front of the list 
accepts: a commmand name of type T, and a description of the command of type U 
returns: void */

template <class T, class U>
void List<T, U>::insertAtFront(T& command, U& description)
{
	// create new node with linux command and its description
	ListNode<T, U>* node = new ListNode<T, U>(command, description);

	// direct new node to point at previous head of list
	node->setNext(mpHead); 

	// set new node as new head of list
	mpHead = node;

	// increment # of items in list
	++mNumItems;
}

/* description: searches for a requested command and deletes the node containing the command, 
if found
accepts: a string containing the command to remove 
returns: a bool indicating if an element was successfully deleted from the list, 
true if deleted, false otherwise */

template <class T, class U>
bool  List<T, U>::removeNode(const string& remCommand)
{
	// fast/slow ptr approach for one pass
	ListNode<T, U>* prev = nullptr,
		*curr = mpHead;

	bool found = false; // indicates if the command searched to delete was found

	// search while not at end of the list and haven't found command to delete
	while (curr != nullptr && !found)
	{
		// if found, aka current node contains the command to delete
		if (curr->getCommand() == remCommand)
		{
			// indicate that the data to be deleted was found
			found = true;

			// case 1: removing at the front of the list, since prev ptr was not advanced
			if (prev == nullptr)
			{
				mpHead = curr->getNext(); // update head of the list to current's next ptr
			}
			// case 2: removing at the end of the list or somewhere in the middle
			else 
			{
				// set the previous node's link to current's link
				prev->setNext(curr->getNext()); 
			}
			
			// delete the current node 
			delete curr;

			// decrement the # items in list
			--mNumItems;
		}

		// advance previous and current ptrs if data not found!
		if (!found)
		{
			prev = curr;
			curr = curr->getNext();
		}
	}

	return found;
}

/* description: checks for a duplicate command, returns true if finds duplicate or false otherwise.
* time complexity: O(n) in worst case, O(1) in best case
accepts/returns: a string containing the data to check for duplicate within the list, bool to indicate if
duplicate is found*/

template <class T, class U>
bool List<T, U>::checkDuplicate(string& command)
{
	ListNode<T, U>* curr = mpHead;

	// loop until end of list or duplicate found
	for (; curr != nullptr &&
		curr->getCommand() != command; curr = curr->getNext());

	// if didn't get to end of list without breaking out of loop, found duplicate
	return curr != nullptr;
}

/* description: finds the command @ position n in the list and prompts user to select correct answer from 3
* randomly generated descriptions. prints a message indicating correct/incorrect input and the correct 
command/description combo. returns true if the user gets the question right, false otherwise.
* time complexity: O(n) in worst case @ position n, O(1) in best case @ pos 0
accepts/returns: an integer representing the position of the command to ask a question about; a std::vector 
of integers that contain #s 1-n where n is the # of nodes in list (used to randomize selections for answer choices), 
a bool indicating if the player got the question right (1) or wrong (0) 
preconditions: randoms must contain all distinct elements and no repeats */

template <class T, class U>
bool List<T, U>::askQuestion(int position, vector<int> randoms)
{
	ListNode<T, U>* question = mpHead, // initially we are searching from head of list (pos 0)
		*incorrect1 = mpHead, // will contain 2 incorrect descriptions to display along w/ correct
		*incorrect2 = mpHead;

	int j = 1, // for displaying list of answer options
		answer = 0;

	bool correct = false; // indicates if user got Q correct

	string answerStr; // will contain the user's answer to question

	// for shuffle() function
	std::random_device rd;
    std::mt19937 g(rd());

	// remove the position of the correct answer from the vector 
	randoms.erase(find(randoms.begin(), randoms.end(), position));

	// shuffle random vector to get 2 other incorrect descriptions
	shuffle(randoms.begin(), randoms.end(), g);

	// find and save the correct command/description pair
	question = this->getNodeAtPos(position);
	
	// randomly generate 2 incorrect descriptions using values in "randoms" as positions in list
	// since randoms is shuffled, index 0 and 1 will have 2 random positions
	incorrect1 = this->getNodeAtPos(randoms[0]);  

	incorrect2 = this->getNodeAtPos(randoms[1]);

	// randomly order the answer options to display to screen

	ListNode<T, U>* answerOptions[3] = { question, incorrect1, incorrect2 };

	shuffle(answerOptions, answerOptions + 3, g);

	// display question and 3 possible answers in random order
	cout << "COMMAND: " << question->getCommand() << '\n';

	for (int i = 0; i < 3; ++i)
	{
		cout << "\n\n" << j << ". " << answerOptions[i]->getDescription() << '\n';

		++j; 
	}

	// prompt for an answer 1-3 
	answer = getAnswer();

	// check if answer is correct/incorrect, return result
	ListNode<T, U>* node = answerOptions[answer - 1];

	correct = node->getDescription() == question->getDescription();

	system("clear");

	// display incorrect/correct message
	if (!correct)
	{
		cout << "\nIncorrect! " << question->getCommand() << " - " << question->getDescription()
			<< ". You have lost one point. ";

	}
	else
	{
		cout << "\nCorrect! " << question->getCommand() << " - " << question->getDescription()
			<< ". You have earned one point. ";
	}

	return correct;

}

/* description: finds and returns the node at the given "position" param in the list.
accepts/returns: an integer position, a ptr to the node @ the searched position or a nullptr if position
not found */

template <class T, class U>
ListNode<T, U>* List <T, U>::getNodeAtPos(int position)
{
	ListNode<T, U>* node = mpHead;

	// loop until find the correct position or hit end of list (position doesn't exist)
	for (int i = 0; node != nullptr && i < position; ++i)
	{
		node = node->getNext();
	}

	return node;
}

/* description: saves all data contained in the list to the commands.csv file.
accepts/returns: void, a bool indicating if file was opened or not */

template <class T, class U>
bool List<T, U>::saveData()
{
	bool success = false;

	ListNode<T, U>* curr = mpHead;

	// create a file type for writing
	ofstream outfile("commands.csv");

	if (outfile.is_open())
	{
		success = true; // file opened successfully

		// read each node and write data to file, while not at end of list
		while (curr != nullptr)
		{
			outfile << curr->getCommand() << ", \"" << curr->getDescription() << "\"\n";

			// update curr
			curr = curr->getNext();
		}

		outfile.close();
	}

	return success;
}