#include <iostream>
#include <string>
using namespace std;

struct Tab {
    int id;
    string title;
    string url;
    Tab* next;
    Tab* prev;
};

// browser class manage
class BrowserManager {
private:
    Tab* head;
    Tab* current;
    int nextId;

public:
    BrowserManager() {
        head = NULL;
        current = NULL;
        nextId = 1;
    }

    void openTab(string title, string url) {
        Tab* newTab = new Tab;
        newTab->id = nextId++;
        newTab->title = title;
        newTab->url = url;
        newTab->next = NULL;
        newTab->prev = NULL;

        if (head == NULL) {
            newTab->next = newTab;
            newTab->prev = newTab;
            head = current = newTab;
        } else {
            // inserting after current node
            newTab->next = current->next;
            newTab->prev = current;
            current->next->prev = newTab;
            current->next = newTab;
            current = newTab;
        }
        cout << "Tab opened: " << newTab->title << " (" << newTab->url << ")" << endl;
    }

    // close current tab
    void closeCurrentTab() {
        if (current == NULL) {
            cout << "No tabs to close." << endl;
            return;
        }
        Tab* temp = current;
        if (current->next == current) {
            head = current = NULL;
        } else {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            if (current == head) {
                head = current->next;
            }
            current = current->next;
        }
        cout << "Tab closed: " << temp->title << " (" << temp->url << ")" << endl;
        delete temp;
    }

    // Move Next
    void moveNextTab() {
        if (current == NULL) {
            cout << "No tabs available." << endl;
            return;
        }
        current = current->next;
        cout << "Moved to tab: " << current->title << " (" << current->url << ")" << endl;
    }

    // move previous
    void movePrevTab() {
        if (current == NULL) {
            cout << "No tabs available." << endl;
            return;
        }
        current = current->prev;
        cout << "Moved to tab: " << current->title << " (" << current->url << ")" << endl;
    }

    // display current tab
    void displayCurrentTab() {
        if (current == NULL) {
            cout << "No tabs open." << endl;
            return;
        }
        cout << "Current tab: " << current->title << " (" << current->url << ")" << endl;
    }

    // display all tabs forward
    void displayAllTabsForward() {
        if (head == NULL) {
            cout << "No tabs open." << endl;
            return;
        }
        Tab* temp = head;
        cout << "All tabs (forward):" << endl;
        do {
            cout << temp->id << ". " << temp->title << " (" << temp->url << ")" << endl;
            temp = temp->next;
        } while (temp != head);
    }

    // display all tabs backward
    void displayAllTabsBackward() {
        if (head == NULL) {
            cout << "No tabs open." << endl;
            return;
        }
        Tab* temp = head->prev;
        cout << "All tabs (backward):" << endl;
        do {
            cout << temp->id << ". " << temp->title << " (" << temp->url << ")" << endl;
            temp = temp->prev;
        } while (temp != head->prev);
    }

    // search tab by id
    void searchTabById(int id) {
        if (head == NULL) {
            cout << "No tabs open." << endl;
            return;
        }
        Tab* temp = head;
        do {
            if (temp->id == id) {
                cout << "Tab found: " << temp->title << " (" << temp->url << ")" << endl;
                return;
            }
            temp = temp->next;
        } while (temp != head);
        cout << "Tab with ID " << id << " not found." << endl;
    }

    // destructor to free memory
    ~BrowserManager() {
        if (head == NULL) return;
        Tab* temp = head->next;
        while (temp != head) {
            Tab* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        delete head;
    }
};

int main() {
    BrowserManager browser;
    int choice;

    do {
        cout << "\nBrowser Tab Manager" << endl;
        cout << "1. Open Tab" << endl;
        cout << "2. Close Current Tab" << endl;
        cout << "3. Move to Next Tab" << endl;
        cout << "4. Move to Previous Tab" << endl;
        cout << "5. Display Current Tab" << endl;
        cout << "6. Display All Tabs Forward" << endl;
        cout << "7. Display All Tabs Backward" << endl;
        cout << "8. Search Tab by ID" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character after choice input

        switch (choice) {
            case 1: {
                string title, url;
                cout << "Enter tab title: ";
                getline(cin, title);
                cout << "Enter tab URL: ";
                getline(cin, url);
                browser.openTab(title, url);
                break;
            }
            case 2:
                browser.closeCurrentTab();
                break;
            case 3:
                browser.moveNextTab();
                break;
            case 4:
                browser.movePrevTab();
                break;
            case 5:
                browser.displayCurrentTab();
                break;
            case 6:
                browser.displayAllTabsForward();
                break;
            case 7:
                browser.displayAllTabsBackward();
                break;
            case 8: {
                int id;
                cout << "Enter tab ID to search: ";
                cin >> id;
                browser.searchTabById(id);
                break;
            }
            case 9:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 9);

    return 0;
}