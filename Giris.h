#pragma once
namespace Giris_Hissesi{
    DB::Database Database_all;
    static short guest_id;
    static double balance_admin = 0;
    //ozumnen account yaradiram
    void DbSetUp() {
        DB::Admin newadmin("admin","1234");
        Database_all.Add(newadmin);
        
        DB::Product newproduct("T-shirt", "Qirmizi", 20, "dbuasbdu sadb saudbsa",120);
        Database_all.Add(newproduct);
    };
    void admin();
    void guest();
    void start() {
        cout << endl  << "E-BAZAR-a xos gelmisiniz" << endl << endl;
        cout << "1.Qonag kimi daxil ol" << endl;
        cout << "2.Admin kimi daxil ol" << endl;
        char selection;
        cin >> selection;
        if(selection == '1') {
            guest();
        } else if(selection == '2') {
            admin();
        }
    }
    void guest() {
        while(true) {
            system("clear");
            string name;
            double balance;
            string CD = __DATE__;
            cout << "Enter your name and balance: ";
            cin >> name >> balance;
            try {
                DB::Customer newCustomer(name,balance, CD);
                cout << newCustomer.getCD();
                Giris_Hissesi::Database_all.Add(newCustomer);
                guest_id = newCustomer.getId();
                break;
            } catch(Errors::Exception &a) {
                cout << a.what();
            }
        }
        Esas_Sehife::guest_menu();
    }
    bool log_in(string _user, string _pass) {
        short count = Database_all.admins.size();
        for(size_t i = 0;count>i;i++) {
            if(Database_all.admins[i].getUsername() == _user
               && Database_all.admins[i].getPassword() == _pass
               ) {
                return true;
            }
        }
        Errors::Exception a("Duzgun username ve parol daxil edin \n",to_string(__LINE__),__FILE__,__TIME__);
        throw a;
    }
    void admin() {
        while(true) {
            system("clear");
            cout << endl << "LOGIN" << endl;
            cout << "Enter username and password to log in: ";
            string username;
            string pass;
            cin >> username >> pass;
            try {
                log_in(username,pass);
            }catch(Errors::Exception &a) {
                cout << a.what();
                continue;
            }
            break;
        }
        Esas_Sehife::admin_menu();
    }
};
