#ifndef _MAXHEAP_H_
#define _MAXHEAP_H_

#include <unordered_map>
#include <vector>

#define LEFT(i) (2 * (i))
#define RIGHT(i) (2 * (i) + 1)
#define PARENT(i) ((i) / 2)

// Binary max-heap to represent integer keys of type K with values
// (priorities) of type V
template <class K, class V> class MaxHeap {
    struct Node { // An element of the heap: a pair (key, value)
        K key;
        V value;
    };

    int size;            // Number of elements in heap
    int maxSize;         // Maximum number of elements in heap
    std::vector<Node> a; // The heap array
    std::unordered_map<K, int>
            pos; // maps a key into its position on the array a
    const K KEY_NOT_FOUND;

    void upHeap(int i);
    void downHeap(int i);
    void swap(int i1, int i2);

public:
    MaxHeap(int n,
            const K &notFound); // Create a max-heap for a max of n pairs (K,V)
    // with notFound returned when empty
    int getSize();              // Return number of elements in the heap
    bool hasKey(const K &key);  // Heap has key?
    void insert(const K &key,
                const V &value); // Insert (key, value) on the heap
    void increaseKey(const K &key, const V &value); // Increase value of key
    K removeMax(); // remove and return key with greater value
};

// ----------------------------------------------

// Make a value go "up the tree" until it reaches its position
template <class K, class V> void MaxHeap<K, V>::upHeap(int i) {
    while (i > 1 && a[i].value > a[PARENT(i)].value) { // while pos greater than parent,
        // keep swapping to upper position
        swap(i, PARENT(i));
        i = PARENT(i);
    }
}

// Make a value go "down the tree" until it reaches its position
template <class K, class V> void MaxHeap<K, V>::downHeap(int i) {
    while (LEFT(i) <= size) { // while within heap limits
        int j = LEFT(i);
        if (RIGHT(i) <= size && a[RIGHT(i)].value > a[j].value)
            j = RIGHT(i); // choose greater child
        if (a[i].value > a[j].value)
            break;  // node already greater than children, stop
        swap(i, j); // otherwise, swap with greater child
        i = j;
    }
}

// Swap two positions of the heap (update their positions)
template <class K, class V> void MaxHeap<K, V>::swap(int i1, int i2) {
    Node tmp = a[i1];
    a[i1] = a[i2];
    a[i2] = tmp;
    pos[a[i1].key] = i1;
    pos[a[i2].key] = i2;
}

// ----------------------------------------------

// Create a max-heap for a max of n pairs (K,V) with notFound returned when
// empty
template <class K, class V>
MaxHeap<K, V>::MaxHeap(int n, const K &notFound)
        : KEY_NOT_FOUND(notFound), size(0), maxSize(n), a(n + 1) {}

// Return number of elements in the heap
template <class K, class V> int MaxHeap<K, V>::getSize() { return size; }

// Heap has key?
template <class K, class V> bool MaxHeap<K, V>::hasKey(const K &key) {
    return pos.find(key) != pos.end();
}

// Insert (key, value) on the heap
template <class K, class V>
void MaxHeap<K, V>::insert(const K &key, const V &value) {
    if (size == maxSize)
        return; // heap is full, do nothing
    if (hasKey(key))
        return; // key already exists, do nothing
    a[++size] = {key, value};
    pos[key] = size;
    upHeap(size);
}

// Increase value of key to the indicated value
template <class K, class V>
void MaxHeap<K, V>::increaseKey(const K &key, const V &value) {
    if (!hasKey(key))
        return; // key does not exist, do nothing
    int i = pos[key];
    if (value < a[i].value)
        return; // value would decrease, do nothing
    a[i].value = value;
    upHeap(i);
}

// remove and return key with smaller value
template <class K, class V> K MaxHeap<K, V>::removeMax() {
    if (size == 0)
        return KEY_NOT_FOUND;
    K max = a[1].key;
    pos.erase(max);
    a[1] = a[size--];
    downHeap(1);
    return max;
}

#endif