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

class Persistance{

    private:
    ShoppingCart* cart;

    public:
    virtual void save(ShoppingCart* cart) = 0;
};
class SQLPersistance : public Persistance{

    public:
    void save(ShoppingCart* cart) override {

        cout << "Saving this cart data into SQL..." << endl;
    }
};
class MongoDBPersistance : public Persistance{

    public:
    void save(ShoppingCart* cart) override {

        cout << "Saving this cart data into MongoDB..." << endl;
    }
};
class FilePersistance : public Persistance{

    public:
    void save(ShoppingCart* cart) override {

        cout << "Saving this cart data into File..." << endl;
    }
};

int main(){

    ShoppingCart* cart = new ShoppingCart();

    cart -> addProduct(new Product("Laptop", 45000));
    cart -> addProduct(new Product("Mouse", 400));

    CartInvoicePrinter* printer = new CartInvoicePrinter(cart);

    SQLPersistance* sqlSave = new SQLPersistance();
    MongoDBPersistance* mongoSave = new MongoDBPersistance();
    FilePersistance* fileSave = new FilePersistance();

    sqlSave->save(cart);
    mongoSave->save(cart);
    fileSave->save(cart);

    return 0;

}