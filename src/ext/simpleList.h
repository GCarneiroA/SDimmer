
#ifndef SIMPLELIST_H
#define SIMPLELIST_H

template<class T>
struct SimpleListNode
{
    T                  data;
    SimpleListNode<T> *next = nullptr;
};

template<typename T>
class SimpleList
{
public:
    SimpleList();
    SimpleList(int(*compare)(T &a, T &b));
    virtual ~SimpleList();

    virtual void setCompare(int (* compare)(T& a, T& b));

    virtual int size();
    virtual bool isSorted();
    virtual bool isEmpty();

    virtual void add(int index, T obj);
    virtual void add(T obj);
    virtual void insert(T obj);

    virtual void replace(int index, T obj);
    virtual void swap(int x, int y);

    virtual void remove(int index);
    virtual void removeFirst();
    virtual void removeLast();

    virtual bool has(T obj);
    virtual int count(T obj);

    virtual T shift();
    virtual T pop();
    virtual T get(int index);
    virtual T getFirst();
    virtual T getLast();

    virtual void moveToEnd();

    virtual int search(T obj);
    virtual int searchNext(T obj);
    virtual int binSearch(T obj);

    virtual void sort();
    virtual void clear();

private:
    int (*compare)(T &a, T &b);
    int listSize;
    SimpleListNode<T> *listBegin;
    SimpleListNode<T> *listEnd;

    SimpleListNode<T> *lastNodeGot;
    int lastIndexGot;
    bool isCached;

    bool sorted;

    virtual SimpleListNode<T> *getNode(int index);
    virtual int binSearch(T obj, int lowerEnd, int upperEnd);
};

#endif
