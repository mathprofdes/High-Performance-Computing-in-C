#ifndef QUEUE_H_
#define QUEUE_H_

#include <deque>

using namespace std;

template<class T>
class Queue {
private:
	deque<T> messagequeue;
public:
	Queue();
	virtual ~Queue();

	void Enqueue(T item);
	T Dequeue();
	int Size();
	bool Empty();
};

template<class T>
Queue<T>::Queue() {
}

template<class T>
Queue<T>::~Queue() {
}

template<class T>
void Queue<T>::Enqueue(T item) {
	messagequeue.push_back(item);
}

template<class T>
T Queue<T>::Dequeue() {
	T item = messagequeue.front();
	messagequeue.pop_front();
	return item;
}

template<class T>
int Queue<T>::Size() {
	return messagequeue.size();
}

template<class T>
bool Queue<T>::Empty() {
	return messagequeue.empty();
}

#endif /* QUEUE_H_ */
