

#include <iostream>   // For input/output
#include <random>     // For random number generation
#include <ctime>      // For seeding RNG
using namespace std;

// TODO: Add reorder and restocking functionality. 
// Probably will need to optimize code in future check-ins

int main() {
	int store_inventory;
	int reserve_inventory;
	int shelf_capacity;
	int days;
	cout << "Enter initial number of monitors in the store: ";
	cin >> store_inventory;
	cout << "Enter initial number of monitors in reserve: ";
	cin >> reserve_inventory;
	cout << "Enter shelf capacity (max monitors store can hold): ";
	cin >> shelf_capacity;
	cout << "Enter number of days to simulate: ";
	cin >> days;

	// Set up random number generator for daily demand (e.g., 1-10 monitors)
	mt19937 rng(static_cast<unsigned int>(time(nullptr)));
	uniform_int_distribution<int> demand_dist(1, 10);


	int total_sold = 0;
	int stockouts = 0;
	int days_store_empty = 0;

	// Variable to keep a running sum of inventory at the start of each day
	double inventory_sum = 0;
	int days_simulated = 0; // To track actual days run in case simulation ends early

	for (int day = 1; day <= days; ++day) {
		if (store_inventory == 0 && reserve_inventory == 0) {
			cout << "\nBoth store and reserve are out of stock. Simulation ends on day " << day << ".\n";
			break;
		}


	// Add inventory at the start of the day to the running sum
	inventory_sum += store_inventory;
	days_simulated++;

		int demand = demand_dist(rng);
		int sold = min(demand, store_inventory);
		store_inventory -= sold;
		total_sold += sold;
		if (sold < demand) stockouts++;

		// If store is empty at the end of the day (before restock), count it
		if (store_inventory == 0) days_store_empty++;

		// Restock from reserve
		int restock = min(shelf_capacity - store_inventory, reserve_inventory);
		store_inventory += restock;
		reserve_inventory -= restock;

		cout << "Day " << day << ": Demand = " << demand
			<< ", Sold = " << sold
			<< ", Store Inventory = " << store_inventory
			<< ", Reserve = " << reserve_inventory << endl;
	}

	// Calculate average daily inventory (avoid division by zero)
	double average_inventory = (days_simulated == 0) ? 0 : inventory_sum / days_simulated;

	cout << "\nTotal monitors sold: " << total_sold << endl;
	cout << "Days with stockouts (demand > inventory): " << stockouts << endl;
	cout << "Days store was empty at end of day: " << days_store_empty << endl;
	cout << "Average daily inventory at start of day: " << average_inventory << endl;
	cout << "Monitors left in store: " << store_inventory << endl;
	cout << "Monitors left in reserve: " << reserve_inventory << endl;
	return 0;
}
