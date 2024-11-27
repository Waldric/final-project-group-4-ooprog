#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Contact {
protected:
    int id;
    string name;
    string phone;
    string email;
    string group;
    string birthday;
    string emergencyContact;
    int age;
    string address;

public:
    Contact(int id, string name, string phone, string email, string group, string birthday, string emergencyContact, int age, string address)
        : id(id), name(name), phone(phone), email(email), group(group), birthday(birthday), emergencyContact(emergencyContact), age(age), address(address) {}

    int getId() { 
        return id; 
    }
    string getName() { 
        return name; 
    }
    string getPhone() { 
        return phone; 
    }
    string getEmail() { 
        return email; 
    }
    string getGroup() { 
        return group; 
    }
    string getBirthday() { 
        return birthday; 
    }
    string getEmergencyContact() { 
        return emergencyContact; 
    }
    int getAge() { 
        return age; 
    }
    string getAddress() { 
        return address; 
    }

    void setName(string newName) { 
        name = newName; 
    }
    void setPhone(string newPhone) { 
        phone = newPhone; 
    }
    void setEmail(string newEmail) { 
        email = newEmail; 
    }
    void setGroup(string newGroup) {
        group = newGroup; 
    }
    void setBirthday(string newBirthday) { 
        birthday = newBirthday; 
    }
    void setEmergencyContact(string newEmergencyContact) { 
        emergencyContact = newEmergencyContact; 
    }
    void setAge(int newAge) { 
        age = newAge; 
    }
    void setAddress(string newAddress) { 
        address = newAddress; 
    }
};

class BusinessContact : public Contact {
    string company;

public:
    BusinessContact(int id, string name, string phone, string email, string group, string birthday, string emergencyContact, int age, string address, string company)
        : Contact(id, name, phone, email, group, birthday, emergencyContact, age, address), company(company) {}

    //Display function (Must only display the contact that have a company):
};

class User {
protected:
    string username;
    string password;
    string role;

public:
    User(string username, string password, string role) : username(username), password(password), role(role) {}

    string getUsername() { 
        return username; 
    }
    string getPassword() { 
        return password; 
    }
    string getRole() { 
        return role; 
    }

    //All core functionalities:

};

class Admin : public User {
public:
    Admin(string username, string password) : User(username, password, "Admin") {}

    //Create, Update and Remove functions:
};

class Guest : public User {
public:
    Guest(string username, string password) : User(username, password, "NormalUser") {}

    //Read, Search and Filter functions:
};

class ContactManager {
private:
    vector<Contact> contacts;
    Admin admin;

public:
    void displayMenu() {
        int choice;
        do {
            cout << "\n=== Contact Manager ===\n";
            cout << "1. Add Contact\n";
            cout << "2. View Contacts\n";
            cout << "3. Search\n";
            cout << "4. Filter\n";
            cout << "5. Sort\n";
            cout << "6. Group\n";
            cout << "7. Delete\n";
            cout << "0. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            //Switch cases:
        }
    }
};

int main () {
    cout<< "betlog";
}