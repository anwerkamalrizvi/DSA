#include <iostream>
#include <string>
#include <limits> 
using namespace std;

struct Passenger{
    string name;
    Passenger* next;

};

struct Flight{

    string flightNumber;
    Passenger* passengers;
    
    Flight* next;
};

Flight* flightHead = nullptr;

void addFlight(string number) 
{
    Flight* newFlight = new Flight();
    newFlight->flightNumber = number;
    newFlight->passengers = nullptr;
    newFlight->next = flightHead;
    flightHead = newFlight;
}

Passenger* addPassenger(Passenger* h ,string n){
    Passenger* newPassenger = new Passenger();
    newPassenger->name = n;
    newPassenger->next = h;
    return newPassenger;
}

void removePassenger(Passenger*& h, string n)
 {
    if(h==nullptr) return;
    
    if (h->name== n) 
    {
         Passenger* temp = h;
        h = h->next;
        delete temp;
        return;
    }
    
    Passenger* current = h;
    while (current->next!= nullptr && current->next->name!= n) 
    
    {
        current = current->next;
     }
    
    if (current->next!=nullptr){
        Passenger* temp = current->next;
         current->next = current->next->next;
        delete temp;
    }
}

bool  checkPassenger(Passenger* head, string name) 
{
    Passenger* current = head;
    while(current!= nullptr) 
    {
        if (current->name == name) return true;
        current = current->next;
    }
    return false;
}

void displayPassengers(Passenger* head) 
{
    Passenger* current = head;
    while (current != nullptr) 
    {
        cout << current->name<<endl;
        current = current->next;
    }
}

Flight* findFlight(string number) 
{
     Flight* current = flightHead;
    while (current!= nullptr) {
        if (current->flightNumber == number) return current;
        
        current = current->next;
    }
    return nullptr;
}

int main() 
{
    addFlight("PK714");
    addFlight("PK116");
    
    int choice;
    string name, flightNum;
    
    do {
        cout<<"\n\t\t-->PIA Reservation System<--\n\n1. Reserve a ticket\n2. Cancel a reservation\n3. Check reservation\n4. Display passengers\n5. Exit\n";
        cout<<"Enter your choice(1 - 5): ";
        
        // Fixed input validation to prevent infinite loop
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 0; // Set to invalid choice
        }
        
        switch(choice) 
        {
            case 1:
                cout << "Enter the flight#: ";
                cin >> flightNum;
                cout << "Enter the passenger name: ";
                cin >> name;
                {
                    Flight* flight = findFlight(flightNum);
                    if (flight!= nullptr) {
                        flight->passengers = addPassenger(flight->passengers, name);
                        cout << "Reservation for passenger "<<name<<" is added to the flight "<<flightNum<<". \n";
                    } else {
                        cout<< "No such flight exists!\n";
                    }
                }
                break;
                
            case 2:
                cout<<"You selected to cancel a reservation.\n";
                cout<<"Enter flight number: ";
                cin >> flightNum;
                cout<<"Enter passenger name: ";
                cin >> name;
                {
                    Flight* flight = findFlight(flightNum);
                    if (flight!= nullptr) {
                        removePassenger(flight->passengers, name);
                        cout<<"Reservation of passenger has been cancelled sucessfully!\n";
                    } else {
                        cout<<"No such flight ever exists in data!\n";
                    }
                }
                break;
                
            case 3:
                cout<<"Enter flight number: ";
                cin>>flightNum;
                cout<<"Enter passenger name: ";
                cin >> name;
                {
                    Flight* flight = findFlight(flightNum);
                    if (flight!= nullptr) 
                    {
                        if (checkPassenger(flight->passengers, name)) 
                        {
                            cout<<"Reservation found for the passenger "<<name<<"! \n";
                        } else 
                        {
                            cout << "Have you wrote your own name?; No such reservation found for the passenger\n";
                        }
                    }else 
                    {
                        cout << "Flight has been departured in YOUR DREAMS...; No such flight found\n";
                    }
                }
                break;
                
            case 4:
                cout<<"Enter flight number: ";
                cin>>flightNum;
                {

                    Flight *flight = findFlight(flightNum);
                    if (flight!= nullptr) 
                    {
                        cout << "Passengers on the flight are: " << flightNum << ":\n";
                        displayPassengers(flight->passengers);
                    } else {
                        cout << "This flight was departured in YOUR DREAMS...;No such flight found!\n";
                    }
                }
                break;
                
            case 5:
                cout << "Closing all the files, folders, directories of the program...\n";
                break;
                
            default:
                cout << "This software is not your toy!; Invalid input entered.\n";
                break;
        }
    } while(choice!= 5);
    
    return 0;

}

