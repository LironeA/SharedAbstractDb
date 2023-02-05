#include <iostream>
#include "master.h"
#include "slave.h"

using namespace std;

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

int display_options() {
    printf("Choose option:\n"
           "0 - Quit\n"
           "1 - Insert Master\n"
           "2 - Get Master\n"
           "3 - Update Master\n"
           "4 - Delete Master\n"
           "5 - Insert Slave\n"
           "6 - Get Slave\n"
           "7 - Update Slave\n"
           "8 - Delete Slave\n");
}

int unsupported_operation() {
    cout << "This operation is not supported." << endl;
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
                break;
            default:
                unsupported_operation();
                break;
        }
    } while(1);
}


