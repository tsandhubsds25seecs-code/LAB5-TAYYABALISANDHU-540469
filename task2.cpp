#include <iostream>
#include <string>
using namespace std;

struct Photo {
    int id;
    string name;
    string date;
    string location;
    Photo* next;
    Photo* prev;
};

// photo album class manage
class PhotoAlbum {
private:
    Photo* head;
    Photo* current;
    int nextId;

public:
    PhotoAlbum() {
        head = NULL;
        current = NULL;
        nextId = 1;
    }

    // add photo at end of circular doubly linked list
    void addPhoto(string name, string date, string location) {
        Photo* newPhoto = new Photo;
        newPhoto->id = nextId++;
        newPhoto->name = name;
        newPhoto->date = date;
        newPhoto->location = location;
        newPhoto->next = NULL;
        newPhoto->prev = NULL;

        if (head == NULL) {
            newPhoto->next = newPhoto;
            newPhoto->prev = newPhoto;
            head = current = newPhoto;
        } else {
            // inserting at end (before head)
            Photo* tail = head->prev;
            newPhoto->next = head;
            newPhoto->prev = tail;
            tail->next = newPhoto;
            head->prev = newPhoto;
        }
        cout << "Photo added: " << newPhoto->name
             << " (" << newPhoto->location << ")" << endl;
    }

    // insert photo after current
    void insertAfterCurrent(string name, string date, string location) {
        if (current == NULL) {
            cout << "No photos in album." << endl;
            return;
        }

        Photo* newPhoto = new Photo;
        newPhoto->id = nextId++;
        newPhoto->name = name;
        newPhoto->date = date;
        newPhoto->location = location;
        newPhoto->next = NULL;
        newPhoto->prev = NULL;

        // inserting after current node
        newPhoto->next = current->next;
        newPhoto->prev = current;
        current->next->prev = newPhoto;
        current->next = newPhoto;

        cout << "Photo inserted after current: " << newPhoto->name << endl;
    }

    // remove photo by id
    void removePhotoById(int id) {
        if (head == NULL) {
            cout << "No photos in album." << endl;
            return;
        }

        Photo* temp = head;
        do {
            if (temp->id == id) {
                // found
                if (temp->next == temp) {
                    // only one photo
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
                cout << "Photo removed: " << temp->name << endl;
                delete temp;
                return;
            }
            temp = temp->next;
        } while (temp != head);

        cout << "Photo with ID " << id << " not found." << endl;
    }

    // remove current photo
    void removeCurrentPhoto() {
        if (current == NULL) {
            cout << "No photos in album." << endl;
            return;
        }

        Photo* temp = current;
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
        cout << "Photo removed: " << temp->name << endl;
        delete temp;
    }

    // move next
    void moveNextPhoto() {
        if (current == NULL) {
            cout << "No photos available." << endl;
            return;
        }
        current = current->next;
        cout << "Moved to photo: " << current->name
             << " (" << current->location << ")" << endl;
    }

    // move previous
    void movePrevPhoto() {
        if (current == NULL) {
            cout << "No photos available." << endl;
            return;
        }
        current = current->prev;
        cout << "Moved to photo: " << current->name
             << " (" << current->location << ")" << endl;
    }

    // display all photos forward
    void displayAlbumForward() {
        if (head == NULL) {
            cout << "No photos in album." << endl;
            return;
        }
        Photo* temp = current;
        cout << "Album (forward):" << endl;
        do {
            cout << temp->id << ". " << temp->name
                 << " | " << temp->date
                 << " | " << temp->location << endl;
            temp = temp->next;
        } while (temp != current);
    }

    // display all photos backward
    void displayAlbumBackward() {
        if (head == NULL) {
            cout << "No photos in album." << endl;
            return;
        }
        Photo* temp = current;
        cout << "Album (backward):" << endl;
        do {
            cout << temp->id << ". " << temp->name
                 << " | " << temp->date
                 << " | " << temp->location << endl;
            temp = temp->prev;
        } while (temp != current);
    }

    // search photo by id
    void searchPhotoById(int id) {
        if (head == NULL) {
            cout << "No photos in album." << endl;
            return;
        }
        Photo* temp = head;
        do {
            if (temp->id == id) {
                cout << "Photo found: " << temp->name
                     << " | " << temp->date
                     << " | " << temp->location << endl;
                return;
            }
            temp = temp->next;
        } while (temp != head);
        cout << "Photo with ID " << id << " not found." << endl;
    }

    // count photos
    void countPhotos() {
        if (head == NULL) {
            cout << "Total photos: 0" << endl;
            return;
        }
        int count = 0;
        Photo* temp = head;
        do {
            count++;
            temp = temp->next;
        } while (temp != head);
        cout << "Total photos: " << count << endl;
    }

    // destructor to free memory
    ~PhotoAlbum() {
        if (head == NULL) return;
        Photo* temp = head->next;
        while (temp != head) {
            Photo* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
        delete head;
    }
};

int main() {
    PhotoAlbum album;
    int choice;

    // initial input: number of photos
    int n;
    cout << "Enter number of photos: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        string name, date, location;
        cout << "\nPhoto " << (i + 1) << ":" << endl;
        cout << "Enter photo name: ";
        getline(cin, name);
        cout << "Enter date taken: ";
        getline(cin, date);
        cout << "Enter location: ";
        getline(cin, location);
        album.addPhoto(name, date, location);
    }

    do {
        cout << "\nPhoto Album Manager" << endl;
        cout << "1. Add Photo" << endl;
        cout << "2. Insert Photo After Current" << endl;
        cout << "3. Remove Photo by ID" << endl;
        cout << "4. Remove Current Photo" << endl;
        cout << "5. Move to Next Photo" << endl;
        cout << "6. Move to Previous Photo" << endl;
        cout << "7. Display Album Forward" << endl;
        cout << "8. Display Album Backward" << endl;
        cout << "9. Search Photo by ID" << endl;
        cout << "10. Count Photos" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore newline character after choice input

        switch (choice) {
            case 1: {
                string name, date, location;
                cout << "Enter photo name: ";
                getline(cin, name);
                cout << "Enter date taken: ";
                getline(cin, date);
                cout << "Enter location: ";
                getline(cin, location);
                album.addPhoto(name, date, location);
                break;
            }
            case 2: {
                string name, date, location;
                cout << "Enter photo name: ";
                getline(cin, name);
                cout << "Enter date taken: ";
                getline(cin, date);
                cout << "Enter location: ";
                getline(cin, location);
                album.insertAfterCurrent(name, date, location);
                break;
            }
            case 3: {
                int id;
                cout << "Enter photo ID to remove: ";
                cin >> id;
                album.removePhotoById(id);
                break;
            }
            case 4:
                album.removeCurrentPhoto();
                break;
            case 5:
                album.moveNextPhoto();
                break;
            case 6:
                album.movePrevPhoto();
                break;
            case 7:
                album.displayAlbumForward();
                break;
            case 8:
                album.displayAlbumBackward();
                break;
            case 9: {
                int id;
                cout << "Enter photo ID to search: ";
                cin >> id;
                album.searchPhotoById(id);
                break;
            }
            case 10:
                album.countPhotos();
                break;
            case 11:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 11);

    return 0;
}