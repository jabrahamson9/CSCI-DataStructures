#include <iostream>
#include <fstream>
#include <sstream>
#include "LinkedListPriority.h"

using namespace std;

void LL::addPatient(patient* lady){
	if(head == NULL)//if the LL is empty puts the lady at the first spot
	{
		head = lady;
		return;
	}

	patient* current = head;
	while(current != NULL)
	{
		if(lady->timeLabor < current->timeLabor)//checks to see if ladys time to labor is less than the next
		{
			if(current == head)//inserts node before first lady at the HEAD
			{
				lady->next=current;
				current->prev=lady;
				head=lady;
				return;
			}
			else//inserts lady in middle of LL
			{
				lady->next=current;
				current->prev->next=lady;
				lady->prev=current->prev;
				current->prev=lady;
				return;
			}
		}
		else if(lady->timeLabor > current->timeLabor)//checks to see that lady's time to labor is  more
		{
			if(current->next == NULL)//puts lady at end of LL
			{
				current->next=lady;
				lady->prev=current;
				return;
			}
		}
//////////////////////////////////////////////////////////// NOW WE MUST DON IT ALL GAIN IN THE CASE THAT THEY HAVE EQUAL TIMES
		else if(lady->timeLabor == current->timeLabor) //analyze t_rec
		{
			if(lady->t_rec < current->t_rec)//checks to see if lady's treatment time is less
			{
				if(current == head)//inserts node before first lady at HEAD
				{
					lady->next=current;
					current->prev=lady;
					head=lady;
					return;
				}
				else//inserts lady befor in middle of LL
				{
					lady->next=current;
					current->prev->next=lady;
					lady->prev=current->prev;
					current->prev=lady;
					return;
				}
			}
			else if(lady->t_rec > current->t_rec)//checks to see that lady's treatment time is  more
			{
				if(current->next == NULL)//puts lady at end of list
				{
					current->next=lady;
					lady->prev=current;
					return;
				}
			}
		}
		current=current->next;//interates through LL
	}
}

void LL::print(){
	patient* current = head;
  int counter=1;
	while(current!=NULL){ //simple print function
		cout<<counter<<":  "<<current->name<<",   "<<current->timeLabor<<",   "<<current->t_rec<<endl;
		current=current->next;
    counter++;
	}
}


void LL::destroyNode(){
  cout<<head->name<<" will be Dequeued"<<endl;
  head=head->next;
  delete(head->prev); //dont know the difference between free and delete
}


void LL::destroyList(){
   struct patient* current = head;
   struct patient* next;
   while (current != NULL) { 
       next = current->next; //makes sure that you are deleting behind the current node
       free(current);
       current = next;
   }
   
   head = NULL;
   cout<<"List was successfully Dequeued"<<endl;
}