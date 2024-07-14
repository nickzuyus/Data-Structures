// Data Structures Spring 2023
// CS 2413
// Nick Zuyus
#include <iostream>
#include <time.h> // for experiments
using namespace std;

//Method Used to insert a "target" element into Array A that returns an updated array
// the element is just added onto the end of the array
int *insertionA(int arr[], int size, int target)
{
    cout << "Inserting " << target << " in A" << endl;
    arr[size] = target;
    return arr;
}
// Method Used to insert a "target" element into Array B 
// The element is placed in order of increasing order
int *insertionB(int arr[], int size, int target)
{
    cout << "Inserting " << target << " in B" << endl;
    int i = size - 1;

    while (arr[i] >= target && i >= 0)
    {
        arr[i + 1] = arr[i];
        i--;
    }
    arr[i + 1] = target;
    return arr;
}
// this method takes a target number scanned in from the input and finds two numbers in
//the dynamic arrays that add up to the target number
// if no 2 numbers are able to add up to the target then the target is just printed
void sumOfNumbers(int arr[], int size, int target)
{
    for (int k = 0; k < size; k++)
    {
        for (int m = k + 1; m < size; m++)
        {
            if (arr[k] + arr[m] == target)
            {
                cout << target << endl
                     << " = " << arr[k] << " + " << arr[m] << endl;
                return;
            }
        }
    }
    cout << target << endl;
    return;
}
// this method is strictly used to print arrays after they have been modified
void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}
// this method finds the target value in array B, removes it and returns an updated array
// that has all elements in indexes after the target and shifts them to the left
// if the target is not in the array then a statement is printed letting the user know
int *removalB(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            for (int k = i; k < size; k++)
            {
                arr[k] = arr[k + 1];
            }
            cout << "Removing " << target << " at " << i << " in "
                 << "B" << endl;
            return arr;
        }
    }

    cout << "Element " << target << "  not found in B" << endl;
    return arr;
}
// this method does the exact same that a removalB except it prints it uses array A
// the only reason for two seperate methods was for printing purposes
int *removalA(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == target)
        {
            for (int k = i; k < size; k++)
            {
                arr[k] = arr[k + 1];
            }
            cout << "Removing " << target << " at " << i << " in "
                 << "A" << endl;
            return arr;
        }
    }
    cout << "Element " << target << "  not found in A" << endl;
    return arr;
}
// this method is used to search through array A
// binary search cannot be used because this array is not sorted
int search(int arr[], int size, int target)
{
    for (int i = 0; i < size; i++)
        if (arr[i] == target)
            return i;
    return -1;
}
// this method is used to search through array B
// since the array is sorted, binary search can be used
int binarySearch(int arr[], int low, int high, int target)
{
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        // Check if x is present at mid
        if (arr[mid] == target)
            return mid;

        // If x greater, ignore left half
        if (arr[mid] < target)
            low = mid + 1;

        // If x is smaller, ignore right half
        else
            high = mid - 1;
    }

    return -1;
}
// algorithm used to sort array B 
void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;

        // Move elements of arr[0..i-1],
        // that are greater than key, to one
        // position ahead of their
        // current position
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main()
{
    int maxValues;     // max number of values to store / length of the arrays
    int currentValues; // as we add, the number of values in the arrays
    int tempVal;       // variable used to read the number
    cin >> maxValues;  // read the maximum number of values from the redirected input file
//uses maxValues to give the length of the array
    cout << "Length of the array: " << maxValues << endl;
    // TODO create a dynamic array A of size maxValues
    int *A = new int[maxValues];

    // TODO read in the number from the redirected input
    cout << "Array A: ";
    // for loop going through array A to print out the unsorted array
    for (int i = 0; i < maxValues; i++)
    {
        cin >> tempVal;
        A[i] = tempVal;
        cout << A[i] << " ";
    }
    cout << endl;
    // TODO sort the array A and store it in B - any sorting algorithm can be used
   // this section makes a copy of array A named B and uses the insertion sort method to sort the array
    int *B = new int[maxValues];
    for (int i = 0; i < maxValues; i++)
    {
        B[i] = A[i];
    }
    insertionSort(B, maxValues);
// this section prins out thesorted array B
    cout << "Array B: ";

    for (int i = 0; i < maxValues; i++)
    {
        cout << B[i] << " ";
    }
    cout << endl;
    cout << endl;
    cout << "Find:" << endl;
// this ignores the next three lines of the input file then stores the amount of integers
// and creates a new dynamic array called searchB
    cin.ignore(3);
    int numRep;
    cin >> numRep;

    int *searchB = new int[numRep];
// this for loop itterates through searchB and fills the array with inputs from the file
    for (int i = 0; i < numRep; i++)
    {
        cin >> tempVal;
        searchB[i] = tempVal;
// uses binary search to find the target value in array B      
        if ((binarySearch(B, 0, maxValues, tempVal)) != -1)
        {
            cout << "Element " << tempVal << "  found at " << binarySearch(B, 0, maxValues, tempVal) << " in B" << endl;
        }
        else
        {
            cout << "Element " << tempVal << "  not found in B" << endl;
        }
    }

    cout << endl;
    cout << endl;
// makes a dynamic array called searchA and uses the search method to find the target element and give it's index
    int *searchA = new int[5];

    for (int k = 0; k < 5; k++)
    {
        searchA[k] = searchB[k];
        tempVal = searchA[k];
        if ((search(A, maxValues, tempVal)) != -1)
        {
            cout << "Element " << tempVal << "  found at " << search(A, maxValues, tempVal) << " in A" << endl;
        }
        else
        {
            cout << "Element " << tempVal << "  not found in A" << endl;
        }
    }

    cout << endl
         << "SumPairs:" << endl
         << "B:" << endl;
// ignores the 3 unused lines of input from the file
    cin.ignore(3);
    int sumRep;
    cin >> sumRep;
// creates new dynamic array that is the length of the next amount of integers before a break in the input
    int *sumPairsB = new int[sumRep];
// fills suumPairsB with input elements and uses the sumOfNumbers method
    for (int i = 0; i < sumRep; i++)
    {
        cin >> tempVal;
        sumPairsB[i] = tempVal;
        sumOfNumbers(B, maxValues, tempVal);
    }

    cout << endl
         << endl
         << "A:" << endl;
//creats dynamic array sumPairsA of length next amount of input files
    int *sumPairsA = new int[sumRep];

    for (int i = 0; i < sumRep; i++)
    {
        sumPairsA[i] = sumPairsB[i];
        tempVal = sumPairsA[i];
        sumOfNumbers(A, maxValues, tempVal);
    }

    cout << endl
         << "Remove:" << endl;
// again ignores the 3 lines of unused input then gets length of inputs used
    int remRep;
    cin.ignore(3);
    cin >> remRep;
// creats dynamic array removeB 
    int *removeB = new int[remRep];
//for loop fills removeB with imput values and uses the removalB method to remove a target value
    for (int i = 0; i < remRep; i++)
    {
        cin >> tempVal;
        removeB[i] = tempVal;
        removalB(B, maxValues, tempVal);
    }

    cout << endl;
//does the same thing as sections above except not with dynamic array removeA
    int *removeA = new int[remRep];

    for (int i = 0; i < remRep; i++)
    {
        removeA[i] = removeB[i];
        tempVal = removeA[i];
        removalA(A, maxValues, tempVal);
    }
// this section prints out the updated arrays after the target values have been removed
    cout << endl;
    maxValues = maxValues - remRep + 1;
    cout << "After removal Array A: ";
    printArray(A, maxValues);

    cout << "After removal Array B: ";
    printArray(B, maxValues);
// end of printed section
    cout << endl
         << "Insert:" << endl;
// ignores the three lines of unused input and gets the length of the dynamic array insertB
    int insRep;
    cin.ignore(3);
    cin >> insRep;

    int *insertB = new int[insRep];
    int size = maxValues;
// this for loop adds in the input values by calling insertionB 
// also increments the size of the array each time to make room for each new element
// values are added in a sorted order to keep the sorted order of array B
    for (int i = 0; i < insRep; i++)
    {
        size++;
        cin >> tempVal;
        insertB[i] = tempVal;
        insertionB(B, size - 1, tempVal);
    }

    cout << endl;
// does the same this that the last for loop but created the insertA element 
// since A is not sorted the elements are added in at the end of the array
    int *insertA = new int[insRep];
    size = maxValues;

    for (int i = 0; i < insRep; i++)
    {
        insertA[i] = insertB[i];
        tempVal = insertA[i];
        insertionA(A, size, tempVal);
        size++;
    }

    maxValues = maxValues + insRep;
    cout << endl;
// prints out the updated arrays after the inserted values have been added
    cout << "After insertions Array A: ";
    printArray(A, maxValues);

    cout << "After insertions Array B: ";
    printArray(B, maxValues);

    cout << endl;
// end of main method
    return 0;
}
