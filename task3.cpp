#include <iostream>
#include <string>
using namespace std;

struct Coach {
    int number;
    string type;
    int capacity;
    int passengers;
    Coach* next;
    Coach* prev;
};

// train class manage
class TrainManager {
private:
    Coach* head;
    Coach* current;

    // helper: find coach by number
    Coach* findByNumber(int number) {
        if (head == NULL) return NULL;
        Coach* temp = head;
        do {
            if (temp->number == number) return temp;
            temp = temp->next;
        } while (temp != head);
        return NULL;
    }

public:
    TrainManager() {
        head = NULL;
        current = NULL;
    }

    // add coach at end of train
    void addCoach(int number, string type, int capacity, int passengers) {
        Coach* newCoach = new Coach;
        newCoach->number = number;
        newCoach->type = type;
        newCoach->capacity = capacity;
        newCoach->passengers = passengers;
        newCoach->next = NULL;
        newCoach->prev = NULL;

        if (head == NULL) {
            newCoach->next = newCoach;
            newCoach->prev = newCoach;
            head = current = newCoach;
        } else {
            // inserting at end (before head)
            Coach* tail = head->prev;
            newCoach->next = head;
            newCoach->prev = tail;
            tail->next = newCoach;
            head->prev = newCoach;
        }
        cout << "Coach added: " << newCoach->number
             << " (" << newCoach->type << ")" << endl;
    }

    // insert coach after specified coach number
    void insertCoachAfter(int targetNumber, int number, string type,
                          int capacity, int passengers) {
        Coach* target = findByNumber(targetNumber);
        if (target == NULL) {
            cout << "Coach " << targetNumber << " not found." << endl;
            return;
        }

        Coach* newCoach = new Coach;
        newCoach->number = number;
        newCoach->type = type;
        newCoach->capacity = capacity;
        newCoach->passengers = passengers;

        // inserting after target node
        newCoach->next = target->next;
        newCoach->prev = target;
        target->next->prev = newCoach;
        target->next = newCoach;

        cout << "Coach inserted: " << newCoach->number
             << " after coach " << targetNumber << endl;
    }

    // remove coach by number
    void removeCoach(int number) {
        if (head == NULL) {
            cout << "No coaches in train." << endl;
            return;
        }

        Coach* temp = head;
        do {
            if (temp->number == number) {
                if (temp->next == temp) {
                    // only one coach
                    head = current = NULL;
                } else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;
                    if (temp == head) {
                        head = temp->next;
                    }
                    if (temp == current) {
                        current = temp->next;
                    }
                }
                cout << "Coach removed: " << temp->number << endl;
                delete temp;
                return;
            }
            temp = temp->next;
        } while (temp != head);

        cout << "Coach " << number << " not found." << endl;
    }

    // move forward (next coach)
    void moveForward() {
        if (current == NULL) {
            cout << "No coaches available." << endl;
            return;
        }
        current = current->next;
        cout << "Moved forward to coach: " << current->number << endl;
    }

    // move backward (previous coach)
    void moveBackward() {
        if (current == NULL) {
            cout << "No coaches available." << endl;
            return;
        }
        current = current->prev;
        cout << "Moved backward to coach: " << current->number << endl;
    }

    // display train clockwise (forward)
    void displayClockwise() {
        if (head == NULL) {
            cout << "No coaches in train." << endl;
            return;
        }
        Coach* temp = head;
        cout << "Train (clockwise):" << endl;
        do {
            cout << "Coach " << temp->number
                 << " | " << temp->type
                 << " | Capacity: " << temp->capacity
                 << " | Passengers: " << temp->passengers
                 << " | Empty: " << (temp->capacity - temp->passengers)
                 << endl;
            temp = temp->next;
        } while (temp != head);
    }

    // display train anti-clockwise (backward)
    void displayAntiClockwise() {
        if (head == NULL) {
            cout << "No coaches in train." << endl;
            return;
        }
        Coach* temp = head->prev;   // start from tail
        cout << "Train (anti-clockwise):" << endl;
        do {
            cout << "Coach " << temp->number
                 << " | " << temp->type
                 << " | Capacity: " << temp->capacity
                 << " | Passengers: " << temp->passengers
                 << " | Empty: " << (temp->capacity - temp->passengers)
                 << endl;
            temp = temp->prev;
        } while (temp != head->prev);
    }

    // search coach by number
    void searchCoach(int number) {
        if (head == NULL) {
            cout << "No coaches in train." << endl;
            return;
        }
        Coach* temp = head;
        do {
            if (temp->number == number) {
                cout << "Coach found: " << temp->number
                     << " | " << temp->type
                     << " | Capacity: " << temp->capacity
                     << " | Passengers: " << temp->passengers << endl;
                return;
            }
            temp = temp->next;
        } while (temp != head);
        cout << "Coach " << number << " not found." << endl;
    }

    // find coach with maximum available (empty) capacity
    void findMaxAvailableCapacity() {
        if (head == NULL) {
            cout << "No coaches in train." << endl;
            return;
        }
        Coach* temp = head;
        Coach* best = head;
        int maxEmpty = head->capacity - head->passengers;

        do {
            int empty = temp->capacity - temp->passengers;
            if (empty > maxEmpty) {
                maxEmpty = empty;
                best = temp;
            }
            temp = temp->next;
        } while (temp != head);

        cout << "Coach with max empty seats: " << best->number
             << " (" << best->type << ")"
             << " | Empty seats: " << maxEmpty << endl;
    }

    // display current coach
    void displayCurrentCoach() {
        if (current == NULL) {
            cout << "No coaches in train." << endl;
            return;
        }
        cout << "Current coach: " << current->number
             << " | " << current->type
             << " | Capacity: " << current->capacity
             << " | Passengers: " << current->passengers << endl;
    }

    // reverse train direction by swapping next/prev pointers
    void reverseTrain() {
        if (head == NULL || head->next == head) {
            cout << "Nothing to reverse." << endl;
            return;
        }

        Coach* temp = head;
        do {
            // swap next and prev of every node
            Coach* swapPtr = temp->next;
            temp->next = temp->prev;
            temp->prev = swapPtr;
            temp = temp->prev;   // move to next node (old next is now prev)
        } while (temp != head);

        // head's next was originally its prev (old tail) — new head
        head = head->next;

        cout << "Train direction reversed." << endl;
    }

    // destructor to free memory
    ~TrainManager() {
        if (head == NULL) return;
        Coach* temp = head->next;
        while (temp != head) {
            Coach* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        delete head;
    }
};

