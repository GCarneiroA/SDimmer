
#include "simpleList.h"

template<typename T>
SimpleList<T>::SimpleList()
    : compare(nullptr)
    , listSize(0)
    , listBegin(nullptr)
    , listEnd(nullptr)
    , lastNodeGot(nullptr)
    , lastIndexGot(-1)
    , isCached(false)
    , sorted(true)
{
}

template<typename T>
SimpleList<T>::SimpleList(int(*compare)(T &a, T &b))
    : compare(nullptr)
    , listSize(0)
    , listBegin(nullptr)
    , listEnd(nullptr)
    , lastNodeGot(nullptr)
    , lastIndexGot(-1)
    , isCached(false)
    , sorted(true)
{
    setCompare(compare);
}

template<typename T>
SimpleList<T>::~SimpleList() 
{
    clear();
}

template<typename T>
void SimpleList<T>::setCompare(int (* compare)(T& a, T& b)) 
{
    this->compare = compare;
    sort();
}

template<typename T>
int SimpleList<T>::size() 
{
    return listSize;
}

template<typename T>
bool SimpleList<T>::isSorted() 
{
    return sorted;
}

template<typename T>
bool SimpleList<T>::isEmpty() 
{
    return listSize == 0;
}

template<typename T>
void SimpleList<T>::add(int index, T obj) 
{
    if ((index < 0) || (index >= listSize)) {
        return;
    }

    SimpleListNode<T> *newNode = new SimpleListNode<T>();
    newNode->data = obj;

    if (index == 0) {
        listBegin = newNode;
    } else {
        SimpleListNode<T> *nodePrev = getNode(index -1);
        newNode->next = nodePrev->next;
        nodePrev->next = newNode;
    }

    listSize++;
    sorted = false;
}

template<typename T>
void SimpleList<T>::add(T obj) 
{
    SimpleListNode<T> *newNode = new SimpleListNode<T>();
    newNode->data = obj;

    if (!listBegin) {
        listBegin = newNode;
    }

    if (listEnd) {
        listEnd->next = newNode;
        listEnd = newNode;
    } else {
        listEnd = newNode;
    }
    listSize++;
    sorted = false;
}

template<typename T>
void SimpleList<T>::insert(T obj) 
{
    if (!compare) {
        add(obj);
        return;
    }

    if (!sorted) sort();

    // create new node
    SimpleListNode<T> *newNode = new SimpleListNode<T>();
    newNode->data = obj;

    if (listSize == 0) {
        // add at start (first node)
        listBegin = newNode;

        listEnd = newNode;
    } else {
        if (compare(obj, listEnd->data) >= 0) {
            // add at end
            listEnd->next = newNode;
            listEnd = newNode;
        } else if (compare(obj, listBegin->data) < 0) {
            // add at start
            newNode->next = listBegin;
            listBegin     = newNode;
        } else {
            // insertion sort
            SimpleListNode<T>* h = listBegin;
            SimpleListNode<T>* p = nullptr;
            bool found = false;

            // here a sequential search, because otherwise the previous node couldn't be accessed
            while (h && !found) {
                if (compare(obj, h->data) < 0) {
                    found = true;
                } else {
                    p = h;
                    h = h->next;
                }
            }
            newNode->next = h;

            if (p) p->next = newNode;
        }
    }

    listSize++;
}

template<typename T>
void SimpleList<T>::replace(int index, T obj) 
{
    if ((index >= 0) && (index < listSize)) {
        getNode(index)->data = obj;
    }
}

template<typename T>
void SimpleList<T>::swap(int x, int y) 
{
    // only continue when the index numbers are unequal and at least 0
    if ((x != y) && (x >= 0) && (y >= 0)) {
        if (x > y) { // the first index should be smaller than the second. If not, swap them!
            int h = x;
            x = y;
            y = h;
        }

        // When data is small, copy it
        if (sizeof(T) < 24) {
            SimpleListNode<T>* nodeA = getNode(x);
            SimpleListNode<T>* nodeB = getNode(y);
            T h                      = nodeA->data;
            nodeA->data = nodeB->data;
            nodeB->data = h;
        }

        // otherwise change the pointers
        else {
            // Example: a -> b -> c -> ... -> g -> h -> i
            //          we want to swap b with h
            SimpleListNode<T>* nodeA = getNode(x - 1);                      // x.prev
            SimpleListNode<T>* nodeB = getNode(x);                          // x
            SimpleListNode<T>* nodeC = getNode(x + 1);                      // x.next
            SimpleListNode<T>* nodeG = y - 1 == x ? nodeB : getNode(y - 1); // y.prev
            SimpleListNode<T>* nodeH = getNode(y);                          // y
            SimpleListNode<T>* nodeI = getNode(y + 1);                      // y.next

            // a -> h -> i      b -> c -> ... -> g -> h -> i
            if (nodeA) nodeA->next = nodeH;
            else listBegin = nodeH;

            // a -> h -> c -> ... -> g -> h -> i    b -> i
            if (nodeH != nodeC) // when nodes between b and h exist
                nodeH->next = nodeC;
            else nodeH->next = nodeB;

            // a -> h -> i      b -> i
            nodeB->next = nodeI;

            if (!nodeI) listEnd = nodeB;

            // a -> h -> c -> ... -> g -> b -> i
            if (nodeG != nodeB) // when more than 1 nodes between b and h exist
                nodeG->next = nodeB;
        }
    }
}

