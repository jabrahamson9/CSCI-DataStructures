#include <iostream>
#include <fstream>
#include <sstream>
#include "MovieTree.h"


using namespace std;


MovieNodeBST* MovieTree:: createNode(char Zletter){
    MovieNodeBST* nn=new  MovieNodeBST(Zletter);
    return nn;
}


MovieTree::MovieTree(){

}

MovieTree::MovieTree(char Zletter){
	root=createNode(Zletter);
}
MovieTree::~MovieTree(){
}

void DeleteAll(MovieNodeBST * node){

}

 bool MovieTree::searchKeyHelper(MovieNodeBST* root, char Zletter){
    MovieNodeBST* p=root;
 	bool istrue=false;

    if(root==NULL)
        return false;
    if(root->letter==Zletter){
        return true;
    }
    while(!istrue && p!=NULL){
	 	if(p->letter == Zletter){
	 		istrue=true;
            break;
	 	}
	 	else if(p->letter < Zletter){
	 		p = p->rightChild;
	 	}
	 	else if(p->letter > Zletter){
	 		p = p->leftChild;
	 	}
	 }
	 if(istrue==true){
        return true;
     }
     else{
        return false;
     }
 }

bool MovieTree::searchKey(char Zletter){
    return searchKeyHelper(root, Zletter);
}

MovieNodeBST*  MovieTree::searchKeyHelperLetter(MovieNodeBST* root, char Zletter){
    MovieNodeBST* p=root;
 	bool istrue=false;

    if(root->letter==Zletter){
        return p;
    }
    while(!istrue && p!=NULL){
	 	if(p->letter == Zletter){
	 		istrue=true;
            break;
	 	}
	 	else if(p->letter < Zletter){
	 		p = p->rightChild;
	 	}
	 	else if(p->letter > Zletter){
	 		p = p->leftChild;
	 	}
	 }
	 if(istrue==true){
        return p;
     }
 }
/*
MovieNodeBST* MovieTree::searchKeyLetter(char Zletter){
    return searchKeyHelper(root, Zletter);
}*/


 MovieNodeBST* MovieTree::insertNodeHelper(MovieNodeBST* curNode, char Zletter){
 	if(curNode == NULL){
 		return createNode(Zletter);
 	}
 	else if(Zletter < curNode->letter){
 		curNode->leftChild=insertNodeHelper(curNode->leftChild, Zletter);
 	}
 	else if(Zletter > curNode->letter){
 		curNode->rightChild=insertNodeHelper(curNode->rightChild, Zletter);
 	}

    return curNode;
 }

MovieNodeLL* addCity( MovieNodeLL* head,  MovieNodeLL* prevNode,  int ranking, string title, int releaseYear, int quantity){
	if(head == NULL){
		MovieNodeLL* n1 = new MovieNodeLL(ranking, title,releaseYear, quantity);
		return n1;
	}
	if(prevNode == NULL){
		MovieNodeLL* n1 = new MovieNodeLL(ranking, title, releaseYear, quantity);
		return n1;
	}
	MovieNodeLL* temp=new MovieNodeLL(ranking, title, releaseYear, quantity);
	temp->next=prevNode->next;//outs it into the link
	prevNode->next=temp;

	return head;
}

void MovieTree::addMovieNode(int ranking, string title, int releaseYear, int quantity){
	char let = title[0];
	if(searchKey(let)==false){
		if(root == NULL) // if the BST is empty create the root
	        root = createNode(let);
	    else // insert the data in the tree rooted at root
	        insertNodeHelper(root, let);
	}

}


void MovieTree::printMovieInventory(MovieNodeBST * node){
	     if(node)
     {
            printMovieInventory( node->leftChild);
            cout << " "<< node->letter;
            printMovieInventory( node->rightChild);
     }
}

void MovieTree::printMovieInventory(){
	printMovieInventory(root);
}



int main(){
	MovieTree* test=new MovieTree('T');

	test->addMovieNode(5,"Captain",1999,12);
	test->addMovieNode(5,"Captain",1999,12);
	test->addMovieNode(5,"Zaptain",1999,12);
	test->addMovieNode(5,"Aaptain",1999,12);
	test->addMovieNode(5,"Zaptain",1999,12);
	

	test->printMovieInventory();

	return 0;
}



/*
	string filename="Assignment6Movies.txt";
	ifstream text(filename);
	if(text.is_open()){
		while(!text.eof()){
			string line="";
			getline(text, line);
			istringstream ss(line);//this is used to split the message into its individual words
			string token;
			int i=0;
			string temp[5];
			while(getline(ss, token, ',')){//split sp each word is sent seperate
				temp[i]=token;
				i++;
			}
			string word=temp[2];
			word="";
		}
	}
	*/