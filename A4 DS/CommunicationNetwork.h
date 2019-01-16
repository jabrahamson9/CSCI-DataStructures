#ifndef COMMUNICATIONNETWORK_H
#define COMMUNICATIONNETWORK_H

#include <iostream>

using namespace std;

struct City{
	string cityName;
	City* next;
	City*previous;
	string message;
	City(string cname, City *n, City* pr, string initmessage){ //setting up parameters of the node
		cityName=cname;
		previous=pr;
		next=n;
		message=initmessage;
	}
};


class CommunicationNetwork{
	public:
		CommunicationNetwork();	//default constructor
		~CommunicationNetwork();	//destructor
		int printMenu();
		void cityList();
		void buildNetwork();
		void printNetwork();
		void addCity(string, string);
		void transmitMsg(char* filename);
		City* search(string value /*City* head*/);
		void deleteCity(string delName);
		void deleteNetwork();
		string filename;
	private:
		City* tail;
		City* head;

};

#endif

