#include "../includes_usr/fileIO.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <ostream>
#include <vector>

using namespace std;
/* clears, then loads books from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries in books
 * 			SUCCESS if all data is loaded
 * */
int loadBooks(std::vector<book> &books, const char* filename)
{
	ifstream myfile;

	myfile.open(filename);

	bool isopen = true;

	//makes sure file is open and returns boolean depending on outcome
	if (!myfile.is_open() || myfile.fail()) {
		isopen = false;
		cout << "Can't load file";
	}
	string line;
	while (getline(myfile, line))
	{
		stringstream linee(line);
		string word;
		int count = 1;
		book holderBook;
		string holderString;
		while (getline(linee, holderString, ',')) {
			if (count == 1)
			{
				holderBook.book_id = stoi(holderString);
			}
			if (count == 2)
			{
				//messy but will remove the " on the ends
				holderString.erase(
						remove(holderString.begin(), holderString.end(), '\"'),
						holderString.end());
				holderString.erase(
						remove(holderString.begin(), holderString.end(), ' '),
						holderString.end());
				holderBook.title = holderString;
			}
			if (count == 3)
			{
				//messy but will remove the " on the ends
				holderString.erase(
						remove(holderString.begin(), holderString.end(), '\"'),
						holderString.end());

				holderBook.author = holderString;
			}
			if (count == 4)
			{
				book_checkout_state  checkoutstate;
				if(holderString.compare("0"))
					checkoutstate = UNKNOWN;
				if(holderString.compare("1"))
					checkoutstate = IN;
				if(holderString.compare("2"))
					checkoutstate = OUT;

				holderBook.state = checkoutstate;
			}
			if (count == 5)
			{
				holderBook.loaned_to_patron_id = stoi(holderString);
			}
			if (count > 5){
				cout << "To many arguments in the book file";
			}
			count ++;//TODO change this to count-= -1;

		}
		//TODO have a checker here to make sure all the books data has been set


	//have an if here to see if we need to push it
			books.push_back(holderBook);

	}
	myfile.close();
	if(isopen && books.size() >=1){
		return SUCCESS;
	}
	if(isopen && books.size() ==0){
		return NO_BOOKS_IN_LIBRARY;
	}
	return COULD_NOT_OPEN_FILE;

}

/* serializes books to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_BOOKS_IN_LIBRARY if there are 0 entries books (do not create file)
 * 			SUCCESS if all data is saved
 * */
int saveBooks(std::vector<book> &books, const char* filename)
{
	//makes sure there are books in the vector so save. We dont want any empty files
	if(books.size() == 0)
	{
		cout << "NO books  ";
		return NO_BOOKS_IN_LIBRARY;
	}
	ofstream myfile(filename);
	//makes sure file is open and returns boolean depending on outcome
	if (!myfile.is_open() || myfile.fail())
	{
		cout << "NO File   ";
		return COULD_NOT_OPEN_FILE;
	}

	//trying not to make any variables that may not be needed if the two fail conditions are true;
	book currentbook;
	string writeLine;
	for(int x = 0; x < books.size(); x++){
		currentbook = books.at(x);
		writeLine = "";
		writeLine += "\"" + to_string(currentbook.book_id) + "\",";
		writeLine += "\"" + currentbook.title + "\",";
		writeLine += "\"" + currentbook.author + "\",";
		//writeLine += "\"" + currentbook.title + "\",";
		if(currentbook.state == IN)
			writeLine += "1,";
		if(currentbook.state == OUT)
			writeLine += "2,";
		if(currentbook.state == UNKNOWN)
			writeLine += "0,";
		writeLine += to_string(currentbook.loaned_to_patron_id);
		cout << writeLine + "\n";
		myfile << writeLine + "\n";
	}

	myfile.close();
	return SUCCESS;

}

/* clears, then loads patrons from the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons
 * 			SUCCESS if all data is loaded
 * */
int loadPatrons(std::vector<patron> &patrons, const char* filename)
{
	return SUCCESS;
}

/* serializes patrons to the file filename
 * returns  COULD_NOT_OPEN_FILE if cannot open filename
 * 			NO_PATRONS_IN_LIBRARY if there are 0 entries in patrons  (do not create file)
 * 			SUCCESS if all data is saved
 * */
int savePatrons(std::vector<patron> &patrons, const char* filename)
{
	return SUCCESS;
}
