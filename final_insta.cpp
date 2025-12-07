#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

using namespace std;

/// Prouct Classes - ABDELRAHMAN ///
// Product variables
struct ProductData {
    string name;
    double price;
    int quantity;
    string category;
};

// Product Class
class Product {
public:
    ProductData data;

    // Default Constructor
    Product() {
        data.name = "";
        data.price = 0.0;
        data.quantity = 0;
        data.category = "";
    }

    // Parametriezed Constructor
    Product(string n, double p, int q, string c) {
        data.name = n;
        data.price = p;
        data.quantity = q;
        data.category = c;
    }

    // Reduce Quantity Function
    void reduceQuantity(int amount) {
        if (amount <= data.quantity) {
            data.quantity -= amount;
        } else {
            cout << "There's no stock" << endl;
        }
    }

    // Dispaly product information
    void displayProduct() const {
        cout << data.category << endl;
        cout << data.name
             << " Price: " << fixed << setprecision(2) << data.price
             << " Qty: " << data.quantity << endl;
    }
};

// All Products Class 
class AllProducts {
public:
    Product* products;
    int size;
    int capacity;

    // Constructor and Destructor
    AllProducts() {
        capacity = 10;
        size = 0;
        products = new Product[capacity];
    }

    ~AllProducts() {
        delete[] products;
    }

    // Resize the Capacity of the products
    void resize() {
        capacity *= 2;
        Product* newProducts = new Product[capacity];
        for (int i = 0; i < size; i++) {
            newProducts[i] = products[i];
        }
        delete[] products;
        products = newProducts;
    }

    // Add Product Function
    void addProduct(Product p) {
        if (size >= capacity) {
            resize();
        }
        products[size++] = p;
    }

    // Remove Product Function
    void removeProduct(int index) {
        if (index < 0 || index >= size) {
            cout << "Invalid index" << endl;
            return;
        }

        for (int i = index; i < size - 1; i++) {
            products[i] = products[i + 1];
        }
        size--;
    }

    // Get the product index
    Product* getProduct(int index) {
        if (index >= 0 && index < size)
            return &products[index];
        return nullptr;
    }

    // Display All products
    void displayAll() {
        for (int i = 0; i < size; i++) {
            cout << i + 1 << ". ";
            products[i].displayProduct();
        }
    }
};

/// Wallet Class - OMAR ///
// Wallet Struct
struct WalletInfo {
    double walletBalance;
    double totalSpent;
};

// Wallet Class
class Wallet {
public:
    WalletInfo data;

    Wallet(double initialBalance = 0.0) {
        data.walletBalance = initialBalance;
        data.totalSpent = 0.0;
    }

    void displayBalance() const {
        cout << "Balance: " << data.walletBalance << " LE" << endl;
        cout << "Total Spent: " << data.totalSpent << " LE" << endl;
    }

    bool EnoughBalance(double amount) const {
        return amount > 0 && amount <= data.walletBalance;
    }

    // Checkout algorithm
    bool buyFromCart(double amount) {
        if (!EnoughBalance(amount)) {
            return false;
        } else {
            data.walletBalance -= amount;
            data.totalSpent += amount;
            return true;
        }
    }

    // Adding money to the wallet
    void addFunds(double amount) {
        if (amount > 0) {
            data.walletBalance += amount;
        }
    }

    // Save the payment to the file
    void save() {
        ofstream file("payment.txt");
        if (!file.is_open()) 
            return;
        file << data.walletBalance << endl;
        file << data.totalSpent << endl;
        file.close();
    }

    // Load the payment from the file
    void load() {
        ifstream file("payment.txt");
        if (!file.is_open()) 
            return;
        file >> data.walletBalance;
        file >> data.totalSpent;
        file.close();
    }
};

/// User Classes - MOATAZ ///
// User Struct
struct UserData {
    string username;
    string password;
    string address;
    int age;
    bool isAdmin;
};

// User Class
class User {
public:
    UserData data;
    Wallet wallet;

    User() : wallet(0.0) {
        data.username = "";
        data.password = "";
        data.address = "";
        data.age = 0;
        data.isAdmin = false;
    }

    User(string u, string pass, string a, int ag, double w, bool admin) : wallet(w) {
        data.username = u;
        data.password = pass;
        data.address = a;
        data.age = ag;
        data.isAdmin = admin;
    }

    // Check if the user is a special client
    bool isSpecialClient() const {
        return wallet.data.totalSpent >= 1000;
    }

