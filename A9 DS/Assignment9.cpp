#include <iostream>
#include <fstream>
#include <vector>
#include "Graph.hpp"


using namespace std;

int main(int argc, char* argv[]){
	//Building Graph
	ifstream dataFile(argv[1]);
	if(dataFile.fail()){
		cout << "Data file failed to open!" << endl;
		return 0;
	}
	string line;
	int filecounter = 0;
	int commacounter = 0;
	int namecounter = 0;
	vector<string> citynames;
	vector<int> cityData;
	Graph g;
	while(getline(dataFile,line)){
		if(filecounter==0){
			//Adding cities to a vector of city names
			line = line + ",";
			line = line.substr(7,line.length());
			for(int i=0 ; i<line.length() ; i++){
				if(line[i]==','){
					citynames.push_back(line.substr(i-commacounter,commacounter));
					commacounter = 0;
				}
				else{
					commacounter++;
				}
			}
			for(int i=0 ; i<citynames.size() ; i++){
				g.addVertex(citynames[i]);
			}
		}
		else{
			for(int i=0 ; i<line.length() ; i++){
				if(line[i]==','){
					line = line.substr(i+1,line.length());
					break;
				}
			}
			line = line + ",";
			for(int i=0 ; i<line.length() ; i++){
				if(line[i]==','){
					cityData.push_back(stoi(line.substr(i-commacounter,commacounter)));
					commacounter = 0;
				}
				else{
					commacounter++;
				}
			}
			for(int i=0 ; i<cityData.size() ; i++){
				if(cityData[i]!=-1){
					g.addEdge(citynames[namecounter],citynames[i],cityData[i]);
				}
			}
			cityData.clear();
			namecounter++;
		}
		filecounter++;
	}

	//Menu
	bool quit = false;
	string v1;
	string v2;
	string menuinput;
	while(quit!=true){
		cout << "======Main Menu======" << endl;
		cout << "1. Print vertices" << endl;
		cout << "2. Find districts" << endl;
		cout << "3. Find shortest path" << endl;
		cout << "4. Find shortest weighted path" << endl;
		cout << "5. Quit" << endl;
		getline(cin,menuinput);
		if(menuinput=="1"){
			g.displayEdges();
		}
		if(menuinput=="2"){
			g.assignDistricts();
		}
		if(menuinput=="3"){
			string startC;
			string endC;
			cout << "Enter a starting city:" << endl;
			getline(cin,startC);
			cout << "Enter an ending city:" << endl;
			getline(cin,endC);
			g.shortestPath(startC,endC);
		}
		if(menuinput=="4"){
			string sC;
			string eC;
			cout << "Enter a starting city:" << endl;
			getline(cin,sC);
			cout << "Enter an ending city:" << endl;
			getline(cin,eC);
			g.shortestWeightedPath(sC,eC);
		}
		if(menuinput=="5"){
			cout << "Goodbye!" << endl;
			quit = true;
		}
	}
	dataFile.close();
	return 0;
}