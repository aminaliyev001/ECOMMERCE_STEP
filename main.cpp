#include <iostream>
#include <vector>
#include<string>
using namespace std;
#include"Errors.h"


namespace Giris_Hissesi{
bool log_in(string _user, string _pass);
void DbSetUp();
};
namespace Esas_Sehife {void admin_menu(); void guest_menu();void purchaseProduct(int _id, short _count);};


#include"Database.h"
#include"Giris.h"

//E BAZAR APP
//1.clear to cls for windows




namespace Esas_Sehife {
void admin_menu() {
    while(true) {
        system("clear");
        cout << endl << "Admin paneline xos gelmisiniz!" << endl;
        cout << "Balance: " << Giris_Hissesi::balance_admin << "$" << endl;
        cout << "1. Show all products" << endl;
        cout << "2. Add a new product" << endl;
        cout << "3. Delete a product" << endl;
        cout << "4. Update a product" << endl;
        cout << "0. Arxaya qayit" << endl;
        char selection;
        cin >> selection;
        if(selection == '1') {
            system("clear");
            try {
                Giris_Hissesi::Database_all.Read(Giris_Hissesi::Database_all.products);
            } catch(Errors::Exception &a) {
                cout << a.what();
            }
            cout << "Press something to go back" << endl;
            char s;
            cin.ignore();
            cin >> s;
            continue;
        } else if(selection == '2') {
            while(true) {
                system("clear");
                
                string name;
                string price;
                string color;
                string tesvir;
                string quantity;
                cin.ignore();
                
                cout << "Name: ";
                getline(cin, name);
                
                cout << "Price: ";
                getline(cin, price);
                
                cout << "Color: ";
                getline(cin, color);
                
                cout << "Tesvir: ";
                getline(cin, tesvir);
                
                cout << "Quantity: ";
                getline(cin, quantity);
                
                try {
                    DB::Product newProduct(name,color, stoi(quantity),tesvir, stod(price));
                    Giris_Hissesi::Database_all.Add(newProduct);
                    break;
                } catch(Errors::Exception &a) {
                    cout << a.what();
                }
            }
            admin_menu();
            break;
        }
        else if(selection == '3') {
            system("clear");
            cin.ignore();
            int selection;
            cout << endl << "Select id of the product to delete: ";
            cin >> selection;
            try {
                Giris_Hissesi::Database_all.DeleteProductById(selection);
            } catch(Errors::Exception &a) {
                cout << a.what();
            }
        }
        else if(selection == '4') {
            system("clear");
            bool _check = true;
            while(_check) {
                cin.ignore();
                int selection;
                cout << endl << "Select id of the product to update: ";
                cin >> selection;
                try {
                    Giris_Hissesi::Database_all.findProductById(selection);
                    Giris_Hissesi::Database_all.updateProductById(selection);
                    _check = false;
                } catch(Errors::Exception &a) {
                    cout << a.what();
                }
            }
        }
        else if(selection == '0') {
            Giris_Hissesi::start();
            break;
        }
    }
}
void purchaseProduct(int _id, short _count) {
    if(Giris_Hissesi::Database_all.findProductById(_id)){
        short stock = Giris_Hissesi::Database_all.products.size();
        for(size_t i = 0;stock > i;i++) {
            if(Giris_Hissesi::Database_all.products[i].getId() == _id) {
                if(Giris_Hissesi::Database_all.products[i].getQ() >= _count) {
                    double odenmeliPul = (Giris_Hissesi::Database_all.products[i].getPrice() * _count);
                    double balance_afterpay = ( Giris_Hissesi::Database_all.getBalanceByIdCustomer(Giris_Hissesi::guest_id) - odenmeliPul);
                    if(balance_afterpay>=0) {
                        Giris_Hissesi::Database_all.setBalanceByIdCustomer(balance_afterpay, Giris_Hissesi::guest_id);
                        Giris_Hissesi::Database_all.products[i].setQ(Giris_Hissesi::Database_all.products[i].getQ() - _count);
                        Giris_Hissesi::balance_admin += odenmeliPul;
                        return;
                    } else {
                        Errors::Exception a("Yeteri geder pul yoxdur customerda",to_string(__LINE__),__FILE__,__TIME__);
                        throw a;
                    }
                } else {
                    Errors::Exception a("Yeteri geder stokda mehsul yoxdur",to_string(__LINE__),__FILE__,__TIME__);
                    throw a;
                }
            }
        }
    } else {
        Errors::Exception a("Bu id-de mehsul tapilmadi",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
    
}
void showProduct(int _id) {
    bool true_false =  true;
    while(true_false) {
        system("clear");
        
        Giris_Hissesi::Database_all.findProductById(_id);
        cout << endl << endl;
        Giris_Hissesi::Database_all.displayProductById(_id);
        cout << endl << endl;
        cout << "Menim balansim: " << Giris_Hissesi::Database_all.getBalanceByIdCustomer(Giris_Hissesi::guest_id) << "$" << endl;
        
        cout << "0. Geri qayit" << endl;
        cout << "1. Indi al ve geri don" << endl;
        char p;
        cin.ignore();
        cin >> p;
        if(p == '0') {
            true_false = false;
            guest_menu();
        }
        else if (p == '1')
        {
            cout << endl << "Nece eded bu mehsuldan istediyinizi daxil edin: ";
            cin.ignore();
            short count;
            cin >> count;
            try {
                purchaseProduct(_id, count);
                true_false = false;
                guest_menu();
            }
            catch(Errors::Exception &a) {
                cout << a.what();
            }
        }
    }
}
void guest_menu() {
    cout << endl << "Menim balansim: " << Giris_Hissesi::Database_all.getBalanceByIdCustomer(Giris_Hissesi::guest_id) << "$" << endl;
    cout << "------- MEHSULLAR --------" << endl;
    try {
        Giris_Hissesi::Database_all.Read_short(Giris_Hissesi::Database_all.products);
    }
    catch(Errors::Exception &a) {
        cout << a.what();
        Giris_Hissesi::start();
    }
    bool loop_ = true;
    while (loop_) {
        int getid;
        cin.ignore();
        cout << endl << endl << "Etrafli baxmag ucun mehsulun ID-ni daxil edin ve ya geriye qayitmag ucun 0" << endl;
        cin >> getid;
        if(getid == 0) {
            loop_ = false;
            Giris_Hissesi::start();
        }
        try {
            showProduct(getid);
            loop_ = false;
        }catch(Errors::Exception &a) {
            cout << a.what();
            continue;
        }
    }
}
};
int main() {
    Giris_Hissesi::DbSetUp();
    Giris_Hissesi::start();
    return 0;
}