    // Display User's information
    void displayInfo() const {
        cout << "\n===== USER INFO =====" << endl;
        cout << "Username: " << data.username << endl;
        cout << "Address: " << data.address << endl;
        cout << "Type: " << (data.isAdmin ? "ADMIN" : "CUSTOMER") << endl;
        if (!data.isAdmin) {
            wallet.displayBalance();
            cout << "Special Client: " << (isSpecialClient() ? "YES" : "NO") << endl;
        }
        cout << "===================" << endl;
    }
};

// All Users Class
class AllUsers {
public:
    User* users;
    int size;
    int capacity;

    AllUsers() {
        capacity = 10;
        size = 0;
        users = new User[capacity];
        loadFromFile();
    }

    ~AllUsers() {
        delete[] users;
    }

    // Resize user's capacity
    void resize() {
        capacity *= 2;
        User* newUsers = new User[capacity];
        for (int i = 0; i < size; i++) {
            newUsers[i] = users[i];
        }
        delete[] users;
        users = newUsers;
    }

    // Add user
    void addUser(User u) {
        if (size >= capacity) {
            resize();
        }
        users[size++] = u;
    }

    // Search for the user
    User* findUser(string username) {
        for (int i = 0; i < size; i++) {
            if (users[i].data.username == username) {
                return &users[i];
            }
        }
        return nullptr;
    }

    // Check if the user exists
    bool userExists(string username) {
        return findUser(username) != nullptr;
    }

    // Save users to the file.
    void saveToFile() {
        ofstream file("users.txt");
        if (!file.is_open()) return;

        for (int i = 0; i < size; i++) {
            file << users[i].data.username << ","
                 << users[i].data.password << ","
                 << users[i].data.address << ","
                 << users[i].data.age << ","
                 << users[i].wallet.data.walletBalance << ","
                 << users[i].wallet.data.totalSpent << ","
                 << (users[i].data.isAdmin ? 1 : 0) << endl;
        }
        file.close();
    }

    // Load users from the file.
    void loadFromFile() {
        ifstream file("users.txt");
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            string* parts = new string[7];
            int partCount = 0;
            string cur;

            // Get user's information from the CSV line.
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == ',') {
                    parts[partCount++] = cur;
                    cur.clear();
                } else {
                    cur += line[i];
                }
            }
            parts[partCount++] = cur;

            // Assign the information to the user class
            if (partCount >= 7) {
                User u(parts[0], parts[1], parts[2], 
                       atoi(parts[3].c_str()), 
                       atof(parts[4].c_str()), 
                       parts[6] == "1");
                u.wallet.data.totalSpent = atof(parts[5].c_str());
                addUser(u);
            }

            delete[] parts;
        }
        file.close();
    }
};

// File Manager for Products
class ProductFileManager {
public:
    // Save products in pipe separated file
    void saveProducts(AllProducts& allProducts) {
        ofstream file("products.txt");
        if (!file.is_open()) return;

        for (int i = 0; i < allProducts.size; i++) {
            file << allProducts.products[i].data.name << "|"
                 << allProducts.products[i].data.price << "|"
                 << allProducts.products[i].data.quantity << "|"
                 << allProducts.products[i].data.category << "\n";
        }
        file.close();
    }

    // Load Products from the file
    void loadProducts(AllProducts& allProducts) {
        ifstream file("products.txt");
        if (!file.is_open()) return;

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            string* parts = new string[4];
            int partCount = 0;
            string cur;

            // Get the data from the PSV file
            for (int i = 0; i < line.length(); i++) {
                if (line[i] == '|') {
                    parts[partCount++] = cur;
                    cur.clear();
                } else {
                    cur += line[i];
                }
            }
            parts[partCount++] = cur;

            // Assing the product information to the product class.
            if (partCount >= 4) {
                Product p(parts[0], atof(parts[1].c_str()), 
                         atoi(parts[2].c_str()), parts[3]);
                allProducts.addProduct(p);
            }

            delete[] parts;
        }
        file.close();
    }
};

/// Cart Class - DALY ///
// Cart Item Struct
struct CartItemData {
    string name;
    double price;
    int quantity;
};

// Cart Class
class Cart {
public:
    CartItemData* items;
    int size;
    int capacity;
    double discountApplied;

    Cart() {
        capacity = 100;
        size = 0;
        items = new CartItemData[capacity];
        discountApplied = 0;
    }

