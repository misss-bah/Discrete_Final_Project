#ifndef functions_h
#define functions_h

#include <iostream>
#include <string>

using namespace std;

const int max_mappings = 100;

template<typename domain, typename codomain>
class function {
private:
    struct mapping {
        domain input;
        codomain output;
    };

    mapping mappings[max_mappings];
    int mappingcount;

    bool hasdomainelement(const domain& input) const;

public:
    function();

    bool addmapping(const domain& input, const codomain& output);
    codomain apply(const domain& input) const;

    bool isinjective() const;
    bool issurjective(const codomain codomain[], int codomainsize) const;
    bool isbijective(const codomain codomain[], int codomainsize) const;

    function<domain, codomain> compose(const function<codomain, domain>& other) const;
    function<codomain, domain> inverse() const;

    void display() const;
    int getsize() const {
        return mappingcount;
    }
};

class functionmodule {
private:
    function<string, string> studenttocourse;
    function<string, string> coursetofaculty;
    function<string, string> facultytoroom;

public:
    functionmodule();

    void assignstudenttocourse(const string& student, const string& course);
    void assigncoursetofaculty(const string& course, const string& faculty);
    void assignfacultytoroom(const string& faculty, const string& room);

    void verifyinjectivity(const string& functionname);
    void verifysurjectivity(const string& functionname);
    void testfunctioncomposition();
    void testinversefunction();

    void displayallfunctions() const;
};


template<typename domain, typename codomain>
function<domain, codomain>::function() : mappingcount(0) {}

template<typename domain, typename codomain>
bool function<domain, codomain>::hasdomainelement(const domain& input) const {
    for (int i = 0; i < mappingcount; i++)
    {
        if (mappings[i].input == input) {
            return true;
        }
    }
    return false;
}

template<typename domain, typename codomain>
bool function<domain, codomain>::addmapping(const domain& input, const codomain& output) {
    if (hasdomainelement(input))
    {
        return false; // functions must be well-defined
    }
    if (mappingcount < max_mappings)
    {
        mappings[mappingcount].input = input;
        mappings[mappingcount].output = output;
        mappingcount++;
        return true;
    }
    return false;
}

template<typename domain, typename codomain>
codomain function<domain, codomain>::apply(const domain& input) const {
    for (int i = 0; i < mappingcount; i++)
    {
        if (mappings[i].input == input) {
            return mappings[i].output;
        }
    }
    return codomain();
}

template<typename domain, typename codomain>
bool function<domain, codomain>::isinjective() const {
    for (int i = 0; i < mappingcount; i++)
    {
        for (int j = i + 1; j < mappingcount; j++)
        {
            if (mappings[i].output == mappings[j].output) {
                return false;
            }
        }
    }
    return true;
}

template<typename domain, typename codomain>
bool function<domain, codomain>::issurjective(const codomain codomain[], int codomainsize) const {
    for (int i = 0; i < codomainsize; i++)
    {
        bool found = false;
        for (int j = 0; j < mappingcount; j++)
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

template<typename domain, typename codomain>
bool function<domain, codomain>::isbijective(const codomain codomain[], int codomainsize) const
{
    return isinjective() && issurjective(codomain, codomainsize);
}

template<typename domain, typename codomain>
void function<domain, codomain>::display() const {
    cout << "{ ";
    for (int i = 0; i < mappingcount; i++)
    {
        cout << mappings[i].input << " → " << mappings[i].output;
        if (i < mappingcount - 1)
            cout << ", ";
    }
    cout << " }";
}

#endif