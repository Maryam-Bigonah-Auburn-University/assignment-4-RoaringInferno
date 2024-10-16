#include <iostream>

class GasPump {
	private: // Constants
		static constexpr double GAS_DISPENSE_RATE{0.1};
	private: // Members
		double amountDispensed,
		       amountCharged,
		       costPerGallon;

	public: // Constructors
		GasPump() :
			amountDispensed(0.0),
			amountCharged(0.0),
			costPerGallon(0.0)
		{}
	public: // Methods
		double getAmountDispensed() { return amountDispensed; }
		double getAmountCharged() { return amountCharged; }
		double getCostPerGallon() { return costPerGallon; }
		void setCostPerGallon(double cpg) { costPerGallon = cpg; }
        
		void dispense(int seconds) {
			double amountDispensedThisPump = GAS_DISPENSE_RATE * seconds;
			amountDispensed += amountDispensedThisPump;
			amountCharged += amountDispensedThisPump * costPerGallon;
		}
		void reset() {
			amountDispensed = 0.0;
			amountCharged = 0.0;
		}		
};
	
int main() {
	
    //Define variables
	GasPump pump1;

    // Define Class Object
	double pricepergalloninput;
	int secondsinput;
	std::cout << "Enter the price per gallon: ";
	std::cin >> pricepergalloninput;
	std::cout << "Enter the number of seconds to dispense: ";
	std::cin >> secondsinput;

    // Call Functions
	pump1.setCostPerGallon(pricepergalloninput);
	pump1.dispense(secondsinput);

	// Output
	std::cout << "Amount dispensed: " << pump1.getAmountDispensed() << "\n";
	std::cout << "Cost per gallon: " << pump1.getCostPerGallon() << "\n";
	std::cout << "Amount charged: " << pump1.getAmountCharged() << "\n";

	return 0;
}
