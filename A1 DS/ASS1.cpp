//Jon Abrahamson
//Assignment 1
//Zagrodzki 300
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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


struct stuff{ //array of structs
		string type;
		int state;
		int price;
};


//takes a filename as an input to be opened in command prompt. reads in the file and then creates an array of structs to store items on the message board, after each new item is added to
//the array, the function then checks if there is a match (if its for sale it looks for a equal or greater wanting price and vice versa). The function then displays the sold items
//onto the message board as they occur and delete the two items off of the array. After the file was fully read, the function then reveals the left over items (the items remaining in the array).
int main(int argc, char* argv[]){ //this is to prompt the comman prompt for input. arc is number of commands and argv is the array in which they are stored
	ifstream filename(argv[1]);//retrieving the filename from command prompt
	int count=0;
	stuff listing[100];//the array of structs, 100 is the max number of lines
	string parts[100];//parts is where the split function will store its content
	while(!filename.eof()){ //searches file until the end
		bool change= false; //this is to decide if a match was found
		int intprice=0;
		string price="";
		string yn="";			//intitalizing strings
		string typeof = "";
		string line;
		getline(filename, line); //retrieve the entire line and store it as a string "line"
		Split(line, ',', parts, 3); //split function seperates at comma and stores items in parts with size 3
		typeof = parts[0];
		listing[count].type=typeof;
		yn = parts[1]; // used 1 becasue there was a space before
		if(yn[1]=='f'){ //"for sale"
			listing[count].state=1; //1 means the item is for sale
		}
		else{
			listing[count].state=0; //0 is wanted
		}
		price = parts[2];
		price=price.erase(0,1); //get rid of space in string
		intprice=stoi(price);
		listing[count].price=intprice; //now an int

	for(int i=0; i<=count; i++){
			if(listing[i].type==listing[count].type && listing[i].state != listing[count].state){ // sees if its the same item but one for sale and one wanted
				if(listing[i].state == 0 && listing[count].state == 1 && listing[i].price >= listing[count].price){
					cout<<listing[count].type<<" "<<listing[count].price<<endl; //count is the for sale
					for(int j=i; j<= count; j++){	
						listing[j].type=listing[j+1].type;
						listing[j].state=listing[j+1].state;	//these shift the array left
						listing[j].price=listing[j+1].price;
					}
						change=true; //match found
						break;
				}
				else if(listing[i].state == 1 && listing[count].state == 0 && listing[count].price >= listing[i].price){
					cout<<listing[i].type<<" "<<listing[i].price<<endl; //i is the for sale
					for(int j=i; j<= count; j++){	
						listing[j].type=listing[j+1].type;
						listing[j].state=listing[j+1].state;
						listing[j].price=listing[j+1].price;
					}
						change=true; //match found
						break;
				}
			}
	}
		if(change == true){ //this is where the bool comes in, if true then two items are removed
			count=count-2;  //so then we must substract 2 from the number of items in the array
		}
		count++;
	}
	cout<<"#"<<endl;
	for(int i=0; i<count; i++){ //this is to just display what is left on the board AKA the array
		string str="";
		if(listing[i].state==1){
			str = "for sale";
		}
		else{
			str="wanted";
		}
		cout<<listing[i].type<<", "<<str<<", "<<listing[i].price<<endl;
	}
	cout<<"#"<<endl;
	filename.close(); //closing file

	return 0;
}