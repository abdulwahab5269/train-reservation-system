#include <iostream>
#include <string>
#include <limits> // For numeric_limits
using namespace std;

const int TOTAL_SEATS = 20;

struct Passenger {
    string name;
    int seatNumber;
    string destination;
    bool isBooked;
};

void displayMenu() {
    cout << "\n=== Train Seat Reservation ===\n";
    cout << "1. Book a Seat\n";
    cout << "2. View All Reservations\n";
    cout << "3. Search Reservation by Seat Number\n";
    cout << "4. Cancel Reservation\n";
    cout << "5. Exit\n";
    cout << "Choose an option (1-5): ";
}

void clearInputBuffer() {
    cin.clear(); // Clear any error flags
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    Passenger* passengers = new Passenger[TOTAL_SEATS];  //pointer to dynamically allocate memory for passengers

    // Initialize all seats
    for (int i = 0; i < TOTAL_SEATS; ++i) {
        passengers[i].seatNumber = i + 1;
        passengers[i].isBooked = false;
    }

    int option;

    do {
        displayMenu();
        
        // Check if input is valid
        while (!(cin >> option) || option < 1 || option > 5) {
            cout << "Invalid input. Please enter a number between 1 and 5: ";
            clearInputBuffer();
        }
        clearInputBuffer(); // Clear the buffer after successful input

        switch (option) {
            case 1: {
                int seat;
                cout << "Enter seat number (1-" << TOTAL_SEATS << "): ";
                
                while (!(cin >> seat) || seat < 1 || seat > TOTAL_SEATS) {
                    cout << "Invalid seat number. Please enter between 1 and " << TOTAL_SEATS << ": ";
                    clearInputBuffer();
                }
                clearInputBuffer();

                if (passengers[seat - 1].isBooked) {
                    cout << "Seat " << seat << " is already booked by " 
                         << passengers[seat - 1].name << ".\n";
                    break;
                }

                cout << "Enter name: ";
                getline(cin, passengers[seat - 1].name);
                
                cout << "Enter destination: ";
                getline(cin, passengers[seat - 1].destination);

                passengers[seat - 1].isBooked = true;
                cout << "Seat booked successfully!\n";
                break;
            }

            case 2: {
                cout << "\n--- All Reservations ---\n";
                bool found = false;
                for (int i = 0; i < TOTAL_SEATS; ++i) {
                    if (passengers[i].isBooked) {
                        cout << "Seat " << passengers[i].seatNumber
                             << " | Name: " << passengers[i].name
                             << " | Destination: " << passengers[i].destination << "\n";
                        found = true;
                    }
                }
                if (!found) cout << "No reservations found.\n";
                break;
            }

            case 3: {
                int seat;
                cout << "Enter seat number to search: ";
                
                while (!(cin >> seat) || seat < 1 || seat > TOTAL_SEATS) {
                    cout << "Invalid seat number. Please enter between 1 and " << TOTAL_SEATS << ": ";
                    clearInputBuffer();
                }
                clearInputBuffer();

                if (passengers[seat - 1].isBooked) {
                    cout << "Seat " << seat << " is booked by "
                         << passengers[seat - 1].name << " to "
                         << passengers[seat - 1].destination << ".\n";
                } else {
                    cout << "No reservation found for seat " << seat << ".\n";
                }
                break;
            }

            case 4: {
                int seat;
                cout << "Enter seat number to cancel: ";
                
                while (!(cin >> seat) || seat < 1 || seat > TOTAL_SEATS) {
                    cout << "Invalid seat number. Please enter between 1 and " << TOTAL_SEATS << ": ";
                    clearInputBuffer();
                }
                clearInputBuffer();

                if (passengers[seat - 1].isBooked) {
                    cout << "Cancelling reservation for " << passengers[seat - 1].name << ".\n";
                    passengers[seat - 1].isBooked = false;
                    passengers[seat - 1].name = "";
                    passengers[seat - 1].destination = "";
                    cout << "Reservation cancelled successfully.\n";
                } else {
                    cout << "No active booking on seat " << seat << ".\n";
                }
                break;
            }

            case 5:
                cout << "Exiting the system. Thank you!\n";
                break;
        }

    } while (option != 5);

    delete[] passengers;
    return 0;
}