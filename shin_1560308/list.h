#ifndef LIST_H
#define LIST_H

#include<iostream>
#include<assert.h>
// Linked List object that maintains both head and tail pointers
// and the size of the list.  Note that you have to keep the head,
// tail and size consistent with the intended state of the List 
// otherwise very bad things happen. 
template<typename Type>
class List {
public:

	List();
	~List();

	void	printItems() const;
	bool	isEmpty() const;
	
	void	addToFront(Type item);
	void	addToRear(Type item);
	void	addItem(int index, Type item);

	// Note that the user must first ensure the list is not empty
	// Prior to calling these functions.
	Type	getFront() const;
	Type	getRear() const;
	Type	getItem(int index) const;


	int		getSize() const;
	int		findItem(Type item) const;

	bool	deleteFront();
	bool	deleteRear();
	bool	deleteItem(int index);

private:
	// Forward declare the nodes for our List.
	// Will be implemented along with list's
	// member functions
	class Node; 

	// We'll have both head and tail points for 
	// Fast insertion/deletion from both ends.
	Node*	head;
	Node*	tail;

	// Keep track of size of list
	int		size;
};


// List Implementation
//
//  Since List is a template class, which is not an actual 
//  class yet, not until we actually instantiate the list, 
//  we need to keep the class implementation together with 
//  the definition.  There are ways to simulate having 
//  separate "implementation/definition" with templates, 
//  but they aren't necessary and can be confusing.
//

// Node definition
//		Already Implemented, nothing to do here but to use it.
template<typename Type>
class List<Type>::Node {
public:
	Node() :next(nullptr) {}
	Node(Type item, Node* next) : item(item), next(next) {}

	Type  item;
	Node* next;
};

// 1. List default constructor
//		Set head and tail pointer to point to nothing, size is zero
template<typename Type>
List<Type>::List(){

    head = nullptr;
    tail = nullptr;
    size = 0;
}

// 2. List destructor
//		Traverses the nodes and deletes them without causing memory leak
template<typename Type>
List<Type>::~List() {

    Node* tmp = head;
    while(tmp != nullptr){
        head = head->next;
        delete tmp;
        tmp = head;
    }

}

// 3. List printItems
//		Traverses list and prints items in list to console followed by newline.
//		Assumes << is overloaded for object Type.
//		Indicates the Front and Rear of list, for example:
//
//			Front (3,4) (2,4) (1,1) Rear
//
template<typename Type>
void List<Type>::printItems() const {

    std::cout << "Front ";
    Node* tmp = head;
    while (tmp != nullptr) {
        std::cout << tmp->item << " ";
        tmp = tmp->next;
    }
    std::cout << "Rear" << std::endl;
	
}

// 4. List isEmpty
//		returns true if there are no items in the list
//		otherwise returns false.
template<typename Type>
bool List<Type>::isEmpty() const {

    if(head==nullptr) return true;
    else return false;
    
    //Node* tmp = head;
    //while(tmp != nullptr){
    //    if(!tmp){tmp=tmp->next;}
    //    else return false;
    //}
    //return true;
}


// 5. List addToFront
//		Adds a new item to the front of the list
//		updates head, tail, and size accordingly.
//		
//		Two cases to consider: If the list is empty 
//		and if the list has items already it.
//
template<typename Type>
void List<Type>::addToFront(Type item) {

    if(head==nullptr){
        head = new Node;
        tail = head;
        head->item = item;
        head->next = nullptr;
        size ++;
        return;
    }
    
    Node* tmp = new Node;
    tmp->item = item;
    tmp->next = head;
    head = tmp;
    size++;
    
}

// 6. List addToRear
//		Adds a new item to the rear of the list
//		updates head, tail, and size accordingly.
//
//		Two cases to consider: If the list is empty 
//		and if the list has items already it.
//
template<typename Type>
void List<Type>::addToRear(Type item) {

    if(head == nullptr){addToFront(item); return;}
    Node* tmp = new Node;
    tmp->item = item;
    tmp->next = nullptr;
    tail->next = tmp;
    tail = tmp;
    size++;
	
}

// 7. List addItem
//		Adds a new item at the index indicated
//		updates head, tail, and size accordingly.
//
//		If the index is less than or equal to zero 
//			add to the front.
//		If the index is greater than or equal to
//			the size of the list, add to the rear.
//		All other cases, add the item to the appropriate
//			location
//
template<typename Type>
void List<Type>::addItem(int index, Type item) {

    if (head == nullptr){addToFront(item); return;}
    if (index <= 0){addToFront(item); return;}
    if (index >= size){addToRear(item); return;}
    Node* tmp = new Node;
    Node* pnt = head;
    tmp->item = item;
    for(int i=0; i<(index-1); i++){
        pnt = pnt->next;
    }
    tmp->next = pnt->next;
    pnt->next = tmp;
    size++;
	
}

