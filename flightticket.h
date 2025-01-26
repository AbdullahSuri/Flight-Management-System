#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include<iostream>

using namespace std;

class Flight_Ticket
{
	private:
		string companyName;
		int flightNumber;
		string country_of_origin;
		string country_of_destination;
		string stopOver;
		string price;
		string time_of_departure;
		string time_of_arrival;
		string date;

	public:
		Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date);
		Flight_Ticket() {};
		//getter functions
		string getcompanyName() const 
		{ 
			return companyName; 
		}
		int getflightNumber() const 
		{ 
			return flightNumber; 
		}
		string getcountry_of_origin() const
		{ 
			return country_of_origin; 
		}
		string getcountry_of_destination() const 
		{ 
			return country_of_destination; 
		}
		string getstopOver() const 
		{ 
			return stopOver; 
		}
		string getprice() const 
		{ 
			return price; 
		}
		string gettime_of_departure() const 
		{ 
			return time_of_departure; 
		}
		string gettime_of_arrival() const 
		{ 
			return time_of_arrival; 
		}
		string getdate() const 
		{ 
			return date; 
		}
		
		// add additional methods as needed
};

#endif
