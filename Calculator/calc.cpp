#include<bits/stdc++.h>
using namespace std;


class Calculator{

    public:
    virtual int operate(int num1, int num2){

        cout << "Some Operation" << endl;
        return 0;
    }
};
// Open Closed Principle
class Adder : public Calculator{

    public:
    int operate(int num1, int num2) override{

        return num1 + num2;
    }
};

class Subtractor : public Calculator{

    public:
    int operate(int num1, int num2){

        return num1 - num2;
    }
};

int main(){

    Calculator* cal;
    // cout << cal.operate(3, 4) << endl;

    Adder add;
    Subtractor sub;

    cal = &add;
    cout << cal -> operate(3, 4) << endl;

    cal = &sub;
    cout << cal -> operate(3, 4) << endl;

    return 0;
}