    ~Cart() {
        delete[] items;
    }

    bool isEmpty() {
        return size == 0;
    }

    void clear() {
        size = 0;
        discountApplied = 0;
    }

    // Add a product to the cart
    void addProduct(Product& p, int quantity) {
        // Check if product already exists
        for (int i = 0; i < size; i++) {
            if (items[i].name == p.data.name) {
                items[i].quantity += quantity;
                return;
            }
        }

        // Add new product
        if (size < capacity) {
            items[size].name = p.data.name;
            items[size].price = p.data.price;
            items[size].quantity = quantity;
            size++;
        }
    }

    // Calculate the total amount
    double calculateTotal() {
        double total = 0.0;
        for (int i = 0; i < size; i++) {
            total += items[i].price * items[i].quantity;
        }
        total -= discountApplied;
        return total;
    }

    // Display the cart
    void display() {
        if (isEmpty()) {
            cout << "Cart is empty.\n";
            return;
        }

        cout << "----- CART -----\n";
        for (int i = 0; i < size; i++) {
            cout << items[i].name
                 << " | Price: " << items[i].price
                 << " | Qty: " << items[i].quantity << "\n";
        }
        cout << "Discount: " << discountApplied << "\n";
        cout << "Total: " << calculateTotal() << " EGP\n";
        cout << "----------------\n";
    }
};

// Supermarket System
class SupermarketSystem {
private:
    AllProducts allProducts;
    AllUsers allUsers;
    ProductFileManager productFM;
    User* currentUser;
    Cart cart;

    // Intialize some products
    void initProducts() {
        productFM.loadProducts(allProducts);
        if (allProducts.size == 0) {
            allProducts.addProduct(Product("Milk 1L", 20.0, 50, "Dairy"));
            allProducts.addProduct(Product("Bread", 5.0, 100, "Bakery"));
            allProducts.addProduct(Product("Eggs 6pc", 30.0, 60, "Dairy"));
            allProducts.addProduct(Product("Rice 1kg", 40.0, 30, "Grocery"));
            allProducts.addProduct(Product("Water 1.5L", 10.0, 200, "Drinks"));
            productFM.saveProducts(allProducts);
        }
    }

    // Register user funcion
    void registerUser() {
        string username, password, address;
        int age, type;
        double wallet = 0;

        cout << "\n===== REGISTER =====" << endl;
        cout << "Username: ";
        cin >> username;

        // Check if user exists
        if (allUsers.userExists(username)) {
            cout << "User already exists!" << endl;
            return;
        }

        cout << "Password: ";
        cin >> password;
        cin.ignore();
        cout << "Address: ";
        getline(cin, address);
        cout << "Age: ";
        cin >> age;

        cout << "User Type (1=Customer, 2=Admin): ";
        cin >> type;

        bool isAdmin = (type == 2);

        // Ask for the wallet amount if the user is a customer
        if (!isAdmin) {
            cout << "Initial wallet: ";
            cin >> wallet;
        }

        User newUser(username, password, address, age, wallet, isAdmin);
        allUsers.addUser(newUser);
        allUsers.saveToFile();
        cout << "Registered!" << endl;
    }

    // Login user function
    void loginUser() {
        string username, password;
        cout << "\n===== LOGIN =====" << endl;
        cout << "Username: ";
        cin >> username;

        // Search for the user in the file
        currentUser = allUsers.findUser(username);
        if (currentUser == nullptr) {
            cout << "User NOT Found!" << endl;
            return;
        }

        cout << "Password: ";
        cin >> password;

        // Match the passwords
        if (currentUser->data.password == password) {
            cout << "Login success!" << endl;
        } else {
            cout << "Wrong password!" << endl;
            currentUser = nullptr;
        }
    }

    // Customer Menu //
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
            // Browse Products
            case 1: {
                cout << "\n===== PRODUCTS =====" << endl;
                allProducts.displayAll();

                cout << "Add product (number, qty): ";
                int num, qty;
                cin >> num >> qty;

                // Add a product to the cart
                if (num > 0 && num <= allProducts.size) {
                    Product* p = allProducts.getProduct(num - 1);
                    if (p != nullptr && qty <= p->data.quantity) {
                        cart.addProduct(*p, qty);
                        cout << "Added to cart!" << endl;
                    } else {
                        cout << "Not enough stock available." << endl;
                    }
                } else {
                    cout << "Invalid product number." << endl;
                }
                break;
            }

