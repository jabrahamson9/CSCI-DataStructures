#include <iostream>
#include "CommunicationNetwork.h"
#include <fstream>//file I/O
#include <sstream>//for parsing a string

using namespace std;

CommunicationNetwork::CommunicationNetwork(){
}

CommunicationNetwork::~CommunicationNetwork(){
		deleteNetwork();
		head=NULL;
		tail=NULL;
}



void CommunicationNetwork::buildNetwork(){ //builds the base network with the already provided nodes
	City* pathA=new City("Los Angeles",NULL, NULL,"");
	City* pathB=new City("Phoenix", NULL, pathA,"");
	City* pathC=new City("Denver", NULL, pathB,"");
	City* pathD=new City("Dallas", NULL, pathC,"");
	City* pathE=new City("St. Louis",NULL, pathD,"");
	City* pathF=new City("Chicago", NULL, pathE,"");
	City* pathG=new City("Atlanta", NULL, pathF,"");
	City* pathH=new City("Washington, D.C.", NULL, pathG,"");
	City* pathI=new City("New York", NULL, pathH,"");
	City* pathJ=new City("Boston", NULL, pathI,"");
	head=pathA;
	pathA->next=pathB;
	pathB->next=pathC;
	pathC->next=pathD;
	pathD->next=pathE;
	pathE->next=pathF;
	pathF->next=pathG;
	pathG->next=pathH;
	pathH->next=pathI;
	pathI->next=pathJ;
	pathJ=tail;

		cout<<"===CURRENT PATH==="<<endl;
		City* p = head; //artificial node
		cout<<"NULL <- ";
		while(p!=NULL){
			if(p->next==NULL){
				cout<<p->cityName<<" -> ";
			}
			else if(p==head){
				cout<<p->cityName<<" <- ";
			}
			else{
			cout<<p->cityName<<" <-> ";
			}
			p=p->next;
		}
		cout<<"NULL"<<endl;
		cout<<"=================="<<endl;
}

//this is a fucntion that I made myself to be abkle to search the established network to find the previous node in which we were going to
//add a new link after it. We need this because the link is duynamic and the pointer must be found in order to manipulate the list after it
City* CommunicationNetwork::search(string value /*City* head*/){
	City* current=head;
	while(current!=NULL){
		if(current->cityName==value){
			return current; //tAShis means the node was found and it is then returned to be used 
		}
		current=current->next;
	}
	return NULL;
}

//takes in the head of the path as a paramter and then prints the current path by setting an artifical node that links through each node and prints its info until it hits the tail\
//or a NULL node
void CommunicationNetwork::printNetwork(){
		cout<<"===CURRENT PATH==="<<endl;
		City* p = head; //artificial node
		cout<<"NULL <- ";
		while(p!=NULL){
			if(p->next==NULL){
				cout<<p->cityName<<" -> ";
			}
			/*else if(p==head){
				cout<<p->cityName<<" <- ";
			}*/
			else{
			cout<<p->cityName<<" <-> ";
			}
			p=p->next;
		}
		cout<<"NULL"<<endl;
		cout<<"=================="<<endl;
}

//takes in the head, a previous node and a new City name as parameters. the previous node was found in main through a search funtion and then this function checks to see if 
//one of the parameters was a NULL value, if not it then searhcces for the previous node and adds the new node/City in after it.
void CommunicationNetwork::addCity(string newCityName, string prevCityName){
	City* newCity=new City(newCityName,NULL,NULL,"");
	City* z=head;
	if(head==NULL && tail==NULL){
		head=newCity;
		tail=newCity;
		newCity->next=NULL;
		newCity->previous=NULL;
	}
	else if(prevCityName==""){
		tail->next=newCity;
		newCity->previous=tail;
		newCity->next=NULL;
		tail=newCity;
	}
	else if(prevCityName=="First"){
		newCity->next=head;
		head->next->previous=newCity;
		newCity->previous=NULL;
		head=newCity;
	}
	else{
		while(z!=NULL){
			if(z->cityName==prevCityName){
				newCity->next=z->next;
				newCity->previous=z;
				z->next=newCity;
			}
			z=z->next;
		}
	}

	//return head;
}

//sets the message equal to the message string of each node and then once it moves the message to the next node it deletes it from the
//previous one
void CommunicationNetwork::transmitMsg(char* filename){
	ifstream text(filename);//file containing message
	if(text.is_open()){//checkls if it is open
	while(!text.eof()){
		string line="";
		getline(text, line);
		istringstream ss(line);//this is used to split the message into its individual words
		string token;
		while(getline(ss, token, ' ')){//split sp each word is sent seperate
			string mess=token;
			City* temp = new City("", NULL, NULL, ""); //artificial node to go through linked list
			temp=head;
			while(temp!=NULL){//couts as each link recievs the message
				temp->message=mess;
				cout<<temp->cityName<<" received "<<temp->message<<endl;
				temp->message="";
				temp=temp->next;
			}
			City* tempZ = new City("", NULL, NULL, "");
			tempZ=tail;
			tempZ=tempZ->previous;
			while(tempZ!=NULL){
				tempZ->message=mess;
				cout<<tempZ->cityName<<" received "<<tempZ->message<<endl;
				tempZ->message="";
				tempZ=tempZ->previous;
			}
		}
	}
	}
	else{
		cout<<"FILE FAILED TO OPEN"<<endl;
	}
}

//just the general start menu
int CommunicationNetwork::printMenu(){
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


void CommunicationNetwork::deleteCity(string delName){
	City* tempA;
	City* tempB;
	City* tempC;
	bool found = false;
	tempA=head;
	while(tempA!=NULL){
		if(tempA->cityName==delName){
			if(tempA->previous==NULL){
				tempA->next->previous==NULL;
				head=tempA->next;
			}
			else if(tempA->next==NULL){
				tempA->previous->next=NULL;
				tail=tempA->next;
			}
			else{
				tempA->previous->next=tempA->next;
				tempA->next->previous=tempA->previous;
				delete tempA;
			}
			found = true;
		}
		tempA=tempA->next;
	}
	if(found==false){
		cout<< delName<<" not found "<<endl;
	}
}

void CommunicationNetwork::deleteNetwork(){
	City* temp= head;
	while(temp!=NULL){
		City* p = head; //artificial node
		while(p!=NULL){
			cout<<"deleting "<<p->cityName<<endl;
			p=p->next;
		}
		head->next=temp->next;
		temp->next=NULL;
		temp=head->next;
	}
	head=NULL;
}
