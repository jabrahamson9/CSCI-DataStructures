#include "AS9.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;


void Graph::addEdge(string v1, string v2, int weight){

    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    /*adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = weight;
                    vertices[j].adj.push_back(av2);*/
                }
            }
        }
    }
}
void Graph::addVertex(string n){
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" already in the graph."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        vertices.push_back(v);

    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    int z;
    for(int i = 0; i < vertices.size(); i++){
        cout<<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
        	if(vertices[i].adj[j].weight>0){
            	cout<<vertices[i].adj[j].v->name;
            	z=j+1;
            	break;
        	}
        }
        for(int j = z; j < vertices[i].adj.size(); j++){
        	if(vertices[i].adj[j].weight>0){
            	cout<<"***"<<vertices[i].adj[j].v->name;
        	}
        }
        cout<<endl;
    } 

}



void Graph::shortestPath(string root, string goal){
	vector<string> Q;
	vector<string> children;
	string path = "";
	Q.push(root);
	while(!Q.empty())
	{
		vector<string< t = Q.front();
		path += t.getValue();
		Q.pop();
		if(t == goal){
			return path;
		}
		children = t.getChildren();
		for (int i = 0; i < children.size(); ++i){
			Q.push(children[i]);
		}
	}
	return path;
}

int main(int argc, char* argv[]){
	Graph g;
	ifstream myfile;
	myfile.open(argv[1]);
	string line;
	vector<string> cityname_vector;

	// Read Just the First Line
	getline(myfile, line);
	stringstream sp(line);
	string ignore;
	getline(sp, ignore, ','); //Skipped the first element in the line (first word)
	string cname;
	while(getline(sp, cname, ',')){
		//cout<< "Adding Vertex "<<cname<<endl;
		cityname_vector.push_back(cname); //stores in vector
		g.addVertex(cname);
	}

	//Read other lines WONT INCLUDE FIRST BECASUE OF ALREADY DID GETLINE ONCE
	while(getline(myfile,line)){
		stringstream ss(line);
		string src;
		getline(ss, src, ',');
		string weight;
		int ii=0; //counter
		while(getline(ss, weight, ',')){
			string dst= cityname_vector[ii];
			int w=stoi(weight);
			if(w>0){
				//cout<<"Adding edge"<<endl;
				g.addEdge(src, dst, w);
			}
			ii++;
		}
	}

	while(1==1){
		cout<<"======Main Menu======"<<endl;
		cout<<"1. Print vertices"<<endl;
		cout<<"2. Vertex adjacent"<<endl;
		cout<<"3. Quit"<<endl;
		string option;
		cin>>option;
		if(option=="1"){
			g.displayEdges();
			option="";
		}
		else if(option=="2"){
			option="";
			string city1;
			string city2;
			cout<<"Enter first city:"<<endl;
			cin.ignore();
			getline(cin,city1);
			cout<<endl<<"Enter second city:"<<endl;
			//cin.ignore();
			getline(cin,city2);
			g.isAdjacent(city1, city2);
		}
		else if(option=="3"){
			cout<<"Goodbye!"<<endl;
			option="";
			break;
		}
	}
	myfile.close();
	return 0;
}

