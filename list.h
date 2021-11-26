// file: list.h
// author: Alex Varga
// version: 1.0
// date: 12th november 2020
#ifndef LIST_H
#define LIST_H

//Struct data structure for each node in FlowList Linked List
struct ListItem {
	int year;
	double flow;
};

//Node struct for input into FlowList
struct Node {
	ListItem item;
	Node *next;
};

//Class FlowList - represents a LinkedList 
class FlowList {
	public:
		FlowList();
		FlowList(const FlowList& source);
		FlowList& operator =(const FlowList& rhs);
		~FlowList();
		void insert(int y, double f);
		void remove(int y);
		void print() const;
		Node* front()const;
	
	private:
		Node* headM;
		int check(int y);
		void destroy(); 
		void copy(const FlowList& source); 
};
#endif