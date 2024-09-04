#include<iostream>
#include<vector>
using namespace std;

class Products {
    int id;
    string product_name;
    double price;
public:
    Products() : id(0), product_name(""), price(0.0) {}

    void acceptProduct() {
        cout << "Enter id: ";
        cin >> id;
        cout << "Enter product name: ";
        cin >> product_name;
        cout << "Enter price: ";
        cin >> price;  // Corrected this line
    }

    void displayProduct() {
        cout << "\nid: " << id << endl;
        cout << "product name: " << product_name << endl;
        cout << "price: " << price << endl;
    }

    string getProductName() {  // Fixed typo in function name
        return product_name;
    }
};

class Person {
    string name;
public:
    Person() : name("") {}

    virtual void acceptPerson() {
        cout << "Enter Person name: ";
        cin >> name;
    }

    void displayPerson() {
        cout << "\nPerson name: " << name << endl;
    }

    string getName() {
        return name;
    }

    virtual void purchaseProduct(Products p) = 0;
    virtual void displayPurchasedProduct() = 0;
};

class Customer : public Person {
    long long mobile;
    vector<Products> purchasedProduct;
public:
    Customer() : mobile(0) {}

    void purchaseProduct(Products p) override {
        purchasedProduct.push_back(p);
    }

    void displayPurchasedProduct(){
        for(int i = 0; i < purchasedProduct.size(); i++){
            purchasedProduct[i].displayProduct();
        }
    }

    void acceptPerson(){
        Person::acceptPerson();
        cout << "Enter mobile no: ";
        cin >> mobile;
    }
};

// Display menu
int menu() {
    cout << "\n1. Display all products" << endl;
    cout << "2. New Customer" << endl;
    cout << "3. New product" << endl;
    cout << "4. Purchase product" << endl;
    cout << "5. Display all products purchased by customer" << endl;
    cout << "6. End program" << endl;
    int option;
    cout << "Choose option: ";
    cin >> option;
    return option;
}

void purchaseProduct(vector<Products>& prodArr, vector<Person*>& cusArr) {
    string name;
    Person* ptr = nullptr;

    cout << "Enter customer name: ";
    cin >> name;

    for (int i = 0; i < cusArr.size(); i++) {
        if (cusArr[i]->getName() == name) {
            ptr = cusArr[i];
            break;
        }
    }
    if (ptr == nullptr) {
        cout << "Customer not found" << endl;
        return;
    }

    int end = 1;
    while (end) {
        if(prodArr.size() == 0){
            cout << "No product added yet" << endl;
            break;
        }
        cout << "Purchase product: " << endl;
        for (int i = 0; i < prodArr.size(); i++) {
            cout << i + 1 << ". " << prodArr[i].getProductName() << endl;
        }

        cout << prodArr.size() + 1 << ". Exit" << endl;
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == prodArr.size() + 1) {
            end = 0;
        } else if (choice > 0 && choice <= prodArr.size()) {
            ptr->purchaseProduct(prodArr[choice - 1]); 
        } else {
            cout << "Invalid choice!" << endl;
        }
    }
}



void displayPurchasedProduct(vector<Person*> cusArr) {
    string name;
    Person* ptr = nullptr;

    cout << "Enter customer name: ";
    cin >> name;

    for (int i = 0; i < cusArr.size(); i++) {
        if (cusArr[i]->getName() == name) {
            ptr = cusArr[i];
            ptr->displayPurchasedProduct();
            break;
        }
    }
    if (ptr == nullptr) {
        cout << "Customer not found" << endl;
        return;
    }

}

int main() {
    vector<Person*> cusArr;
    vector<Products> prodArr;
    Person* ptr = nullptr;
    Products c;  
    
    int end = 1;  // for ending the program if end = 0 program ends
    while (end) {
        int option = menu();  // get option from menu
        switch (option) {
        case 1:
            cout << "All products details: " << endl;
            for (int i = 0; i < prodArr.size(); i++) {
                prodArr[i].displayProduct();
            }
            break;

        case 2:
            ptr = new Customer;
            ptr->acceptPerson();
            cusArr.push_back(ptr);
            break;

        case 3:
            c.acceptProduct();  
            prodArr.push_back(c);
            break;

        case 4:
            purchaseProduct(prodArr, cusArr);
            break;

        case 5:
            displayPurchasedProduct(cusArr);
            break;

        case 6:
            end = 0;
            cout << "Ending program ..." << endl;
            break;

        default:
            cout << "Invalid option!" << endl;
            break;
        }
    }



    return 0;
}

