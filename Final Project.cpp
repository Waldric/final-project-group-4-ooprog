#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
using namespace std;

class Contact {
protected:
    string id;
    string name;
    string phone;
    string email;
    string birthday;
    string emergencyContact;
    int age;
    string address;
    string category;

public:
    Contact(string id, string name, string phone, string email, string birthday, string emergencyContact, int age, string address)
        : id(id), name(name), phone(phone), email(email), birthday(birthday), emergencyContact(emergencyContact), age(age), address(address), category("None") {}

    string getId() { return id; }
    string getName() { return name; }
    string getPhone() { return phone; }
    string getEmail() { return email; }
    string getBirthday() { return birthday; }
    string getEmergencyContact() { return emergencyContact; }
    int getAge() { return age; }
    string getAddress() { return address; }
    string getCategory() { return category; }

    void setName(string newName) { name = newName; }
    void setPhone(string newPhone) { phone = newPhone; }
    void setEmail(string newEmail) { email = newEmail; }
    void setBirthday(string newBirthday) { birthday = newBirthday; }
    void setEmergencyContact(string newEmergencyContact) { emergencyContact = newEmergencyContact; }
    void setAge(int newAge) { age = newAge; }
    void setAddress(string newAddress) { address = newAddress; }
    void setCategory(string newCategory) { category = newCategory; }
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
};

class Guest : public User {
public:
    Guest(string username, string password) : User(username, password, "NormalUser") {}
};

class ContactManager {
private:
    static ContactManager* instance;
    vector<Contact> contacts;

public:
    ContactManager() = default;

    static ContactManager* getInstance() {
        if (instance == nullptr) {
            instance = new ContactManager();
        }
        return instance;
    }

    ContactManager(const ContactManager&) = delete;
    ContactManager& operator=(const ContactManager&) = delete;

    void addContact(string id, string name, string phone, string email, string birthday, string emergencyContact, int age, string address) {
        contacts.push_back(Contact(id, name, phone, email, birthday, emergencyContact, age, address));
        cout << "Contact added successfully!\n";
    }

    void updateContactCategory(string id, string newCategory) {
        for (int i = 0; i < contacts.size(); i++) {
            if (contacts[i].getId() == id) {
                contacts[i].setCategory(newCategory);
                cout << "Contact group/category updated successfully!\n";
                return;
            }
        }
    }

    void updateContact(string id) {
        for (int i = 0; i < contacts.size(); i++) {
            if (contacts[i].getId() == id) {
                int choiceUpdate;
                do {
                    cout << "\nCurrent contact details:\n";
                    cout << "Name: " << contacts[i].getName() << "\n";
                    cout << "Phone: " << contacts[i].getPhone() << "\n";
                    cout << "Email: " << contacts[i].getEmail() << "\n";
                    cout << "Birthday: " << contacts[i].getBirthday() << "\n";
                    cout << "Emergency Contact: " << contacts[i].getEmergencyContact() << "\n";
                    cout << "Age: " << contacts[i].getAge() << "\n";
                    cout << "Address: " << contacts[i].getAddress() << "\n";
                    cout << "Category: " << contacts[i].getCategory() << "\n"; 

                    cout << "\nWhat do you want to update?\n";
                    cout << "[1] Name\n";
                    cout << "[2] Phone\n";
                    cout << "[3] Email\n";
                    cout << "[4] Birthday\n";
                    cout << "[5] Emergency Contact\n";
                    cout << "[6] Age\n";
                    cout << "[7] Address\n";
                    cout << "[8] Update Group\n";
                    cout << "[9] Exit\n";
                    cout << "Enter your choice: ";
                    cin >> choiceUpdate;

                    cin.ignore();

                    switch (choiceUpdate) {
                        case 1: {
                            string newName;
                            cout << "Enter new Name: ";
                            getline(cin, newName);
                            contacts[i].setName(newName);
                            break;
                        }
                        case 2: {
                            string newPhone;
                            cout << "Enter new Phone: ";
                            getline(cin, newPhone);
                            contacts[i].setPhone(newPhone);
                            break;
                        }
                        case 3: {
                            string newEmail;
                            cout << "Enter new Email: ";
                            getline(cin, newEmail);
                            contacts[i].setEmail(newEmail);
                            break;
                        }
                        case 4: {
                            string newBirthday;
                            cout << "Enter new Birthday: ";
                            getline(cin, newBirthday);
                            contacts[i].setBirthday(newBirthday);
                            break;
                        }
                        case 5: {
                            string newEmergencyContact;
                            cout << "Enter new Emergency Contact: ";
                            getline(cin, newEmergencyContact);
                            contacts[i].setEmergencyContact(newEmergencyContact);
                            break;
                        }
                        case 6: {
                            int newAge;
                            cout << "Enter new Age: ";
                            cin >> newAge;
                            contacts[i].setAge(newAge);
                            cin.ignore();
                            break;
                        }
                        case 7: {
                            string newAddress;
                            cout << "Enter new Address: ";
                            getline(cin, newAddress);
                            contacts[i].setAddress(newAddress);
                            break;
                        }
                            case 8: {
                            string newCategory;
                            cout << "Enter new Category (Family, Friend, Manager, Client, Vendor): ";
                            cin >> newCategory;
                            while (newCategory != "Family" && newCategory != "Friend" && newCategory != "Manager" && newCategory != "Client" && newCategory != "Vendor") {
                                cout << "Invalid category! Please enter 'Family', 'Friend', 'Manager', 'Client' or 'Vendor': ";
                                cin >> newCategory;
                            }
                            contacts[i].setCategory(newCategory);
                            break;
                        }
                        case 9:
                            cout << "Exiting update menu.\n";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                            break;
                    }

                } while (choiceUpdate != 9);

                cout << "Contact updated successfully!\n";
                return;
            }
        }
        cout << "Contact with ID " << id << " not found!\n";
    }
};

