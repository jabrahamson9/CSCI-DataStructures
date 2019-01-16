#include "Graph.hpp"
#include <vector>
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}

void Graph::addEdge(std::string v1, std::string v2, int distance)
{
        for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = distance;
                    vertices[i].adj.push_back(av);
                    //another vertex for edge in other direction
                    /*adjVertex av2;
                    av2.v = &vertices[i];
                    av2.weight = distance;
                    vertices[j].adj.push_back(av2);*/
                }
            }
        }
    }
}
void Graph::addVertex(std::string name)
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name==name){
            found = true;
            cout<<vertices[i].name<<" already in the graph."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = name;
        v.districtID = -1;
        vertices.push_back(v);

    }
}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    for(int i = 0; i < vertices.size(); i++){
        cout << vertices[i].districtID << ":" << vertices[i].name << "-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            if(j==vertices[i].adj.size()-1){
                cout<<vertices[i].adj[j].v->name;
            }
            else{
                cout<<vertices[i].adj[j].v->name<<"***";
            }
            
        }
        cout<<endl;
    }

}

void Graph::assignDistricts()
{
    for(int i=0 ; i<vertices.size() ; i++){
        vertices[i].districtID = -1;
    }
    int counter = 1;
    for(int i=0 ; i<vertices.size() ; i++){
        if(vertices[i].districtID==-1){
            DFSLabel(vertices[i].name,counter);
            counter++;
        }
    }
}

void Graph::DFSLabel(string startingCity, int distID){
    for(int i=0 ; i<vertices.size() ; i++){
        vertices[i].visited = false;
    }
    vertex* start = findVertex(startingCity);
    queue<vertex*> Q;
    Q.push(start);
    while (!Q.empty()){
        vertex* temp = Q.front();
        Q.pop();
        temp->districtID = distID;
        for(int i=0; i < (int)temp->adj.size(); i++){
            if(temp->adj[i].v->visited == false){
                temp->adj[i].v->visited = true;
                Q.push(temp->adj[i].v);
            }
        }
    }
}

void Graph::shortestPath(string startingCity, string endingCity)
{
    for(int i=0 ; i<vertices.size() ; i++){
        vertices[i].visited = false;
        vertices[i].unweightedDistance = 0;
    }
    vertex* start = findVertex(startingCity);
    vertex* dest = findVertex(endingCity);
    vertex* node = new vertex;
    if(start==NULL || dest==NULL){
        cout << "One or more cities doesn't exist" << endl;
        return;   
    }
    if(start->districtID!=dest->districtID){
        cout << "No safe path between cities" << endl;
        return;
    }
    queue<vertex*> Q;
    start->visited = true;
    start->parent = NULL;
    Q.push(start);
    while(!Q.empty()){
        node = Q.front();
        Q.pop();
        for(int i=0 ; i<(int)node->adj.size() ; i++){
            if(!node->adj[i].v->visited){
                node->adj[i].v->parent = node;
                node->adj[i].v->unweightedDistance = node->unweightedDistance + 1;
                node->adj[i].v->visited = true;
                Q.push(node->adj[i].v);
            }
        }
    }
    for(int i=0 ; i<vertices.size() ; i++){
        if(!vertices[i].visited){
            vertices[i].unweightedDistance = INT_MAX;
        }
    }
    int counter = 0;
    vector<string> path;
    while(dest!=NULL){
        path.push_back(dest->name);
        dest = dest->parent;
        counter++;
    }
    cout << counter-1 << ", ";
    for(int i=counter-1 ; i>=0 ; i--){
        if(i>0){
            cout << path[i] << ", ";
        }
        else{
            cout << path[i] << endl;
        }
    }
    path.clear();
}

void Graph::shortestWeightedPath(string startingCity, string endingCity)
{
    bool districts = false;
    for(int i=0 ; i<vertices.size() ; i++){
        vertices[i].visited = false;
        vertices[i].weightedDistance = 0;
        if(vertices[i].districtID==-1){
            districts = true;
        }
    }
    if(districts){
        cout << "Please identify the districts before checking distances" << endl;
        return;
    }
    vertex* start = findVertex(startingCity);
    vertex* dest = findVertex(endingCity);
    vertex* node = new vertex;
    if(start==NULL || dest==NULL){
        cout << "One or more cities doesn't exist" << endl;
        return;   
    }
    if(start->districtID!=dest->districtID){
        cout << "No safe path between cities" << endl;
        return;
    }
    queue<vertex*> Q;
    start->visited = true;
    start->parent = NULL;
    start->weightedDistance = 0;
    Q.push(start);
    while(!Q.empty()){
        node = Q.front();
        Q.pop();
        for(int i=0 ; i<(int)node->adj.size() ; i++){
            if(!node->adj[i].v->visited){
                node->adj[i].v->parent = node;
                node->adj[i].v->weightedDistance = node->weightedDistance + node->adj[i].weight;
                node->adj[i].v->visited = true;
                Q.push(node->adj[i].v);
            }
            else if(node->weightedDistance + node->adj[i].weight < node->adj[i].v->weightedDistance){
                node->adj[i].v->weightedDistance = node->weightedDistance + node->adj[i].weight;
                node->adj[i].v->parent = node;
            }
        }
    }
    for(int i=0 ; i<vertices.size() ; i++){
        if(!vertices[i].visited){
            vertices[i].weightedDistance = INT_MAX;
        }
    }
    int counter = 0;
    vector<string> path;
    int totalDist = dest->weightedDistance;
    vertex* x = dest;
    while(x!=NULL){
        path.push_back(x->name);
        x = x->parent;
        counter++;
    }
    cout << totalDist << ", ";
    for(int i=counter-1 ; i>=0 ; i--){
        if(i>0){
            cout << path[i] << ", ";
        }
        else{
            cout << path[i] << endl;
        }
    }
    path.clear();
}

vertex* Graph::findVertex(string vert){
    vertex* r = new vertex;
    for(int i=0 ; i<vertices.size() ; i++){
        if(vertices[i].name==vert){
            r = &vertices[i];
        }
    }
    return r;
}