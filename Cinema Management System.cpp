#include <iostream>
#include <fstream>
#include <vector>
#include <conio.h>
#include <iomanip>
using namespace std;

class Movie {
public:
    int id;
    string name;
    int seats;
    float price;

    Movie(int i, string n, int s, float p) {
        id = i;
        name = n;
        seats = s;
        price = p;
    }
};

class Cinema {
private:
	
    vector<Movie> movie;

public:
    void loadMovies() {
        movie.clear();
        ifstream file("movie.txt");
        if (!file) return;

        int id, seats;
        float price;
        string name;

        while (file >> id) {
            file.ignore();                
            getline(file, name, '|');      
            file >> seats;
            file.ignore();                 
            file >> price;

            movie.push_back(Movie(id, name, seats, price));
        }
        file.close();
    }
	void saveMovies() {
    ofstream file("movie.txt");

    for (int i = 0; i < movie.size(); i++) {
        file << movie[i].id << "|"
             << movie[i].name << "|"
             << movie[i].seats << "|"
             << movie[i].price << endl;
    }

    file.close();
}

	void viewMovies() {
    loadMovies();
    cout << "\n--- Movies List ---\n";

    for (int i = 0; i < movie.size(); i++) {
        cout << "ID: " << movie[i].id
             << " | Name: " << movie[i].name
             << " | Seats: " << movie[i].seats
             << " | Price: $" << movie[i].price << endl;
    }
}

    void addMultipleMovies() {
        int n;
        cout << "How many movies do you want to add? ";
        cin >> n;fflush(stdin);cin.clear();
        cin.ignore();

        ofstream file("movie.txt", ios::app);

        for (int i = 0; i < n; i++) {
            int id, seats;
            float price;
            string name;

            cout << "\nMovie " << i + 1 << endl;
            cout << "ID: ";cin >> id;fflush(stdin);cin.clear();
            cin.ignore();

            cout << "Movie Name: ";getline(cin, name);fflush(stdin);cin.clear();

            cout << "Seats: ";cin >> seats;fflush(stdin);cin.clear();

            cout << "Price: ";cin >> price;fflush(stdin);cin.clear();
            cin.ignore();

            file << id << "|" << name << "|"
                 << seats << "|" << price << endl;
        }

        file.close();
        cout << "Movies added successfully!\n";
    }void deleteMovie() {
    int id;
    loadMovies();

    cout << "Enter Movie ID to delete: ";cin >> id;fflush(stdin);cin.clear();

    for (int i = 0; i < movie.size(); i++) {
        if (movie[i].id == id) {
            movie.erase(movie.begin() + i);
            saveMovies();
            cout << "Movie deleted successfully!\n";
            return;
        }
    }
    cout << "Movie not found!\n";
}
void searchMovie() {
    int id;
    loadMovies();

    cout << "Enter Movie ID to search: ";cin >> id;fflush(stdin);cin.clear();

    for (int i = 0; i < movie.size(); i++) {
        if (movie[i].id == id) {
            cout << "\nMovie Found\n";
            cout << "ID: " << movie[i].id
                 << " | Name: " << movie[i].name
                 << " | Seats: " << movie[i].seats
                 << " | Price: $" << movie[i].price << endl;
            return;
        }
    }
    cout << "Movie not found!\n";
}
void sortByPrice() {
    loadMovies();

    for (int i = 0; i < movie.size() - 1; i++) {
        for (int j = i + 1; j < movie.size(); j++) {
            if (movie[i].price > movie[j].price) {
                Movie temp = movie[i];
                movie[i] = movie[j];
                movie[j] = temp;
            }
        }
    }

    saveMovies();
    cout << "Movies sorted by price!\n";
}

    void updateSeats() {
    int id, newSeats;
    loadMovies();

    cout << "Enter Movie ID: ";cin >> id;fflush(stdin);cin.clear();
    cout << "Enter New Seats: ";cin >> newSeats;fflush(stdin);cin.clear();

    for (int i = 0; i < movie.size(); i++) {
        if (movie[i].id == id) {
            movie[i].seats = newSeats;
            saveMovies();
            cout << "Seats updated!\n";
            return;
        }
    }
    cout << "Movie not found!\n";
}

