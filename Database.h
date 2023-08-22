#pragma once
namespace DB {
class Customer {
private:
    static short _ID;
    short id;
    string name;
    double balance;
    string connectedDate;
public:
    string getName() const {
        return name;
    }
    double getBalance() const {
        return balance;
    }
    int getId() const {
        return id;
    }
    string getCD() const {
        return connectedDate;
    }
    void setCD(string data) {
        connectedDate = data;
    }
    void setName(string _name) {
        if(_name.size()>2){
            name = _name;
            return;
        }
        Errors::Exception a("Minimum 3 simvol olmalidir ad",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
    void setBalance(double _balance) {
        if(_balance > 0) {
            balance = _balance;
            return;
        }
        Errors::Exception a("Balance 0$ dan boyuk olmalidir",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
    Customer() = delete;
    Customer(string _name, double _balance, string _CD) {
        id = _ID++;
        setName(_name);
        setBalance(_balance);
        setCD(_CD);
    }
    void show() const {
        cout << endl;
        cout << "Name: " << name << endl;
        cout << "Balance: " << balance << endl;
        cout << "Connected date: " << getCD() << endl;
    }
};

short Customer::_ID = 1;

class Admin {
private:
    static short _ID;
    int id;
    string username;
    string password;
public:
    string getUsername() const {
        return username;
    }
    string getPassword() const {
        return password;
    }
    int getId() const {
        return id;
    }

    Admin() = delete;
    Admin(string _username, string _password) {
        id = _ID++;
        username = _username;
        password = _password;
    }
    void show() const {
        cout << endl;
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
    }
};
short Admin::_ID = 1;

class Product {
private:
    static short _ID;
    int id;
    string name;
    double price;
    string color;
    string tesvir;
    int quantity;
public:
    string getName() const {
        return name;
    }
    string getColor() const {
        return color;
    }
    string getTesvir() const {
        return tesvir;
    }
    int getQ() const {
        return quantity;
    }
    double getPrice () const {
        return price;
    }
    int getId() const {
        return id;
    }

    void setName(string _data) {
        if(_data.length()>0){
            name = _data;
            return;
        }
        Errors::Exception a("Adin uzunlugu hec olmasa 1 simvoldan ibaret olmalidir. ",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
    
    void setColor(string _data) {
        if(_data.length()>0){
            color = _data;
            return;
        }
        Errors::Exception a("Reng bos qala bilmez, hec olmasa 1 simvoldan ibaret olmalidir. ",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
    
    void setTesvir(string _data) {
        if(_data.length() > 15){
            tesvir = _data;
            return;
        }
        Errors::Exception a("Tesvir bos qala bilmez, hec olmasa 15 simvoldan ibaret olmalidir. ",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
    
    void setQ(int _data) {
        if(_data>0){
            quantity = _data;
            return;
        }
        Errors::Exception a("Minimum 1 eded mehsul movcud olmalidir. ",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
    void setPrice(double _data) {
        if(_data >= 1) {
            price = _data;
            return;
        }
        Errors::Exception a("Minimum 1$ olmalidir mehsul. ",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
    
    Product() = delete;
    Product(string _name, string _color, int _quantity, string _tesvir,double _price) {
        id = _ID++;
        setName(_name);
        setColor(_color);
        setQ(_quantity);
        setTesvir(_tesvir);
        setPrice(_price);
    }
    void show() const {
        cout << endl;
        cout << "ID: " << getId() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Color: " << getColor() << endl;
        cout << "Quantity: " << getQ()<< endl;
        cout << "Tesvir: " << getTesvir()<< endl;
        cout << "Price: " << getPrice()<< "$" <<  endl;
    }
    void show_short() const {
        cout << endl;
        cout << "ID: " << getId() << endl;
        cout << "Name: " << getName() << endl;
        cout << "Price: " << getPrice()<< "$" << endl;
    }
};
short Product::_ID = 1;

class Order {
private:
    static int _ID;
    int id;
    int custumerId;
    vector<Product> products;
    string datetime;
public:
    string getDatetime() const {
        return datetime;
    }
    int getCustomerId() const {
        return custumerId;
    }
    int getId() const {
        return id;
    }
    vector<Product> getProducts() const {
        return products;
    }
    void setProducts(vector<Product> _products) {
        if(_products.size()>0) {
            products = _products;
            return;
        }
        Errors::Exception a("Productlarin ici bos qala bilmez \n",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
    void setDatetime(string _datetime) {
        if(datetime.length()>0){
            datetime = _datetime;
            return;
        }
        Errors::Exception a("Datetime bos qala bilmez \n",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
    Order() = delete;
    Order(int _customerID, vector<Product> _products, string _datetime) {
        id = _ID++;
        custumerId = _customerID;
        setProducts(_products);
        setDatetime(_datetime);
    }
    string getNamesOfProducts() const {
        string data;
        for(size_t i = 0;products.size()>i;i++) {
            data+=products[i].getName();
        }
        return data;
    }
    
    void show() const {
        cout << endl;
        cout << "Order ID: " << id << endl;
        cout << "Products: " << getNamesOfProducts() << endl;
        cout << "Customer ID: " << custumerId << endl;
        cout << "Datetime: " << getDatetime() << endl;
    }
    
};
int Order::_ID = 1;

class Database {
private:
    friend void Esas_Sehife::admin_menu();
    friend void Giris_Hissesi::DbSetUp();
    friend bool Giris_Hissesi::log_in(string _user, string _pass);
    friend void Esas_Sehife::guest_menu();
    friend void Esas_Sehife::purchaseProduct(int _id, short _count);
    
    vector<Product> products;
    vector<Order> orders;
    vector<Customer> customers;
    vector<Admin> admins;
public:
    template <typename T>
    void Read(vector<T> items) {
        if(items.size()>0) {
            for (auto item : items) {
                item.show();
            }
        } else {
            Errors::Exception a("Gostermeye hecne yoxdur. \n",to_string(__LINE__),__FILE__,__TIME__);
            throw a;
        }
    }
    
    double getBalanceByIdCustomer(int _id) noexcept{
        double balance = 0;
        for (auto item : customers) {
            if(item.getId() == _id)
                balance = item.getBalance();
        }
        return balance;
    }
    
    void setBalanceByIdCustomer(double _mebleg, int _id) {
        bool success = false;
        for (auto &item : customers) {
            if(item.getId() == _id) {
                item.setBalance(_mebleg);
                success = true;
            }
        }
        if(!success)
        {
            Errors::Exception a("Bele bir id-de customer movcud deyil \n",to_string(__LINE__),__FILE__,__TIME__);
            throw a;
        }
    }
    
    void Read_short(vector <Product> items) {
        if(items.size()>0) {
            for (auto item : items) {
                item.show_short();
            }
        } else {
            Errors::Exception a("Gostermeye hecne yoxdur. \n",to_string(__LINE__),__FILE__,__TIME__);
            throw a;
        }
    }
    bool findProductById(int _id) {
        for (auto item : products) {
            if(item.getId() == _id)
                return true;
        }
        Errors::Exception a("Bele bir id-de mehsul movcud deyil \n",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
    void updateProductById(int _id) {
            for (auto& item : products) {
                if(item.getId() == _id)
                {
                    string name;
                    string color;
                    string quantity;
                    string tesvir;
                    string price;
                    cin.ignore();
                    cout << endl;
                    cout << "Name: (" << item.getName() << ") Enter press deyismemek ucun"  << endl;
                    getline(cin,name);
                    cout << "Color: (" << item.getColor() << ") Enter press deyismemek ucun"  << endl;
                    getline(cin,color);
                    cout << "Quantity: (" << item.getQ() << ") Enter press deyismemek ucun"  << endl;
                    getline(cin,quantity);
                    cout << "Tesvir: (" << item.getTesvir() << ") Enter press deyismemek ucun"  << endl;
                    getline(cin,tesvir);
                    cout << "Price: (" << item.getPrice() << ") Enter press deyismemek ucun"  << endl;
                    getline(cin,price);
                    
                    if(name.empty())
                        name = item.getName();
                    if(color.empty())
                        color = item.getColor();
                    if(quantity.empty())
                        quantity = to_string(item.getQ());
                    if(tesvir.empty())
                        tesvir = item.getTesvir();
                    if(price.empty())
                        price = to_string(item.getPrice());
                    DB::Product newproduct(name, color, stoi(quantity), tesvir,stod(price));
                    item = newproduct;
                }
            }
    }
    void displayProductById(int _id) {
        for (auto item : products) {
            if(item.getId() == _id)
                item.show();
        }
    }
    void Add(Admin& data) {
            admins.push_back(data);
        }

    void Add(Customer& data) {
            customers.push_back(data);
    }
    
    void Add(Product& data) {
            products.push_back(data);
        }
    
    void Add(Order& data) {
            orders.push_back(data);
    }
    
    void DeleteProductById(int id) {
        for (auto it = products.begin(); it != products.end(); ++it) {
            if (it->getId() == id) {
                products.erase(it);
                return;
            }
        }
        Errors::Exception a("Bu id-de product tapilmadi.",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }

    void DeleteOrderById(int id) {
        for (auto it = orders.begin(); it != orders.end(); ++it) {
            if (it->getId() == id) {
                orders.erase(it);
                return;
            }
        }
        Errors::Exception a("Bu id-de product tapilmadi.",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }

    void DeleteAdminById(int id) {
        for (auto it = admins.begin(); it != admins.end(); ++it) {
            if (it->getId() == id) {
                admins.erase(it);
                return;
            }
        }
        Errors::Exception a("Bu id-de product tapilmadi.",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }

    void DeleteCustomerById(int id) {
        for (auto it = customers.begin(); it != customers.end(); ++it) {
            if (it->getId() == id) {
                customers.erase(it);
                return;
            }
        }
        Errors::Exception a("Bu id-de product tapilmadi.",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
};
};
