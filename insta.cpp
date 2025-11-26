#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include <limits>
#include <ctime>

using namespace std;

// Product Class - Abdelrahman Aymen 
class Product {
private:
    string name;
    double price;
    int quantity;
    string category;

public:
    // Default Constructor
    Product() {
        name = "";
        price = 0;
        quantity = 0;
        category = "";
    }

    // Parametrized Constructor
    Product(string n, double p, int q, string c) {
        name = n;
        price = p;
        quantity = q;
        category = c;
    }

    // Setters
    void setName(string n) { name = n; }
    void setPrice(double p) { price = p; }
    void setQuantity(int q) { quantity = q; }
    void setCategory(string c) { category = c; }

    // Getters
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    string getCategory() const { return category; }

    void reduceQuantity(int amount) {
        if (amount <= quantity) {
            quantity -= amount;
        } else {
            cout << "There's no stock" << endl;
        }
    }

    void displayProduct() const {
        cout << category << endl;
        cout << name
             << " Price: " << fixed << setprecision(2) << price
             << " Qty: " << quantity << endl;
    }
};

// User Class - Moataz Badawy
class User {
private:
    string username;
    string password;
    string address;
    int age;
    double wallet;
    double totalSpent;
    bool isAdmin;

public:
    // Default Constructor
    User() {
        // Generate Random Username (e.g. user-G3)
        string u = "user-";
        char c = 'A' + rand() % 26;
        char d = '0' + rand() % 10;
        u.push_back(c);
        u.push_back(d);

        username = u;
        password = "";
        address = "";
        age = 0;
        wallet = 0;
        totalSpent = 0;
        isAdmin = false;
    }

    // Parametrized Constructor
    User(string u, string pass, string a, int ag, double w, bool admin) {
        username = u;
        password = pass;
        address = a;
        age = ag;
        wallet = w;
        totalSpent = 0;
        isAdmin = admin;
    }

    // Getters
    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getAddress() const { return address; }
    double getWallet() const { return wallet; }
    double getTotalSpent() const { return totalSpent; }
    bool getIsAdmin() const { return isAdmin; }

    void addWallet(double amount) {
        if (amount > 0)
            wallet += amount;
    }

    bool deductWallet(double amount) {
        if (amount > 0 && wallet >= amount) {
            wallet -= amount;
            return true;
        }
        return false;
    }

    void addSpent(double amount) {
        if (amount > 0)
            totalSpent += amount;
    }

    bool isSpecialClient() const {
        return totalSpent >= 10000;
    }

    // Setters
    void setPassword(string p) { password = p; }
    void setAddress(string a) { address = a; }

    // Display user's inofrmation (5. Profile)
    void displayInfo() const {
        cout << "\n===== USER INFO =====" << endl;
        cout << "Username: " << username << endl;
        cout << "Address: " << address << endl;
        cout << "Type: " << (isAdmin ? "ADMIN" : "CUSTOMER") << endl;
        if (!isAdmin) {
            cout << "Wallet: " << fixed << setprecision(2) << wallet << " LE" << endl;
            cout << "Total Spent: " << fixed << setprecision(2) << totalSpent << " LE" << endl;
            cout << "Special Client:  " << (isSpecialClient() ? "YES" : "NO") << endl;
        }
        cout << "===================" << endl;
    }

    // Setters
    void setWallet(double w) { wallet = w; }
    void setTotalSpent(double t) { totalSpent = t; }
};

// Managing the data using File I/O
class FileManager {
public:
    bool saveUser(const User &u) {
        ofstream file("users.txt", ios::app);
        if (!file.is_open())
            return false;
        file << u.getUsername() << "," << u.getPassword() << "," << u.getAddress() << ","
             << 0 << "," << u.getWallet() << "," << u.getTotalSpent() << "," << (u.getIsAdmin() ? 1 : 0) << endl;

        file.close();
        return true;
    }

