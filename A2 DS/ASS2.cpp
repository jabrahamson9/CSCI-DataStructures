//Jon Abrahamson
//HW 2
//CSCI 2270-301
//Zagrodzki
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct words{
	int times;
	string word;
};

//function takes in a pointer to a memory location as well as a pointer to the cpacity of the old array. it then uses dynamic allocation to create a new array with twice the capacity
//of the old array. it then deletes the old array to free up memory.
void doublearray(words*& oldarray, int* capacity){
	int newCapacity = *capacity*2;
	words* newArray = new words[newCapacity];
	for(int i=0; i<*capacity; i++){
		newArray[i]=oldarray[i];
	}
	delete [] oldarray;
	oldarray = newArray;
	*capacity = newCapacity;
}

string ignorearr[50];//array of the common words to skip

//Split function splits a string at a character and stores them into a temp array which will
//be used to convert parts to ints
int Split(string str, char separator, string max[],int size){
    int counter=0;
    string word="";
    for(int i=0; i<str.length();i++){
        if(str[i]==separator){
            max[counter]=word; //stores the word into an array
            word=""; //resets the word to empty
            counter++;
        }
        else{
            word=word+str[i]; //this keeps adding characters to the string
        } 
    }
    if(word!=""){
        max[counter]=word; //adds the last word to the array
        counter++;
    }
    return counter;
}

int main(int argc, char* argv[]){
	string sent[20]; //this is the array to store each word of a line, the size is the total words that could be on the line
	int* capacity = new int(100); //creates the dynamic capacity varable pointer and sets it to 100 to begin, this will be doubled though
	words* structarray; //declare the struct array
	structarray = new words[*capacity]; //create the array with a dynamic size
	int doubles=0;
	ifstream hg(argv[1]);
	ifstream ignore(argv[2]);
	int totalwords=0;
	if(hg.fail() || ignore.fail()){//check to see if file opened correctly
		cout<<"File Failed To Open";
		return 0; 
	}

	int arrcount=0;
	while(!ignore.eof()){ //this loop fills the ignore array with the common most wrods in the document
		string ignoreword="";
		getline(ignore, ignoreword);
		ignorearr[arrcount]=ignoreword;
		arrcount++;
	}
	int count=0;
	totalwords=totalwords-3;
	while(!hg.eof()){
		string line="";
		getline(hg, line);
		int spaces=0;
		for(int z=0; z<line.length(); z++){
			if(line[z]==' '){
				spaces++;//basically a word counter
			}
		}
		if(line.length()<3){ //accounts for blank lines
			spaces=0;
			totalwords=totalwords-1;//spaces count as a word in the function so must subtract one
		}
		
		Split(line, ' ', sent, spaces);
		bool newword;//to see when a word existed in the array already
		if(spaces!=0){//so it doesnt take into account blank lines
			for(int i=0; i<spaces; i++){
				newword=false;//initializes so that it assumes the word isnt in the array
				int index=1;
				for(int j=-1; j<count; j++){
					if(sent[i]==structarray[j].word){//this means that the new word already was present in the array
						structarray[j].times++;	//occurance
						totalwords++;
						newword=true;			
					}
				}
				if(newword==false){//word doesnt exist
					structarray[count].word=sent[i]; //adds to array
					structarray[count].times=1;
					count++;
					totalwords++;
					if(count==*capacity){
						doublearray(structarray, capacity); ///double the capacity using dynamic array
						doubles++; //counts the number times the array is doubled
					}
				}
				for(int i=0; i<count; i++){
					for(int j=0; j<50; j++){
						if(structarray[i].word==ignorearr[j]){//if the new word is one of the 50 most common words then it removes it from the list
							for(int x=i; x<count; x++){
								structarray[x].word=structarray[x+1].word;
								structarray[x].times=structarray[x+1].times;
							}
							count=count-1;
							totalwords=totalwords-1;//account for removal
						}
					}
				}
			}
		}

}//*********************************************************


	    int n=10;//ten most common words
	    int max=0;
	    string wordmax="";
	    int i;
	    int j;
	    int B[n];
	    string topword[n];
			    for(i=0;i<count;i++){
				        if(structarray[i].times>max)
				        max=structarray[i].times;
				    	wordmax=structarray[i].word;
			       }
			     B[0]=max;//the top most occuring word

			     for(i=1;i<n;i++){
					       max=0;
					       wordmax="";
					       for(j=0;j<count;j++){
					         if(structarray[j].times>max&&structarray[j].times<B[i-1])
					            max=structarray[j].times; //finds the most common word other than the one already found and sets it as max 
					        	wordmax=structarray[j].word;
					       }
					        B[i]=max;//adds it to the array
					        topword[i]=structarray[i].word; //this is just to find the word that goes aliong with it
			     }
			    for(int z=0; z<count; z++){
				    for(int i=0; i<n; i++){
				    	if(structarray[z].times==B[i])
				     		topword[i]=structarray[z].word;//finding the words in the main array that corresponds with the most occuring words
				    }
				}

for(int i=0;i<n;i++){
	cout<<B[i]<<" - "<<topword[i]<<endl;
}
cout<<"#"<<endl<<"Array doubled: "<<doubles<<endl<<"#"<<endl;
cout<<"Unique non-common words: "<<count-1<<endl<<"#"<<endl;
cout<<"Total non-common words: "<<totalwords;
			


	ignore.close();
	hg.close();
	return 0;
}