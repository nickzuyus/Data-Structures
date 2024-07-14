// Project 6
// CS 2413 Data Structures
// Spring 2023

#include <iostream>
#include <string> // for storing string
#include <fstream> // for reading a file again and again
#include <map> 
#include <unordered_map>
#include <vector>

using namespace std;
// write hash function
int hashStr(string str){
	// sets hashVal to zero each time so each itteration resets
    int hashVal = 0;
	// for loop to take value of each character in the string
    for(int i = 0; i < str.size(); i++){
        char c = tolower(str[i]);
	// multiplying the value by 31 because it is an ofter used prime number and dividing by 250 so that values arent too large
        hashVal = (hashVal * 31 + (c - 'a')) % 250; 
    }
    return hashVal;

}

// write display functions for map and unordered map
//display method for map
void display(map <int, vector <string> > myMap){
	// itterator to get through each line in the map
    for(auto it = myMap.begin(); it != myMap.end(); ++it){
        cout << it->first << ": ";
        for(auto str : it->second){
            cout << str << " ";
        }
        cout << endl;
    }
}
//display method for unordered map 
void display(unordered_map <int, vector <string> > myMap){
	//itterator to get through each line 
    for(auto it = myMap.begin(); it != myMap.end(); ++it){
        cout << it->first << ": ";
        for(auto str : it->second){
            cout << str << " ";
        }
        cout << endl;
    }
}

using namespace std;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
	string fileName; // to read in the name of the fileInput from redirected input

	cin >> fileName;
	cout << "Name of fileInput: " << fileName << endl;


	// MAP
	map <int, vector<string> > m1;
	// open a fileName in read mode
	ifstream fI; 
	fI.open(fileName);

	char option;
	string temp;
	
    // reading and performing operations
    // start timer

	//print statement to denote ordered map
	cout << "Map:" << endl;
	//while loop that goes through each line in the file 
    while(!fI.eof()){
		// reading in commanc and name for each line 
		fI >> option;
        fI >> temp;
		// hash position in map
        int pos = hashStr(temp);
        auto it = m1.find(pos);
        if(it == m1.end()){
			// vector of strings for repeating names 
            vector<string> loop;
            loop.push_back(temp);
			// inserting names into the map
			m1.insert(make_pair(pos, loop));
        } 
		else {
			// adds name to end of loop
           it->second.push_back(temp);
        }
		//conditional to remove the key and value when the read in command is R
		if(option == 'R'){
        m1.erase(pos);
        }
    }
display(m1);
    // stop timer

	// close the opened file
	fI.close();



	// UNORDERED MAP
	unordered_map<int, vector<string> > m2;
	// open a file again in read mode
	fI.open(fileName);

    // start timer

	//denoting unordered map
	cout << "Unorderd Map:" << endl;
    while(!fI.eof()){
		// reading in commands and names 
		fI >> option;
        fI >> temp;
		// setting hash position and itterator
        int pos = hashStr(temp);
        auto it = m2.find(pos);
        if(it == m2.end()){
			// vector of strings to hold repeating names 
            vector<string> loop;
            loop.push_back(temp);
			// inserting the loop and key into the unordered map
			m2.insert(make_pair(pos, loop));
        } 
		else {
           it->second.push_back(temp);
        }
		// conditional for if command is R
		if(option == 'R'){
        m2.erase(pos);
        }
    }
display(m2);


    // stop timer
	// close the opened file
	fI.close();

	return 0;
}
