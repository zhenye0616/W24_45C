#include "coins.hpp"
#include <iostream>
using namespace std;

void Coins::print(std::ostream& out) const {
    out << quarters << " quarters, "
        << dimes << " dimes, "
        << nickels << " nickels, "
        << pennies << " pennies";
}

Coins coins_required_for_cents( int amount_in_cents){
    int quarters = amount_in_cents / CENTS_PER_QUARTER;
    amount_in_cents %= CENTS_PER_QUARTER;
    int dimes = amount_in_cents / CENTS_PER_DIME;
    amount_in_cents %= CENTS_PER_DIME;
    int nickels = amount_in_cents / CENTS_PER_NICKEL;
    amount_in_cents %= CENTS_PER_NICKEL;
    int pennies = amount_in_cents; // The rest are pennies

    return Coins(quarters, dimes, nickels, pennies);
}

std::ostream& operator<<(std::ostream& out, const Coins& coins){
    coins.print(out);
    return out;
}

Coins Coins::extract_exact_change( const Coins& coins){
    quarters -= coins.quarters;
    dimes -= coins.dimes;
    nickels -= coins.nickels;
    pennies -= coins.pennies;
    return coins;
}

void Coins::deposit_coins(Coins& coins) {
        quarters += coins.quarters;
        dimes += coins.dimes;
        nickels += coins.nickels;
        pennies += coins.pennies;
}

int Coins::total_value_in_cents() const {
        return quarters * CENTS_PER_QUARTER + dimes * CENTS_PER_DIME +
               nickels * CENTS_PER_NICKEL + pennies;
    }


bool Coins::has_exact_change_for_coins(const Coins& coins) const {
    return quarters >= coins.quarters &&
           dimes >= coins.dimes &&
           nickels >= coins.nickels &&
           pennies >= coins.pennies;
}


void coins_menu(std::istream& in, std::ostream& out) {
    Coins myCoins(0, 0, 0, 0); // Initialize with zero coins
    int choice;

    do {
        out << "\nCoins Menu\n";
        out << "1. Deposit Change\n";
        out << "2. Extract Change\n";
        out << "3. Print Balance\n";
        out << "4. Exit\n";
        out << "\nUser Input: ";

        in >> choice;

        switch (choice) {
            case 1: {
                int q, d, n, p;
                out << "\nQuarters? ";
                in >> q;
                out << "Dimes? ";
                in >> d;
                out << "Nickels? ";
                in >> n;
                out << "Pennies? ";
                in >> p;
                Coins deposit_amount(q, d, n, p);
                myCoins.deposit_coins(deposit_amount);
                out << "\nThank you!\n";
                break;
            }
            case 2: {
                int q, d, n, p;
                out << "\nQuarters? ";
                in >> q;
                out << "Dimes? ";
                in >> d;
                out << "Nickels? ";
                in >> n;
                out << "Pennies? ";
                in >> p;
                Coins extractionRequest(q, d, n, p);
                if (myCoins.has_exact_change_for_coins(extractionRequest)) {
                    myCoins.extract_exact_change(extractionRequest);
                    out << "\nThank you!\n";
                } else {
                    out << "\nERROR: Insufficient Funds\n";
                }
                break;
            }
            case 3: {
                int totalCents = myCoins.total_value_in_cents();
                out << "\nTotal Balance: $" << (totalCents / 100) << ".";
                if (totalCents % 100 < 10) {
                    out << "0";
                }
                out << (totalCents % 100) << "\n\nThank you!\n";
                break;
            }
            case 4: {
                out << "\nExiting...\n";
                break;
            }
            default: {
                out << "\nERROR: Invalid Command\n";
                break;
            }
        }
    } while (choice != 4);
}