    bool loadUser(const string &username, User &outUser) {
        ifstream file("users.txt");
        if (!file.is_open())
            return false;

        string line;
        while (getline(file, line)) {
            if (line.empty())
                continue;

            vector<string> parts;
            string cur;
            for (char ch : line) {
                if (ch == ',') {
                    parts.push_back(cur);
                    cur.clear();
                } else {
                    cur.push_back(ch);
                }
            }
            parts.push_back(cur);

            if (parts.size() < 7)
                continue;

            if (parts[0] == username) {
                string uname = parts[0];
                string pass = parts[1];
                string addr = parts[2];
                int age = stoi(parts[3]);
                double wallet = stod(parts[4]);
                double totalSpent = stod(parts[5]);
                bool isAdmin = (parts[6] == "1");

                User u(uname, pass, addr, age, wallet, isAdmin);
                u.setTotalSpent(totalSpent);
                outUser = u;

                file.close();
                return true;
            }
        }

        file.close();
        return false;
    }

    bool updateUser(const User &u) {
        ifstream in("users.txt");
        if (!in.is_open()) return false;
        vector<string> lines;
        string line;
        while (getline(in, line)) {
            lines.push_back(line);
        }
        in.close();

        ofstream out("users_tmp.txt");
        if (!out.is_open()) return false;
        for (string &ln : lines) {
            if (ln.empty()) continue;
            vector<string> parts;
            string cur;
            for (char ch : ln) {
                if (ch == ',') {
                    parts.push_back(cur);
                    cur.clear();
                } else {
                    cur.push_back(ch);
                }
            }
            parts.push_back(cur);

            if (parts.size() < 7) {
                out << ln << "\n";
                continue;
            }

            if (parts[0] == u.getUsername()) {
                out << u.getUsername() << "," << u.getPassword() << "," << u.getAddress() << ","
                    << 0 << "," << u.getWallet() << "," << u.getTotalSpent() << "," << (u.getIsAdmin() ? 1 : 0) << "\n";
            } else {
                out << ln << "\n";
            }
        }
        out.close();

        remove("users.txt");
        rename("users_tmp.txt", "users.txt");
        return true;
    }

    bool saveProducts(const vector<Product> &products) {
        ofstream file("products.txt");
        if (!file.is_open()) return false;
        for (const Product &p : products) {
            file << p.getName() << "|" << p.getPrice() << "|" << p.getQuantity() << "|" << p.getCategory() << "\n";
        }
        file.close();
        return true;
    }

    bool loadProducts(vector<Product> &outProducts) {
        ifstream file("products.txt");
        if (!file.is_open())
            return false;
        outProducts.clear();
        string line;
        while (getline(file, line)) {
            if (line.empty())
                continue;
            vector<string> parts;
            string cur;
            for (char ch : line) {
                if (ch == '|') {
                    parts.push_back(cur);
                    cur.clear();
                } else {
                    cur.push_back(ch);
                }
            }
            parts.push_back(cur);
            if (parts.size() < 4) continue;
            string name = parts[0];
            double price = stod(parts[1]);
            int qty = stoi(parts[2]);
            string cat = parts[3];
            outProducts.push_back(Product(name, price, qty, cat));
        }
        file.close();
        return true;
    }
};

// Cart Class - Mohammed Daly
struct CartItem {
    string name;
    double price;
};
class Cart {
private:
    static const int MAX_ITEMS = 100;
    CartItem products[MAX_ITEMS];
    int quantities[MAX_ITEMS];
    int itemCount;
    double totalPrice;
    bool rushOrder;         // Later
    double rushFee;         // Later
    int discountApplied;    // Later

public:
    // Default Constructor
    Cart() {
        itemCount = 0;
        totalPrice = 0.0;
        rushOrder = false;
        rushFee = 0.0;
        discountApplied = 0;
    }

    bool isEmpty() {
        return itemCount == 0;
    }

    void clear() {
        itemCount = 0;
        totalPrice = 0.0;
        rushOrder = false;
        rushFee = 0.0;
        discountApplied = 0;
    }