	void bookTicket() {
    int id, qty;
    loadMovies();
    viewMovies();

    cout << "Enter Movie ID: ";cin >> id;fflush(stdin);cin.clear();
    cout << "Enter Tickets: ";cin >> qty;fflush(stdin);cin.clear();

    for (int i = 0; i < movie.size(); i++) {
        if (movie[i].id == id && qty <= movie[i].seats) {
            movie[i].seats -= qty;
            saveMovies();
            cout << "Booking successful!\n";
            cout << "Total Price: $" << qty * movie[i].price << endl;
            return;
        }
    }
    cout << "Booking failed!\n";
}

	void cancelTicket() {
    int id, qty;
    loadMovies();

    cout << "Enter Movie ID: ";cin >> id;fflush(stdin);cin.clear();
    cout << "Enter Tickets to Cancel: ";cin >> qty;fflush(stdin);cin.clear();

    for (int i = 0; i < movie.size(); i++) {
        if (movie[i].id == id) {
            movie[i].seats += qty;
            saveMovies();
            cout << "Ticket cancelled!\n";
            return;
        }
    }
    cout << "Movie not found!\n";
}

};
bool adminLogin() {
    string user, pass;
    cout << "\n--- Admin Login ---\n";
    cout << "Username: ";cin >> user;fflush(stdin);cin.clear();
    
    cout << "Password: ";cin >> pass;fflush(stdin);cin.clear();

    return (user == "admin" && pass == "1234");
}
void adminMenu(Cinema &cinema) {
    char choice;
    do {
	        cout << "\n--- Admin Menu ---\n";
	        cout << "Press Key [1] for Add Movies\n";
	        cout << "Press Key [2] for delete movie\n";
	        cout << "Press Key [3] for View Movies\n";
	        cout << "Press Key [4] for Update Seats\n";
	        cout << "Press Key [5] for Search Movie by ID\n";
	        cout << "Press Key [6] for Sort Movie by PRICE\n";
	        cout << "Press Key [7] for Logout\n";
	        choice = getch();

        switch (choice) {
        case '1':{
        	cinema.addMultipleMovies();
			break;
		}
        case '2':{
        	cinema.deleteMovie();
			break;
		}
				 
        case '3':{
        	cinema.viewMovies(); 
			break;
		}
				 
        case '4':{
        	cinema.updateSeats();
			break;
		}
				 
        case '5':{
        	cinema.searchMovie(); 
			break;
		}
				 
        case '6':{
        	cinema.sortByPrice();
			break;
		}
				 
        case '7':{
        	cout << "Logged out.\n"; 
        	exit(0);
			break;
		}
        
        default: cout << "Invalid option!\n";
        }
    } while (true);
}

void userMenu(Cinema &cinema) {
    char choice;
    do {
        cout << "\n--- User Menu ---\n";
        cout << "Press Key [1] for View Movies\n";
        cout << "Press Key [2] for Book Ticket\n";
        cout << "Press Key [3] for Cancel Ticket\n";
        cout << "Press Key [4] for Back\n";
        
        choice = getch();

        switch (choice) {
        	
        case '1':
				 cinema.viewMovies(); 
				 break;
        case '2':
				 cinema.bookTicket();
				  break;
        case '3': 
				cinema.cancelTicket();
				 break;
        case '4': exit(0);
        
				 cout << "Returning...\n";
				  break;
        default: cout << "Invalid option!\n";
        
        }
    } while (true);
}
int main() {
    Cinema cinema;
    char choice;

    do {
        cout << "\n==== CINEMA MANAGEMENT SYSTEM ====\n";
        cout << "Press Key [1] for Admin Login\n";
        cout << "Press Key [2] for User Menu\n";
        cout << "Press Key [3] for Exit\n";
        
        choice = getch();

        switch (choice) {
        case '1':
            if (adminLogin())
                adminMenu(cinema);
            else
                cout << "Login failed!\n";
            break;
        case '2':
            userMenu(cinema);
            break;
        case '3': exit(0);
            	cout << "Thank you for using CMS!\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (true);

    return 0;
}
