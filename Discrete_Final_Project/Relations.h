//#ifndef RELATIONS_H
//#define RELATIONS_H
//
//#include <iostream>
//#include <string>
//using namespace std;
//
//const int MAX_RELATION_PAIRS = 200;
//
//template<typename T1, typename T2>
//class Relation {
//private:
//    struct Pair {
//        T1 first;
//        T2 second;
//    };
//
//    Pair pairs[MAX_RELATION_PAIRS];
//    int pairCount;
//
//public:
//    Relation();
//
//    void addPair(const T1& first, const T2& second);
//    bool contains(const T1& first, const T2& second) const;
//    int getSize() const {
//        return pairCount;
//    }
//    bool isReflexive(const T1 domain[], int domainSize) const;
//    bool isSymmetric() const;
//    bool isTransitive() const;
//    bool isAntisymmetric() const;
//
//    bool isEquivalenceRelation(const T1 domain[], int domainSize) const;
//    bool isPartialOrder(const T1 domain[], int domainSize) const;
//
//    Relation<T1, T2> compose(const Relation<T2, T1>& other) const;
//
//    void display() const;
//};
//
//class RelationModule {
//private:
//    Relation<string, string> studentCourse;
//    Relation<string, string> facultyCourse;
//    Relation<string, string> courseRoom;
//
//public:
//    RelationModule();
//
//    void addStudentCourse(const string& student, const string& course);
//    void addFacultyCourse(const string& faculty, const string& course);
//    void addCourseRoom(const string& course, const string& room);
//
//    void checkRelationProperties();
//    void findIndirectEnrollments();
//    void composeRelations();
//
//    void displayAllRelations() const;
//};
//
//
//template<typename T1, typename T2>
//Relation<T1, T2>::Relation() : pairCount(0) {}
//
//template<typename T1, typename T2>
//void Relation<T1, T2>::addPair(const T1& first, const T2& second)
//{
//    if (pairCount < MAX_RELATION_PAIRS && !contains(first, second)) {
//        pairs[pairCount].first = first;
//        pairs[pairCount].second = second;
//        pairCount++;
//    }
//}
//
//template<typename T1, typename T2>
//bool Relation<T1, T2>::contains(const T1& first, const T2& second) const {
//    for (int i = 0; i < pairCount; i++)
//    {
//        if (pairs[i].first == first && pairs[i].second == second)
//            return true;
//    }
//    return false;
//}
//
//template<typename T1, typename T2>
//bool Relation<T1, T2>::isReflexive(const T1 domain[], int domainSize) const {
//    for (int i = 0; i < domainSize; i++)
//    {
//        if (!contains(domain[i], domain[i]))
//            return false;
//    }
//    return true;
//}
//
//template<typename T1, typename T2>
//bool Relation<T1, T2>::isSymmetric() const {
//    for (int i = 0; i < pairCount; i++)
//    {
//        if (!contains(pairs[i].second, pairs[i].first))
//            return false;
//    }
//    return true;
//}
//
//template<typename T1, typename T2>
//bool Relation<T1, T2>::isTransitive() const {
//    for (int i = 0; i < pairCount; i++)
//    {
//        for (int j = 0; j < pairCount; j++)
//        {
//            if (pairs[i].second == pairs[j].first && !contains(pairs[i].first, pairs[j].second))
//            {
//                return false;
//            }
//        }
//    }
//    return true;
//}
//
//template<typename T1, typename T2>
//bool Relation<T1, T2>::isAntisymmetric() const {
//    for (int i = 0; i < pairCount; i++)
//    {
//        for (int j = 0; j < pairCount; j++)
//        {
//            if (pairs[i].first == pairs[j].second && pairs[i].second == pairs[j].first && pairs[i].first != pairs[i].second)
//            {
//                return false;
//            }
//        }
//    }
//    return true;
//}
//
//template<typename T1, typename T2>
//bool Relation<T1, T2>::isEquivalenceRelation(const T1 domain[], int domainSize) const {
//    return isReflexive(domain, domainSize) && isSymmetric() && isTransitive();
//}
//
//template<typename T1, typename T2>
//bool Relation<T1, T2>::isPartialOrder(const T1 domain[], int domainSize) const {
//    return isReflexive(domain, domainSize) && isAntisymmetric() && isTransitive();
//}
//
//template<typename T1, typename T2>
//Relation<T1, T2> Relation<T1, T2>::compose(const Relation<T2, T1>& other) const {
//    Relation<T1, T2> result;
//
//    for (int i = 0; i < pairCount; i++)
//    {
//        for (int j = 0; j < other.pairCount; j++)
//        {
//            if (pairs[i].second == other.pairs[j].first) {
//                result.addPair(pairs[i].first, other.pairs[j].second);
//            }
//        }
//    }
//    return result;
//}
//
//template<typename T1, typename T2>
//void Relation<T1, T2>::display() const {
//    cout << "{ ";
//    for (int i = 0; i < pairCount; i++)
//    {
//        cout << "(" << pairs[i].first << ", " << pairs[i].second << ")";
//        if (i < pairCount - 1)
//            cout << ", ";
//    }
//    cout << " }";
//}
//
//#endif
