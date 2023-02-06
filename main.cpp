#include <iostream>
#include "master.h"
#include "slave.h"

using namespace std;

int unsupported_operation() {
    cout << "This operation is not supported." << endl;
}

int get_master() {
    struct master m;
    int id;
    cout << "Id:" << endl;
    cin >> id;
    m.id = id;
    if(get_m(&m, id) == 0) {
        cout << "Name: " << m.name << " Id: " << m.id << endl;
    }
    else {
        cout << "Error occurred during the get operation" << endl;
    }
}

int insert_master(){
    struct master m;

    cout << "Name:" << endl;
    cin >> m.name;
    if (insert_m(&m) == 0) {
        cout << "Master created."<< endl <<  "Name: " << m.name << endl << "Id: " << m.id << endl;
    }
    else {
        cout << "Error occurred during the insert operation" << endl;
    }
}


int update_master()
{
    struct master m;

    cout << "Id:" << endl;
    cin >> m.id;
    cout << "Name:" << endl;
    cin >> m.name;
    if(update_m(&m) == 0){
        cout << "Master updated. Name: " << m.name << "Id: " << m.id << endl;
    } else{
        cout << "Error occurred during the update operation" << endl;
    }
}

int delete_master(){
    struct master m;
    int id;
    cout << "Id:" << endl;
    cin >> id;
    m.id = id;

    /*if(delete_m(&m) == 1){
        cout << "Master deleted." << endl;
    } else{
        cout << "Error" << endl;
    }*/
}

int calc_master()
{
    struct master m;
    int id;
    cout << "Id:" << endl;
    cin >> id;
    m.id = id;

    unsupported_operation();

    /*if(calk_m(&m) == 1){
        cout << "Master deleted." << endl;
    } else{
        cout << "Error" << endl;
    }*/
}

int ut_master(){
    unsupported_operation();
}

int get_slave() {
    struct slave s;
    int id;
    cout << "Id:" << endl;
    cin >> id;
    s.id = id;
    if(get_s(&s, id) == 0) {
        cout << "Name: " << s.name << " Id: " << s.id << " Master: " << s.m_id <<  endl;
    }
    else {
        cout << "Error occurred during the get operation" << endl;
    }
}

int insert_slave(){
    struct slave s;

    cout << "Name:" << endl;
    cin >> s.name;
    cout << "MasterID:" << endl;
    cin >> s.m_id;
    if (insert_s(&s) == 0) {
        cout << "Slave created."<< endl <<  "Name: " << s.name << endl << "Id: " << s.id << " Master: " << s.m_id <<  endl;
    }
    else {
        cout << "Error occurred during the insert operation" << endl;
    }
}


int update_slave()
{
    struct slave s;

    cout << "Id:" << endl;
    cin >> s.id;
    cout << "Name:" << endl;
    cin >> s.name;
    cout << "MasterID:" << endl;
    cin >> s.m_id;
    if(update_s(&s) == 0){
        cout << "Slave updated. Name: " << s.name << "Id: " << s.id << " Master: " << s.m_id <<  endl;
    } else{
        cout << "Error occurred during the update operation" << endl;
    }
}

int delete_slave(){
    struct slave s;
    int id;
    cout << "Id:" << endl;
    cin >> id;
    s.id = id;

    /*if(delete_s(&s) == 1){
        cout << "Slave deleted." << endl;
    } else{
        cout << "Error" << endl;
    }*/
}

int calc_slave()
{
    struct slave s;
    int id;
    cout << "Id:" << endl;
    cin >> id;
    s.id = id;

    unsupported_operation();

    /*if(calk_s(&s) == 1){
        cout << "Master deleted." << endl;
    } else{
        cout << "Error" << endl;
    }*/
}

int ut_slave(){
    unsupported_operation();
}

int display_options() {
    printf("Choose option:\n"
           "0 - Quit\n"
           "1 - Insert Master\n"
           "2 - Get Master\n"
           "3 - Update Master\n"
           "4 - Delete Master\n"
           "5 - UT-Master\n"
           "6 - Insert Slave\n"
           "7 - Get Slave\n"
           "8 - Update Slave\n"
           "9 - Delete Slave\n"
           "10 - UT-Slave\n"
    );

}


int main() {
    int command_id;
    do {
        display_options();
        cin >> command_id;
        switch (command_id) {
            case 0:
                return 0;
            case 1:
                insert_master();
                break;
            case 2:
                get_master();
                break;
            case 3:
                update_master();
                break;
            case 4:
                delete_master();
                break;
            case 5:
                ut_master();
                break;
            case 6:
                insert_slave();
                break;
            case 7:
                get_slave();
                break;
            case 8:
                update_slave();
                break;
            case 9:
                delete_slave();
                break;
            case 10:
                ut_slave();
                break;
            default:
                unsupported_operation();
                break;
        }
    } while(1);
}


