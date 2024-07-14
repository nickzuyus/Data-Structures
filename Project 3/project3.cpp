// Project 3
// CS 2413 Data Structures
// Spring 2023

#include <iostream>
#include <vector> // for array of transactions
#include <list>	  // for blockchain

using namespace std;

class transaction
{
	int tID;		  // transaction id
	int fromID;		  // source ID
	int toID;		  // target ID
	int tAmount;	  // how much is being transfered
	string timeStamp; // time of the transaction read from the input file

public:
	transaction() {} // default constructor
	transaction(int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp)
	{
		tID = temptID;
		fromID = tempfromID;
		toID = temptoID;
		tAmount = temptAmount;
		timeStamp = temptimeStamp;
	} // non default constructor - default 100 for values

	void display() // for printing out all parts of each transaction
	{
		cout << tID << " " << fromID << " " << toID << " " << tAmount << " " << timeStamp << endl;
	}
};

class block
{
	int blockNumber;				   // block number of the current block
	int currentNumTransactions;		   // how many transactions are currently in the block
	int maxNumTransactions;			   // how many maximum transactions can be in the block
	vector<transaction> bTransactions; // vector of transaction objects

public:
	block()
	{ // default constructor
		blockNumber = 0;
		currentNumTransactions = 0;
		maxNumTransactions = 0;
	}
	block(int bNumber, int maxTransactions) // non default constructor
	{
		blockNumber = bNumber;
		maxNumTransactions = maxTransactions;
		currentNumTransactions = 0;
		cout << "Adding block #" << bNumber << endl; // for first part of output
	}
	// insert method to insert a new transaction
	void insertT(transaction t)
	{
		if (currentNumTransactions < maxNumTransactions) // if statement so to make sure there is not an excess of transactions in a block
		{
			bTransactions.push_back(t);
			cout << "Inserting transaction to block #" << blockNumber << endl;
			currentNumTransactions++;
		}
	}

	void display() // method for displaying blocks after transactions were added
	{
		cout << "Block Number: " << blockNumber << " -- Number of Transaction: " << currentNumTransactions << endl;
	}

	// setters and getters as needed
	int getNumberTransactions() // returns current Number of Transactions
	{
		return currentNumTransactions;
	}
	int getMaxTransactions() // returns maximum number of transactions
	{
		return maxNumTransactions;
	}

	vector<transaction> getTransactions() // returns a vector of all transactions in a block for printing purposes
	{
		return bTransactions;
	}
};

class blockChain
{
	int currentNumBlocks; // maintain the size of the list/block chain list
	list<block> bChain;	  // blockchain as a linked list

public:
	blockChain()
	{ // default constructor
		currentNumBlocks = 0;
	}
	blockChain(int tPerB) // non default constructor
	{
		currentNumBlocks = 1;
		block *number = new block(currentNumBlocks, tPerB);
		bChain.push_front(*number); // push created block to front of the block chain so that the block is never empty when using insert method
	}
	// insert method to insert new transaction into the block chain - add new block if existing block is full
	void insert(transaction t)
	{
		// if statement to make a new block if initial block is at max capicaty of transactions
		if ((bChain.front().getNumberTransactions()) == (bChain.front().getMaxTransactions()))
		{
			block *secondBlock = new block(currentNumBlocks + 1, bChain.front().getMaxTransactions());
			secondBlock->insertT(t);
			currentNumBlocks++;
			// pushes new block to the front of the linked list so that it is now the one being checked for amount of transactions
			bChain.push_front(*secondBlock);
		}
		else
		{
			// else to insert transaction if block is not full
			bChain.front().insertT(t);
		}
	}

	// setters and getters as needed

	int getNumBlocks()
	{
		return currentNumBlocks;
	}
	// allows you to itterate through blocks from the begining to access them
	block &getBlock(int index)
	{
		list<block>::iterator iterator = bChain.begin();
		advance(iterator, index);
		return *iterator;
	}
};

int main()
{
	int numTransactionsPerBlock; // max transactions per block

	cin >> numTransactionsPerBlock;
	cout << "Number of transactions per block: " << numTransactionsPerBlock << endl;

	int totalNumTransactions; // total transactions to be read from the input file

	cin >> totalNumTransactions;
	cout << "Total number of transactions: " << totalNumTransactions << endl;
	cin.ignore();

	// object of block chain
	blockChain *b1 = new blockChain(numTransactionsPerBlock);

	// insert transactions into the blockchain
	int transactionID;
	int fromID;
	int toID;
	int transferAmt;
	string timeStamp;

	// for loop to read in all the data for all transactions
	// also to insert them into blocks
	for (int i = 0; i < totalNumTransactions; i++)
	{

		cin >> transactionID;
		cin >> fromID;
		cin >> toID;
		cin >> transferAmt;
		cin >> timeStamp;

		transaction *a = new transaction(transactionID, fromID, toID, transferAmt, timeStamp);
		b1->insert(*a);
	}
	// print statement for output purposes
	cout << "Current number of blocks: " << b1->getNumBlocks() << endl;
	// for loop to print out each block, it's number, and amount of transactions
	for (int i = b1->getNumBlocks() - 1; i >= 0; i--)
	{
		block &Block = b1->getBlock(i);
		Block.display();
		vector<transaction> transactions = b1->getBlock(i).getTransactions();
		// for loop to print out all of the transactions in each block
		for (int i = 0; i < transactions.size(); i++)
		{
			transactions[i].display();
		}
	}
	return 0;
}
