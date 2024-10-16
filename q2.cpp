#include <iostream>

/**
 * I would create 3 classes: TempKelvin, TempCelsius, and TempFahrenheit.
 * Each class would have a private member variable to store the temperature in the respective unit.
 * Each class would have a getter and setter for their private member variable, and a value constructor.
 * Then, each class would have a copy constructor and conversion constructor and operator.
 * They would have private inline static member functions to convert between the units, so that the formulas are centralized, but performance is not lost.
 */

class Temperature {
	private:
		double degreesKelvin,
		       degreesFahrenheit,
		       degreesCelsius;
	public:
		void setTempKelvin(double degreesKelvin) { this->degreesKelvin = degreesKelvin; }
		double getTempKelvin() { return degreesKelvin; }
		void setTempCelsius() { degreesCelsius = degreesKelvin - 273.15; }
		double getTempCelsius() { return degreesCelsius; } 
		void setTempFahrenheit() { degreesFahrenheit = degreesCelsius * 9.0 / 5.0 + 32.0; }
		double getTempFahrenheit() { return degreesFahrenheit; }
};

int main() {
	Temperature temp;

	double kelvin;
	std::string kelvinString_input;
	std::cout << "Enter the temperature in Kelvin: ";
	std::cin >> kelvinString_input;
	kelvin = std::stod(kelvinString_input);

	temp.setTempKelvin(kelvin);
	temp.setTempCelsius();
	temp.setTempFahrenheit();
	std::cout << "Temperature in Kelvin: " << std::to_string(temp.getTempKelvin()) << "\n";
	std::cout << "Temperature in Celsius: " << std::to_string(temp.getTempCelsius()) << "\n";
	std::cout << "Temperature in Fahrenheit: " << std::to_string(temp.getTempFahrenheit()) << "\n";
}