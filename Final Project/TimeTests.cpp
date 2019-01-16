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




   
struct compare //tells how to compare patients
{
  bool operator()(const patient* a, patient* b)
  {
    if(a->timeLabor == b->timeLabor)
      return a->t_rec > b->t_rec;
    else
      return a->timeLabor > b->timeLabor;

  }
};

priority_queue<patient*, vector<patient*>, compare> pq;

void STL(string file_name)//STL implementation 
{
  //ifstream file(argv[1])
  ifstream file(file_name);
  if(file.is_open())
  {
    string line="";
    getline(file, line); // to skip first line
    while(!file.eof())
    {
      //patient* temp;
      line = "";
      getline(file, line);
      istringstream ss(line);//this is used to split the message into its individual words
      string seg="";
      int i=0;
      string name;
      int t_labor, t_rec;
      while(getline(ss, seg, ','))//needs to be \r
      {
        if(i==0)
          name=seg;
        else if(i==1)
          t_labor=stoi(seg);
        else if(i==2)
          t_rec=stoi(seg);
        i++;
      }
      patient* temp = new patient(name, t_labor, t_rec);
      pq.push(temp);
    }
    int l=1;

  // else{
  //   cout<<"File failed to open."<<endl;
  // }
}
file.close();
}
void STLdequeue(){
  //cout<<"Rank\tPatient\tTTL\tTFT"<<endl;
  int count=1;
    while(!pq.empty())
    {
      //cout<<count<<"\t"<<pq.top()->name<<"\t"<<pq.top()->t_labor<<"\t"<<pq.top()->t_rec<<endl;
      pq.pop();
      count++;
    }
    
  } 



int main(){
	LL test;
	 for(int i=0; i<500; i++){
	 	ofstream LLoutData("STLdequeueData587.csv", std::ios_base::app);


	 	STL("patient587.csv");


	 	auto start = chrono::steady_clock::now();//////////////////////////////////////////////////
    	STLdequeue();
    	auto end = chrono::steady_clock::now();/////////////////////////////////////////////////////////////
    	LLoutData<<chrono::duration_cast<chrono::nanoseconds>(end - start).count()<<endl; //////////////////////////////
    	LLoutData.close();


      }
}