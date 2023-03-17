#include <iostream>
#include <string>

using namespace std;

class Person {
    string m_name{"James"};
    int m_age{};
public:
    void sayname() {
        cout << m_name;
    }
};

void saySomething(const char* ch) {
    cout << ch << endl;
}

int main() {
    char ch = 'A';
    double d = 12.34;
    for (int i = 0; i < 10; ++i)
        if (i != 5)
            cout << i + 1 << ". Hello world" << endl;

    saySomething("Lets go home now");

    Person p;
    p.sayname();
}