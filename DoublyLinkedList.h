#include <iostream>
using namespace std;
template<typename T>
class DoublyLinkedList
{
private:
	struct Node
	{
		T data;
		Node* next;
		Node* prev;
		Node() : data(T()), next(nullptr), prev(nullptr) {}
		Node(T value) : data(value), next(nullptr), prev(nullptr) {}
		Node(T value, Node* n) : data(value), next(n), prev(nullptr) {}
		Node(T value, Node* n, Node* p) : data(value), next(n), prev(p) {}
        };
	Node* head;
	Node* tail;
	void remove(Node* delNode);
public:
	DoublyLinkedList() : head(nullptr), tail(nullptr) {}
	DoublyLinkedList(Node* head, Node* tail): head(head), tail(tail) {}
	~DoublyLinkedList();
	DoublyLinkedList(DoublyLinkedList const& copy);
	DoublyLinkedList& operator=(DoublyLinkedList const& copy);
	void insert(int index,T val);
	void insertFront(T val);
	void insertBack(T val);
	void deleteVal(T val);
	void print();
};

template<class T>
void DoublyLinkedList<T>::remove(Node* delNode)
{
	if (delNode == nullptr)
		return;
	if (head == delNode)
		head = delNode->next;
	if (delNode->next != nullptr)
		delNode->next->prev = delNode->prev;
	if (delNode->prev != nullptr)
		delNode->prev->next = delNode->next;

	free(delNode);
}

template<class T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	Node* tmp = head;
	while (tmp != nullptr)
	{
		Node* next = tmp->next;
		tmp->prev = nullptr;
		tmp->next = nullptr;
		tmp = next;
	}
	head = nullptr;
	tail = nullptr;
	tmp = nullptr;
}

template<typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList const& copy)
{
	Node* current = copy.head;
	if (copy.head == nullptr)
	{
		head = nullptr;
		tail = nullptr;
	}
	else
	{	
		head = copy.head;
		tail = copy.tail;
		Node* current_my;
		while(current!=nullptr)
		{
			current_my= new Node(current->data,current->next,current->prev);
			current = current->next;
			current_my = current_my->next;
		} 
	}
}

template<typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(DoublyLinkedList const& copy)
{
	if (copy.head == nullptr)
	{
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		head = copy.head;
		tail = copy.tail;
		Node* current = copy.head;
		Node* current_my;
		while (current != nullptr);
		{
			current_my = new Node(current->data, current->next, current->prev);
			current = current->next;
			current_my = current_my->next;
		}
	}
}

template<typename T>
void DoublyLinkedList<T>::insert(int index, T val)
{
	Node* tmp;
	int i = 0;
	if (head == nullptr)
		return;
	else
	{
		tmp = head;
		if (index == 0)
			insertFront(val);
		while (tmp != nullptr && i < index)
		{
			tmp = tmp->next;
			i++;
		}
		if (tmp ==nullptr)
			insertBack(val);
		else
		{
			if (tmp != nullptr)
			{
				
				Node* newNode=new Node(val,tmp,tmp->prev);
				tmp ->prev->next= newNode;
				tmp->prev = newNode;
			}
		}
		
	}
}

template<typename T>
void DoublyLinkedList<T>::insertFront(T val)
{
	Node* tmp = head;
	if (head == nullptr)
	{
		Node* newNode = new Node(val);
		head = newNode;
		tail = newNode;
	}
	else
	{
		Node* newNode = new Node(val, head, nullptr);
		head->prev=newNode;
		head = head->prev;
	}
}

template<typename T>
void DoublyLinkedList<T>::insertBack(T val)
{
	if (tail== nullptr)
	{
		Node* newNode = new Node(val);
		head = newNode;
		tail = newNode;
	}
	else
	{
		Node* newNode = new Node(val, nullptr, tail);
		tail->next = newNode;
		tail = tail->next;
	}
}

template<typename T>
void DoublyLinkedList<T>::deleteVal(T val)
{
	Node* tmp=head;
	if (head == nullptr)
		return;
        if (head->data == val)
	{
		head = head->next;
		head->prev = nullptr;
		remove(tmp);
	}
	else
	{
		Node* next;
		while (tmp != nullptr)
		{
			if(tmp->data == val)
			{
				next = tmp->next;
				if(tmp->next!=nullptr)
					next->prev=tmp->prev;
				remove(tmp);
				tmp=next;
			}
			else
				tmp=tmp->next;
		}
	}
}

template<typename T>
void DoublyLinkedList<T>::print()
{
	Node* tmp = head;
	while (tmp != nullptr)
	{
		cout << "Data: " << tmp->data << "  prev:";
		if (tmp->prev == nullptr)
			cout << "nullptr ";
		else
			cout << tmp->prev->data;

		cout << " next: ";

		if (tmp->next == nullptr)
			cout << "nullptr ";
		else
			cout << tmp->next->data << endl;
		tmp = tmp->next;
	}
	cout << endl;
}
