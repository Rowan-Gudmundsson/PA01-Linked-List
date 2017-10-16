#include "ListLinked.h"

template < typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr):dataItem(nodeData), next(nextPtr) {}

template < typename DataType>
List<DataType>::List(int) {

	head = NULL;

	cursor = NULL;
}

template < typename DataType>
List<DataType>::List(const List<DataType>& other) {


	this = other;
}

template < typename DataType>
List<DataType>& List<DataType>::operator = (const List& other) {

	head = other->head;

	if (isEmpty()) cursor = NULL;
	else cursor = other->cursor;

	return this;
}

template < typename DataType>
List<DataType>::~List() {

	if(!isEmpty()) clear();
}

template < typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error) {

	if(isFull()) throw logic_error("insert() full list");

	ListNode* newNode = new ListNode(newDataItem, NULL);

	if (isEmpty()) {

		head = newNode;
	}
	else {

		newNode->next = cursor->next;
		cursor->next = newNode;
	}

	cursor = newNode;
}

template < typename DataType>
void List<DataType>::remove() throw (logic_error) {

	if(isEmpty()) throw logic_error("remove() empty list");

	ListNode* currentNode;
	ListNode* nextNode;

	if(cursor == head) {

		head = head->next;
		delete[] cursor;
		cursor = head;
	}
	else if(cursor->next == NULL) {

		currentNode = cursor;
		gotoPrior();
		delete[] currentNode;
		cursor->next = NULL;
		gotoBeginning();
	}
	else {

		currentNode = cursor;
		gotoNext();
		nextNode = cursor;
		gotoPrior();
		gotoPrior();
		cursor->next = nextNode;
		currentNode->next = NULL;
		delete[] currentNode;
		cursor = nextNode;
	}
}

template < typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error) {

	if(isEmpty()) throw logic_error("replace() empty list");

	cursor->dataItem = newDataItem;
}

template < typename DataType>
void List<DataType>::clear() {

	gotoEnd();

	ListNode* currentNode;

	while (cursor != head) {

		currentNode = cursor;
                gotoPrior();
                delete[] currentNode;
                cursor->next = NULL;

	}
	delete[] cursor;
	head = NULL;
	cursor = NULL;
}

template < typename DataType>
bool List<DataType>::isEmpty() const {

	if (head == NULL) return true;
	else return false;
}

template < typename DataType>
bool List<DataType>::isFull() const {

	return false;
}

template < typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error) {

	if(isEmpty()) throw logic_error("gotoBeginning() empty list");

	cursor = head;
}

template < typename DataType>
void List<DataType>::gotoEnd() throw (logic_error) {

	if(isEmpty()) throw logic_error("gotoEnd() empty list");

	while (cursor->next != NULL) {

		cursor = cursor->next;
	}
}

template < typename DataType>
bool List<DataType>::gotoNext() throw (logic_error) {

	if(isEmpty()) throw logic_error("gotoNext() empty list");

	if (cursor->next != NULL) {

		cursor = cursor->next;
		return true;
	}
	else return false;

}

template < typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error) {

	if(isEmpty()) throw logic_error("gotoPrior() empty list");
	if (head != NULL) {

		ListNode* currentNode;

		currentNode = cursor;
		cursor = head;

		while (cursor->next != currentNode) {

			cursor = cursor->next;
		}

		return true;
	}
	else return false;
}

template < typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error) {

	if(isEmpty()) throw logic_error("getCursor() empty list");

	return cursor->dataItem;
}

template <typename DataType>
void List<DataType>::moveToBeginning() throw (logic_error) {

    if(isEmpty()) throw (logic_error("moveToBeginning() empty list"));

    ListNode* newNode = new ListNode(cursor->dataItem, head);

    remove();

    head = newNode;
    cursor = head;
}

template <typename DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error) {

    if(isFull()) throw (logic_error("insertBefore() full list"));

    if(cursor != head) {

        gotoPrior();
        insert(newDataItem);
        gotoPrior();
    }
    else {

        ListNode* newNode = new ListNode(newDataItem, head);
        head = newNode;
        cursor = head;
    }
}

template <typename DataType>
void List<DataType>::showStructure() const

// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

{
    if ( isEmpty() )
    {
       cout << "Empty list" << endl;
    }
    else
    {
	for (ListNode* temp = head; temp != 0; temp = temp->next) {
	    if (temp == cursor) {
		cout << "[";
	    }

	    // Assumes that dataItem can be printed via << because
	    // is is either primitive or operator<< is overloaded.
	    cout << temp->dataItem;

	    if (temp == cursor) {
		cout << "]";
	    }
	    cout << " ";
	}
	cout << endl;
    }
}
