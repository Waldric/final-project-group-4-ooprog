#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <stdexcept>
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

    string getId() const { return id; }
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

public:
    vector<Contact> contacts;
    bool isValidPhoneNumber(const string& phone) {
    for (char ch : phone) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return phone.length() == 11;
}

bool isValidEmail(const string& email) {
    return email.find('@') != string::npos;
}

bool isValidBirthday(const string& birthday) {
    if (birthday.length() != 10) return false;
    if (birthday[2] != '/' || birthday[5] != '/') return false; 
    for (int i = 0; i < birthday.length(); i++) {
        if (i != 2 && i != 5 && !isdigit(birthday[i])) return false;
    }
    return true;
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

bool isValidInput(const string& input) {
    return !input.empty();
}

    bool isIdExist(const string& id) const {
        for (const Contact& contact : contacts) { 
            if (contact.getId() == id) {
                return true;
            }
        }
        return false;
    }

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

    void viewContacts(){
        if(contacts.empty()){
            cout << "No contacts available.\n";
            return;
        }
        cout << "\n=== Contact List ===\n";
        cout << left << setw(10) << "ID" 
             << setw(20) << "Name" << setw(15) << "Phone" 
             << setw(25) << "Email" << setw(10) << "Age" 
             << setw(15) << "Category" << setw(30) << "Address" << "\n";
        cout << string(125, '-') << "\n";
       
            for (size_t i = 0; i < contacts.size(); ++i) {
                Contact contact = contacts[i]; 
                cout << left << setw(10) << contact.getId()
                     << setw(20) << contact.getName()
                     << setw(15) << contact.getPhone()
                     << setw(25) << contact.getEmail()
                     << setw(10) << contact.getAge()
                     << setw(15) << contact.getCategory()
                     << setw(30) << contact.getAddress() << "\n";
            }       
        }
    void displayContact(Contact& contact) {
        cout << "\nContact Found!\n";
        cout << left << setw(10) << "ID" 
             << setw(20) << "Name" << setw(15) << "Phone" 
             << setw(25) << "Email" << setw(10) << "Age" 
             << setw(15) << "Category" << setw(30) << "Address" << "\n";
        cout << string(125, '-') << "\n";
        cout << left << setw(10) << contact.getId()
             << setw(20) << contact.getName()
             << setw(15) << contact.getPhone()
             << setw(25) << contact.getEmail()
             << setw(10) << contact.getAge()
             << setw(15) << contact.getCategory()
             << setw(30) << contact.getAddress() << "\n";
    }

    void searchContact() {
        int searchChoice;
        cout << "\nSelect the attribute to search by:\n";
        cout << "[1] Search by ID\n";
        cout << "[2] Search by Name\n";
        cout << "[3] Search by Phone\n";
        cout << "Enter your choice: ";
        cin >> searchChoice;
        cin.ignore();  

        string searchTerm;
        switch (searchChoice) {
            case 1: {
                cout << "Enter Contact ID to search: ";
                getline(cin, searchTerm);
                bool found = false;
                for (auto& contact : contacts) {
                    if (contact.getId() == searchTerm) {
                        displayContact(contact);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Contact with ID " << "'" << searchTerm  << "'" << " not found.\n";
                }
                break;
            }
            case 2: {
                cout << "Enter Contact Name to search: ";
                getline(cin, searchTerm);
                bool found = false;
                for (auto& contact : contacts) {
                    if (contact.getName() == searchTerm) {
                        displayContact(contact);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Contact with Name " << "'" << searchTerm  << "'" << " not found.\n";
                }
                break;
            }         
            case 3: {
                cout << "Enter Contact Phone to search: ";
                getline(cin, searchTerm);
                bool found = false;
                for (auto& contact : contacts) {
                    if (contact.getPhone() == searchTerm) {
                        displayContact(contact);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "Contact with Phone " << "'" << searchTerm  << "'" << " not found.\n";
                }
                break;
            }
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    void updateContactCategory(string id, string newCategory) {
        try {
            bool found = false;
            for (int i = 0; i < contacts.size(); i++) {
                if (contacts[i].getId() == id) {
                    contacts[i].setCategory(newCategory);
                    found = true;
                    cout << "Contact group/category updated successfully!\n";
                    break;
                }
            }
            if (!found) {
                throw invalid_argument("Contact with ID " + id + " not found!");
            }
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    void updateContact(string id) {
        try {
            bool found = false;
            for (size_t i = 0; i < contacts.size(); i++) {
                if (contacts[i].getId() == id) {
                    found = true;
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
                            do {
                                cout << "Enter new Name: ";
                                getline(cin, newName);
                                if (newName.empty()) {
                                    cout << "Name cannot be empty. Try again.\n";
                                }
                            } while (newName.empty());
                            contacts[i].setName(newName);
                            break;
                        }
                        case 2: {
                            string newPhone;
                            do {
                                cout << "Enter new Phone Number (11 digits): ";
                                getline(cin, newPhone);
                                if (!isValidPhoneNumber(newPhone)) {
                                    cout << "Invalid phone number! Please enter a 11-digit phone number: ";
                                }
                            } while (!isValidPhoneNumber(newPhone));
                            contacts[i].setPhone(newPhone);
                            break;
                        }
                        case 3: {
                            string newEmail;
                            do {
                                cout << "Enter new Email (must contain '@'): ";
                                getline(cin, newEmail);
                                if (!isValidEmail(newEmail)) {
                                    cout << "Invalid email! Please enter a valid email address with '@': ";
                                }
                            } while (!isValidEmail(newEmail));
                            contacts[i].setEmail(newEmail);
                            break;
                        }
                        case 4: {
                            string newBirthday;
                            do {
                                cout << "Enter new Birthday (MM/DD/YYYY): ";
                                getline(cin, newBirthday);
                                if (!isValidBirthday(newBirthday)) {
                                    cout << "Invalid format! Please enter your birthday in MM/DD/YYYY format: ";
                                }
                            } while (!isValidBirthday(newBirthday));
                            contacts[i].setBirthday(newBirthday);
                            break;
                        }
                        case 5: {
                            string newEmergencyContact;
                            do {
                                cout << "Enter new Emergency Contact: ";
                                getline(cin, newEmergencyContact);
                                if (newEmergencyContact.empty()) {
                                    cout << "Emergency Contact cannot be empty. Try again.\n";
                                }
                            } while (newEmergencyContact.empty());
                            contacts[i].setEmergencyContact(newEmergencyContact);
                            break;
                        }
                        case 6: {
                            int newAge;
                            do {
                                cout << "Enter new Age: ";
                            } while (!isValidAgeInput(newAge));
                            contacts[i].setAge(newAge);
                            break;
                        }
                        case 7: {
                            string newAddress;
                            do {
                                cout << "Enter new Address: ";
                                getline(cin, newAddress);
                                if (newAddress.empty()) {
                                    cout << "Address cannot be empty. Try again.\n";
                                }
                            } while (newAddress.empty());
                            contacts[i].setAddress(newAddress);
                            break;
                        }
                        case 8: {
                            string newCategory;
                            cout << "Enter new Category (Family, Friend, Manager, Client, Vendor): ";
                            cin >> newCategory;
                            while (newCategory != "Family" && newCategory != "Friend" && newCategory != "Manager" && newCategory != "Client" && newCategory != "Vendor") {
                                cout << "Invalid category! Please enter 'Family', 'Friend', 'Manager', 'Client', or 'Vendor': ";
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
            if (!found) {
                throw invalid_argument("Contact with the given ID does not exist.");
            }
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
    
    void deleteContact(string id) {
        try {
            for (size_t i = 0; i < contacts.size(); i++) {
                if (contacts[i].getId() == id) {
                    contacts.erase(contacts.begin() + i);
                    cout << "Contact with ID " << id << " has been deleted successfully!\n";
                    return;
                }
            }
            throw invalid_argument("Contact with ID " + id + " not found!");
        }
        catch (const invalid_argument& e) {
            cout << "Error: " << e.what() << endl;
        }
    }
void filterContacts() {
    if (contacts.empty()) {
        cout << "No contacts available to filter.\n";
        return;
    }

    int filterChoice;
    cout << "\n=== Filter Contacts ===\n";
    cout << "[1] Name\n";
    cout << "[2] Phone\n";
    cout << "[3] Email\n";
    cout << "[4] Birthday\n";
    cout << "[5] Emergency Contact\n";
    cout << "[6] Age\n";
    cout << "[7] Address\n";
    cout << "[8] Category\n";
    cout << "Enter your choice: ";
    cin >> filterChoice;

    cout << "\n=== Filtered Contacts ===\n";
    for (size_t i = 0; i < contacts.size(); ++i) {
        Contact contact = contacts[i];  

        switch (filterChoice) {
            case 1:
                cout << "Name: " << contact.getName() << "\n";
                break;
            case 2:
                cout << "Phone: " << contact.getPhone() << "\n";
                break;
            case 3:
                cout << "Email: " << contact.getEmail() << "\n";
                break;
            case 4:
                cout << "Birthday: " << contact.getBirthday() << "\n";
                break;
            case 5:
                cout << "Emergency Contact: " << contact.getEmergencyContact() << "\n";
                break;
            case 6:
                cout << "Age: " << contact.getAge() << "\n";
                break;
            case 7:
                cout << "Address: " << contact.getAddress() << "\n";
                break;
            case 8:
                cout << "Category: " << contact.getCategory() << "\n";
                break;
            default:
                cout << "Invalid choice.\n";
                return;
        }
        cout << "-----------------------\n"; 
        }
    }
};

bool isValidPhoneNumber(const string& phone) {
    for (char ch : phone) {
        if (!isdigit(ch)) {
            return false;
        }
    }
    return phone.length() == 11;
}

bool isValidEmail(const string& email) {
    return email.find('@') != string::npos;
}

bool isValidBirthday(const string& birthday) {
    if (birthday.length() != 10) return false;
    if (birthday[2] != '/' || birthday[5] != '/') return false; 
    for (int i = 0; i < birthday.length(); i++) {
        if (i != 2 && i != 5 && !isdigit(birthday[i])) return false;
    }
    return true;
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

bool isValidInput(const string& input) {
    return !input.empty();
}

class SortStrategy : public ContactManager {
public:
    virtual void sort(vector<Contact>& contacts) const = 0;
    virtual ~SortStrategy() = default;
};

class SortByNameAscending : public SortStrategy {
public:
   void sort(vector<Contact>& contacts) const override { 
        for (size_t i = 0; i < contacts.size() - 1; ++i) {
            for (size_t j = 0; j < contacts.size() - i - 1; ++j) {
                if (contacts[j].getName() > contacts[j + 1].getName()) {
                    swap(contacts[j], contacts[j + 1]);
                }
            }
        }
    }
};

class SortByNameDescending : public SortStrategy {
public:
    void sort(vector<Contact>& contacts) const override {
        for (size_t i = 0; i < contacts.size() - 1; ++i) {
            for (size_t j = 0; j < contacts.size() - i - 1; ++j) {
                if (contacts[j].getName() < contacts[j + 1].getName()) {
                    swap(contacts[j], contacts[j + 1]);
                }
            }
        }
    }
};

class SortByAgeAscending : public SortStrategy {
public:
    void sort(vector<Contact>& contacts) const override {
        for (size_t i = 0; i < contacts.size() - 1; ++i) {
            for (size_t j = 0; j < contacts.size() - i - 1; ++j) {
                if (contacts[j].getAge() > contacts[j + 1].getAge()) {
                    swap(contacts[j], contacts[j + 1]);
                }
            }
        }
    }

};

class SortByAgeDescending : public SortStrategy {
public:
    void sort(vector<Contact>& contacts) const override {
        for (size_t i = 0; i < contacts.size() - 1; ++i) {
            for (size_t j = 0; j < contacts.size() - i - 1; ++j) {
                if (contacts[j].getAge() < contacts[j + 1].getAge()) {
                    swap(contacts[j], contacts[j + 1]);
                }
            }
        }
    }
};

class SortByIdAscending : public SortStrategy {
public:
    void sort(vector<Contact>& contacts) const override {
        for (size_t i = 0; i < contacts.size() - 1; ++i) {
            for (size_t j = 0; j < contacts.size() - i - 1; ++j) {
                if (contacts[j].getId() > contacts[j + 1].getId()) {
                    swap(contacts[j], contacts[j + 1]);
                }
            }
        }
    }
};

class SortByIdDescending : public SortStrategy {
public:
    void sort(vector<Contact>& contacts) const override {
        for (size_t i = 0; i < contacts.size() - 1; ++i) {
            for (size_t j = 0; j < contacts.size() - i - 1; ++j) {
                if (contacts[j].getId() < contacts[j + 1].getId()) {
                    swap(contacts[j], contacts[j + 1]);
                }
            }
        }
    }
};

class SortContacts {
private:
    SortStrategy* strategy;

public:
    void setStrategy(SortStrategy& newStrategy) {
        strategy = &newStrategy;
    }

    void sort(vector<Contact>& contacts) {
        if (strategy) {
            strategy->sort(contacts);
            cout << "Contacts sorted successfully!\n";
        } else {
            cout << "No sorting strategy set.\n";
        }
    }
};

int main() {
    ContactManager manager;

    while (true) {
        string role;

        cout << "\n=== Login ===\n";
        cout << "[1] Login as User\n";
        cout << "[2] Login as Guest\n";
        cout << "Choose an option: ";
        int loginChoice;
        cin >> loginChoice;

        if (loginChoice == 1) {
            role = "User";
            cout << "Logged in as User. Full access granted.\n";
        } else if (loginChoice == 2) {
            role = "Guest";
            cout << "Logged in as Guest. Limited access granted.\n";
        } else {
            cout << "Invalid choice. Exiting program.\n";
            return 0;
        }

        int choice;
        do {
            cout << "\n=== Contact Manager ===\n";
            if (role == "User") {
                cout << "[1] Add Contact\n";
                cout << "[2] View Contacts\n";
                cout << "[3] Update Contacts\n";
                cout << "[4] Delete Contact\n";
                cout << "[5] Search\n";
                cout << "[6] Filter\n";
                cout << "[7] Sort\n";
                cout << "[8] Update Group\n";
                cout << "[9] Logout\n";
            } else { 
                cout << "[1] View Contacts\n";
                cout << "[2] Search\n";
                cout << "[3] Filter\n";
                cout << "[4] Logout\n";
            }
            cout << "Enter your choice: ";
            cin >> choice;

            try {
                if (role == "User") {
                    switch (choice) {
                        case 1: {
                            string id, name, phone, email, birthday, emergencyContact, address;
                            int age;
                            cout << "Enter your ID: ";
                            cin >> id;
                            if (manager.isIdExist(id)) {
                                throw invalid_argument("ID already exists. Please use another ID.");
                            }
                            cout << "Enter your Age: ";
                            isValidAgeInput(age);
                            cin.ignore();
                            do {
                                cout << "Enter your Name: ";
                                getline(cin, name);
                            } while (!isValidInput(name));
                            do {
                                cout << "Enter your Phone Number (11 digits): ";
                                getline(cin, phone);
                            } while (!isValidPhoneNumber(phone));
                            do {
                                cout << "Enter your Email (must contain '@'): ";
                                getline(cin, email);
                            } while (!isValidEmail(email));
                            do {
                                cout << "Enter your Birthday (MM/DD/YYYY): ";
                                getline(cin, birthday);
                            } while (!isValidBirthday(birthday));
                            cout << "Enter your Emergency Contact: ";
                            getline(cin, emergencyContact);
                            cout << "Enter your Address: ";
                            getline(cin, address);
                            manager.addContact(id, name, phone, email, birthday, emergencyContact, age, address);
                            break;
                        }
                        case 2:
                            manager.viewContacts();
                            break;
                        case 3: {
                            string id;
                            cout << "Enter Contact ID to update: ";
                            cin >> id;
                            manager.updateContact(id);
                            break;
                        }
                        case 4: {
                            string id;
                            cout << "Enter Contact ID to delete: ";
                            cin >> id;
                            manager.deleteContact(id);
                            break;
                        }
                        case 5:
                            manager.searchContact();
                            break;
                        case 6:
                            manager.filterContacts();
                            break;
                        case 7: {
                            vector<Contact> contacts;
                            SortContacts sorting;
                            SortByNameAscending nameAsc;
                            SortByNameDescending nameDesc;
                            SortByAgeAscending ageAsc;
                            SortByAgeDescending ageDesc;
                            SortByIdAscending idAsc;
                            SortByIdDescending idDesc;
                            int sortOption, order;

                            cout << "[1] Sort By Name " << endl;
                            cout << "[2] Sort By Age " << endl;
                            cout << "[3] Sort By ID " << endl;
                            cout << "Enter your choice: ";
                            cin >> sortOption;

                            cout << "Do you want to sort in:" << endl;
                            cout << "[1] Ascending Order " << endl;
                            cout << "[2] Descending Order " << endl;
                            cout << "Enter sorting order: ";
                            cin >> order;

                            if (sortOption == 1 && order == 1) {
                                sorting.setStrategy(nameAsc);
                            } else if (sortOption == 1 && order == 2) {
                                sorting.setStrategy(nameDesc);
                            } else if (sortOption == 2 && order == 1) {
                                sorting.setStrategy(ageAsc);
                            } else if (sortOption == 2 && order == 2) {
                                sorting.setStrategy(ageDesc);
                            } else if (sortOption == 3 && order == 1) {
                                sorting.setStrategy(idAsc);
                            } else if (sortOption == 3 && order == 2) {
                                sorting.setStrategy(idDesc);
                            } else {
                                cout << "invalid input! please try again. " << endl;
                            }

                            sorting.sort(manager.contacts);
                            manager.viewContacts();
                            break;
                        }
                        case 8: {
                            string id, newCategory;
                            cout << "Enter Contact ID to update the group: ";
                            cin >> id;
                            cout << "Enter the new group/category (Family, Friend, Manager, Client, Vendor): ";
                            cin >> newCategory;
                            manager.updateContactCategory(id, newCategory);
                            break;
                        }
                        case 9:
                            cout << "Logging out...\n";
                            break;
                        default:
                            cout << "Invalid option. Please try again.\n";
                    }
                } else {
                    switch (choice) {
                        case 1:
                            manager.viewContacts();
                            break;
                        case 2:
                            manager.searchContact();
                            break;
                        case 3:
                            manager.filterContacts();
                            break;
                        case 4:
                            cout << "Logging out...\n";
                            break;
                        default:
                            cout << "Invalid option. Please try again.\n";
                    }
                }
            } catch (const exception& e) {
                cout << "An error occurred: " << e.what() << endl;
            }
        } while ((role == "User" && choice != 9) || (role == "Guest" && choice != 4));
    }

    return 0;
}