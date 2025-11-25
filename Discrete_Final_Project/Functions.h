#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <string>

using namespace std;

const int MAX_MAPPINGS = 100;

template<typename Domain, typename Codomain>
class Function {
private:
    struct Mapping {
        Domain input;
        Codomain output;
    };

    Mapping mappings[MAX_MAPPINGS];
    int mappingCount;

    bool hasDomainElement(const Domain& input) const;

public:
    Function();

    bool addMapping(const Domain& input, const Codomain& output);
    Codomain apply(const Domain& input) const;

    bool isInjective() const;
    bool isSurjective(const Codomain codomain[], int codomainSize) const;
    bool isBijective(const Codomain codomain[], int codomainSize) const;

    Function<Domain, Codomain> compose(const Function<Codomain, Domain>& other) const;
    Function<Codomain, Domain> inverse() const;

    void display() const;
    int getSize() const {
        return mappingCount;
    }
};

class FunctionModule {
private:
    Function<string, string> studentToCourse;
    Function<string, string> courseToFaculty;
    Function<string, string> facultyToRoom;

public:
    FunctionModule();

    void assignStudentToCourse(const string& student, const string& course);
    void assignCourseToFaculty(const string& course, const string& faculty);
    void assignFacultyToRoom(const string& faculty, const string& room);

    void verifyInjectivity(const string& functionName);
    void verifySurjectivity(const string& functionName);
    void testFunctionComposition();
    void testInverseFunction();

    void displayAllFunctions() const;
};


template<typename Domain, typename Codomain>
Function<Domain, Codomain>::Function() : mappingCount(0) {}

template<typename Domain, typename Codomain>
bool Function<Domain, Codomain>::hasDomainElement(const Domain& input) const {
    for (int i = 0; i < mappingCount; i++)
    {
        if (mappings[i].input == input) {
            return true;
        }
    }
    return false;
}

template<typename Domain, typename Codomain>
bool Function<Domain, Codomain>::addMapping(const Domain& input, const Codomain& output) {
    if (hasDomainElement(input))
    {
        return false; // Functions must be well-defined
    }
    if (mappingCount < MAX_MAPPINGS)
    {
        mappings[mappingCount].input = input;
        mappings[mappingCount].output = output;
        mappingCount++;
        return true;
    }
    return false;
}

template<typename Domain, typename Codomain>
Codomain Function<Domain, Codomain>::apply(const Domain& input) const {
    for (int i = 0; i < mappingCount; i++)
    {
        if (mappings[i].input == input) {
            return mappings[i].output;
        }
    }
    return Codomain();
}

template<typename Domain, typename Codomain>
bool Function<Domain, Codomain>::isInjective() const {
    for (int i = 0; i < mappingCount; i++)
    {
        for (int j = i + 1; j < mappingCount; j++)
        {
            if (mappings[i].output == mappings[j].output) {
                return false;
            }
        }
    }
    return true;
}

template<typename Domain, typename Codomain>
bool Function<Domain, Codomain>::isSurjective(const Codomain codomain[], int codomainSize) const {
    for (int i = 0; i < codomainSize; i++)
    {
        bool found = false;
        for (int j = 0; j < mappingCount; j++)
        {
            if (mappings[j].output == codomain[i]) {
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }
    return true;
}

template<typename Domain, typename Codomain>
bool Function<Domain, Codomain>::isBijective(const Codomain codomain[], int codomainSize) const
{
    return isInjective() && isSurjective(codomain, codomainSize);
}

template<typename Domain, typename Codomain>
void Function<Domain, Codomain>::display() const {
    cout << "{ ";
    for (int i = 0; i < mappingCount; i++)
    {
        cout << mappings[i].input << " → " << mappings[i].output;
        if (i < mappingCount - 1)
            cout << ", ";
    }
    cout << " }";
}

template<typename Domain, typename Codomain>
Function<Domain, Codomain> Function<Domain, Codomain>::compose(const Function<Codomain, Domain>& other) const {
    Function<Domain, Codomain> result;
    for (int i = 0; i < mappingCount; i++) {
        for (int j = 0; j < other.mappingCount; j++) {
            if (mappings[i].output == other.mappings[j].input) {
                result.addMapping(mappings[i].input, other.mappings[j].output);
            }
        }
    }
    return result;
}

template<typename Domain, typename Codomain>
Function<Codomain, Domain> Function<Domain, Codomain>::inverse() const {
    Function<Codomain, Domain> result;
    if (isInjective()) {
        for (int i = 0; i < mappingCount; i++) {
            result.addMapping(mappings[i].output, mappings[i].input);
        }
    }
    return result;
}

#endif