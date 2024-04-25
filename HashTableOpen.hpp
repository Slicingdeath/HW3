#pragma once

#include "Dictionary.hpp"
#include "hashing.hpp"
#include "StreetAddress.hpp"

template<typename Key, typename Val>
class HashTableOpen: public Dictionary<Key, Val> {
protected:
    // an element in a dictionary, contains a key and a value
    struct Record {
        Key k;
        Val v;

        Record() :
                k(Key()), v(Val()) {
        }
        Record(Key x, Val y) :
                k(x), v(y) {
        }
    };

    // a node for the (head of a) linked list at each slot of the hash table
    struct Node {
        Record r;
        Node *next;

        Node(Record record = Record(), Node *node = nullptr) :
                r(record), next(node) {
        }
    };

    // the size of the hash table (total number of slots)
    int M;

    // the underlying (dynamic) array of (dynamic) linked lists
    Node **ht;

    // the method for turning keys into integers;
    // subclasses that specify the template parameter Key
    // will need to override this with a suitable method
    // virtual int hashImpl(const Key&) const = 0;

    // the method for turning keys into valid slots:
    // calls hashImpl and always ensures the return value is between 0 and M-1
    int hash(const Key&) const;

public:
    // default constructor
    HashTableOpen(int = 100);

    // destructor
    virtual ~HashTableOpen();

    // it would be good practice to have a copy constructor and assignment operator,
    // but we'll skip those for this lab.

    // remove all records in the dictionary, resetting to the initial state
    virtual void clear() override;

    // retrieve the record that matches the argument key
    virtual Val find(const Key&) const override;

    // add the record as a key-value pair to the dictionary
    virtual void insert(const Key&, const Val&) override;

    // remove the record that matches the argument key from the dictionary
    virtual void remove(const Key&) override;

    // return the number of records in the dictionary
    virtual int size() const override;
};

template<typename Key, typename Val>
HashTableOpen<Key, Val>::HashTableOpen(int maxSize) :
M(maxSize) {
    ht = new Node*[M];
    for (int i = 0; i < M; ++i) {
        ht[i] = nullptr;
    }
}

template<typename Key, typename Val>
HashTableOpen<Key, Val>::~HashTableOpen() {
    clear();
    delete[] ht;
}

template<typename Key, typename Val>
void HashTableOpen<Key, Val>::clear() {
    for (int i = 0; i < M; ++i) {
        Node* current = ht[i];
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        ht[i] = nullptr;
    }
}

template<typename Key, typename Val>
Val HashTableOpen<Key, Val>::find(const Key &k) const {
    int index = hash(k);
    Node* current = ht[index];
    while (current) {
        if (current->r.k == k) {
            return current->r.v;
        }
        current = current->next;
    }
    throw std::string("Key not found");
}

template<typename Key, typename Val>
void HashTableOpen<Key, Val>::insert(const Key &k, const Val &v) {
    int index = hash(k);
    Node* newNode = new Node(Record(k, v), ht[index]);
    ht[index] = newNode;
}

template<typename Key, typename Val>
void HashTableOpen<Key, Val>::remove(const Key &k) {
    int index = hash(k);
    Node* current = ht[index];
    Node* prev = nullptr;
    while (current) {
        if (current->r.k == k) {
            if (prev) {
                prev->next = current->next;
            } else {
                ht[index] = current->next;
            }
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
    throw std::string("Key not found");
}

template<typename Key, typename Val>
int HashTableOpen<Key, Val>::size() const {
    int count = 0;
    for (int i = 0; i < M; ++i) {
        Node* current = ht[i];
        while (current) {
            ++count;
            current = current->next;
        }
    }
    return count;
}

template<typename Key, typename Val>
int HashTableOpen<Key, Val>::hash(const Key &k) const {
    // subclasses can implement `hashImpl` without having to worry about the # of slots
    // and we can call `hash` in this class's methods without having to worry about the same thing
	if (std::is_same<Key, StreetAddress>::value) {
		return hashString(k.toString(), 2) % M;
	} else {
	    return hashString(toString(k), 2) % M;
	}
}

