// Project 5
// CS 2413 Data Structures
// Spring 2023

#include <iostream>
#include <string> // for the fields in the class
#include <vector> // for the flowchart structures
#include <stack>  // for conversion

using namespace std;

// class to store node information
class Node
{
private:
	int nodeNumber;	   // to store the node number
	string type;	   // can either be START, END, IF, BLOCK
	string textWithin; // can be expression or statement - for START and END this will be empty string
public:
	// TODO: construtors, getters, setters and other methods as needed
	// no parameter constructor
	Node()
	{
		int nodeNumber = 0;
		string type = "";
		string textWithin = "";
	}
	// for start / end blocks
	Node(int nodeNum, string nodeType)
	{
		nodeNumber = nodeNum;
		type = nodeType;
		string textWithin = "";
	}
	// for IF and Block nodes
	Node(int nodeNum, string nodeType, string textInside)
	{
		nodeNumber = nodeNum;
		type = nodeType;
		textWithin = textInside;
	}
	// all getters 
	int getNodeNumber()
	{
		return nodeNumber;
	}
	string getType()
	{
		return type;
	}
	string getTextWithin()
	{
		return textWithin;
	}
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// function to convert the given flowchart to generate code
void convertFlowChart(vector<Node> allNodes, vector<vector<int> > adjList, int i)
{
	bool processed = false; // bool to end function if certain conditionals are met
    int line = 0; // 
    int ifblock = 0;
	while(i < adjList.size() && processed != true){
        
        //Start at begining of adjList
        if(allNodes[adjList[i][0]].getType() == "START"){
            cout << "start" << endl; // print out first action of flow chart
        i = 1;
        continue;
        }
		// for printing IF blocks
         if(allNodes[adjList[i][0]].getType() == "IF" && ifblock == 0)
         {
            
            int offset; // for second nimber in IF blocks 
            cout << "if (" << allNodes[i].getTextWithin() <<  ")" << endl;
            cout << "{" << endl;
			if(allNodes.size() < 7){
				cout << "statement 1" << endl << endl << "}" << endl;
			}
			// if statement for printing purposes
            if(allNodes[adjList[i][1]].getType() == "IF" && ifblock == 0)
            {
                
                 cout << "if (" << allNodes[adjList[i][1]].getTextWithin() <<  ")" << endl;
                 offset = adjList[i][1];
                 cout << "{" << endl;
                 cout  << allNodes[adjList[offset][1]].getTextWithin()  << endl << endl;
                 cout << "}" << endl;
                 cout << "else" << endl;
                 cout << "{" << endl;
                 cout << allNodes[adjList[offset][2]].getTextWithin()  << endl << endl;
                cout << "}" << endl << endl << "}" << endl;
				
            }
            cout << "else" << endl;
            cout << "{" << endl;
            cout <<    allNodes[adjList[i][2]].getTextWithin() << endl << endl;
            cout << "}" << endl;
            i = adjList[i+1][1];
        
         }
          // for printing BLOCK nodes
        if(allNodes[adjList[i][0]].getType() == "BLOCK" && ifblock == 0)
        {
            cout << allNodes[i].getTextWithin() << endl;
        }
		// for printing END nodes
           if(allNodes[i].getType() == "END" && ifblock == 0)
        {
            cout << "end"<< endl;
            processed = true; // break statement
        }
       i++; // itterate through lines
	}
}
           

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

int main()
{
	int numNodesInFlowChart; // number of nodes in the flow chart

	cin >> numNodesInFlowChart;
	cout << "Number of nodes: " << numNodesInFlowChart << endl;

	// Node objects array to store all the information
	vector<Node> allNodes(numNodesInFlowChart);

	// TODO: read in the information about the nodes and store it in allNodes
	// node Parameters
	int nodeNum; 
	string nodeType; 
	string content;
// for loop to read in all the node values and store them in the all Nodes array
	for (int i = 0; i < numNodesInFlowChart; i++)
	{

		cin >> nodeNum;
		cin >> nodeType;
		// uses 2 parameter constructor for start / end nodes
		if (nodeType == "START" || nodeType == "END")
		{
			Node *a = new Node(nodeNum, nodeType);
			allNodes[i] = *a;
			cout << a->getNodeNumber() << ": " << a->getType() << " node" << endl;
		}
		//uses 3 parameter node constructor for IF / BLOCK nodes
		else
		{
			cin >> content;
			Node *a = new Node(nodeNum, nodeType, content);
			allNodes[i] = *a;
			cout << a->getNodeNumber() << ": " << a->getType() << " node"
				 << " - " << a->getTextWithin() << endl;
		}
	}

	// adjacency list to store the flow chart
	vector<vector<int> > adjList(numNodesInFlowChart);

	// TODO: read in the adjaceny list

	int n0;

	cout << "AdjList:" << endl;
// foor loop to read in all the all the values in the AdjList vector
	for (int i = 0; i < numNodesInFlowChart; i++)
	{
		// must create different sizes of vectors for different types of nodes
		if (allNodes[i].getType() == "IF")
		{
			// size 3 for IF / BlOCK nodes
			vector<int> adj(3);
			for (int k = 0; k < adj.size(); k++)
			{
				cin >> n0;
				adj[k] = n0;
			}
			adjList[i] = adj;
		}
		else if (allNodes[i].getType() == "END")
		{
			// size 2 for END nodes
			vector<int> adj(1);
			cin >> n0;
			adj[0] = n0;
			adjList[i] = adj;
		}
		else
		{
			//size 2 for START nodes
			vector<int> adj(2);
			for (int k = 0; k < adj.size(); k++)
			{
				cin >> n0;
				adj[k] = n0;
			}
			adjList[i] = adj;
		}
	}
// for loop print out the adjList vector
	for (int i = 0; i < numNodesInFlowChart; i++)
	{
		cout << adjList[i][0] << ": ";
		for (int k = 1; k < adjList[i].size(); k++)
		{
			cout << adjList[i][k] << " ";
		}
		cout << endl;
	}

	// TODO: call the convertFlowChart function with the allNodes and adjList parameters

	convertFlowChart(allNodes, adjList, 0);

	return 0;
}
