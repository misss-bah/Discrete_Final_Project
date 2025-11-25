#ifndef sets_h
#define sets_h

#include <iostream>
#include <string>

using namespace std;

const int max_set_size = 100;

template<typename t>
class set {
private:
    t elements[max_set_size];
    int size;

    bool contains(const t& element) const;

public:
    set();

    bool add(const t& element);
    bool remove(const t& element);
    bool isempty() const {
        return size == 0;
    }
    int getsize() const { 
        return size;
    }
    t getelement(int index) const;

    // set operations
    set<t> unionwith(const set<t>& other) const;
    set<t> intersectionwith(const set<t>& other) const;
    set<t> differencewith(const set<t>& other) const;
    set<t> symmetricdifference(const set<t>& other) const;


    bool issubsetof(const set<t>& other) const;
    bool issupersetof(const set<t>& other) const;
    bool isequal(const set<t>& other) const;


    set<t>** powerset(int& count) const;
    set<t> cartesianproduct(const set<t>& other) const;

    void display() const;
    void clear();
};

class setmodule {
private:
    set<string> students;
    set<string> courses;
    set<string> faculty;
    set<string> rooms;

public:
    setmodule();

    void addstudent(const string& student);
    void addcourse(const string& course);
    void addfaculty(const string& facultymember);
    void addroom(const string& room);


    void findstudentsinbothcourses(const string& course1, const string& course2);
    void findcommonfaculty(const string& dept1, const string& dept2);
    void demonstratesetoperations();
    void generatepowerset(const string& settype);

    void displayallsets() const;
};



template<typename t>
set<t>::set() : size(0) {}

template<typename t>
bool set<t>::contains(const t& element) const {
    for (int i = 0; i < size; i++)
    {
        if (elements[i] == element) {
            return true;
        }
    }
    return false;
}

template<typename t>
bool set<t>::add(const t& element)
{
    if (!contains(element) && size < max_set_size) {
        elements[size++] = element;
        return true;
    }
    return false;
}

template<typename t>
bool set<t>::remove(const t& element) {
    for (int i = 0; i < size; i++)
    {
        if (elements[i] == element) {
            for (int j = i; j < size - 1; j++) {
                elements[j] = elements[j + 1];
            }
            size--;
            return true;
        }
    }
    return false;
}

template<typename t>
t set<t>::getelement(int index) const {
    if (index >= 0 && index < size) {
        return elements[index];
    }
    return t();
}

template<typename t>
set<t> set<t>::unionwith(const set<t>& other) const {
    set<t> result;
    for (int i = 0; i < size; i++)
    {
        result.add(elements[i]);
    }
    for (int i = 0; i < other.size; i++)
    {
        result.add(other.elements[i]);
    }
    return result;
}

template<typename t>
set<t> set<t>::intersectionwith(const set<t>& other) const {
    set<t> result;
    for (int i = 0; i < size; i++)
    {
        if (other.contains(elements[i])) {
            result.add(elements[i]);
        }
    }
    return result;
}

template<typename t>
set<t> set<t>::differencewith(const set<t>& other) const {
    set<t> result;
    for (int i = 0; i < size; i++)
    {
        if (!other.contains(elements[i])) {
            result.add(elements[i]);
        }
    }
    return result;
}

template<typename t>
set<t> set<t>::symmetricdifference(const set<t>& other) const {

    set<t> result = this->differencewith(other);
    set<t> temp = other.differencewith(*this);
    result = result.unionwith(temp);

    return result;
}

template<typename t>
bool set<t>::issubsetof(const set<t>& other) const {
    for (int i = 0; i < size; i++)
    {
        if (!other.contains(elements[i])) {
            return false;
        }
    }
    return true;
}

template<typename t>
bool set<t>::issupersetof(const set<t>& other) const {
    return other.issubsetof(*this);
}

template<typename t>
bool set<t>::isequal(const set<t>& other) const {
    return (size == other.size) && issubsetof(other);
}

template<typename t>
void set<t>::display() const {
    cout << "{ ";
    for (int i = 0; i < size; i++) {
        cout << elements[i];
        if (i < size - 1) cout << ", ";
    }
    cout << " }";
}

template<typename t>
void set<t>::clear() {
    size = 0;
}

#endif