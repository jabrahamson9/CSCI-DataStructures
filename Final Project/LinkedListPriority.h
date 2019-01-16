#ifndef LL_H
#define LL_H
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct patient
{
  string name;
  int timeLabor; //priority time
  int t_rec; //time for treatment
  patient* next;
  patient* prev;
  patient(){}
  patient(string n, int priority, int time)
  {
    name=n;
    timeLabor=priority;
    t_rec=time;
    next=NULL;
    prev=NULL;
  }
};


class LL
{
  public:
    void addPatient(patient* lady); //Adds patient node by>>>
    void print();
    void destroyList();
    void destroyNode();
  private:
    patient* head = NULL;
};

#endif
