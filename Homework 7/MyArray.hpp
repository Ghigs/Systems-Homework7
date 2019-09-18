//
//  MyArray.hpp
//  Homework 6
//
//  Created by Jason Ghiglieri on 3/2/18.
//  Copyright © 2018 Jason Ghiglieri. All rights reserved.
//

#ifndef MyArray_hpp
#define MyArray_hpp

#include <stdio.h>

template <typename T>
class MyArray
{
public:
    MyArray(int size = 0);
    ~MyArray();
    MyArray<T> operator=(MyArray<T>& input);
    
    T get(int index);
    void set(int index, T item);
    int size();
    void resize(int newSize);
    void pushBack(T item);
    T back();
    void popBack();
    
    int getMaxCapacity();
    int getCurrentSize();
private:
    T* arr;
    int currentSize;
    int maxCapacity;
};


template <typename T>
MyArray<T>::MyArray(int size)
{
    if (size > 20)
    {
        arr = new T[size];
        maxCapacity = size;
    }
    else
    {
        arr = new T[20];
        maxCapacity = 20;
    }
    currentSize = size;
}

template <typename T>
MyArray<T>::~MyArray()
{
    delete [] arr;
    arr = NULL;
    currentSize = 0;
}

template <typename T>
MyArray<T> MyArray<T>::operator=(MyArray<T>& input)
{
    int arrayLoop;
    int otherSize;
    if (this->currentSize >= input.currentSize)
    {
        arrayLoop = this->currentSize;
        otherSize = input.currentSize;
    }
    else
    {
        arrayLoop = input.currentSize;
        otherSize = this->currentSize;
    }
    
    for (int i = 0; i < arrayLoop; i++)
    {
        if (i < otherSize)
        {
            this->set(i, input.get(i));
        }
        else
        {
            this->set(i, NULL);
        }
    }
    
    return *this;
}

template <typename T>
T MyArray<T>::get(int index)
{
    return arr[index];
}

template <typename T>
void MyArray<T>::set(int index, T item)
{
    arr[index] = item;
}

template <typename T>
int MyArray<T>::size()
{
    return currentSize;
}

template <typename T>
void MyArray<T>::resize(int newSize)
{
    T* newArr = new T[newSize];
    maxCapacity = newSize;
    
    for (int i = 0; i < newSize; i++)
    {
        if (i < currentSize)
        {
            newArr[i] = arr[i];
        }
    }
    
    if (newSize < currentSize)
    {
        currentSize = newSize;
    }
    
    arr = newArr;
}

template <typename T>
void MyArray<T>::pushBack(T item)
{
    if (currentSize == maxCapacity)
    {
        resize(maxCapacity*2);
    }
    
    set(currentSize, item);
    currentSize++;
}

template <typename T>
T MyArray<T>::back()
{
    return get(currentSize-1);
}

template <typename T>
void MyArray<T>::popBack()
{
    currentSize--;
    set(currentSize, NULL);
}

template <typename T>
int MyArray<T>::getMaxCapacity()
{
    return maxCapacity;
}

template <typename T>
int MyArray<T>::getCurrentSize()
{
    return currentSize;
}

#endif /* MyArray_hpp */
