#include <iostream>
#include <string>
using namespace std;

// Base class representing a product
class Product {
protected:
    long barcode;
    string name;

public:
    // Constructors
    Product() : barcode(0), name("") {}
    Product(long b, string n) : barcode(b), name(n) {}

    // Getter and setter methods for barcode and name
    void setBarcode(long b) {
        barcode = b;
    }

    void setName(string n) {
        name = n;
    }

    long getBarcode() {
        return barcode;
    }

    string getName() {
        return name;
    }

    // Virtual method for scanner (input)
    virtual void scanner() {
        cout << "\nBarcode: ";
        cin >> barcode;
        cout << "Name: ";
        cin >> name;
    }

    // Virtual method for printer (output)
    virtual void printer() {
        cout << "\nBarcode: " << barcode << "\nName: " << name << endl;
    }

    // Virtual method for calculating price
    virtual double getPrice() {
        return 0; // Base class has no price
    }
};

// Derived class for prepacked food products
class PrepackedFood : public Product {
private:
    int quantity;
    double unitPrice;

public:
    // Constructors
    PrepackedFood() : quantity(0), unitPrice(0) {}
    PrepackedFood(long b, string n, int q, double p) : Product(b, n), quantity(q), unitPrice(p) {}

    // Getter and setter methods for quantity and unit price
    void setQuantity(int q) {
        quantity = q;
    }

    void setUnitPrice(double p) {
        unitPrice = p;
    }

    int getQuantity() {
        return quantity;
    }

    double getUnitPrice() {
        return unitPrice;
    }

    // Override scanner method for additional input
    void scanner() override {
        Product::scanner();
        cout << "Quantity: ";
        cin >> quantity;
        cout << "Price per piece: ";
        cin >> unitPrice;
    }

    // Override printer method for additional output
    void printer() override {
        Product::printer();
        cout << "Quantity: " << quantity << "\nPrice per piece: " << unitPrice << endl;
    }

    // Override getPrice method to calculate total price
    double getPrice() override {
        return quantity * unitPrice;
    }
};

// Derived class for fresh food products
class FreshFood : public Product {
private:
    double weight;
    double pricePerKilo;

public:
    // Constructors
    FreshFood() : weight(0), pricePerKilo(0) {}
    FreshFood(long b, string n, double w, double p) : Product(b, n), weight(w), pricePerKilo(p) {}

    // Getter and setter methods for weight and price per kilo
    void setWeight(double w) {
        weight = w;
    }

    void setPricePerKilo(double p) {
        pricePerKilo = p;
    }

    double getWeight() {
        return weight;
    }

    double getPricePerKilo() {
        return pricePerKilo;
    }

    // Override scanner method for additional input
    void scanner() override {
        Product::scanner();
        cout << "Weight (lbs): ";
        cin >> weight;
        cout << "Price per lb: ";
        cin >> pricePerKilo;
    }

    // Override printer method for additional output
    void printer() override {
        Product::printer();
        cout << "Weight (lbs): " << weight << "\nPrice per lb: " << pricePerKilo << "\nTotal: " << weight * pricePerKilo << endl;
    }

    // Override getPrice method to calculate total price
    double getPrice() override {
        return weight * pricePerKilo;
    }
};

// Function to prompt for next article
void show() {
    cout << "\nWhat is the next article?\n0 = No more article\n1 = Fresh food\n2 = Prepacked article\n?";
}

// Function to record products and calculate total price
void record() {
    // Array of pointers to base class Product
    Product *ptr[100];
    int n, count = 0;

    // Arrays to store objects of derived classes
    FreshFood f[100];
    PrepackedFood p[100];
    int i = 0, j = 0;

    show();
    cin >> n;

    // Loop to record products
    while (n != 0) {
        switch (n) {
            case 1: {
                f[i].scanner();
                ptr[count++] = &f[i];
                i++;
                break;
            }
            case 2: {
                p[j].scanner();
                ptr[count++] = &p[j];
                j++;
                break;
            }
            default:
                cout << "Please enter a valid choice!" << endl;
        }
        show();
        cin >> n;
    }

    double total = 0;

    // Loop to print products and calculate total price
    for (int i = 0; i < count; i++) {
        cout << "---------------------" << endl;
        ptr[i]->printer();
        total += ptr[i]->getPrice();
    }

    cout << "---------------------" << endl;
    cout << "Total Price: " << total << endl;
}

int main() {
    cout << "\nWelcome to the checkout desk" << endl;
    char c;

    // Loop to handle multiple customers
    while (true) {
        cout << "\nAnother customer (y/n)? ";
        cin >> c;
        if (c == 'y' || c == 'Y')
            record();
        else
            break;
    }
    return 0;
}
