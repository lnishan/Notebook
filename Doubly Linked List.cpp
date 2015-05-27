#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

template <class T>
struct node
{
	T val;
	node *prev, *next;
	node(T _val): val(_val), prev(NULL), next(NULL) {}
	node(): prev(NULL), next(NULL) {}
};

template <class T>
struct list
{
	node<T> *first, *last;
	list(): first(NULL), last(NULL) {}
	
	void insert(const T &val)
	{
		if (first == NULL)
		{
			first = new node<T>(val);
			last = first;
		}
		else
		{
			last->next = new node<T>(val);
			last->next->prev = last;
			last = last->next;
		}
	}
	void insertFront(const T &val)
	{
		if (first == NULL)
			insert(val);
		else
		{
			first->prev = new node<T>(val);
			first->prev->next = first;
			first = first->prev;
		}
	}
	void insertAfter(const T &val, node<T> *nd)
	{
		if (nd == last)
			insert(val);
		else
		{
			node<T> *tmp = nd->next;
			nd->next = new node<T>(val);
			nd->next->prev = nd;
			nd = nd->next;
			nd->next = tmp;
			tmp->prev = nd;
		}
	}
	void move(node<T> *front, node<T> *rear, node<T> *pos) // assume front, rear != NULL
	{
		// split
		if (front == first)
		{
			first = rear->next;
			if (first) first->prev = NULL;
		}
		else
		{
			front->prev->next = rear->next;
			if (rear->next) rear->next->prev = front->prev;
		}
		// merge
		if (pos)
		{
			node<T> *nxt = pos->next;
			pos->next = front;
			front->prev = pos;
			rear->next = nxt;
			if (nxt) nxt->prev = rear;
		}
		else
		{
			node<T> *nxt = first;
			first = front;
			first->prev = NULL;
			rear->next = nxt;
			if (nxt) nxt->prev = rear;
		}
		if (pos == last) last = rear;
	}
};

int main()
{
	list<int> l;
	l.insert(4);
	l.insert(5);
	l.insert(2);
	l.insertAfter(7, l.first);
	l.insertFront(1);
	
	node<int> *it = l.first;
	while (it)
	{
		printf("%d\n", it->val);
		it = it->next;
	}
	puts("-");
	
	l.move(l.first, l.first->next, l.last->prev);
	it = l.first;
	while (it)
	{
		printf("%d\n", it->val);
		it = it->next;
	}
	return 0;
}
