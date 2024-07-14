// Spring 2023
// Data Structures
// Project 2

#include <iostream>
#include <string>
#include <fstream> // for reading fileInput

using namespace std;

class tableClass
{
protected:
	string **myTable;	// 2D string array to store all values (strings and numbers)
	string *DTarray;	// 1D array to store the data types of each column
	int noRows, noCols; // number of rows and columns

public:
	// Constructors
	tableClass() {}
	//2 parameters are rows and columns of the 2d array
	//Creates DTarray
	//Creats myTable 2d array
	tableClass(int rows, int cols)
	{
		noRows = rows;
		noCols = cols;
		DTarray = new string[cols];
		myTable = new string *[noRows];
		for (int i = 0; i < noRows; i++)
		{
			myTable[i] = new string[noCols];
		}
	}

	// Overload the [] operator to access a row in myTable
	// this allows you the shift entire rows of the 2d array
	string *operator[](int i)
	{
		return myTable[i];
	}
	//reads the file by parsing whenever there is a comma and updating the position of the comma to the next comma
	// File reading Method
	void readCSV(string filename)
	{
		//fstream type variable so that I can access the .csv file
		fstream fileInput;

		string line = "";

		int comma = 0;
		int nextComma = 0;
		int k = 0; // row
		int j = 0; // col
		fileInput.open(filename, fstream::in);
		while (getline(fileInput, line))
		{
			//creates substrings piece of data and stores it in myTable
			myTable[k][j] = line.substr(0, line.find(",")); 
			j++;
			//retruns the position of the first comma and assings it to comma
			comma = line.find(",");
			while (j < noCols)
			{
				comma = line.find(",", comma);
				// assings the position of the second comma to nextComma
				nextComma = line.find(",", comma + 1);
				if (j == 5)
				{
					// had to add this for searching for float values
					myTable[k][j] = line.substr(comma + 1, 5); 
				}
				else
				{
					myTable[k][j] = line.substr(comma + 1, (nextComma - comma - 1));
				}
				j++;
				comma = nextComma;
			}
			j = 0;
			k++;
		}
		fileInput.close();
	}

	// Output Method
	// itterates array and prints myTable
	void display()
	{

		for (int i = 0; i < noRows; i++)
		{
			for (int k = 0; k < noCols; k++)
			{
				// had to use "/t" because the output would be skipping letters if i used " "
				cout << myTable[i][k] << "\t"; 
			}
			//prints out a new line after each row is printed
			cout << endl;
		}
	}

	// Sort the table
	// altered version of project one sort method
	void sortTable()
	{
		int i;
		int j;
		string *key;
		for (i = 1; i < noRows; i++)
		{
			key = myTable[i];
			j = i - 1;

			while (j >= 0 && myTable[j][0] > key[0])
			{
				myTable[j + 1] = myTable[j];
				j = j - 1;
			}
			myTable[j + 1] = key;
		}
	}
	// Search record
	string *searchRecord(string str)
	{
		int i;
		for (i = 0; i < noRows; i++)
		{
			// if statement for when input was not in myTable
			if (myTable[i][0] == str)
			{
				//I had to print in one long statement because when I tried to print in a for loop, the output would not be correct.
				cout << "Record found:"
					 << "\n";
				cout << "\t" << myTable[i][0] << "\t" << myTable[i][1] << "\t" << myTable[i][2] << "\t" << myTable[i][3] << "\t" << myTable[i][4] << "\t" << myTable[i][5] << endl;
				return myTable[i];
			}
		}
		cout << "Record not found" << endl;
		return myTable[i];
	}
	// str will be from the first column

