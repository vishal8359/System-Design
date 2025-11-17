#include <bits/stdc++.h>
using namespace std;

// ---------------- BOOK ----------------
class Book
{
public:
    int id;
    string title;
    string author;
    bool available;

    Book(int id, string t, string a)
        : id(id), title(t), author(a), available(true) {}
};

// ---------------- USER ----------------
class User
{
public:
    int userId;
    string name;
    vector<int> borrowedBooks;

    User(int id, string n) : userId(id), name(n) {}
};

// ---------------- LIBRARY ----------------
class Library
{
private:
    unordered_map<int, Book *> books;
    unordered_map<int, User *> users;

public:
    // add new book
    void addBook(Book *b)
    {
        books[b->id] = b;
        cout << "Book added: " << b->title << endl;
    }

    // add new user
    void addUser(User *u)
    {
        users[u->userId] = u;
        cout << "User added: " << u->name << endl;
    }

    // borrow a book
    void borrowBook(int userId, int bookId)
    {

        if (!users.count(userId))
        {
            cout << "User not found!\n";
            return;
        }
        if (!books.count(bookId))
        {
            cout << "Book not found!\n";
            return;
        }

        Book *b = books[bookId];
        User *u = users[userId];

        if (!b->available)
        {
            cout << "Book already issued!\n";
            return;
        }

        b->available = false;
        u->borrowedBooks.push_back(bookId);

        cout << u->name << " borrowed \"" << b->title << "\"\n";
    }

    // return a book
    void returnBook(int userId, int bookId)
    {

        if (!users.count(userId))
        {
            cout << "User not found!\n";
            return;
        }

        User *u = users[userId];
        Book *b = books[bookId];

        int index = -1;

        for (int i = 0; i < u->borrowedBooks.size(); i++){

            if (u->borrowedBooks[i] == bookId){
                
                index = i;
                break;
            }
        }

        if (index == -1){

            cout << "User did not borrow this book!\n";
            return;
        }

        u->borrowedBooks.erase(u->borrowedBooks.begin() + index);
        b->available = true;

        cout << "Returned: " << b->title << endl;
    }

    // show all available books
    void showAvailable()
    {
        cout << "\n--- Available Books ---\n";
        for (auto &p : books)
        {
            if (p.second->available)
            {
                cout << p.second->id << " - " << p.second->title
                     << " (" << p.second->author << ")\n";
            }
        }
    }

    // show books borrowed by a user
    void showUserBorrowed(int userId)
    {
        if (!users.count(userId))
        {
            cout << "User not found!\n";
            return;
        }

        User *u = users[userId];

        cout << "\nBooks borrowed by " << u->name << ":\n";

        if (u->borrowedBooks.empty())
        {
            cout << "No books borrowed.\n";
            return;
        }

        for (int id : u->borrowedBooks)
        {
            cout << "- " << books[id]->title << endl;
        }
    }
};

// ---------------- MAIN ----------------
int main()
{

    Library lib;

    // add books
    lib.addBook(new Book(1, "The Alchemist", "Paulo Coelho"));
    lib.addBook(new Book(2, "Clean Code", "Robert C. Martin"));
    lib.addBook(new Book(3, "Harry Potter", "J.K. Rowling"));
    lib.addBook(new Book(4, "Deep Work", "Cal Newport"));

    // add users
    lib.addUser(new User(101, "Vishal"));
    lib.addUser(new User(102, "Rohan"));

    // user borrows multiple books
    lib.borrowBook(101, 1);
    lib.borrowBook(101, 3);
    lib.borrowBook(101, 4);

    lib.showUserBorrowed(101);

    lib.showAvailable();

    // user returns a book
    lib.returnBook(101, 3);

    lib.showUserBorrowed(101);
    lib.showAvailable();

    return 0;
}