    void addProduct(Product &p, int quantity) {
        if (itemCount >= MAX_ITEMS) 
            return;
        
        // Check if product already exists
        for (int i = 0; i < itemCount; i++) {
            if (products[i].name == p.getName()) {
                quantities[i] += quantity;
                return;
            }
        }
        
        // Add new product
        products[itemCount].name = p.getName();
        products[itemCount].price = p.getPrice();
        quantities[itemCount] = quantity;
        itemCount++;
    }

    void removeProduct(string name) {
        for (int i = 0; i < itemCount; i++) {
            if (products[i].name == name) {
                for (int j = i; j < itemCount - 1; j++) {
                    products[j] = products[j + 1];
                    quantities[j] = quantities[j + 1];
                }
                itemCount--;
                return;
            }
        }
    }

    void updateQuantity(string name, int newQty) {
        for (int i = 0; i < itemCount; i++) {
            if (products[i].name == name) {
                quantities[i] = newQty;
                return;
            }
        }
    }

    double calculateTotalPrice() {
        totalPrice = 0.0;
        for (int i = 0; i < itemCount; i++) {
            totalPrice += products[i].price * quantities[i];
        }
        totalPrice -= discountApplied;
        totalPrice += rushFee;
        return totalPrice;
    }

    double getTotal() {
        return calculateTotalPrice();
    }

    // Later
    void setRushOrder(bool r) {
        rushOrder = r;
    }

    // Later
    bool isRushOrder() {
        return rushOrder;
    }

    // Later
    void applyRushOrderFee() {
        if (rushOrder) rushFee = 30.0;
        else rushFee = 0.0;
    }

    // Later
    void applyDiscount(int amount) {
        discountApplied = amount;
    }

    // Display the product selected in the cart
    void display() {
        if (isEmpty()) {
            cout << "Cart is empty.\n";
            return;
        }

        cout << "----- CART -----\n";
        for (int i = 0; i < itemCount; i++) {
            cout << products[i].name
                 << " | Price: " << products[i].price
                 << " | Qty: " << quantities[i] << "\n";
        }
        cout << "Discount: " << discountApplied << "\n";
        cout << "Rush fee: " << rushFee << "\n";
        cout << "Total: " << calculateTotalPrice() << " EGP" << "\n";
        cout << "----------------\n";
    }

    int getItemCount() const {
        return itemCount;
    }

    string getProductName(int index) const {
        if (index >= 0 && index < itemCount)
            return products[index].name;
        return "";
    }

    int getProductQuantity(int index) const {
        if (index >= 0 && index < itemCount)
            return quantities[index];
        return 0;
    }
};

// Payment Class - 
class Payment {
private:
    double walletBalance;
    double totalSpent;
    double amountToPay;
    bool success;

public:
    // Constructor
    Payment(double initialBalance = 0.0) {
        walletBalance = initialBalance;
        totalSpent = 0.0;
        amountToPay = 0.0;
        success = false;
    }

    void displayBalance() const {
        cout << "Your Available balance is " << walletBalance << endl;
    }

    void setAmountToPay(double amount) {
        amountToPay = amount;
    }

    bool checkEnoughBalance() {
        if (amountToPay > walletBalance) {
            return false;
        } else
            return true;
    }

    double getTotalSpent() {
        return totalSpent;
    }

    // Checkout algorithm
    bool buyFromCart() {
        if (!checkEnoughBalance()) {
            cout << "There is not enough balance." << endl;
            success = false;
            return false;
        } else {
            walletBalance -= amountToPay;
            totalSpent += amountToPay;
            success = true;
            cout << "Payment successful." << endl;
            return true;
        }
    }

    // Save the payment to the file
    void save() {
        ofstream file("payment.txt");
        if (!file.is_open()) 
            return;
        file << walletBalance << endl;
        file << totalSpent << endl;
        file.close();
    }

    // Load the payment from the file
    void load() {
        ifstream file("payment.txt");
        if (!file.is_open()) 
            return;
        file >> walletBalance;
        file >> totalSpent;
        file.close();
    }

