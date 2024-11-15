#pragma once
#include "../DoublyLinkedLists/DoublyLinkedListTemplate.hpp"


template <typename T>
class HashTable {
private:
    DoublyLinkedList<T> *table;
    unsigned int size;

    unsigned int getIndex(T data) {
        if(!HashFunction) {
            return 0;
        }
        return HashFunction(data, size);
    }

    HashFunction hashFunction;

public:
    using HashFunction = unsigned int (*)(T&, unsigned int tableSize);

    HashTable() {
        table = nullptr;
        size = 0;
    }
    ~HashTable() { deleteTable(); };

    bool createTable(unsigned int nSize, HashFunction hashF) {
        if (!nSize || table || !hashFunction) {
            return false;
        }

        table = new(nothrow) DoublyLinkedList<T>[nSize];
        if (!table) {
            return false;
        }
        
        size = nSize;
        hashFunction = hashF;
        return true;
        
    }

    void deleteTable() {
        if (!size) {
            return;
        }

        if (table) {
            delete [] table;
            table = nullptr;
            size = 0;
        }
    }
    
    bool insert(int data);
    bool remove(int data);

    T *search(T data) {
        unsigned int index = 0;
        
        if (!table) {
            return nullptr;
        }

        index = getIndex(data);
        return (table[index].search(data));
    }

    void print();

};