
// Project 4
// CS 2413 Data Structures
// Spring 2023

#include <iostream>
#include <vector> // for array of transactions and array of blockChains
#include <list>   // for blockchain

using namespace std;

using namespace std;

class transaction
{

    int tID;          // transaction id
    int fromID;       // source ID
    int fromValue;    // P4: how much funds does the source ID person have? If first time, then initialize with 100 coins
    int toID;         // target ID
    int toValue;      // P4: how much funds does the source ID person have? If first time, then initialize with 100 coins
    int tAmount;      // how much is being transfered
    string timeStamp; // time of the transaction read from the input file

public:
    transaction(); // default constructor
    transaction(int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp);

    // all setters and getters
    int getTAmount();
    int getFromID();
    int getToID();
    int getFromValue();
    int getToValue();
    void setFromValue(int id);
    void setToValue(int id);
    int gettID();

    // other methods as needed
    void displayTransaction();
};

transaction::transaction(int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp)
{

    tID = temptID;
    fromID = tempfromID;
    toID = temptoID;
    tAmount = temptAmount;
    timeStamp = temptimeStamp;
    fromValue = 100; // automatically sets toVal and fromVal to 100 for each new transaction
    toValue = 100;
}
// setters and getters
int transaction::getTAmount()
{
    return tAmount;
}
int transaction::getFromID()
{
    return fromID;
}
int transaction::getToID()
{
    return toID;
}
int transaction::getFromValue()
{
    return fromValue;
}
int transaction::getToValue()
{
    return toValue;
}
int transaction::gettID()
{
    return tID;
}
void transaction::setFromValue(int id)
{
    fromValue = id;
}
void transaction::setToValue(int id)
{
    toValue = id;
}

