
#ifndef TS_QUEUE_H
#define TS_QUEUE_H

#include <vector>
#include <mutex>
#include <deque> 
#include "message.h"

// REQUIRES C++17



template<class T>
class tsQueue
{

    std::deque<T> queue;
    std::mutex queue_mutex;


public:
    tsQueue();
    void push_front(T msg);
    void push_back(T msg);
    void clear();
    T pop_back();
    T pop_front();
    size_t size();

};

#endif



template<class T>
tsQueue<T>::tsQueue()
{

}

template<class T>
void tsQueue<T>::push_front(T msg)
{
    std::scoped_lock lock(queue_mutex);
    queue.push_front(msg);
}

template<class T>
void tsQueue<T>::push_back(T msg)
{
    std::scoped_lock lock(queue_mutex);
    queue.push_back(msg);
}

template<class T>
T tsQueue<T>::pop_front()
{
    std::scoped_lock lock(queue_mutex);
    T msg = queue.front();
    queue.pop_front();
    return msg;
}

template<class T>
T tsQueue<T>::pop_back()
{
    std::scoped_lock lock(queue_mutex);
    T msg = queue.back();
    queue.pop_back();
    return msg;
}

template<class T>
size_t tsQueue<T>::size()
{
    return queue.size();
}

template<class T>
void tsQueue<T>::clear()
{
    std::scoped_lock lock(queue_mutex);
    queue.clear();
}