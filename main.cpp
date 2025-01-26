#include <iostream>
#include <cstdlib>
#include <sstream>

#include "flightticket.h"
#include "flighthashtable.h"

void listCommands()
{
	cout << "\n----------------------------------" << endl;
	cout << "import <path>      	:Import flight-tickets from a CSV file" << endl
		 << "export <path>      	:Export flight-tickets to a CSV file" << endl
		 << "count_collisions   	:Print number of collisions" << endl
		 << "add                	:Add a new flight-ticket" << endl
		 << "delete <key>       	:Delete a flight-ticket" << endl
		 << "find <key>         	:Find a flight-ticket's details" << endl
		 << "allinday <date>    	:Display all flight-tickets in a day" << endl
		 << "printASC <key>     	:Print flight-tickets in ascending order" << endl
		 << "help                    :prints all available commands" << endl
		 << "exit               	:Exit the program" << endl;
}

int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE;
	listCommands();
	string user_input;
	string command;
	string parameter, parameter2, xyz;

	do
	{
		cout << ">";
		getline(cin, user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr, command, ' ');
		getline(sstr, parameter, ',');
		getline(sstr, parameter2, ' ');
		getline(sstr, xyz);

		if (command == "import")
		{
			cout << myFlightHASHTABLE.importCSV(parameter) << " tickets imported" << endl;
		}
		else if (command == "export")
		{
			cout << myFlightHASHTABLE.exportCSV(parameter) << " tickets exported" << endl;
		}
		else if (command == "count_collisions")
		{
			cout << "Total number of collisions is " << myFlightHASHTABLE.count_collisions() << endl;
		}
		else if (command == "add")
		{
			string companyName, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date, flightnum_string;
			int flightNumber;
			do
			{
				cout << "Please enter the company name: ";
				getline(cin, companyName);
				if (myFlightHASHTABLE.validcompanyName(companyName))
				{
					break;
				}
				else
				{
					cout << "Invalid company name please try again!!" << endl;
					continue;
				}
			} while (true);
			do
			{
				cout << "Please enter the flight number: ";
				getline(cin, flightnum_string);
				if (myFlightHASHTABLE.validflightnumber(flightnum_string))
				{
					flightNumber = stoi(flightnum_string);
					break;
				}
				else
				{
					cout << "Invalid flight number please try again!!" << endl;
					continue;
				}
			} while (true);
			do
			{
				cout << "Please enter the country of origin: ";
				getline(cin, country_of_origin);
				if (myFlightHASHTABLE.validcoo(country_of_origin))
				{
					break;
				}
				else
				{
					cout << "Invalid country of origin please try again!!" << endl;
					continue;
				}
			} while (true);
			do
			{
				cout << "Please enter the country of destination: ";
				getline(cin, country_of_destination);
				if (myFlightHASHTABLE.validcod(country_of_destination))
				{
					break;
				}
				else
				{
					cout << "Invalid country of destination please try again!!" << endl;
					continue;
				}
			} while (true);
			do
			{
				cout << "Please enter the stopover: ";
				getline(cin, stopOver);
				if (myFlightHASHTABLE.validstopover(stopOver))
				{
					break;
				}
				else
				{
					cout << "Invalid stopover please try again!!" << endl;
					continue;
				}
			} while (true);
			do
			{
				cout << "Please enter the price: ";
				getline(cin, price);
				if (myFlightHASHTABLE.validprice(price))
				{
					break;
				}
				else
				{
					cout << "Invalid price please try again!!" << endl;
					continue;
				}
			} while (true);
			do
			{
				cout << "Please enter the time of departure in the format '23:00': ";
				getline(cin, time_of_departure);
				if (myFlightHASHTABLE.validtod(time_of_departure))
				{
					break;
				}
				else
				{
					cout << "Invalid time of departure please try again!!" << endl;
					continue;
				}
			} while (true);
			do
			{
				cout << "Please enter the time of arrival in the format '23:00': ";
				getline(cin, time_of_arrival);
				if (myFlightHASHTABLE.validtoa(time_of_arrival))
				{
					break;
				}
				else
				{
					cout << "Invalid time of arrival please try again!!" << endl;
					continue;
				}
			} while (true);
			do
			{
				cout << "Please enter the date in the format '1-Apr': ";
				getline(cin, date);
				if (myFlightHASHTABLE.validdate(date))
				{
					break;
				}
				else
				{
					cout << "Invalid date please try again!!" << endl;
					continue;
				}
			} while (true);
			Flight_Ticket *this_ticket = new Flight_Ticket(companyName, flightNumber, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);
			if (myFlightHASHTABLE.add(this_ticket) == 0)
			{
				cout << "Record already exist!!" << endl;
			}
			else
			{
				cout << "Ticket successfully added!!" << endl;
			}
		}
		else if (command == "delete")
		{
			myFlightHASHTABLE.removeRecord(parameter, stoi(parameter2));
		}
		else if (command == "find")
		{
			myFlightHASHTABLE.find(parameter, stoi(parameter2));
		}
		else if (command == "allinday")
		{
			do
			{
				if (myFlightHASHTABLE.validdate(parameter))
				{
					myFlightHASHTABLE.allinday(parameter);
					break;
				}
				else
				{
					cout << "Invalid date please try again!!" << endl;
					break;
				}
			} while (true);
		}
		else if (command == "printASC")
		{
			myFlightHASHTABLE.printASC(parameter, stoi(parameter2));
		}
		else if (command == "help")
		{
			listCommands();
		}
		else if (command == "exit")
		{
			break;
		}
		else if (command == "")
		{
			continue;
		}
		else
		{
			cout << "Invalid command!!" << endl;
		}
	} while (true);

	return 0;
}