void transaction::displayTransaction()
{
    cout << tID << " " << fromID << " " << fromValue << " " << toID << " " << toValue << " " << tAmount << " " << timeStamp << endl;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class block
{
    int blockNumber;                   // block number of the current block
    int currentNumTransactions;        // how many transactions are currently in the block
    int maxNumTransactions;            // how many maximum transactions can be in the block
    vector<transaction> bTransactions; // vector of transaction objects

public:
    // default constructor
    block()
    {
        blockNumber = 0;
        currentNumTransactions = 0;
        maxNumTransactions = 0;
    }
    // non default constructor
    block(int bNumber, int maxTransactions)
    {
        blockNumber = bNumber;
        maxNumTransactions = maxTransactions;
        currentNumTransactions = 0;
    }
    // insert method to insert a new transaction
    void insertT(transaction t)
    {

        if (currentNumTransactions < maxNumTransactions) // if statement so to make sure there is not an excess of transactions in a block
        {
            bTransactions.push_back(t);
            currentNumTransactions++;
            cout << "Inserting transaction to block #" << blockNumber;
        }
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
    // P4: search for an ID in the bTransaction vector
    transaction searchBlock(int recID, int giveID)
    {
        {
            for (int i = bTransactions.size(); i > 0; i--)
            {
                if (bTransactions[i].getFromID() == giveID)
                {
                }
            }
        }
    }
    // other methods as needed
    void display() // method for displaying blocks after transactions were added
    {
        cout << "Block Number: " << blockNumber << " -- Number of Transaction: " << currentNumTransactions << endl;
    }
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class blockChain
{
    int currentNumBlocks; // maintain the size of the list/block chain list
    list<block> bChain;   // blockchain as a linked list

public:
    blockChain()
    { // default constructor
        currentNumBlocks = 0;
    }
    blockChain(int tPerB)
    { // non default constructor
        currentNumBlocks = 1;
        block *number = new block(currentNumBlocks, tPerB);
        bChain.push_back(*number);
    }
    // insert method to insert new transaction into the block chain - add new block if existing block is full
    void insert(transaction t)
    {

        // if statement to make a new block if initial block is at max capicaty of transactions
        if ((bChain.back().getNumberTransactions()) == (bChain.back().getMaxTransactions()))
        {
            block *secondBlock = new block(currentNumBlocks + 1, bChain.back().getMaxTransactions());
            secondBlock->insertT(t);
            currentNumBlocks++;
            // pushes new block to the front of the linked list so that it is now the one being checked for amount of transactions
            bChain.push_back(*secondBlock);
        }
        else
        {
            // else to insert transaction if block is not full
            bChain.back().insertT(t);
        }
    }
    // setters and getters as needed
    int getNumBlocks()
    {
        return currentNumBlocks;
    }
    // get block mehtof that itterates through blockChain to find a block at a specific index
    block &getBlock(int index)
    {
        list<block>::iterator iterator = bChain.begin();
        advance(iterator, index);
        return *iterator;
    }

    // itterates through the blocks in each block chain and calls the searchBlock method for each block
    void searchBC(int recID, int giveID)
    {

        for (list<block>::iterator i = bChain.begin(); i != bChain.end(); i++)
        {

            i->searchBlock(recID, giveID);
        }
    }
    // other methods as needed
    // calls the display method for a specific block in the block chain
    void display(int s)
    {
        getBlock(s).display();
    }
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class blockNetwork
{
    int numNodes;                // maintain the number of nodes in the network
    vector<blockChain> allNodes; // vector of all the blockChains in the network
    vector<int> u;               // edge list u node
    vector<int> v;               // edge list v node

public:
    // default constructor
    blockNetwork()
    {
        numNodes = 0;
    }
    // non default constructor
    blockNetwork(int numberOfNodes)
    {
        int numEdges;
        cin >> numEdges;
        allNodes.resize(numberOfNodes);
        // resizing all of the vectors so that they can be filled
        u.resize(numEdges);
        v.resize(numEdges);
        // read in the values for u and v vectors
        for (int i = 0; i < numEdges; i++)
        {
            cin >> u[i];
            cin >> v[i];
        }
    }
    // insert method to insert new transaction into the block chain in a specific node - there will be a block chain existent in each node (allNodes vector)
    void insert(transaction t, int node)
    {

        allNodes[node].insert(t);
        cout << " in node " << node << endl;
    }
    // display method to display each node
    void display(int node)
    {
        cout << "~~ Node " << node << ":" << endl;
        cout << "Current number of blocks: " << allNodes[node].getNumBlocks() << endl;
    }
    // for inserting blockchain objects into the allNodes vector of n1
    void insertBC(blockChain b1)
    {
        for (int i = 0; i < allNodes.size(); i++)
        {
            allNodes[i] = b1;
        }
    }
    // returns the vector of blockChains
    vector<blockChain> getBlockChain(int i)
    {
        return allNodes;
    }

    // setters and getters as needed
    // other methods as needed
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
    int numNodesInNetwork; // number of nodes in the network

    cin >> numNodesInNetwork;
    cout << "Number of nodes: " << numNodesInNetwork << endl;

    int numTransactionsPerBlock; // max transactions per block

    cin >> numTransactionsPerBlock;
    cout << "Number of transactions per block: " << numTransactionsPerBlock << endl;

    int totalNumTransactions; // total transactions to be read from the input file

    cin >> totalNumTransactions;
    cout << "Total number of transactions: " << totalNumTransactions << endl;

    // object of block network
    blockNetwork *n1 = new blockNetwork(numNodesInNetwork);
    // object of block chain
    blockChain *b1 = new blockChain(numTransactionsPerBlock);
    // inserts all the block chains needed
    for (int i = 0; i < numNodesInNetwork; i++)
    {
        n1->insertBC(*b1);
    }

    // insert transactions into the blockchain
    int node;
    int transactionID;
    int fromID;
    int toID;
    int transferAmt;
    string timeStamp;

    // for loop to read in all the data for all transactions
    // also to insert them into blocks
    for (int i = 0; i < totalNumTransactions; i++)
    {
        cin >> node;
        cin >> transactionID;
        cin >> fromID;
        cin >> toID;
        cin >> transferAmt;
        cin >> timeStamp;

        transaction *a = new transaction(transactionID, fromID, toID, transferAmt, timeStamp);
        n1->insert(*a, node);
    }
    // print statement for output purposes
    for (int i = 0; i <= node; i++)
    {
        n1->display(i);
        vector<blockChain> print = n1->getBlockChain(i);

        for (int s = 0; s < print[i].getNumBlocks(); s++)
        {

            block &Block = print[i].getBlock(s);
            Block.display();
            vector<transaction> transactions = print[i].getBlock(s).getTransactions();
            // for loop to print out all of the transactions in each block
            for (int p = 0; p < transactions.size(); p++)
            {
                transactions[p].displayTransaction();
            }
        }
    }

    return 0;
}