template<typename T>
void SimpleList<T>::remove(int index) 
{
    if ((index < 0) || (index >= listSize)) return;

    SimpleListNode<T>* nodePrev     = getNode(index - 1);
    SimpleListNode<T>* nodeToDelete = getNode(index);

    if (index == 0) {
        listBegin = nodeToDelete->next;
    } else {
        nodePrev->next = nodeToDelete->next;

        if (!nodePrev->next) listEnd = nodePrev;
    }

    delete nodeToDelete;

    isCached = false;

    listSize--;
}

template<typename T>
void SimpleList<T>::removeFirst() 
{
    remove(0);
}

template<typename T>
void SimpleList<T>::removeLast() 
{
    remove(listSize -1);
}

template<typename T>
bool SimpleList<T>::has(T obj) 
{
    return binSearch(obj, 0, listSize -1);
}

template<typename T>
int SimpleList<T>::count(T obj) 
{
    if (compare == nullptr) {
        return -1;
    }
    int c = 0;
    for (int i = 0; i < listSize; i++) {
        if (compare(obj, getNode(i)->data) == 0) {
            c++;
        }
    }
    return c;
}

template<typename T>
T SimpleList<T>::shift() 
{
    T data = getFirst();
    removeFirst();
    return data;
}

template<typename T>
T SimpleList<T>::pop() 
{
    T data = getLast();
    removeLast();
    return data;
}

template<typename T>
T SimpleList<T>::get(int index) 
{
    SimpleListNode<T> *h = getNode(index);
    if (h) {
        return h->data;
    }
    return T();
}

template<typename T>
T SimpleList<T>::getFirst() 
{
    return get(0);
}

template<typename T>
T SimpleList<T>::getLast() 
{
    return get(listSize -1);
}

template<typename T>
void SimpleList<T>::moveToEnd() 
{
    SimpleListNode<T> *h = listBegin;
    if (!h) {
        return;
    }
    listBegin = listBegin->next;
    listEnd->next = h;

    h->next = nullptr;
    listEnd = h;

    lastNodeGot = nullptr;
    lastIndexGot = -1;
    isCached = false;

    sorted = false;
}

template<typename T>
int SimpleList<T>::search(T obj) 
{
    if (compare == nullptr) {
        return -1;
    }
    int i = 0;
    SimpleListNode<T> *hNode = getNode(i);
    bool found = compare(obj, hNode->data) == 0;

    while (!found && i < listSize) {
        i++;
        hNode = getNode(i);
        found = compare(obj, hNode->data) == 0;
    }
    return found ? i : -1;
}

template<typename T>
int SimpleList<T>::searchNext(T obj) 
{
    if (compare == nullptr) {
        return -1;
    }
    int i = lastIndexGot;
    SimpleListNode<T> *hNode = lastNodeGot;
    bool found = compare(obj, hNode->data) == 0;

    while (!found && i < listSize) {
        i++;
        hNode = getNode(i);
        found = compare(obj, hNode->data) == 0;
    }

    return found ? i : -1;
}

template<typename T>
int SimpleList<T>::binSearch(T obj) 
{
    return binSearch(obj) >= 0;
}

template<typename T>
void SimpleList<T>::sort() 
{
    if (compare == nullptr) {
        return;
    }
    int indexH;
    int indexMin;

    SimpleListNode<T> *nodeMin;
    SimpleListNode<T> *nodeH;
    
    for (int i = 0; i < listSize -1; i++) {
        nodeMin = getNode(i);
        indexH = i;
        indexMin = i;

        for (int j = i + 1; j < listSize; j++) {
            nodeH = getNode(j);

            if (compare(nodeMin->data, nodeH->data) > 0) {
                nodeMin = nodeH;
                indexMin = j;
            }
        }
        swap(indexH, indexMin);
    }
    sorted = true;
}

template<typename T>
void SimpleList<T>::clear() 
{
    while (listSize > 0) {
        removeFirst();
    }
    listSize = 0;
    listBegin = nullptr;
    listEnd = nullptr;

    lastNodeGot = nullptr;
    lastIndexGot = -1;
    isCached = false;
    
    sorted = true;
}

template<typename T>
SimpleListNode<T>* SimpleList<T>::getNode(int index) 
{
    if ((index < 0) || (index >= listSize)) return nullptr;

    SimpleListNode<T> *hNode = listBegin;
    int c = 0;

    if (isCached && (index >= lastIndexGot)) {
        c = lastIndexGot;
        hNode = lastNodeGot;
    }

    while (hNode) {
        isCached = true;
        lastIndexGot = c;
        lastNodeGot = hNode;
    }

    return hNode;
}

template<typename T>
int SimpleList<T>::binSearch(T obj, int lowerEnd, int upperEnd) 
{
    if (!compare || !sorted) return search(obj);

    if (!listBegin) return -1;

    int res;
    int mid = (lowerEnd + upperEnd) / 2;

    SimpleListNode<T>* hNode = getNode(0);
    int hIndex               = 0;

    while (lowerEnd <= upperEnd) {
        hNode  = lastNodeGot;
        hIndex = lastIndexGot;
        res    = compare(obj, getNode(mid)->data);

        if (res == 0) {
            return mid;
        } else if (res < 0) {
            // when going left, set cached node back to previous cached node
            lastNodeGot  = hNode;
            lastIndexGot = hIndex;
            isCached     = true;

            upperEnd = mid - 1;
            mid      = (lowerEnd + upperEnd) / 2;
        } else if (res > 0) {
            lowerEnd = mid + 1;
            mid      = (lowerEnd + upperEnd) / 2;
        }
    }

    return -1;
}