int main() {
    TrainManager train;
    int choice;

    // initial input: number of coaches
    int n;
    cout << "Enter number of coaches: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        int number, capacity, passengers;
        string type;
        cout << "\nCoach " << (i + 1) << ":" << endl;
        cout << "Enter coach number: ";
        cin >> number;
        cin.ignore();
        cout << "Enter coach type: ";
        getline(cin, type);
        cout << "Enter capacity: ";
        cin >> capacity;
        cout << "Enter current passengers: ";
        cin >> passengers;
        cin.ignore();
        train.addCoach(number, type, capacity, passengers);
    }

    do {
        cout << "\nTrain Coach Navigation System" << endl;
        cout << "1. Add Coach" << endl;
        cout << "2. Insert Coach After" << endl;
        cout << "3. Remove Coach" << endl;
        cout << "4. Move Forward" << endl;
        cout << "5. Move Backward" << endl;
        cout << "6. Display Train Clockwise" << endl;
        cout << "7. Display Train Anti-clockwise" << endl;
        cout << "8. Search Coach" << endl;
        cout << "9. Find Max Available Capacity" << endl;
        cout << "10. Display Current Coach" << endl;
        cout << "11. Reverse Train Direction" << endl;
        cout << "12. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                int number, capacity, passengers;
                string type;
                cout << "Enter coach number: ";
                cin >> number;
                cin.ignore();
                cout << "Enter coach type: ";
                getline(cin, type);
                cout << "Enter capacity: ";
                cin >> capacity;
                cout << "Enter current passengers: ";
                cin >> passengers;
                cin.ignore();
                train.addCoach(number, type, capacity, passengers);
                break;
            }
            case 2: {
                int target, number, capacity, passengers;
                string type;
                cout << "Enter coach number to insert after: ";
                cin >> target;
                cin.ignore();
                cout << "Enter new coach number: ";
                cin >> number;
                cin.ignore();
                cout << "Enter coach type: ";
                getline(cin, type);
                cout << "Enter capacity: ";
                cin >> capacity;
                cout << "Enter current passengers: ";
                cin >> passengers;
                cin.ignore();
                train.insertCoachAfter(target, number, type, capacity, passengers);
                break;
            }
            case 3: {
                int number;
                cout << "Enter coach number to remove: ";
                cin >> number;
                train.removeCoach(number);
                break;
            }
            case 4:
                train.moveForward();
                break;
            case 5:
                train.moveBackward();
                break;
            case 6:
                train.displayClockwise();
                break;
            case 7:
                train.displayAntiClockwise();
                break;
            case 8: {
                int number;
                cout << "Enter coach number to search: ";
                cin >> number;
                train.searchCoach(number);
                break;
            }
            case 9:
                train.findMaxAvailableCapacity();
                break;
            case 10:
                train.displayCurrentCoach();
                break;
            case 11:
                train.reverseTrain();
                break;
            case 12:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 12);

    return 0;
}