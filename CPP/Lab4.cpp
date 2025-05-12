#include <iostream>
using namespace std;

class BankAccount
{
    private:
        double balance;
        double interest_rate;
    public:
        void set(int dollars, int cents) {
            balance = dollars + (cents / 100);
        }
        
        void update() {
            balance = balance * (1 + interest_rate);
        }

        double get_balance() {
            return balance;
        }

        double get_rate() {
            return interest_rate;
        }

        void set_rate(int rate) {
            interest_rate = rate;
        }
};

class cashRegister {
    private:
        int cashOnHand;

    public:
        cashRegister() {
            cashOnHand = 500;
        }

        cashRegister(int initialCash) {
            cashOnHand = initialCash;
        }

        void acceptAmount(int amount) {
            cashOnHand += amount;
        }

        void printBalance() {
            cout << cashOnHand << endl;
        }
};

class dispenserType {
    private:
        int numberOfItems;
        int cost;
        
    public:
        dispenserType() {
            numberOfItems = 50;
        }

        dispenserType(int initNoOfItem, int initCost) {
            numberOfItems = initNoOfItem;
            cost = initCost;
        }
    
        int getNoOfItems() {
            return numberOfItems;
        }

        int getCost() {
            return cost;
        }

        void makeSale() {
            numberOfItems--;
        }
};

class juiceMachine {
    private:
        cashRegister accountant;
        dispenserType itemDispenser[4];
        string items[4] = {"apple_juice", "orange_juice", "mango_lassi", "fruit_punch"};

    public:
        void startProcess() {
            displayItems();

            int choice = getUserChoice();

            showPrice(choice);
            acceptMoney(choice);
            releaseItem(choice);
        }

        void displayItems() {
            cout << "Items Sold By Machine: ";
            for (int i=0; i<4; i++) {
                cout << items[i] << ", ";
            }
            cout << endl;
        }

        int getUserChoice() {
            string userChoice;

            while (true) {
                cout << "Enter An Item You Want Sold By Machine: ";
                cin >> userChoice;
            
                for (int i=0; i<4; i++) {
                    if (items[i] == userChoice) {
                        if (itemDispenser[i].getNoOfItems() <= 0) {
                            cout << "Item is Sold Out" << endl;
                            continue;
                        }

                        return i;
                    }
                }
                cout << "Please Enter an Actual Item!" << endl;
            }
        }

        void showPrice(int selectedItem) {
            cout << "Price of Item: " << itemDispenser[selectedItem].getCost() << endl;
        }

        void acceptMoney(int selectedItem) {
            accountant.acceptAmount(itemDispenser[selectedItem].getCost());
        }

        void releaseItem(int selectedItem) {
            itemDispenser[selectedItem].makeSale();
        }

};

class population {
    private:
        double sample_size;
        double n_births;
        double n_deaths;

    public:
        population(double population_size, double no_births, double no_deaths) {
            sample_size = population_size < 1 ? 1 :population_size;
            n_births = no_births < 0 ? 0 : no_births;
            n_deaths = no_deaths < 0 ? 0 : no_deaths;
        }

        double get_birth_rate() {
            return n_births / sample_size;
        }

        double get_death_rate() {
            return n_deaths / sample_size;
        }
};




int main() {
    cashRegister newRegister;

    newRegister.acceptAmount(300);
    newRegister.printBalance();

    population newPopulation(10000, 10, 10);

    cout << newPopulation.get_birth_rate() << endl;
    cout << newPopulation.get_death_rate() << endl;


    juiceMachine machine;
    machine.startProcess();


}