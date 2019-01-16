#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct city{
	string cityName;
	city* next;
	string message;
	city(string cname, city *n, string initmessage){
		cityName=cname;
		next=n;
		message=initmessage;
	}
};

city* head=NULL;
city* pathA=new city("Los Angeles", NULL,"");
city* pathB=new city("Phoenix", NULL,"");
city* pathC=new city("Denver", NULL,"");
city* pathD=new city("Dallas", NULL,"");
city* pathE=new city("St. Louis", NULL,"");
city* pathF=new city("Chicago", NULL,"");
city* pathG=new city("Atlanta", NULL,"");
city* pathH=new city("Washington, D.C.", NULL,"");
city* pathI=new city("New York", NULL,"");
city* pathJ=new city("Boston", NULL,"");
city* tail;

int printMenu();
city* buildNetwork();
void printPath(city* head);
city* addCity(city* head, city* prevNode, string city_name);
void transmitMsg(city* head);
city* search(string value, city* head);


int main(){
	while(1==1){
		char choice= '\0';
		choice=printMenu();
		if(choice=='1'){
			head=buildNetwork();
		}
		else if(choice=='2'){
			if(head==NULL){
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
				cin.ignore();
				cout<<"Enter a City City name:"<<endl;
				string newCity;
				getline(cin, newCity);
				cout<<endl;
				cout<<"Enter a previous City City name:"<<endl;
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
			cout<<"Goodbye!"<<endl;
			break;
		}
		else{
			cout<<"Sorry that was not an option, Try Again"<<endl<<endl;
		}
	}
	return 0;
}


city *buildNetwork(){
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
	pathJ->next=tail;
	return head;
}

void printPath(city* head){
		cout<<"===CURRENT PATH==="<<endl;
		city* p = head;
		while(p!=NULL){
			cout<<p->cityName<<" -> ";
			p=p->next;
		}
		cout<<" NULL"<<endl;
		cout<<"=================="<<endl;
}

city* addCity(city* head, city* prevNode, string city_name){
	city* temp=new city(city_name, NULL, "");
	temp->next=prevNode->next;
	prevNode->next=temp;

	return head;
}

void transmitMsg(city* head){
	ifstream text("messageLn.txt");
	while(!text.eof()){
		string line="";
		getline(text, line);
		istringstream ss(line);
		string token;
		while(getline(ss, token, ' ')){
			string mess=token;
			city* temp = new city("", NULL, "");
			temp=head;
			while(temp!=NULL){
				temp->message=mess;
				cout<<temp->cityName<<" received "<<temp->message<<endl;
				temp->message="";
				temp=temp->next;
			}
		}
	}

}

int printMenu(){
	cout<<"======Main Menu======"<<endl;
	cout<<"1. Build Network"<<endl;
	cout<<"2. Print Network Path"<< endl;
	cout<<"3. Transmit Message Coast-To-Coast"<<endl;
	cout<<"4. Add City"<<endl;
	cout<<"5. Quit"<<endl;

	//cout<<endl<<"Type Option Number & Hit Enter:	";
	char choice;
	cin>>choice;
	cout<<endl;
	return choice;
}


city* search(string value, city* head){
	city* current=head;
	while(current!=NULL){
		if(current->cityName==value){
			return current;
		}
		current=current->next;
	}
	return NULL;
}