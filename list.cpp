// file: list.cpp
// author: Alex Varga
// version: 1.1
// date: 12th november 2020
#include "list.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

//Constructor - intializes head Node
FlowList::FlowList() : headM(0){}

//Copy ctor
FlowList::FlowList(const FlowList& source)
{
    copy(source);
}

//Destructor
FlowList::~FlowList()
{
    destroy();
}

//Function to print entire Linked List
void FlowList::print() const
{
    cout << '[';
    if (headM != 0) {
        cout << ' ' << headM->item.year << ' ' << headM->item.flow;
        for (const Node *p = headM->next; p != 0; p = p->next)
            cout << ", " << p->item.year << p->item.flow;
    }
    cout << " ]\n";
} 

//Function to insert new node into list - in order of flow data
void FlowList::insert(int y, double f)
{
	bool check = false;
    Node *new_node = new Node;
    new_node->item.year = y;
	new_node->item.flow = f;
	check = this->check(y); // checks for duplicate

	if(!check)
	{
		if ((headM == 0 || y <= headM->item.year)&& new_node->item.year !=0) {
        new_node->next = headM;
        headM = new_node;
		}
		else {
			Node *before = headM;      // will point to node in front of new node
			Node *after = headM->next; // will be 0 or point to node after new node
			while(after != 0 && y > after->item.year) {
				before = after;
				after = after->next;
			}
			new_node->next = after;
			before->next = new_node;
		}
	}
	else cout << "Error: Duplicate Found\n";
}

//Function to remove node from list based on year of flow
void FlowList::remove(int year)
{
	bool check = false;
	check = this->check(year);
    // if list is empty, do nothing
    if (headM == 0 || year < headM->item.year)
        return;
    
    Node *doomed_node = 0;
    if(check)
	{
		if (year == headM->item.year) {
        doomed_node = headM;
        headM = headM->next;
		delete(doomed_node); // if found right away deletes it
    }
    else {
        Node *before = headM;
        Node *maybe_doomed = headM->next;
        while(maybe_doomed != 0 && year > maybe_doomed->item.year) {
            before = maybe_doomed; // loops through nodes to find the one that we want to remove
            maybe_doomed = maybe_doomed->next;
			if(year == maybe_doomed -> item.year){ // if it finds the node with item == itemA
				before -> next = maybe_doomed -> next; // moves the next pointer from before to the one after the maybe_doomed node that it is pointing to
				delete(maybe_doomed); // deleted the node
				return;
			}
        }
      }
	}
	else cout << "Error: No such Data.\n";	
}

//Function to return front of Linked List
Node* FlowList::front()const
{
	return headM;
}

//Function to check if year exists in List
int FlowList::check(int y)
{
	Node *p = headM;
	while(p != NULL)
	{
		if(p->item.year == y)
			return 1;
		p = p->next;
	}
	return 0;
}

//Function to destroy node from Linked List
void FlowList::destroy()
{
	Node* nextnode = headM; // sets nextnode to point to headM
	while(headM != NULL) // checks that headM isnt pointing to NULL
	{
		nextnode = headM -> next; // changes pointer nextnode to the node headM points to so it can be deleted
		delete(headM); // delete headM
		headM = nextnode; //reassign headM pointer to the node after the deleted one
	}
	
}

FlowList& FlowList::operator =(const FlowList& rhs)
{
    if (this != &rhs) {
        destroy();
        copy(rhs);
    }
    return *this;
}

void FlowList::copy(const FlowList& source)
{
    if(source.headM != NULL)
	{
		this -> headM = new Node; // Creates new node
		this -> headM->item = source.headM->item; //assigns sources item data to new node item
		this -> headM->next = NULL; // points next pointer to null
		Node* Nextsource = source.headM->next; //next source points to empty node
		Node* thisnext = this -> headM;// points to where next node will be input
		while (Nextsource != NULL)
		{
			Node* newNode = new Node; // create new node
			newNode -> item = Nextsource -> item;//copy data over
			newNode -> next = NULL;//null Pointer
			thisnext -> next = newNode; //links old node to new
			thisnext = newNode; //points to new node now
			
			Nextsource = Nextsource -> next; // moves the pointer keeping track of placement of source up 
		}
		
	}
}
 

