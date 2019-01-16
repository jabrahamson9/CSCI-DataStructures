#include <iostream>
#include "Queue.cpp"
#include "Queue.h"
using namespace std;

int main(){
	Queue test(10);
	cout<<"======Main Menu====="<<endl;
	cout<<"1. Enqueue word"<<endl<<"2. Dequeue word"<<endl<<"3. Print queue"<<endl<<"4. Enqueue sentence"<<endl<<"5. Quit"<<endl;

	char z='\0';
	cin>>z;
	while(z!='5'){
		if(z=='1'){
			string word="";
			cout<<"word: ";
			cin>>word;
			test.enqueue(word);
		}
		else if(z=='2'){
			test.dequeue();
		}
		else if(z=='3'){
			test.printQueue();
		}
		else if(z=='4'){
			string sent="";
			cout<<"sentence: ";
			cin.ignore();
			getline(cin, sent);
			test.enqueueSentence(sent);
		}
		cout<<"======Main Menu====="<<endl;
		cout<<"1. Enqueue word"<<endl<<"2. Dequeue word"<<endl<<"3. Print queue"<<endl<<"4. Enqueue sentence"<<endl<<"5. Quit"<<endl;
		cin>>z;
	}
	cout<<"Goodbye!"<<endl;
	return 0;


}