// 8. List getFront
//		returns the first item in the list.
//
template<typename Type>
Type List<Type>::getFront() const {
	// Force check that the head is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(head != nullptr);

    return head->item;

    //Type dumbyVariableSoCodeCompiles_DontActuallyUseThis;
	//return dumbyVariableSoCodeCompiles_DontActuallyUseThis;

}

// 9. List getRear
//		returns the last item in the list
//
template<typename Type>
Type List<Type>::getRear() const {

	// Force check that the tail is pointing to a Node
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(tail != nullptr);

	/* TODO: Note that your code should come after the assert */

    return tail->item;
	//Type dumbyVariableSoCodeCompiles_DontActuallyUseThis;
	//return dumbyVariableSoCodeCompiles_DontActuallyUseThis;
}

// 10. List getItem
//		returns the item at index
//
template<typename Type>
Type List<Type>::getItem(int index) const {

	// Force index to be correct before getting the Item
	// Typical solution for deployement code is to throw
	// exceptions, but since we haven't covered that yet
	// we'll make due with assert, which is used for testing
	assert(index >= 0 && index < size);

	/* TODO: Note that your code should come after the assert */

    Node* tmp = head;
    for (int i=0; i<index; i++){
        tmp = tmp->next;
    }
    
    return tmp->item;
    
	//Type dumbyVariableSoCodeCompiles_DontActuallyUseThis;
	//return dumbyVariableSoCodeCompiles_DontActuallyUseThis;
}

// 11. List getSize
//		return the size of the list
template<typename Type>
int List<Type>::getSize() const {

	/* TODO: Note the return value here is so that the program compiles */
	return size;

}

// 12. List findItem
//		Traverses the list to see if the item is in the list
//		if it is return the index of that item, otherwise
//		return -1. Assumes the == operator is overloaded for
//		object Type.
template<typename Type>
int List<Type>::findItem(Type item) const {

	/* TODO: Note the return value here is so that the program compiles */
    
    Node* tmp = head;
    for(int i=0; i<size; i++){
        if (tmp->item == item) return i;
        tmp = tmp->next; 
    }
	return -1;
}

// 13. List deleteFront
//		Removes the first item in the list returns true
//		if the item was deleted, false otherwise. Updates 
//		head, tail, and size accordingly.
//
//		Must consider at least two cases where the list: is empty, 
//		has one or more items.
//		
template<typename Type>
bool List<Type>::deleteFront() {

    if(getSize()==0){head=nullptr;tail=nullptr; return false;}
    if(head==nullptr){return false;}
    else if(head->next == nullptr){delete head; head=nullptr; size--; return true;}
    else if(head->next != nullptr){
        Node* tmp = head;
        head = head->next;
        delete tmp;
        size--;
        return true;
    }
	/* TODO: Note the return value here is so that the program compiles */
	else return false;
}
// 14. List deleteRear
//		Removes the last item in the list returns true
//		if the item was deleted, false otherwise. Updates 
//		head, tail, and size accordingly.
//
//		Must consider at least three cases where the list: is empty, 
//		has one item, has two or more items.
//	
template<typename Type>
bool List<Type>::deleteRear() {
    
    if(getSize()==0){head=nullptr;tail=nullptr; return false;}
    if(head==nullptr){return false;}
    if(head->next == nullptr){deleteFront(); return true;}
    else if(head->next != nullptr){
        Node* tmp = tail;
        Node* pnt = head;
        while((pnt->next != nullptr)&&(pnt->next->next != nullptr)){//////////////////
            pnt = pnt->next;
        }
        tail = pnt;
        tail->next = nullptr;
        delete tmp;
        size --;
        return true;
    }
	/* TODO: Note the return value here is so that the program compiles */
	else return false;
}

// 15. List deleteItem
//		Removes the item at the index returns true
//		if the item was deleted, false otherwise. Updates 
//		head, tail, and size accordingly. If the index is
//		out of bounds return false.
//
template<typename Type>
bool List<Type>::deleteItem(int index) {

    if(getSize()==0){head=nullptr;tail=nullptr; return false;}
    if (index==0){deleteFront(); return true;}
    else if (index==(size-1)){deleteRear(); return true;}
    else if (index>0 && index<(size-1)){
        Node* tmp=head;
        Node* pnt;
        for(int i=0; i<index-1; i++){
            tmp = tmp->next;
        }
        pnt = tmp->next;
        tmp->next = pnt->next;
        delete pnt;
        size --;
        return true;
    }
	/* TODO: Note the return value here is so that the program compiles */
	else return false;

}

#endif//LIST_H
