#ifndef SharedQueue_h
#define SharedQueue_h

#include <mutex>

template <typename T>
class SharedQueue {
public:
  SharedQueue();
  ~SharedQueue();
  
    /*
     These declarations mean that we do NOT get the automatically
     defined copy/copy-assign functions.  If you try to call one
     by copying the queue, you'll get a compiler error.
     
     This is a common technique for things that are uncopyable (like std::thread and std::mutex, for example).
     
     We really DO want a destructor, so cheating at the
     rule of 3 here makes sense here.
     */
    SharedQueue(const SharedQueue<T>&) = delete;
    SharedQueue<T>& operator=(const SharedQueue<T>&) = delete;

    
  //Return true if the queue is empty
  bool IsEmpty() const;
  
  //Enqueue the next item at the tail of the queue.
  void Add(T value);
  
  //Dequeue the next queue element and store it in "item" variable.  The function returns false if the queue is empty and no item can be retrieved.
  bool Remove(T &item);
  void Print();
private:
  struct QueueItem
    {
    T item;
    QueueItem *next;
  };
    QueueItem* head;
    QueueItem* tail;
    std::mutex lock;
  //Fill in the The private data members.
};

//Fill in the function definitions

template <typename T>
SharedQueue<T>::SharedQueue()
{
    head = NULL;
    tail = NULL;
}

template <typename T>
SharedQueue<T>::~SharedQueue()
{
    while (head != NULL)
    {
        QueueItem* temp = head->next;
        head = NULL;
        head = temp;
        
    }
    tail = NULL;
    head = NULL;
}

template <typename T>
bool SharedQueue<T>::IsEmpty() const
{
    if (head == NULL && tail == NULL)
    {
        return true;
    }
    return false;
}

template <typename T>
void SharedQueue<T>::Add(T value)
{
    lock.lock();
    QueueItem* newItem = new QueueItem();
    newItem->item = value;
    if (IsEmpty())
    {
        head = newItem;
        
        newItem->next = NULL;
        tail = newItem;
    }
    else
    {
        tail->next = newItem;
        newItem->next = NULL;
    
        tail = newItem;
    }
    lock.unlock();
}

template <typename T>
bool SharedQueue<T>::Remove(T &item)
{
    lock.lock();
    int i = 0;
    if (!IsEmpty())
    {
        item = head->item;
        QueueItem* temp = head->next;
        
        if (head == tail)
        {
            tail = NULL;
        }
        delete head;
        head = temp;
        i++;
    }
    lock.unlock();
    if (i == 1)
    {
        return true;
    }
    return false;
}

template <typename T>
void SharedQueue<T>::Print()
{
    lock.lock();
    QueueItem* temp = head;
    while (temp != NULL)
    {
        std::cout << temp->item << ", \n";
        temp = temp->next;
    }
    lock.unlock();
}

#endif
