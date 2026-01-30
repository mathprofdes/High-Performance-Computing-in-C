#ifndef QUEUE_H_
#define QUEUE_H_

#include <deque>
#include <omp.h>

using namespace std;

template<class T>
class Queue {
private:
	deque<T> messagequeue;
	omp_lock_t lock;
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
	omp_init_lock(&lock);
}

template<class T>
Queue<T>::~Queue() {
	omp_destroy_lock(&lock);
}

template<class T>
void Queue<T>::Enqueue(T item) {
	omp_set_lock(&lock);
	messagequeue.push_back(item);
	omp_unset_lock(&lock);
}

template<class T>
T Queue<T>::Dequeue() {
	omp_set_lock(&lock);
	T item = messagequeue.front();
	messagequeue.pop_front();
	omp_unset_lock(&lock);
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
