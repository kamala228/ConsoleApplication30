#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Product {
public:
    string name;
    string description;
    float price;
    int quantity;

    Product(string n, string d, float p, int q) : name(n), description(d), price(p), quantity(q) {}

    void change_price(float new_price) {
        price = new_price;
    }

    void decrease_quantity(int amount) {
        if (amount <= quantity)
            quantity -= amount;
        else
            cout << "Недостатньо товару на складі!" << endl;
    }

    void increase_quantity(int amount) {
        quantity += amount;
    }
};

class Cart {
public:
    vector<pair<Product*, int>> items;

    void add_product(Product* product, int quantity) {
        items.push_back({ product, quantity });
    }

    void remove_product(Product* product) {
        for (auto it = items.begin(); it != items.end(); ++it) {
            if (it->first == product) {
                items.erase(it);
                break;
            }
        }
    }

    float calculate_total() {
        float total = 0;
        for (auto& item : items) {
            total += item.first->price * item.second;
        }
        return total;
    }

    void clear_cart() {
        items.clear();
    }
};

class Order {
public:
    string order_id;
    vector<pair<Product*, int>> products;
    float total_amount;
    string status;

    Order(string id, vector<pair<Product*, int>> items, float total) : order_id(id), products(items), total_amount(total), status("в обробці") {}

    void change_status(string new_status) {
        status = new_status;
    }

    void show_info() {
        cout << "Замовлення #" << order_id << endl;
        cout << "Статус: " << status << endl;
        cout << "Товари:\n";
        for (auto& item : products) {
            cout << "- " << item.first->name << " x" << item.second << " = " << item.first->price * item.second << " грн\n";
        }
        cout << "Загальна сума: " << total_amount << " грн\n";
    }
};

class User {
public:
    string name;
    string email;
    Cart cart;
    vector<Order> order_history;

    User(string n, string e) : name(n), email(e) {}

    void add_to_cart(Product* product, int quantity) {
        cart.add_product(product, quantity);
    }

    void place_order() {
        float total = cart.calculate_total();
        string order_id = "ORD" + to_string(order_history.size() + 1);
        Order new_order(order_id, cart.items, total);
        order_history.push_back(new_order);
        cart.clear_cart();
    }

    void view_orders() {
        for (auto& order : order_history) {
            order.show_info();
            cout << "-------------------------\n";
        }
    }
};
