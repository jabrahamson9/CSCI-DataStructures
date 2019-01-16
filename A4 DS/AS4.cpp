//Jon Abrahamson
//Data Structures 2270-301
//Assignment 3

#include <iostream>
#include <fstream>//file I/O
#include <sstream>//for parsing a string

using namespace std;

struct city{
	string cityName;
	city* next;
	city*prev;
	string message;
	city(string cname, city *n, city* pr, string initmessage){ //setting up parameters of the node
		cityName=cname;
		prev=pr;
		next=n;
		message=initmessage;
	}
};

///this is the beginning path
city* head=new city("NULL",NULL,NULL,"");
city* pathA=new city("Los Angeles",NULL, head,"");
city* pathB=new city("Phoenix", NULL, pathA,"");
city* pathC=new city("Denver", NULL, pathB,"");
city* pathD=new city("Dallas", NULL, pathC,"");
city* pathE=new city("St. Louis",NULL, pathD,"");
city* pathF=new city("Chicago", NULL, pathE,"");
city* pathG=new city("Atlanta", NULL, pathF,"");
city* pathH=new city("Washington, D.C.", NULL, pathG,"");
city* pathI=new city("New York", NULL, pathH,"");
city* pathJ=new city("Boston", NULL, pathI,"");
city* tail;

//declaration of all of the functions used
int printMenu();
void cityList();
city* buildNetwork();
void printPath(city* head);
city* addCity(city* head, city* prevNode, string city_name);
void transmitMsg(city* head);
city* search(string value, city* head);
void deleteCity(string delName);
void deleteNetwork();


int main(){
	while(1==1){ //makes it an infinite loop
		char choice= '\0'; //initializes the options character to empty
		choice=printMenu();
		if(choice=='1'){
			head=buildNetwork();
		}
		else if(choice=='2'){
			if(head==NULL){ // this just makes sure that the list was built before other actions are attempted.
				cout<<"Empty List"<<endl;
			}
			else{
				printPath(head);
			}
		}
		else if(choice=='3'){
			if(head==NULL){
				cout<<"Empty List"<<endl;
			}
			else{
				transmitMsg(head);
			}
		}
		else if(choice=='4'){
			if(head==NULL){
				cout<<"Empty List"<<endl;
			}
			else{
				cin.ignore();//this is needed because it would skip over my getline. This makes it pause first
				cout<<"Enter a City name:";
				string newCity;
				getline(cin, newCity);
				cout<<endl;
				cout<<"Enter a previous City name:";
				string cityPrevious;
				getline(cin, cityPrevious);
				cout<<endl;
				city* current;
				current=search(cityPrevious, head);
				addCity(head, current, newCity);
				cityPrevious="";
				newCity="";
			}
		}
		else if(choice=='5'){
			cout<<"Enter a city Name:";
			string citydel;
			cin.ignore();
			getline(cin, citydel);
			cout<<endl;
			deleteCity(citydel);
		}
		else if(choice=='6'){
			deleteNetwork();
		}
		else if(choice=='7'){
			cout<<"Goodbye!"<<endl;
			break;
		}
		else{
			cout<<"Sorry that was not an option, Try Again"<<endl<<endl;
		}
	}
	return 0;
}


city *buildNetwork(){ //builds the base network with the already provided nodes
	head->next=pathA;
	pathA->next=pathB;
	pathB->next=pathC;
	pathC->next=pathD;
	pathD->next=pathE;
	pathE->next=pathF;
	pathF->next=pathG;
	pathG->next=pathH;
	pathH->next=pathI;
	pathI->next=pathJ;
	pathJ->next=tail;

	return head; // returns the head so that the first part of the link can be used by other functions to searhc the list
}

//takes in the head of the path as a paramter and then prints the current path by setting an artifical node that links through each node and prints its info until it hits the tail\
//or a NULL node
void printPath(city* head){
		cout<<"===CURRENT PATH==="<<endl;
		city* p = head; //artificial node
		while(p!=NULL){
			cout<<p->cityName<<" <-> ";
			p=p->next;
		}
		cout<<" NULL"<<endl;
		cout<<"=================="<<endl;
}

//takes in the head, a previous node and a new city name as parameters. the previous node was found in main through a search funtion and then this function checks to see if 
//one of the parameters was a NULL value, if not it then searhcces for the previous node and adds the new node/city in after it.
city* addCity(city* head, city* prevNode, string city_name){
	if(head == NULL){
		city* n1 = new city(city_name, NULL, NULL, "");
		return n1;
	}
	if(prevNode == NULL){
		city* n1 = new city(city_name, head, NULL, "");
		return n1;
	}
	city* temp=new city(city_name, NULL, NULL, "");
	prevNode->next->prev=temp;
	temp->next=prevNode->next;//outs it into the link
	prevNode->next=temp;
	temp->prev=prevNode;

	return head;
}

//sets the message equal to the message string of each node and then once it moves the message to the next node it deletes it from the
//previous one
void transmitMsg(city* head){
	ifstream text("messageIn.txt");//file containing message
	if(text.is_open()){//checkls if it is open
	while(!text.eof()){
		string line="";
		getline(text, line);
		istringstream ss(line);//this is used to split the message into its individual words
		string token;
		while(getline(ss, token, ' ')){//split sp each word is sent seperate
			string mess=token;
			city* temp = new city("", NULL, NULL, ""); //artificial node to go through linked list
			temp=head;
			while(temp!=NULL){//couts as each link recievs the message
				temp->message=mess;
				cout<<temp->cityName<<" received "<<temp->message<<endl;
				temp->message="";
				temp=temp->next;
			}
		}
	}
	}
	else{
		cout<<"FILE FAILED TO OPEN"<<endl;
	}
}

//just the general start menu
int printMenu(){
	cout<<"======Main Menu======"<<endl;
	cout<<"1. Build Network"<<endl;
	cout<<"2. Print Network Path"<< endl;
	cout<<"3. Transmit Message Coast-To-Coast"<<endl;
	cout<<"4. Add City"<<endl;
	cout<<"5. Delete City"<<endl;
	cout<<"6. Clear Network"<<endl;
	cout<<"7. Quit"<<endl;

	char choice;//this char should just be a number if not then in main it returns that a valid selection wasnt selected
	cin>>choice;
	cout<<endl;
	return choice;
}

//this is a fucntion that I made myself to be abkle to search the established network to find the previous node in which we were going to
//add a new link after it. We need this because the link is duynamic and the pointer must be found in order to manipulate the list after it
city* search(string value, city* head){
	city* current=head;
	while(current!=NULL){
		if(current->cityName==value){
			return current; //tAShis means the node was found and it is then returned to be used 
		}
		current=current->next;
	}
	return NULL;
}

void deleteCity(string delName){
	city* tempA;
	city* tempB;
	city* tempC;
	tempA=search(delName, head);
	if(tempA==NULL){
		cout<<delName<<" not found"<<endl;
	}
	else{
		tempB=tempA->prev;
		tempC=tempA->next; 
		tempB->next=tempC;
		tempC->prev=tempB;
		delete tempA;
	}
}

void deleteNetwork(){
	city* temp= head->next;
	while(temp!=NULL){
		head->next=temp->next;
		temp->next=NULL;
		temp=head->next;
	}
}


