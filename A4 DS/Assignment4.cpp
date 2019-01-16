#include <iostream>
#include "CommunicationNetwork.h"
#include "CommunicationNetwork.cpp"
#include <fstream>//file I/O
#include <sstream>//for parsing a string

using namespace std;

int main(int argc, char* argv[]){
	CommunicationNetwork test;

	while(1==1){ //makes it an infinite loop
		char choice= '\0'; //initializes the options character to empty
		cout<<"======Main Menu======"<<endl;
		cout<<"1. Build Network"<<endl;
		cout<<"2. Print Network Path"<< endl;
		cout<<"3. Transmit Message Coast-To-Coast-To-Coast"<<endl;
		cout<<"4. Add City"<<endl;
		cout<<"5. Delete City"<<endl;
		cout<<"6. Clear Network"<<endl;
		cout<<"7. Quit"<<endl;
		cin>>choice;
		//cout<<endl;
		//choice=test.printMenu();
		if(choice=='1'){
			test.buildNetwork();
			test.printNetwork();
		}
		else if(choice=='2'){
			 // this just makes sure that the list was built before other actions are attempted.
				//cout<<"Empty List"<<endl;
				test.printNetwork();
		}
		else if(choice=='3'){
				//cout<<"Empty List"<<endl;
				test.transmitMsg(argv[1]);
		}
		else if(choice=='4'){
				//cout<<"Empty List"<<endl;
				cin.ignore();//this is needed because it would skip over my getline. This makes it pause first
				cout<<"Enter a city name:";
				string newCity;
				getline(cin, newCity);
				cout<<endl;
				cout<<"Enter a previous city name:";
				string cityPrevious;
				getline(cin, cityPrevious);
				cout<<endl;
				test.addCity(newCity, cityPrevious);
				cityPrevious="";
				newCity="";
		}
		else if(choice=='5'){
			cout<<"Enter a city name:";
			string citydel;
			cin.ignore();
			getline(cin, citydel);
			cout<<endl;
			test.deleteCity(citydel);
		}
		else if(choice=='6'){
			test.deleteNetwork();
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