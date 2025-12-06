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
        cout << "Balance: " << fixed << setprecision(2) << data.walletBalance << " LE" << endl;
        cout << "Total Spent: " << fixed << setprecision(2) << data.totalSpent << " LE" << endl;
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
        cout << "\n========================================" << endl;
        cout << "            👤 USER PROFILE              " << endl;
        cout << "========================================" << endl;
        cout << "Username      : " << data.username << endl;
        cout << "Address       : " << data.address << endl;
        cout << "Account Type  : " << (data.isAdmin ? "ADMIN" : "CUSTOMER") << endl;
        if (!data.isAdmin) {
            cout << "----------------------------------------" << endl;
            wallet.displayBalance();
            cout << "Special Client: " << (isSpecialClient() ? "YES" : "NO") << endl;
        }
        cout << "========================================\n" << endl;
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
            cout << "\n🛒 Your cart is empty.\n";
            return;
        }

        cout << "\n========================================" << endl;
        cout << "           🛒 YOUR CART                 " << endl;
        cout << "========================================" << endl;
        for (int i = 0; i < size; i++) {
            cout << (i + 1) << ". " << items[i].name
                 << "\n   Price: " << fixed << setprecision(2) << items[i].price << " EGP"
                 << " | Qty: " << items[i].quantity
                 << " | Subtotal: " << (items[i].price * items[i].quantity) << " EGP\n";
        }
        cout << "----------------------------------------" << endl;
        if (discountApplied > 0) {
            cout << "Discount Applied: -" << discountApplied << " EGP" << endl;
        }
        cout << "TOTAL: " << fixed << setprecision(2) << calculateTotal() << " EGP" << endl;
        cout << "========================================\n" << endl;
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

        cout << "\n========================================" << endl;
        cout << "          📝 USER REGISTRATION          " << endl;
        cout << "========================================" << endl;
        cout << "Username: ";
        cin >> username;

        // Check if user exists
        if (allUsers.userExists(username)) {
            cout << "\n❌ Error: Username already exists!" << endl;
            cout << "Please try a different username.\n" << endl;
            return;
        }

        cout << "Password: ";
        cin >> password;
        cin.ignore();
        cout << "Address: ";
        getline(cin, address);
        cout << "Age: ";
        cin >> age;

        cout << "\nSelect Account Type:" << endl;
        cout << "  1 - Customer" << endl;
        cout << "  2 - Admin" << endl;
        cout << "Choice: ";
        cin >> type;

        bool isAdmin = (type == 2);

        // Ask for the wallet amount if the user is a customer
        if (!isAdmin) {
            cout << "Initial Wallet Balance (EGP): ";
            cin >> wallet;
        }

        User newUser(username, password, address, age, wallet, isAdmin);
        allUsers.addUser(newUser);
        allUsers.saveToFile();
        
        cout << "\n✅ Registration successful!" << endl;
        cout << "Welcome, " << username << "! You can now login.\n" << endl;
    }

    // Login user function
    void loginUser() {
        string username, password;
        
        cout << "\n========================================" << endl;
        cout << "            🔐 USER LOGIN               " << endl;
        cout << "========================================" << endl;
        cout << "Username: ";
        cin >> username;

        // Search for the user in the file
        currentUser = allUsers.findUser(username);
        if (currentUser == nullptr) {
            cout << "\n❌ Error: User not found!" << endl;
            cout << "Please check your username or register first.\n" << endl;
            return;
        }

        cout << "Password: ";
        cin >> password;

        // Match the passwords
        if (currentUser->data.password == password) {
            cout << "\n✅ Login successful!" << endl;
            cout << "Welcome back, " << username << "!\n" << endl;
        } else {
            cout << "\n❌ Error: Incorrect password!" << endl;
            cout << "Please try again.\n" << endl;
            currentUser = nullptr;
        }
    }

    // Customer Menu //
    void customerShop() {
        int ch;
        do {
            cout << "\n========================================" << endl;
            cout << "          🛍️  CUSTOMER MENU             " << endl;
            cout << "========================================" << endl;
            cout << "1. Browse Products" << endl;
            cout << "2. View Cart" << endl;
            cout << "3. Checkout" << endl;
            cout << "4. Add Funds to Wallet" << endl;
            cout << "5. View Profile" << endl;
            cout << "6. Logout" << endl;
            cout << "========================================" << endl;
            cout << "Enter your choice (1-6): ";
            cin >> ch;

            switch (ch) {
            // Browse Products by Category
            case 1: {
                if (allProducts.size == 0) {
                    cout << "\nNo products available at the moment.\n" << endl;
                    break;
                }

                // Get unique categories
                string* categories = new string[allProducts.size];
                int categoryCount = 0;
                
                for (int i = 0; i < allProducts.size; i++) {
                    bool found = false;
                    for (int j = 0; j < categoryCount; j++) {
                        if (categories[j] == allProducts.products[i].data.category) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        categories[categoryCount++] = allProducts.products[i].data.category;
                    }
                }

                // Display categories
                cout << "\n========================================" << endl;
                cout << "          📂 PRODUCT CATEGORIES         " << endl;
                cout << "========================================" << endl;
                for (int i = 0; i < categoryCount; i++) {
                    cout << (i + 1) << ". " << categories[i] << endl;
                }
                cout << "0. Go Back" << endl;
                cout << "========================================" << endl;
                cout << "Select category: ";
                
                int catChoice;
                cin >> catChoice;
                
                if (catChoice == 0) {
                    delete[] categories;
                    break;
                }
                
                if (catChoice < 1 || catChoice > categoryCount) {
                    cout << "\n❌ Invalid category!\n" << endl;
                    delete[] categories;
                    break;
                }
                
                string selectedCategory = categories[catChoice - 1];
                delete[] categories;
                
                // Display products in selected category
                cout << "\n========================================" << endl;
                cout << "       📦 " << selectedCategory << " PRODUCTS" << endl;
                cout << "========================================" << endl;
                
                int* productIndices = new int[allProducts.size];
                int productCount = 0;
                
                for (int i = 0; i < allProducts.size; i++) {
                    if (allProducts.products[i].data.category == selectedCategory) {
                        productIndices[productCount] = i;
                        cout << (productCount + 1) << ". ";
                        cout << allProducts.products[i].data.name
                             << " - Price: " << fixed << setprecision(2) 
                             << allProducts.products[i].data.price << " EGP"
                             << " | Stock: " << allProducts.products[i].data.quantity << endl;
                        productCount++;
                    }
                }
                
                if (productCount == 0) {
                    cout << "No products in this category." << endl;
                    delete[] productIndices;
                    break;
                }
                
                cout << "========================================" << endl;
                cout << "\nEnter product number (0 to cancel): ";
                int num;
                cin >> num;
                
                if (num == 0) {
                    cout << "Cancelled.\n";
                    delete[] productIndices;
                    break;
                }
                
                if (num < 1 || num > productCount) {
                    cout << "\n❌ Invalid product number!\n" << endl;
                    delete[] productIndices;
                    break;
                }
                
                cout << "Enter quantity: ";
                int qty;
                cin >> qty;
                
                int actualIndex = productIndices[num - 1];
                Product* p = allProducts.getProduct(actualIndex);
                
                if (p != nullptr && qty > 0 && qty <= p->data.quantity) {
                    cart.addProduct(*p, qty);
                    cout << "\n✅ " << qty << "x " << p->data.name << " added to cart!\n" << endl;
                } else if (qty <= 0) {
                    cout << "\n❌ Invalid quantity!\n" << endl;
                } else {
                    cout << "\n❌ Not enough stock! Available: " << p->data.quantity << "\n" << endl;
                }
                
                delete[] productIndices;
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
                    cout << "\n⚠️  Your cart is empty!" << endl;
                    cout << "Please add some products first.\n" << endl;
                    break;
                }

                cart.display();
                double total = cart.calculateTotal();
                
                cout << "Do you want to proceed with payment? (y/n): ";
                char confirm;
                cin >> confirm;
                
                if (confirm != 'y' && confirm != 'Y') {
                    cout << "Checkout cancelled.\n" << endl;
                    break;
                }
                
                cout << "\n💳 Processing payment via wallet..." << endl;
                
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
                        
                        cout << "\n✅ Payment successful!" << endl;
                        cout << "🎉 Order completed! Thank you for shopping with us!" << endl;
                        cout << "New Balance: " << fixed << setprecision(2) 
                             << currentUser->wallet.data.walletBalance << " EGP\n" << endl;
                    } else {
                        cout << "\n❌ Payment failed! Please try again.\n" << endl;
                    }
                } else {
                    cout << "\n❌ Insufficient balance!" << endl;
                    cout << "Your Balance: " << fixed << setprecision(2) 
                         << currentUser->wallet.data.walletBalance << " EGP" << endl;
                    cout << "Required: " << fixed << setprecision(2) << total << " EGP" << endl;
                    cout << "Please add funds to your wallet.\n" << endl;
                }
                break;
            }

            // Add amount to the wallet
            case 4: {
                cout << "\n========================================" << endl;
                cout << "         💰 ADD FUNDS TO WALLET         " << endl;
                cout << "========================================" << endl;
                cout << "Current Balance: " << fixed << setprecision(2) 
                     << currentUser->wallet.data.walletBalance << " EGP" << endl;
                cout << "----------------------------------------" << endl;
                cout << "Enter amount to add (EGP): ";
                double amt;
                cin >> amt;
                
                if (amt > 0) {
                    currentUser->wallet.addFunds(amt);
                    allUsers.saveToFile();
                    cout << "\n✅ Funds added successfully!" << endl;
                    cout << "New Balance: " << fixed << setprecision(2) 
                         << currentUser->wallet.data.walletBalance << " EGP\n" << endl;
                } else {
                    cout << "\n❌ Invalid amount! Please enter a positive value.\n" << endl;
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
                cout << "\n👋 Logging out..." << endl;
                cout << "Thank you for visiting! See you soon.\n" << endl;
                currentUser = nullptr;
                cart.clear();
                return;
            }

            default:
                cout << "\n❌ Invalid choice! Please enter a number between 1 and 6.\n" << endl;
            }
        } while (ch != 6);
    }

    // Admin Menu // 
    void adminPanel() {
        int ch;
        do {
            cout << "\n========================================" << endl;
            cout << "          🔧 ADMIN PANEL                " << endl;
            cout << "========================================" << endl;
            cout << "1. View All Products" << endl;
            cout << "2. Add New Product" << endl;
            cout << "3. Edit Product Price" << endl;
            cout << "4. Remove Product" << endl;
            cout << "5. View Profile" << endl;
            cout << "6. Logout" << endl;
            cout << "========================================" << endl;
            cout << "Enter your choice (1-6): ";
            cin >> ch;

            switch (ch) {
            // view current products
            case 1: {
                cout << "\n========================================" << endl;
                cout << "          📋 ALL PRODUCTS               " << endl;
                cout << "========================================" << endl;
                if (allProducts.size == 0) {
                    cout << "No products in inventory." << endl;
                } else {
                    allProducts.displayAll();
                    cout << "\nTotal Products: " << allProducts.size << endl;
                }
                cout << "========================================\n" << endl;
                break;
            }

            // Add products to the warehouse
            case 2: {
                string name, cat;
                double price;
                int qty;
                
                cout << "\n========================================" << endl;
                cout << "          ➕ ADD NEW PRODUCT            " << endl;
                cout << "========================================" << endl;
                
                cin.ignore();
                cout << "Product Name: ";
                getline(cin, name);
                cout << "Price (EGP): ";
                cin >> price;
                cout << "Quantity: ";
                cin >> qty;
                cin.ignore();
                cout << "Category: ";
                getline(cin, cat);

                if (price > 0 && qty >= 0) {
                    allProducts.addProduct(Product(name, price, qty, cat));
                    productFM.saveProducts(allProducts);
                    cout << "\n✅ Product added successfully!" << endl;
                    cout << name << " has been added to inventory.\n" << endl;
                } else {
                    cout << "\n❌ Invalid input! Price must be positive.\n" << endl;
                }
                break;
            }

            // Edit the price
            case 3: {
                if (allProducts.size == 0) {
                    cout << "\n⚠️  No products available to edit.\n" << endl;
                    break;
                }
                
                cout << "\n========================================" << endl;
                cout << "          ✏️  EDIT PRODUCT PRICE        " << endl;
                cout << "========================================" << endl;
                allProducts.displayAll();
                cout << "========================================" << endl;
                
                int num;
                double newPrice;
                cout << "\nEnter product number (0 to cancel): ";
                cin >> num;
                
                if (num == 0) {
                    cout << "Cancelled.\n";
                    break;
                }
                
                if (num > 0 && num <= allProducts.size) {
                    cout << "Current Price: " << allProducts.products[num - 1].data.price << " EGP" << endl;
                    cout << "Enter new price (EGP): ";
                    cin >> newPrice;
                    
                    if (newPrice > 0) {
                        allProducts.products[num - 1].data.price = newPrice;
                        productFM.saveProducts(allProducts);
                        cout << "\n✅ Price updated successfully!" << endl;
                        cout << allProducts.products[num - 1].data.name 
                             << " is now " << fixed << setprecision(2) << newPrice << " EGP\n" << endl;
                    } else {
                        cout << "\n❌ Invalid price! Must be positive.\n" << endl;
                    }
                } else {
                    cout << "\n❌ Invalid product number!\n" << endl;
                }
                break;
            }

            // Remove Products
            case 4: {
                if (allProducts.size == 0) {
                    cout << "\n⚠️  No products available to remove.\n" << endl;
                    break;
                }
                
                cout << "\n========================================" << endl;
                cout << "          🗑️  REMOVE PRODUCT            " << endl;
                cout << "========================================" << endl;
                allProducts.displayAll();
                cout << "========================================" << endl;
                
                int num;
                cout << "\nEnter product number to remove (0 to cancel): ";
                cin >> num;
                
                if (num == 0) {
                    cout << "Cancelled.\n";
                    break;
                }
                
                if (num > 0 && num <= allProducts.size) {
                    string productName = allProducts.products[num - 1].data.name;
                    
                    cout << "Are you sure you want to remove '" << productName << "'? (y/n): ";
                    char confirm;
                    cin >> confirm;
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        allProducts.removeProduct(num - 1);
                        productFM.saveProducts(allProducts);
                        cout << "\n✅ Product removed successfully!" << endl;
                        cout << productName << " has been removed from inventory.\n" << endl;
                    } else {
                        cout << "Removal cancelled.\n" << endl;
                    }
                } else {
                    cout << "\n❌ Invalid product number!\n" << endl;
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
                cout << "\n👋 Logging out from admin panel..." << endl;
                cout << "Goodbye, Admin!\n" << endl;
                currentUser = nullptr;
                return;
            }

            default:
                cout << "\n❌ Invalid choice! Please enter a number between 1 and 6.\n" << endl;
            }
        } while (ch != 6);
    }

public:
    SupermarketSystem() {
        currentUser = nullptr;
        initProducts();
    }

    // Code runner
    void run() {
        int ch;
        
        cout << "\n========================================" << endl;
        cout << "=       WELCOME TO OUR SUPERMARKET     =" << endl;
        cout << "========================================\n" << endl;
        
        do {
            cout << "========================================" << endl;
            cout << "            🏪 MAIN MENU                " << endl;
            cout << "========================================" << endl;
            cout << "1. Register New Account" << endl;
            cout << "2. Login" << endl;
            cout << "3. Exit" << endl;
            cout << "========================================" << endl;
            cout << "Enter your choice (1-3): ";
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
                cout << "\n========================================" << endl;
                cout << "    Thank you for shopping with us!    " << endl;
                cout << "          See you again soon!          " << endl;
                cout << "========================================\n" << endl;
            } else {
                cout << "\n❌ Invalid choice! Please enter a number between 1 and 3.\n" << endl;
            }
        } while (ch != 3);
    }
};

int main() {
    SupermarketSystem system;
    system.run();
    return 0;
}