    // Getters
    double getWalletBalance() { return walletBalance; }
    double getAmountToPay() { return amountToPay; }
};

// Supermarket System - Handling the interface and the operations
class SupermarketSystem {
private:
    vector<Product> products;
    User currentUser;
    Cart cart;
    FileManager fm;

    // Initilizeing some products
    void initProducts() {
        if (!fm.loadProducts(products)) {
            products.push_back(Product("Milk 1L", 20.0, 50, "Dairy"));
            products.push_back(Product("Bread", 5.0, 100, "Bakery"));
            products.push_back(Product("Eggs 6pc", 30.0, 60, "Dairy"));
            products.push_back(Product("Rice 1kg", 40.0, 30, "Grocery"));
            products.push_back(Product("Water 1.5L", 10.0, 200, "Drinks"));
            fm.saveProducts(products);
        }
    }

    void registerUser() {
        string username, password, address;
        int age, type;
        double wallet = 0;

        cout << "\n===== REGISTER =====" << endl;
        cout << "Username: ";
        cin >> username;

        User tmp;
        if (fm.loadUser(username, tmp)) {
            cout << "User already exists!" << endl;
            return;
        }

        cout << "Password: ";
        cin >> password;
        cout << "Address: ";
        getline(cin, address);
        cout << "Age: ";
        cin >> age;

        cout << "User Type (1=Customer, 2=Admin): ";
        cin >> type;

        bool isAdmin = (type == 2);

        if (!isAdmin) {
            cout << "Initial wallet: ";
            cin >> wallet;
        }

        User newUser(username, password, address, age, wallet, isAdmin);

        if (fm.saveUser(newUser)) {
            cout << "Registered!" << endl;
        } else {
            cout << "Failed to save user." << endl;
        }
    }

    void loginUser() {
        string username, password;
        cout << "Username: ";
        cin >> username;

        if (!fm.loadUser(username, currentUser)) {
            cout << "User NOT Found!" << endl;
            return;
        }

        cout << "Password: ";
        cin >> password;

        if (currentUser.getPassword() == password) {
            cout << "Login success!" << endl;
        } else {
            cout << "Wrong password!" << endl;
            currentUser = User();
        }
    }

    void customerShop() {
        while (true) {
            cout << "\n===== SHOP =====" << endl;
            cout << "1. Browse" << endl;
            cout << "2. View Cart" << endl;
            cout << "3. Checkout" << endl;
            cout << "4. Add Wallet" << endl;
            cout << "5. Profile" << endl;
            cout << "6. Logout" << endl;
            cout << "Choice: ";

            int ch;
            cin >> ch;

            switch (ch) {
            // Browse
            case 1: {
                cout << "\n===== PRODUCTS =====" << endl;
                for (int i = 0; i < products.size(); i++) {
                    cout << i + 1 << ". ";
                    products[i].displayProduct();
                }

                cout << "Add product (number, qty): ";
                int num, qty;
                cin >> num >> qty;

                if (num > 0 && num <= products.size()) {
                    if (qty <= products[num - 1].getQuantity())
                        cart.addProduct(products[num - 1], qty);
                    else
                        cout << "Not enough stock available." << endl;
                } else {
                    cout << "Invalid product number." << endl;
                }
                break;
            }

            // View Cart
            case 2: {
                cart.display();
                break;
            }

            // Checkout
            case 3: {
                if (cart.isEmpty()) {
                    cout << "Cart empty!" << endl;
                    break;
                }

                cart.display();
                cout << "Paying via wallet..." << endl;
                Payment p(currentUser.getWallet());
                p.setAmountToPay(cart.getTotal());
                
                if (p.buyFromCart()) {
                    currentUser.setWallet(p.getWalletBalance());
                    
                    // Update product quantities
                    for (int i = 0; i < cart.getItemCount(); i++) {
                        string productName = cart.getProductName(i);
                        int qty = cart.getProductQuantity(i);
                        
                        for (int j = 0; j < (int)products.size(); j++) {
                            if (products[j].getName() == productName) {
                                products[j].reduceQuantity(qty);
                            }
                        }
                    }
                    
                    currentUser.addSpent(cart.getTotal());
                    fm.updateUser(currentUser);
                    fm.saveProducts(products);
                    cart.clear();
                    cout << "Order completed!" << endl;
                } else {
                    cout << "Not enough balance in wallet!" << endl;
                }
                break;
            }

            case 4: {
                double amt;
                cout << "Amount: ";
                cin >> amt;
                if (amt > 0) {
                    currentUser.addWallet(amt);
                    fm.updateUser(currentUser);
                    cout << "Updated!" << endl;
                } else {
                    cout << "Invalid amount." << endl;
                }
                break;
            }

            case 5: {
                currentUser.displayInfo();
                break;
            }

            case 6: {
                cout << "Logged Out" << endl;
                currentUser = User();
                cart.clear();
                return;
            }

            default:
                cout << "Invalid Choice!" << endl;
            }
        }
    }

