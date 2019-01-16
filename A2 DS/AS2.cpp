//JC Abrahamson
//Assignment 2
//CSCI2270-300

#include <iostream>
#include <fstream>
using namespace std;


struct Items
{
    string word;
    int count;
};

void getStopWords(char *ignoreWordFileName, string ignoreArr[]);
bool isStopWord(string word, string ignoreArr[]);
int getTotalNumberNonStopWords(Items list[], int length);
void arraySort(Items list[], int length);
void printTopN(Items ItemsList[], int topN);

int main(int argc, char* argv[])
{
    ifstream inStream;      

    Items *arr;          
    Items *newArr;         
    string ignoreArr[50]; 
    int doubles = 0;   // stores the times we double the array
    int location = 0;         // stores the location of the last element in the arr
    int capcity = 100;  // stores the capacity of th e array
    int totalWords = 0;     // stores the total number of unique words in the document
    int TopNum = stoi(argv[1]);

    if (argc != 4) // to make it so that the correct files are inputted into command prompt
    {
        cout << "Command Prompt: <top __ words> <bookfilename> <ignoreWordsfilename>" << endl;
        return 0;
    }
    
    inStream.open(argv[2]); //opens file

    if (!inStream) //error if file doesn't open
    {
        cout << "Error opening file" << endl;
        return 0;
    }

    arr = new Items[capcity]; // initializes array to whatever the capacity is
    string word;                     
    Items tmp;                    
    bool found;                  

    getStopWords(argv[3], ignoreArr);

    while (!inStream.eof()) //check the whole file line by line
    {
        found = false;

        inStream >> word; // read in word by word of the line
        if(!isStopWord(word, ignoreArr))
        {
            for (int i = 0; i < location; i++) // check if the word has already in the list
            {
                if (word==arr[i].word)
                {
                    found=true;
                    arr[i].count++;
                    i = location;
                }
            }
            if (found == false) //checks if word was found and if it isnt then add it to the array
            {
                if (location < capcity)
                {
                    arr[location].word = word;
                    arr[location].count = 1;
                    location++;
                }
                // if there is not enough space, double the size of the array
                else
                {
                    newArr = new Items[capcity*2]; //new array
                    for (int i = 0; i < capcity; i++)
                        newArr[i] = arr[i];
                    newArr[capcity].word = word;
                    newArr[capcity].count = 1;
                    location++;
                    delete[] arr; //free up memory
                    arr = newArr; //reallocate array content to original
                    capcity *= 2; //double array
                    doubles++; //count for "double array"
                }
            }
        }

    }
    inStream.close();
    arraySort(arr, location); 
    printTopN(arr, TopNum);

    // print how many time the array doubled
    cout << "#" << endl;
    cout << "Array doubled: " << doubles << endl;

    // print the unique non-common words
    cout << "#" << endl;
    cout << "Unique non-common words: "<< location <<endl;

    // print out the total number of non-common words
    cout << "#" << endl;
    totalWords = getTotalNumberNonStopWords(arr, location);
    cout << "Total non-common words: " << totalWords << endl;

    // free the final array
    delete[] arr;

    return 0;
}

/*
* Function name: printTopN
* Purpose: to print the top N high frequency words
* @param ItemsList - a pointer that points to a *sorted* array of Itemss 
* @param topN - the number of top frequency words to print
* @return none
*/
void printTopN(Items ItemsList[], int topN)
{
    // print out the most frequent words
    for (int i = 0; i < topN; i++)
        cout << ItemsList[i].count << " - " << ItemsList[i].word << endl;
}

/*
* Function name: getTotalNumberNonStopWords
* Purpose: compute the total number of words saved in the words array (including repeated words)
* @param list - an array of Itemss containing non-stopwords
* @param length - the length of the words array
* @return - the total number of words in the words array (including repeated words multiple times)
*/
int getTotalNumberNonStopWords(Items list[], int length)
{
    // print out the sum of all the words in the Items list
    int totalWords = 0;
    for (int i = 0; i < length; i++)
        totalWords += list[i].count;
    return totalWords;
}

/*
* Function name: isStopWord
* Purpose: to see if a word is a stop word
* @param word - a word (which you want to check if it is a stop word)
* @param ignoreArr - the array of strings storing ignore/stop words 
* @return - true (if word is a stop word), or false (otherwise)
*/
bool isStopWord(string word, string ignoreArr[])
{
    for (int i = 0; i < 50; i++) //search all stop words
        if (word == ignoreArr[i])
            return true;
    return false;
}

/*
* Function name: getStopWords
* Purpose: read stop word list from file and store into an array
* @param ignoreWordFile - filename (the file storing ignore words)
* @param ignoreArr - store ignore words from the file (pass by reference) 
* @return - none
* Note: The number of words is fixed to 50
*/
void getStopWords(char *ignoreWordFileName, string ignoreArr[])
{
    // open the file
    ifstream in_stream;
    in_stream.open(ignoreWordFileName);

    // go through the words in the text file and store them in the ignoreArr array
    int count = 0;
    string line;
    while (!in_stream.eof())
    {
        getline(in_stream, line);
        ignoreArr[count++] = line;
    }
    in_stream.close();
}

/*
* Function name: arraySort
* Purpose: sort an array of Itemss, increasing, by their count fields 
* @param list - an array of Itemss to be sorted
* @param length - the length of the words array
*/
void arraySort(Items list[], int length) //use bubble sort
{
    int i, j;
    Items temp;
    for(i = 0; i < length; i++)
    {
        for (j = i+1; j < length; j++)
        {
            if (list[i].count < list[j].count)
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        }
    }
}