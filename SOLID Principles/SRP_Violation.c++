#include <iostream> 
#include <string>
#include <vector>
using namespace std;

class Product{

    public:
    double price;
    string name;

    Product(string name, double price){

        this -> price = price;
        this -> name = name;
    }
};


// Violating SRP(Single Responsibilty Principle)
class ShoppingCart{

    private:
    vector<Product*> products;

    public:
    void addProduct(Product* p){

        products.push_back(p);
    }
    const vector<Product*> getProducts (){

        return products;
    }

    // 1. calculating totalPrice 
    double calculateTotal(){

        double total = 0;
        for(auto p : products){

            total += p->price;
        }

        return total;
    }

    // 2. printInvoice
    void printInvoice(){

        cout << "Cart Invoice : " << endl;
        for(auto p : products){

            cout << p -> name << " -$" << p->price << endl;
        }

        cout << "Total Price : $" << calculateTotal() << endl;
    }

    // 3. Save to Db
    void saveToDatabase(){

        cout << "Saving this order to DB...." << endl;
    }
};


int main(){

    ShoppingCart* cart = new ShoppingCart();

    cart -> addProduct(new Product("Laptop", 45000));
    cart -> addProduct(new Product("Mouse", 400));

    cart->printInvoice();
    cart->saveToDatabase();
    cout << "Total Amount is : " << cart->calculateTotal() << endl;


    return 0;

}