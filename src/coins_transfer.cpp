#include <iostream>
#include "coins.hpp"

using namespace std;

int main() {
    // Create two Coins objects
    Coins piggyBank(50, 50, 50, 50); // 50 quarters, 50 dimes, 50 nickels, 50 pennies
    Coins pocket(8, 3, 6, 8);        // 8 quarters, 3 dimes, 6 nickels, 8 pennies

    // Print piggyBank and pocket
    cout << "Initial piggy Bank: " << piggyBank << endl;
    cout << "Initial pocket: " << pocket << endl;

    int costOfChips = 149; 
    Coins chipsCost = coins_required_for_cents(costOfChips);
    Coins changeUsed = pocket.extract_exact_change(chipsCost);
    cout << "Bought a bag of chips for using pocket"<< endl;
    cout << "Chips required the coins: "<< chipsCost << endl;
    cout << "Pocket after paying for chips: " << pocket << endl;
    
    int transferAmountCents = 405;
    Coins transferAmount = coins_required_for_cents(transferAmountCents);
    Coins transferredCoins = piggyBank.extract_exact_change(transferAmount);
    pocket.deposit_coins(transferredCoins);
    cout << "Transfering money to pocket " << endl;
    cout << "Coins for transfer " << transferAmount << endl;
    cout << "Pocket: " << pocket << endl;
    cout << "Piggy Bank: " << piggyBank << endl;
    
    Coins sofa(10, 10, 10, 10); // Coins found in sofa
    piggyBank.deposit_coins(sofa);
    cout << "Transfering sofa change to piggy bank" << endl;
    cout << "sofa: " << sofa << endl;
    cout << "Piggy Bank: " << piggyBank << endl;
    
    int totalCents = piggyBank.total_value_in_cents();
    cout << "Piggy bank total: $" << (totalCents / 100) << "." << (totalCents % 100 < 10 ? "0" : "") << (totalCents % 100) << endl;

    return 0;
}