    void adminPanel() {
        while (true) {
            cout << "\n===== ADMIN =====" << endl;
            cout << "1. View Products" << endl;
            cout << "2. Add Product" << endl;
            cout << "3. Edit Price" << endl;
            cout << "4. Remove Product" << endl;
            cout << "5. Profile" << endl;
            cout << "6. Logout" << endl;
            cout << "Choice: ";

            int ch;
            cin >> ch;

            switch (ch) {
            case 1: {
                cout << "\n===== ALL PRODUCTS =====" << endl;
                for (int i = 0; i < (int)products.size(); i++) {
                    cout << (i + 1) << ". ";
                    products[i].displayProduct();
                }
                break;
            }
            case 2: {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                string name, cat;
                double price;
                int qty;
                cout << "Name: ";
                getline(cin, name);
                cout << "Price: ";
                cin >> price;
                cout << "Quantity: ";
                cin >> qty;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Category: ";
                getline(cin, cat);

                products.push_back(Product(name, price, qty, cat));
                fm.saveProducts(products);
                cout << "Added!" << endl;
                break;
            }
            case 3: {
                int num;
                double newPrice;

                cout << "Product number: ";
                cin >> num;
                cout << "New price: ";
                cin >> newPrice;
                if (num > 0 && num <= (int)products.size()) {
                    products[num - 1].setPrice(newPrice);
                    fm.saveProducts(products);
                    cout << "Updated!" << endl;
                } else {
                    cout << "Invalid Product!" << endl;
                }
                break;
            }
            case 4: {
                int num;
                cout << "Product number: ";
                cin >> num;
                if (num > 0 && num <= (int)products.size()) {
                    products.erase(products.begin() + num - 1);
                    fm.saveProducts(products);
                    cout << "Removed!" << endl;
                } else {
                    cout << "Invalid Product!" << endl;
                }
                break;
            }
            case 5: {
                currentUser.displayInfo();
                break;
            }
            case 6: {
                cout << "Logged Out!" << endl;
                currentUser = User();
                return;
            }
            default:
                cout << "Invalid Choice!" << endl;
            }
        }
    }

public:
    SupermarketSystem() {
        initProducts();
    }

    void run() {
        while (true) {
            cout << "\n========== SUPERMARKET ==========" << endl;
            cout << "1. Register" << endl;
            cout << "2. Login" << endl;
            cout << "3. Exit" << endl;
            cout << "Choice: ";

            int ch;
            cin >> ch;

            if (ch == 1) {
                registerUser();
            } else if (ch == 2) {
                loginUser();
                if (currentUser.getUsername() != "") {
                    if (currentUser.getIsAdmin())
                        adminPanel();
                    else
                        customerShop();
                }
            } else if (ch == 3) {
                cout << "Thank you for shoping with us today!" << endl;
                break;
            } else {
                cout << "Invalid choice." << endl;
            }
        }
    }
};

int main() {
    srand(time(0));
    SupermarketSystem system;
    system.run();

    return 0;
}