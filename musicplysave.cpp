#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Node {
public:
    string data;
    Node* next;
    Node* prev;

    Node(const string& musicName) : data(musicName), next(nullptr), prev(nullptr) {}
};

class Playlist {
private:
    Node* head;
    Node* current_node;

public:
    Playlist() : head(nullptr), current_node(nullptr) {}

    void insert() {
        cout << "Enter Music Name:\n";
        string temp;
        getline(cin >> ws, temp);

        Node* new_node = new Node(temp);
        if (head == nullptr) {
            new_node->next = new_node->prev = new_node;
            head = current_node = new_node;
        } else {
            Node* last = head->prev;
            new_node->prev = last;
            last->next = new_node;
            new_node->next = head;
            head->prev = new_node;
        }
        cout << "Music added!\n";
    }

    void delete_music() {
        if (head == nullptr) {
            cout << "No Music is there to delete!\n";
            return;
        }
        cout << "Enter Music Name to delete:\n";
        string temp;
        getline(cin >> ws, temp);
        Node* ptr = head;

        do {
            if (ptr->data == temp) {
                if (ptr->next == ptr) { 
                    cout << "One file deleted! Playlist is Empty Now!\n";
                    head = nullptr;
                } else {
                    Node* prev = ptr->prev;
                    Node* next = ptr->next;
                    prev->next = next;
                    next->prev = prev;
                    if (ptr == head) head = next; 
                }
                delete ptr;
                cout << "Music deleted!\n";
                return;
            }
            ptr = ptr->next;
        } while (ptr != head);
        cout << "No Music file is there!\n";
    }

    void show_playlist() const {
        if (head == nullptr) {
            cout << "Playlist is Empty!\n";
            return;
        }
        Node* show_ptr = head;
        cout << "\nDisplaying Playlist:\n";
        int i = 1;
        do {
            cout << "Song " << i++ << ": " << show_ptr->data << "\n";
            show_ptr = show_ptr->next;
        } while (show_ptr != head);
    }

    void play_next() {
        if (current_node == nullptr) {
            cout << "No songs in Playlist!\n";
            return;
        }
        current_node = current_node->next;
        cout << "Playing Next Song: " << current_node->data << "\n";
    }

    void play_previous() {
        if (current_node == nullptr) {
            cout << "No songs in Playlist!\n";
            return;
        }
        current_node = current_node->prev;
        cout << "Playing Previous Song: " << current_node->data << "\n";
    }

    void play_first() {
        if (head == nullptr) {
            cout << "Playlist is Empty!\n";
        } else {
            cout << "Playing First Music: " << head->data << "\n";
            current_node = head; 
        }
    }

    void play_last() {
        if (head == nullptr) {
            cout << "Playlist is Empty!\n";
        } else {
            current_node = head->prev;
            cout << "Playing Last Music: " << current_node->data << "\n";
        }
    }

    void play_specific() {
        if (head == nullptr) {
            cout << "No music is there to be searched!\n";
            return;
        }
        cout << "Enter Music Name to search:\n";
        string temp;
        getline(cin >> ws, temp);
        Node* ptr = head;

        do {
            if (ptr->data == temp) {
                cout << "Music Found!\n";
                cout << "Playing Music: " << ptr->data << "\n";
                return;
            }
            ptr = ptr->next;
        } while (ptr != head);
        cout << "There is no Music file with this name!\n";
    }

    // File Handling
    void save_to_file(const string& filename) const {
        ofstream outFile(filename); 
        if (!outFile) {
            cout << "Error opening file for writing!\n";
            return;
        }

        Node* ptr = head;
        if (ptr) {
            do {
                outFile << ptr->data << "\n"; 
                ptr = ptr->next;
            } while (ptr != head);
        }
        outFile.close();
        cout << "Playlist saved to " << filename << "!\n";
    }

    void load_from_file(const string& filename) {
        ifstream inFile(filename); 
        if (!inFile) {
            cout << "Error opening file for reading!\n";
            return;
        }

        string musicName;
        while (getline(inFile, musicName)) { 
            insert_music(musicName); 
        }
        inFile.close();
        cout << "Playlist loaded from " << filename << "!\n";
    }

    void insert_music(const string& musicName) {
        Node* new_node = new Node(musicName);
        if (head == nullptr) {
            new_node->next = new_node->prev = new_node;
            head = current_node = new_node;
        } else {
            Node* last = head->prev;
            new_node->prev = last;
            last->next = new_node;
            new_node->next = head;
            head->prev = new_node;
        }
    }

    ~Playlist() {
        if (head == nullptr) return;
        Node* current = head;
        Node* next_node;
        do {
            next_node = current->next;
            delete current;
            current = next_node;
        } while (current != head);
    }
};

int main() {
    Playlist playlist;
    int choice;

    while (true) {
        cout << "\n-----Song Playlist Application-----\n";
        cout << "1. Add Music\n";
        cout << "2. Remove Music\n";
        cout << "3. Show Playlist\n";
        cout << "4. Play next file\n";
        cout << "5. Play previous file\n";
        cout << "6. Play first file\n";
        cout << "7. Play last file\n";
        cout << "8. Play specific file\n";
        cout << "9. Save Playlist to File\n"; 
        cout << "10. Load Playlist from File\n"; 
        cout << "11. Exit\n\n";
        cin >> choice;

        switch (choice) {
            case 1:
                playlist.insert();
                break;
            case 2:
                playlist.delete_music();
                break;
            case 3:
                playlist.show_playlist();
                break;
            case 4:
                playlist.play_next();
                break;
            case 5:
                playlist.play_previous();
                break;
            case 6:
                playlist.play_first();
                break;
            case 7:
                playlist.play_last();
                break;
            case 8:
                playlist.play_specific();
                break;
            case 9: { // Save Playlist
                string filename;
                cout << "Enter filename to save: ";
                getline(cin >> ws, filename);
                playlist.save_to_file(filename);
                break;
            }
            case 10: { // Load Playlist
                string filename;
                cout << "Enter filename to load: ";
                getline(cin >> ws, filename);
                playlist.load_from_file(filename);
                break;
            }
            case 11:
                return 0;
            default:
                cout << "Invalid choice, please try again.\n";
        }
    }
}
