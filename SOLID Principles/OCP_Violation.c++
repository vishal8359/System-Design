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

    // calculating totalPrice 
    double calculateTotal(){

        double total = 0;
        for(auto p : products){

            total += p->price;
        }

        return total;
    }
};

class CartInvoicePrinter{

    private:
    ShoppingCart* cart;

    public:
    CartInvoicePrinter(ShoppingCart* cart){

        this -> cart = cart;
    }
    void printInvoice(){

        cout << "Cart Invoice : " << endl;
        for(auto p : cart->getProducts()){

            cout << p -> name << " -$" << p->price << endl;
        }

        cout << "Total Price : $" << cart->calculateTotal() << endl;
    }
}; 

class CartDBStore{
    private:
    ShoppingCart* cart;
    public:
    CartDBStore(ShoppingCart* cart){

        this -> cart = cart;
    }
    // Save to Db - Method overiding
    void saveToSQLDatabase(){

        cout << "Saving this order to SQL DB...." << endl;
    }

    void saveToMongoDatabase(){

        cout << "Saving this order to SQL DB...." << endl;
    }

    void saveToFile(){

        cout << "Saving this order to File...." << endl;
    }
};

int main(){

    ShoppingCart* cart = new ShoppingCart();

    cart -> addProduct(new Product("Laptop", 45000));
    cart -> addProduct(new Product("Mouse", 400));

    CartInvoicePrinter* printer = new CartInvoicePrinter(cart);

    CartDBStore* db = new CartDBStore(cart); 

    printer->printInvoice();
    db->saveToMongoDatabase();

    return 0;

}