	// Search value from table
	// prints out the position of a target value str
	void searchValue(string str)
	{
		bool find = false;
		cout << "Searching for " << str << endl;
		for (int i = 0; i < noRows; i++)
		{
			for (int k = 0; k < noCols; k++)
			{
				// this if statement prints out the position that str was found in
				if ((myTable[i][k] == str))
				{
					find = true;
					cout << " found in (" << i << ", " << k << ")" << endl;
				}				
			}
		}
		// this if statement prints for the case that str is not a value in the column
		if(find == false){
			cout << "Value not found" << endl;
		}
	}
// I made this method so that I could fill the DTarray 
	string *parseDT(string str) 
	{
		for (int i = 0; i < noCols; i++)
		{
			cin >> str;
			DTarray[i] = str;
		}
		return DTarray;
	}
// method to call whenever you need print every columns data type
	void printDT() 
	{
		for (int i = 0; i < noCols; i++)
		{
			cout << DTarray[i] << " ";
		}
		cout << endl;
	}
	// Getters
	tableClass *getColumns(int colLeft, int colRight)
	{
		// new table class with all rows and only amount of columns between colRight and colLeft
		tableClass *c = new tableClass(noRows, (colRight - colLeft));
//for loop filling the new table class' DTarray variables and printing them out
		for (int i = colLeft; i < colRight; i++)
		{
			c->DTarray[i - colLeft] = DTarray[i]; 
			cout << c->DTarray[i - colLeft] << " ";
		}
		cout << endl;
		//for loop ittering c -> myTable, filling the values, and printing them out
		for (int i = 0; i < noRows; i++)
		{
			for (int k = colLeft; k < colRight; k++)
			{
				c->myTable[i][k - colLeft] = myTable[i][k];
				cout << c->myTable[i][k - colLeft] << " ";
			}
			cout << endl;
		}

		return c;
	} 
	// returns a tableClass with a set of columns from colLeft to colRight indices
	tableClass *getRows(int rowTop, int rowBottom)
	{
		tableClass *r = new tableClass((rowBottom - rowTop), noCols);
// for loop filling the new table class' DTarray variables and printing them out
		for (int i = 0; i < noCols; i++)
		{
			r->DTarray[i] = DTarray[i];
			cout << r->DTarray[i] << " ";
		}
		cout << endl;
// for loop ittering r -> myTable, filling the values, and printing them out
		for (int i = rowTop; i < rowBottom && i < noRows; i++) 
		{
			for (int k = 0; k < noCols; k++)
			{
				r->myTable[i - rowTop][k] = myTable[i][k]; 
				cout << r->myTable[i - rowTop][k] << "\t";
			}
			cout << endl;
		}

		return r;
	} // returns a tableClass with a set of rows from rowTop to rowBottom indices
	tableClass *getRowsCols(int colLeft, int colRight, int rowTop, int rowBottom)
	{
		tableClass *rc = new tableClass((rowBottom - rowTop), (colRight - colLeft));
		//for loop filling the new table class' DTarray variables and printing them out
		for (int i = colLeft; i < colRight; i++)
		{
			rc->DTarray[i - colLeft] = DTarray[i];
			cout << rc->DTarray[i - colLeft] << " ";
		}
		cout << endl;
		//for loop ittering rc -> myTable, filling the values, and printing them out
		for (int i = rowTop; i < rowBottom && i < noRows; i++)
		{
			for (int k = colLeft; k < colRight; k++)
			{
				rc->myTable[i - rowTop][k -colLeft] = myTable[i][k];
				cout << rc->myTable[i - rowTop][k - colLeft] << "\t";
			}
			cout << endl;
		}
		return rc;
	}

	// Find info of a given column
	// finds the minimum value of a column of numbers
	double findMin(int colNumber)
	{
		
		int m;
		//if statement for exception in input2.txt
		if(colNumber > 5){
			cout << "Column Number " << colNumber << " out of bounds" << endl;
			return m;
		}
		
		int i = 0;
		m = stoi(myTable[i][colNumber]);
		for (i = 0; i < noRows - 1; i++)
		{
			m = min(m, stoi(myTable[i + 1][colNumber]));
		}
		cout << "Min of " << colNumber << " is " << m << endl;
		return m;
	} // returns the min of the given column

	// Destructor
	~tableClass(){
		noRows = 0;
		noCols = 0;
		delete(myTable);
		delete(DTarray);
	};
};

int main()
{
	int numRows, numCols;
	string fileName;
	char option;
	string DT;
	string str;
	string *dataTypes = new string[numCols];

	cin >> numRows >> numCols >> fileName;
	cout << "NumRows: " << numRows << endl;
	cout << "NumCols: " << numCols << endl;
	cout << "FileName: " << fileName << endl;

	tableClass *d = new tableClass(numRows, numCols);

	d->parseDT(DT);

	d->readCSV(fileName);
	d->sortTable();
//these if statements allow for the input.txt file to give the queries in any order, it itterates the line and uses getline to find which problem is being solved
	int line = 0;
	while (!cin.eof())
	{

		line++;
		getline(cin, str);

		if (str[0] == 'F')
		{
			d->searchRecord(str.substr(2, str.length()));
		}
		if (str[0] == 'V')
		{
			d->searchValue(str.substr(2, str.length()));
		}
		if (str[0] == 'D')
		{
			d->printDT();
			d->display();
		}
		if (str[0] == 'I')
		{
			//stoi is a method to convert a string to an integer
			int min;
			min = stoi(str.substr(2, str.length()));
			d->findMin(min);
		}
		if (str[0] == 'C')
		{
			int colLeft = stoi(str.substr(2, 1));
			int colRight = stoi(str.substr(4, 1));
			d->getColumns(colLeft, colRight);
		}
		if (str[0] == 'R')
		{
			int pos;
			int rowTop = stoi(str.substr(2, str.length()));
			pos = 5; // is rowTop is a single digit number
			for (int i = 0; i < 10; i++)
			{
				if (rowTop == i)  //use this if statement for if the first row value is single digits
				{
					pos = 4;
				}
			}
			int rowBottom = stoi(str.substr(pos, str.length()));
			d->getRows(rowTop, rowBottom);
		}
		if (str[0] == 'S')
		{
			int colLeft = stoi(str.substr(2, 1));
			int colRight = stoi(str.substr(4, 1));
			int pos;
			int rowTop = stoi(str.substr(6, str.length()));
			pos = 9;
			for (int i = 0; i < 10; i++)
			{
				if (rowTop == i)
				{
					pos = 8;
				}
			}
			int rowBottom = stoi(str.substr(pos, str.length()));

			d->getRowsCols(colLeft, colRight, rowTop, rowBottom);
		}
	}

	return 0;
	//
}