            // View cart
            case 2: {
                cart.display();
                break;
            }

            // Checkout the cart
            case 3: {
                if (cart.isEmpty()) {
                    cout << "Cart empty!" << endl;
                    break;
                }

                cart.display();
                double total = cart.calculateTotal();
                
                cout << "Paying via wallet..." << endl;
                
                // If the payment is successful and there is enought balance
                if (currentUser->wallet.EnoughBalance(total)) {
                    if (currentUser->wallet.buyFromCart(total)) {
                        // Update product quantities
                        for (int i = 0; i < cart.size; i++) {
                            for (int j = 0; j < allProducts.size; j++) {
                                if (allProducts.products[j].data.name == cart.items[i].name) {
                                    allProducts.products[j].reduceQuantity(cart.items[i].quantity);
                                }
                            }
                        }

                        // Save the changes in the file.
                        allUsers.saveToFile();
                        productFM.saveProducts(allProducts);
                        cart.clear();
                        cout << "Payment successful!" << endl;
                        cout << "Order completed!" << endl;
                    } else {
                        cout << "Payment failed!" << endl;
                    }
                } else {
                    cout << "Not enough balance in wallet!" << endl;
                }
                break;
            }

            // Add amount to the wallet
            case 4: {
                double amt;
                cout << "Amount: ";
                cin >> amt;
                if (amt > 0) {
                    currentUser->wallet.addFunds(amt);
                    allUsers.saveToFile();
                    cout << "Wallet Updated!" << endl;
                } else {
                    cout << "Invalid amount." << endl;
                }
                break;
            }

            // Display user's profile
            case 5: {
                currentUser->displayInfo();
                break;
            }

            // Logout
            case 6: {
                cout << "Logged Out" << endl;
                currentUser = nullptr;
                cart.clear();
                return;
            }

            default:
                cout << "Invalid Choice!" << endl;
            }
        }
    }

    // Admin Menu // 
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
            // view current products
            case 1: {
                cout << "\n===== ALL PRODUCTS =====" << endl;
                if (allProducts.size == 0) {
                    cout << "No products available." << endl;
                } else {
                    allProducts.displayAll();
                }
                break;
            }

            // Add products to the warehouse
            case 2: {
                string name, cat;
                double price;
                int qty;
                cin.ignore();
                cout << "Name: ";
                getline(cin, name);
                cout << "Price: ";
                cin >> price;
                cout << "Quantity: ";
                cin >> qty;
                cin.ignore();
                cout << "Category: ";
                getline(cin, cat);

                allProducts.addProduct(Product(name, price, qty, cat));
                productFM.saveProducts(allProducts);
                cout << "Product Added!" << endl;
                break;
            }

            // Edit the price
            case 3: {
                int num;
                double newPrice;
                cout << "Product number: ";
                cin >> num;
                
                if (num > 0 && num <= allProducts.size) {
                    cout << "New price: ";
                    cin >> newPrice;
                    allProducts.products[num - 1].data.price = newPrice;
                    productFM.saveProducts(allProducts);
                    cout << "Price Updated!" << endl;
                } else {
                    cout << "Invalid Product!" << endl;
                }
                break;
            }

            // Remove Products
            case 4: {
                int num;
                cout << "Product number: ";
                cin >> num;
                if (num > 0 && num <= allProducts.size) {
                    allProducts.removeProduct(num - 1);
                    productFM.saveProducts(allProducts);
                    cout << "Product Removed!" << endl;
                } else {
                    cout << "Invalid Product!" << endl;
                }
                break;
            }

            // Display Admin's Profile
            case 5: {
                currentUser->displayInfo();
                break;
            }

            // Log out
            case 6: {
                cout << "Logged Out!" << endl;
                currentUser = nullptr;
                return;
            }

            default:
                cout << "Invalid Choice!" << endl;
            }
        }
    }

public:
    SupermarketSystem() {
        currentUser = nullptr;
        initProducts();
    }

    // Code runner
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
                if (currentUser != nullptr) {
                    if (currentUser->data.isAdmin)
                        adminPanel();
                    else
                        customerShop();
                }
            } else if (ch == 3) {
                cout << "Thank you for shopping with us today!" << endl;
                break;
            } else {
                cout << "Invalid choice." << endl;
            }
        }
    }
};

int main() {
    SupermarketSystem system;
    system.run();

    return 0;
}