bool isValidAge(int age) {
    return age > 0;
}

bool isValidInput(const string& input) {
    return !input.empty();
}

bool isValidAgeInput(int& age) {
    while (true) {
        cin >> age;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            cout << "Invalid input! Please enter a valid age (number only): ";
        } else if (age <= 0) {
            cout << "Age must be positive. Try again: ";
        } else {
            return true;
        }
    }
}

int main () {
    ContactManager manager;
    int choice;

    do {
        cout << "\n=== Contact Manager ===\n";
        cout << "[1] Add Contact\n";
        cout << "[2] View Contacts\n";
        cout << "[3] Update Contacts\n";
        cout << "[4] Delete\n";
        cout << "[5] Search\n";
        cout << "[6] Filter\n";
        cout << "[7] Sort\n";
        cout << "[8] Update Group\n";
        cout << "[9] Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string id;
                int age;
                string name, phone, email, birthday, emergencyContact, address;

                cout << "Enter your ID: ";
                cin >> id;

                cout << "Enter your Age: ";
                isValidAgeInput(age);

                cin.ignore();
                do {
                    cout << "Enter your Name: ";
                    getline(cin, name);
                    if (!isValidInput(name)) {
                        cout << "Name cannot be empty. Try again.\n";
                    }
                } while (!isValidInput(name));

                do {
                    cout << "Enter your Phone Number: ";
                    getline(cin, phone);
                    if (!isValidInput(phone)) {
                        cout << "Phone number cannot be empty. Try again.\n";
                    }
                } while (!isValidInput(phone));

                do {
                    cout << "Enter your Email: ";
                    getline(cin, email);
                    if (!isValidInput(email)) {
                        cout << "Email cannot be empty. Try again.\n";
                    }
                } while (!isValidInput(email));

                cout << "Enter your birthday: ";
                getline(cin, birthday);
                cout << "Enter your Emergency Contact: ";
                getline(cin, emergencyContact);
                cout << "Enter your Address: ";
                getline(cin, address);

                manager.addContact(id, name, phone, email, birthday, emergencyContact, age, address);
                break;
            }

            case 2: {   
                break;
            }

            case 3: {
                string id;
                cout << "Enter Contact ID to update: ";
                cin >> id;
                manager.updateContact(id);
                break;
            }

            case 8: {
                string id;
                cout << "Enter Contact ID to update the group: ";
                cin >> id;

                string newCategory;
                cout << "Enter the new group/category (Family, Friend, Manager, Client, Vendor): ";
                cin >> newCategory;

                while (newCategory != "Family" && newCategory != "Friend" && newCategory != "Manager" && newCategory != "Client" && newCategory != "Vendor") {
                    cout << "Invalid category! Please enter 'Family', 'Friend', 'Manager', 'Client', or 'Vendor': ";
                    cin >> newCategory;
                }

                manager.updateContactCategory(id, newCategory);
                break;
            }
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }

    } while (choice != 9);
}
