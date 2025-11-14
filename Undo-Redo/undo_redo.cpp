#include<bits/stdc++.h>
using namespace std;


class Action{

    public:
    string text;
    Action* prev;
    Action* next;

    Action(string text){

        this -> text = text;
        prev = NULL;
        next = NULL;
    }
};

class Editor{

    Action* head;
    Action* curr;
    public:

    Editor(){

        head = new Action("Start");
        curr = head;
    }

    void performAction(string text){

        if(curr -> next){

            Action* temp = curr -> next;
            while(temp){

                Action* del = temp;
                temp = temp -> next;
                delete del;
            }
            curr -> next = NULL;
        }
        Action* node = new Action(text);
        node -> prev = curr;
        curr -> next = node;
        curr = node;
        
        cout << "Action performed successfully" << endl;
    }

    void undo(){

        if (curr -> prev == NULL) {
            cout << "Nothing to undo\n";
            return;
        }
        if(curr -> prev){

            curr = curr -> prev;
        }
        cout << "undo" << endl;
    }
    void redo(){

        if (curr -> next == NULL) {
            cout << "Nothing to redo\n";
            return;
        }

        if(curr -> next){

            curr = curr -> next;
        }
        cout << "redo" << endl;
    }
    void showState() {
        cout << "Current action: " << curr -> text << endl;
    }
};

int main(){

    Editor* editor = new Editor();
    editor->showState();
    editor->performAction("I ");
    editor->performAction("am ");
    editor->performAction("Vishal");
    editor->showState();
    editor->undo();
    editor->showState();
    editor->performAction("Radhika");
    editor->showState();
    
    return 0;
}