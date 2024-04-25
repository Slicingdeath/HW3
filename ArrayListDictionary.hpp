#pragma once

#include "Dictionary.hpp"
#include "ArrayList.hpp"

template<typename Key, typename Val>
class ArrayListDictionary: public Dictionary<Key, Val> {
private:
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

    // the underlying array-based list
    ArrayList<Record> *list;

    // sequential search algorithm (iterative)
    Val seqSearchIter(const Key&) const;

    // copy the state of the argument dictionary to `this`
    void copy(const ArrayListDictionary<Key, Val>&);



public:

    // constructor with the search implementation and the maximum size as the arguments
    ArrayListDictionary(int = 100);

    // copy constructor
    ArrayListDictionary(const ArrayListDictionary<Key, Val>&);

    // overloaded assignment operator
    ArrayListDictionary<Key, Val>& operator=(
            const ArrayListDictionary<Key, Val>&);

    // destructor
    virtual ~ArrayListDictionary();

    // remove all records in the dictionary, resetting to the initial state
    virtual void clear() override;

    // retrieve the record that matches the argument key
    // if multiple records match, return an arbitrary one
    virtual Val find(const Key&) const override;

    // add the record as a key-value pair to the dictionary
    virtual void insert(const Key&, const Val&) override;

    // remove the record that matches the argument key from the dictionary
    // if multiple records match, remove an arbitrary one
    virtual void remove(const Key&) override;

    // return the number of records in the dictionary
    virtual int size() const override;
};

template<typename Key, typename Val>
ArrayListDictionary<Key, Val>::ArrayListDictionary(int i) :
        list(new ArrayList<Record>(i)) {
}

template<typename Key, typename Val>
ArrayListDictionary<Key, Val>::ArrayListDictionary(
        const ArrayListDictionary<Key, Val> &copyObj) {
    copy(copyObj);
}

template<typename Key, typename Val>
ArrayListDictionary<Key, Val>& ArrayListDictionary<Key, Val>::operator=(
        const ArrayListDictionary<Key, Val> &rightObj) {
    if (this != &rightObj) {
        delete list;
        copy(rightObj);
    }
    return *this;
}

template<typename Key, typename Val>
ArrayListDictionary<Key, Val>::~ArrayListDictionary() {
    delete list;
}

template<typename Key, typename Val>
void ArrayListDictionary<Key, Val>::clear() {
    list->clear();
}

template<typename Key, typename Val>
void ArrayListDictionary<Key, Val>::copy(
        const ArrayListDictionary<Key, Val> &copyObj) {
    list = new ArrayList<Record>(*copyObj.list);
}

template<typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::find(const Key &k) const {
    try {
        return seqSearchIter(k);

    } catch (...) {
        throw std::string(
                "find: error, unsuccessful search, target key not found");
    }
}

// XXX: this implementation doesn't work in general! Sorry!
// if you want to use binary search (SearchImpl::BIN_REC or SearchImpl::BIN_ITER)
// you will need to make sure you insert things in sorted order
template<typename Key, typename Val>
void ArrayListDictionary<Key, Val>::insert(const Key &k, const Val &v) {
	for (int i = 0; i < list->getLength(); i++) {
	    if (list->getElement(i).k == k) {
	        std::cout << "Key is already present" << std::endl;
	        return;
	    }
	}
    list->append(Record(k, v));
}

template<typename Key, typename Val>
void ArrayListDictionary<Key, Val>::remove(const Key &k) {
    bool flag = false;

    for (int i = 0; i < list->getLength(); i++) {
        if (list->getElement(i).k == k) {
            list->replace(i, list->getElement(list->getLength() - 1));
            list->remove(list->getLength() - 1);
            flag = true;
            break;
        }
    }

    if (!flag) {
        throw std::string(
                "remove: error, unable to find record with matching key to remove");
    }
}

template<typename Key, typename Val>
Val ArrayListDictionary<Key, Val>::seqSearchIter(const Key &target) const
{
    // TODO
	for (int i = 0; i < list->getLength(); i++)
	{
		if(list->getElement(i).k == target)
		{
			return list->getElement(i).v;
		}
	}
	// loop finishes but does not find record with matching key, search unsuccessful
	throw -1;
}


template<typename Key, typename Val>
int ArrayListDictionary<Key, Val>::size() const {
    return list->getLength();
}
