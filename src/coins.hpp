#ifndef COINS_HPP
#define COINS_HPP

#include <iosfwd>

constexpr int CENTS_PER_QUARTER =25;
constexpr int CENTS_PER_DIME = 10;
constexpr int CENTS_PER_NICKEL = 5;

class Coins{
public:
	
	 Coins(int q, int d, int n, int p) : quarters(q), dimes(d), nickels(n), pennies(p) {}


	void deposit_coins(Coins& coins); //done
	

	bool has_exact_change_for_coins(const Coins&coins) const;

	Coins extract_exact_change( const Coins& coins);//done

	int  total_value_in_cents() const; //done

	void print(std::ostream& out) const;//done

	bool operator==(const Coins&coins) const = default;

private:
	int quarters, dimes, nickels, pennies;
};

std::ostream& operator<<(std::ostream& out, const Coins& coins);//done

Coins coins_required_for_cents( int amount_in_cents);//done

void print_cents(int cents, std::ostream& out);
Coins ask_for_coins(std::istream& in, std::ostream& out);
void coins_menu(std::istream& in, std::ostream& out); //done
#endif
