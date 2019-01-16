#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>
#include "LinkedListPriority.cpp"
#include "LinkedListPriority.h"
#include "heap.cpp"

using namespace std;
using namespace std::chrono;



struct compare //how to determine priority
{
  bool operator()(const patient* a, patient* b)
  {
    if(a->timeLabor == b->timeLabor)
      return a->t_rec > b->t_rec;
    else
      return a->timeLabor > b->timeLabor;

  }
};

priority_queue<patient*, vector<patient*>, compare> pq; //creates STL priorityy queue
void queueSTL(string file_name);
void STLdequeue();
void STLdequeueOnce();



////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char* argv[]){
  LL test;
  MinHeap heap;
  string tmp[4]; //used to parse the string of the .csv file

  while(2==2){
    cout<<"**************************************\n";
    cout<<"*  1. Build LL priority queue        *\n";
    cout<<"*  2. Build Heap priority queue      *\n";
    cout<<"*  3. Build STL priority queue       *\n";
    cout<<"*  4. Dequeue LL                     *\n";
    cout<<"*  5. Dequeue Heap                   *\n";
    cout<<"*  6. Dequeue STL Queue              *\n";
    cout<<"*  7. Dequeue all LL                 *\n";
    cout<<"*  8. Dequeue all Heap               *\n";
    cout<<"*  9. Dequeue all STL Queue          *\n";
    cout<<"*  0. Quit                           *\n";
    cout<<"**************************************\n";

    char choice;
    cin>>choice;





    if(choice=='1'){
      ifstream file(argv[1]); //command line argument
      vector<string> name;
      vector<int> deliverTime; //these vectors are used for storing the values parsed in the file
      vector<int> tieBreaker;
      string tmp[4];
      if(file.is_open()){
        while(!file.eof()){
          string line = "";
          getline(file, line);
          istringstream ss(line);//this is used to split the message into its individual words
          string token;
          int iter=0;
          while(getline(ss, token, ',')){ //parses by the comma which seems to be default for seperation of .csv??????????
            tmp[iter]=token;
            iter++;
          }
          if(tmp[1]!="Priority"){
            name.push_back(tmp[0]); //adding to the vector
            int deliverTimeInt = stoi(tmp[1]);
            int tieBreakerInt = stoi(tmp[2]);
            patient* girl = new patient(tmp[0],deliverTimeInt,tieBreakerInt); //creating "patient" nodes
            test.addPatient(girl); //creating the queue;
          }
        }
        cout<<"Linked List Priority Queue Built"<<endl;
      }



      else{
        cout<<"File Failed To Open"<<endl;
      }


    }
    else if(choice=='2'){ 
      ifstream file(argv[1]);
      if(file.is_open()){
        for(int i=0; i<500; i++){
        while(!file.eof()){
          string line = "";
          getline(file, line);
          istringstream ss(line);//this is used to split the message into its individual words
          string token;
          int iter=0;
          while(getline(ss, token, ',')){
            tmp[iter]=token;
            iter++;
          }
          if(tmp[1]!="Priority"){
            string name = tmp[0];
            int deliverTimeInt = stoi(tmp[1]);
            int tieBreakerInt = stoi(tmp[2]);
            patient girl;
            girl.name=name; //didnt use nodes this time just instances of struct much easier
            girl.timeLabor=deliverTimeInt;
            girl.t_rec=tieBreakerInt;
            heap.push(girl);  //creates the heap/ queue
          }
        }
      }
    }
      cout<<"Heap Priority Queue Built"<<endl;
    }
    else if(choice=='3'){
      queueSTL(argv[1]);
      cout<<"STL Priority Queue Built"<<endl;
    }
    else if(choice=='4'){
      test.destroyNode();
    }
    else if(choice=='5'){
      heap.pop();
    }
    else if(choice=='6'){
      STLdequeueOnce();
    }
    else if(choice=='7'){
      test.print();
      test.destroyList();
    }
    else if(choice=='8'){
      heap.popAll();
    }
    else if(choice=='9'){
      STLdequeue();
    }
    else if(choice=='0'){
      break;
    }


}
  return 0;
}
///////////////////////////////////////////////////////////////////




void queueSTL(string file_name){//queueSTL implementation 
  ifstream file(file_name);
  if(file.is_open())
  {
    string line="";
    getline(file, line); // to skip first line BETTER THAN THE FIRST TIME I DID IT WHEN I SAID THE FIRST LINE SHOULD NOT EQUAL PRIORITY
    while(!file.eof())
    {
      line = "";
      getline(file, line);
      istringstream ss(line);//split the message into elements
      string lineseg="";
      int i=0;
      string name;
      int timeLabor, t_rec;
      while(getline(ss, lineseg, ','))//splits at ,
      {
        if(i==0)
          name=lineseg;
        else if(i==1)
          timeLabor=stoi(lineseg);
        else if(i==2)
          t_rec=stoi(lineseg);
        i++;
      }
      patient* temp = new patient(name, timeLabor, t_rec);
      pq.push(temp); //adds to queue
    }
}
  else{
    cout<<"File failed ot Open"<<endl;
  }
file.close();
}
void STLdequeue(){
  cout<<"Rank\tPatient\tTTL\tTFT"<<endl;
  int count=1;
    while(!pq.empty())
    {
      cout<<count<<": "<<pq.top()->name<<"  "<<pq.top()->timeLabor<<"   "<<pq.top()->t_rec<<endl;
      pq.pop();
      count++;
    }
    
  }
void STLdequeueOnce(){
      cout<<"Dequeue  "<<pq.top()->name<<"   "<<pq.top()->timeLabor<<"   "<<pq.top()->t_rec<<endl;
      pq.pop();
}