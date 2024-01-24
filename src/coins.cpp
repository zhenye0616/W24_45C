#include "coins.hpp"
#include <iostream>
#include <iomanip>
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
    if (has_exact_change_for_coins(coins)) {
            quarters -= coins.quarters;
            dimes -= coins.dimes;
            nickels -= coins.nickels;
            pennies -= coins.pennies;

            return coins;
    }else
        return Coins(0, 0, 0, 0);
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

void print_cents(int cents, std::ostream& out) {
    int dollars = cents / 100;
    int remainingCents = cents % 100;

    // Use std::setw and std::setfill to ensure two decimal places for cents
    out << "$" << dollars << "." << std::setw(2) << std::setfill('0') << remainingCents;
}

Coins ask_for_coins(std::istream& in, std::ostream& out) {
    int quarters, dimes, nickels, pennies;

    out << "Quarters? ";
    in >> quarters;
    out << "Dimes? ";
    in >> dimes;
    out << "Nickels? ";
    in >> nickels;
    out << "Pennies? ";
    in >> pennies;

    return Coins(quarters, dimes, nickels, pennies);
}

void coins_menu(std::istream& in, std::ostream& out) {
    Coins myCoins(0, 0, 0, 0);
    int choice;

    do {
        out << "Coins Menu\\s";
        out << "1. Deposit Change\n";
        out << "2. Extract Change\n";
        out << "3. Print Balance\n";
        out << "4. Exit\n";
        out << "User Input: ";
        in >> choice;

        switch (choice) {
            case 1: {
                Coins depositAmount = ask_for_coins(in, out);
                myCoins.deposit_coins(depositAmount);
                out << "\nThank you!\n";
                break;
            }
            case 2: {
                Coins extractionRequest = ask_for_coins(in, out);
                if (myCoins.has_exact_change_for_coins(extractionRequest)) {
                    myCoins.extract_exact_change(extractionRequest);
                    out << "\nThank you!\n";
                } else {
                    out << "\nERROR: Insufficient Funds\n";
                }
                break;
            }
            case 3: {
                print_cents(myCoins.total_value_in_cents(), out);
                out << "\n\nThank you!\n";
                break;
            }
            case 4:
                break;
            default:
                out << "\nERROR: Invalid Command\n";
                break;
        }
    } while (choice != 4);
}