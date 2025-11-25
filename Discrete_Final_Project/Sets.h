//#ifndef SETS_H
//#define SETS_H
//
//#include <iostream>
//#include <string>
//
//using namespace std;
//
//const int MAX_SET_SIZE = 100;
//
//template<typename T>
//class Set {
//private:
//    T elements[MAX_SET_SIZE];
//    int size;
//
//    bool contains(const T& element) const;
//
//public:
//    Set();
//
//    bool add(const T& element);
//    bool remove(const T& element);
//    bool isEmpty() const {
//        return size == 0;
//    }
//    int getSize() const { 
//        return size;
//    }
//    T getElement(int index) const;
//
//    // Set operations
//    Set<T> unionWith(const Set<T>& other) const;
//    Set<T> intersectionWith(const Set<T>& other) const;
//    Set<T> differenceWith(const Set<T>& other) const;
//    Set<T> symmetricDifference(const Set<T>& other) const;
//
//
//    bool isSubsetOf(const Set<T>& other) const;
//    bool isSupersetOf(const Set<T>& other) const;
//    bool isEqual(const Set<T>& other) const;
//
//
//    Set<T>** powerSet(int& count) const;
//    Set<T> cartesianProduct(const Set<T>& other) const;
//
//    void display() const;
//    void clear();
//};
//
//class SetModule {
//private:
//    Set<string> students;
//    Set<string> courses;
//    Set<string> faculty;
//    Set<string> rooms;
//
//public:
//    SetModule();
//
//    void addStudent(const string& student);
//    void addCourse(const string& course);
//    void addFaculty(const string& facultyMember);
//    void addRoom(const string& room);
//
//
//    void findStudentsInBothCourses(const string& course1, const string& course2);
//    void findCommonFaculty(const string& dept1, const string& dept2);
//    void demonstrateSetOperations();
//    void generatePowerSet(const string& setType);
//
//    void displayAllSets() const;
//};
//
//
//
//template<typename T>
//Set<T>::Set() : size(0) {}
//
//template<typename T>
//bool Set<T>::contains(const T& element) const {
//    for (int i = 0; i < size; i++)
//    {
//        if (elements[i] == element) {
//            return true;
//        }
//    }
//    return false;
//}
//
//template<typename T>
//bool Set<T>::add(const T& element)
//{
//    if (!contains(element) && size < MAX_SET_SIZE) {
//        elements[size++] = element;
//        return true;
//    }
//    return false;
//}
//
//template<typename T>
//bool Set<T>::remove(const T& element) {
//    for (int i = 0; i < size; i++)
//    {
//        if (elements[i] == element) {
//            for (int j = i; j < size - 1; j++) {
//                elements[j] = elements[j + 1];
//            }
//            size--;
//            return true;
//        }
//    }
//    return false;
//}
//
//template<typename T>
//T Set<T>::getElement(int index) const {
//    if (index >= 0 && index < size) {
//        return elements[index];
//    }
//    return T();
//}
//
//template<typename T>
//Set<T> Set<T>::unionWith(const Set<T>& other) const {
//    Set<T> result;
//    for (int i = 0; i < size; i++)
//    {
//        result.add(elements[i]);
//    }
//    for (int i = 0; i < other.size; i++)
//    {
//        result.add(other.elements[i]);
//    }
//    return result;
//}
//
//template<typename T>
//Set<T> Set<T>::intersectionWith(const Set<T>& other) const {
//    Set<T> result;
//    for (int i = 0; i < size; i++)
//    {
//        if (other.contains(elements[i])) {
//            result.add(elements[i]);
//        }
//    }
//    return result;
//}
//
//template<typename T>
//Set<T> Set<T>::differenceWith(const Set<T>& other) const {
//    Set<T> result;
//    for (int i = 0; i < size; i++)
//    {
//        if (!other.contains(elements[i])) {
//            result.add(elements[i]);
//        }
//    }
//    return result;
//}
//
//template<typename T>
//Set<T> Set<T>::symmetricDifference(const Set<T>& other) const {
//
//    Set<T> result = this->differenceWith(other);
//    Set<T> temp = other.differenceWith(*this);
//    result = result.unionWith(temp);
//
//    return result;
//}
//
//template<typename T>
//bool Set<T>::isSubsetOf(const Set<T>& other) const {
//    for (int i = 0; i < size; i++)
//    {
//        if (!other.contains(elements[i])) {
//            return false;
//        }
//    }
//    return true;
//}
//
//template<typename T>
//bool Set<T>::isSupersetOf(const Set<T>& other) const {
//    return other.isSubsetOf(*this);
//}
//
//template<typename T>
//bool Set<T>::isEqual(const Set<T>& other) const {
//    return (size == other.size) && isSubsetOf(other);
//}
//
//template<typename T>
//void Set<T>::display() const {
//    cout << "{ ";
//    for (int i = 0; i < size; i++) {
//        cout << elements[i];
//        if (i < size - 1) cout << ", ";
//    }
//    cout << " }";
//}
//
//template<typename T>
//void Set<T>::clear() {
//    size = 0;
//}
//
//#endif