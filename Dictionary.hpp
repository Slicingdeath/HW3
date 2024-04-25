#pragma once

template<typename Key, typename Val>
class Dictionary {
public:
    // default constructor
    Dictionary() {
    }

    // destructor
    virtual ~Dictionary() {
    }

    // remove all records in the dictionary, resetting to the initial state
    virtual void clear() = 0;

    // retrieve the record that matches the argument key
    virtual Val find(const Key&) const = 0;

    // add the record as a key-value pair to the dictionary
    virtual void insert(const Key&, const Val&) = 0;

    // remove the record that matches the argument key from the dictionary
    virtual void remove(const Key&) = 0;

    // return the number of records in the dictionary
    virtual int size() const = 0;
};
