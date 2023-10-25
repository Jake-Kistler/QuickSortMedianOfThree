//Jake Kistler
//QuickSort done with median of three

#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>

using namespace std;

//core functions
int medianOfThree(int *arr, int leftIndex, int rightIndex); 
int partition(int *arr, int startIndex, int endIndex);
void quickSort(int *arr, int startIndex, int endIndex);
void insertionSort(int *arr, int startIndex, int endIndex);

//Helper functions
void exchageElement(int *arr, int a, int b);
void displayArray(int *arr, int size);
void displayGlobals();

//Global variables
const int SMALL_LIST_SIZE = 11;
int numExchanges = 0;
int numComparisons = 0;

int main(int argc, char **argv)
{
    string fileName;
    int listLength;

    cout << "Welcome to the quicksort test!" << endl;

    if(argc > 1)
    {
        cout << "File name collected as command line argument." << endl;
        fileName = argv[1];
    }
    else
    {
        cout << "File was not provided, please enter a file name." << endl;
        getline(cin,fileName);
    }

    ifstream file(fileName);

    if(!file.is_open())
    {
        cout << "Could not open file: " << fileName << endl;
        return EXIT_FAILURE;
    }

    //grab the list length 
    file >> listLength;

    int *parentArray = new int[listLength];

    //read data to the array
    int i = 0;
    while(!file.eof())
    {
        file >> parentArray[i];
        i++;
    }

    file.close();

    cout << "Parent array contains... " << endl;
    displayArray(parentArray, listLength);

    cout << "QuickSorting the array..." << endl;
    quickSort(parentArray, 0, listLength - 1);

    cout << "The sorted array: " << endl;
    displayArray(parentArray, listLength);

    cout << "Sorting metrics: " << endl;
    displayGlobals();

    string outputFileName;
    //editting the name of the output file
    if(fileName.size() > 4 & fileName.substr(fileName.size() - 4) == ".txt")
    {
        //strip the .txt and add "_sorted.txt"
        outputFileName = fileName.substr(0, fileName.size() - 4) + "_sorted.txt";
    }
    else
    {
        outputFileName = fileName + "_sorted";
    }
    

   
    ofstream output(outputFileName);

    cout << "Writting sorted list to " << outputFileName << endl;

    for(int i = 0; i < listLength; i++)
    {
         output << parentArray[i] << " ";
    }

    delete[] parentArray;
    return EXIT_SUCCESS;






}//EOM

int medianOfThree(int *arr,int leftIndex, int rightIndex)
{
    int middle = (leftIndex + rightIndex) / 2;
    
    numComparisons++;
    if(arr[leftIndex] > arr[middle])
    {
        exchageElement(arr, leftIndex, middle);
    }

    numComparisons++;
    if(arr[leftIndex] > arr[rightIndex])
    {
        exchageElement(arr, leftIndex, rightIndex);
    }

    numComparisons++;
    if(arr[middle] > arr[rightIndex])
    {
        exchageElement(arr, middle, rightIndex);
    }

    return middle;
}//EOF

int partition(int *arr, int startIndex, int endIndex)
{
    int pivotIndex = medianOfThree(arr, startIndex, endIndex);
    int pivotValue = arr[pivotIndex];

    exchageElement(arr, pivotIndex, endIndex);

    int i = startIndex;

    for(int k = startIndex; k < endIndex; k++)
    {
        numComparisons++;
        if(arr[k] < pivotValue)
        {
            exchageElement(arr, i, k);
            i++;
        }
    }

    exchageElement(arr, i, endIndex);
    return i;
}

void quickSort(int *arr, int startIndex, int endIndex)
{
    int currentSize = endIndex - startIndex + 1;

    if(currentSize <= SMALL_LIST_SIZE)
    {
        //cout << "List deemed too small to quicksort, insertion sorting the list." << endl;
        insertionSort(arr, startIndex, endIndex);
        return;
    }

    if(startIndex < endIndex)
    {
        int pivotindex = partition(arr, startIndex, endIndex);
        quickSort(arr, startIndex, pivotindex - 1);
        quickSort(arr, pivotindex + 1, endIndex);
    }
}

void insertionSort(int *arr, int startIndex, int endIndex)
{
    for(int i = startIndex + 1; i <= endIndex; i++)
    {
        int key = arr[i];
        int j = i - 1;

        while(j >= startIndex)
        {
            numComparisons++;
            if(arr[j] <= key)
            {
                break;
            }

            numExchanges++;
            arr[j + 1] = arr[j];
            j -= 1;
        }

        arr[j + 1] = key;
    }
}

//Helper functions
void exchageElement(int *arr, int a, int b)
{
    numExchanges++;

    int temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;

}

void displayArray(int *arr, int size)
{
    const int MAX_DISPLAY_SIZE = 200;
    const int COLUMNS = 10;

    if (size <= MAX_DISPLAY_SIZE)
    {
        // display the entire array
        for (int i = 0; i < size; i++)
        {
            cout << setw(6) << arr[i] << " ";

            if ((i + 1) % COLUMNS == 0)
            {
                cout << endl;
            }
        }

        cout << endl;
    }
    else
    {
        // display the first 100 and last 100 elements
        for (int i = 0; i < 100; i++)
        {
            cout << setw(6) << arr[i] << " ";

            if ((i + 1) % COLUMNS == 0)
            {
                cout << endl;
            }
        }

        cout << "... (skipping " << (size - 200) << " elements)..." << endl;

        // now the last 100 elements
        for (int i = size - 100; i < size; i++)
        {
            cout << setw(6) << arr[i] << " ";

            if ((i + 1) % COLUMNS == 0)
            {
                cout << endl;
            }
        }

        cout << endl;
    }
} // END PRINT ARRAY

void displayGlobals()
{
    cout << "Number of exchanges made : " << numExchanges << endl;
    cout << "Number of of comparisons made: " << numComparisons << endl;
}