#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include<iostream>
#include<sstream>
#include "flightticket.h"
#include "mylist.h"
// include additional header files as needed

using namespace std;

class HashNode
{
	private:
		string key; // key = companyName+','+flightNumber
		Flight_Ticket value;
	public:
		HashNode(){}
		HashNode(string key, Flight_Ticket value)
		{
			this->key = key;
			this->value = value;
		}
		string getkey()
		{
			return key;
		}
		friend class FlightHASHTABLE;
};

//=============================================================================
class FlightHASHTABLE
{
	private:
		MyList<HashNode> *buckets;		//List of Buckets, Please create your own Linked List Class called MyList
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
		// add more attributes as needed
	public:
		FlightHASHTABLE();						//constructor
		~FlightHASHTABLE();						//destructor
		long hashCode(string key); 						//implement and test different hash functions 
		int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
		int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file
		int count_collisions();					//return the number of collisions in the HashTable
		int add(Flight_Ticket* data);			//add new flight to the HashTable
		void removeRecord (string companyName, int flightNumber);	//Delete a record with key from the hashtable
		void find(string companyName, int flightNumber);		//Find and Display records with same key entered 
		void allinday(string date);  					//Find and Display records with same day entered
		void printASC(string companyName, int flightNumber);  		//display the collisions for the entered key in an ascending order 
		void update_capacity(string path);


		// the following are functions to check for the validity of the input 
		bool validcompanyName(string companyName)
		{
			bool is_digit = all_of(companyName.begin(), companyName.end(),::isdigit);
			return !(is_digit);
		}
		bool validflightnumber(string flightNumber)
		{
			bool is_digit = all_of(flightNumber.begin(), flightNumber.end(),::isdigit);
			return (is_digit);
		}
		bool validcoo(string country_of_origin)
		{
			bool is_digit = all_of(country_of_origin.begin(), country_of_origin.end(),::isdigit);
			return !(is_digit);
		}
		bool validcod(string country_of_destination)
		{
			bool is_digit = all_of(country_of_destination.begin(), country_of_destination.end(),::isdigit);
			return !(is_digit);
		}
		bool validstopover(string stopOver)
		{
			bool is_digit = all_of(stopOver.begin(), stopOver.end(),::isdigit);
			return (is_digit);
		}
		bool validprice(string price)
		{
			bool is_digit = all_of(price.begin(), price.end(),::isdigit);
			return (is_digit);
		}
		bool validtod(string time_of_departure)
		{
			bool is_digit = all_of(time_of_departure.begin(), time_of_departure.end(),::isdigit);
			if (is_digit)
			{
				return false;
			}
			else
			{
				stringstream sstr(time_of_departure);
				if(isdigit(sstr.peek()))
				{
					int i;
					sstr>>i;
					if(sstr.peek() == ':' && i<24)
					{
						sstr.get();
						if(isdigit(sstr.peek()))
						{
							int w;
							sstr>>w;
							if (w<60)
							{
								return true;
							}
							else
							{
								return false;
							}	
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
			
		}
		bool validtoa(string time_of_arrival)
		{
			bool is_digit = all_of(time_of_arrival.begin(), time_of_arrival.end(),::isdigit);
			if (is_digit)
			{
				return false;
			}
			else
			{
				stringstream sstr(time_of_arrival);
				if(isdigit(sstr.peek()))
				{
					int i;
					sstr>>i;
					if(sstr.peek() == ':' && i<24)
					{
						sstr.get();
						if(isdigit(sstr.peek()))
						{
							int w;
							sstr>>w;
							if (w<60)
							{
								return true;
							}
							else
							{
								return false;
							}	
						}
						else
						{
							return false;
						}
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
		bool validdate(string date)
		{
			bool is_digit = all_of(date.begin(), date.end(),::isdigit);
			if (is_digit)
			{
				return false;
			}
			else
			{
				stringstream sstr(date);
				if(isdigit(sstr.peek()))
				{
					int i;
					sstr>>i;
					if(sstr.peek()=='-' && i<32)
					{
						sstr.get();
						while (!sstr.eof())
						{
							if(isdigit(sstr.peek()))
							{
								return false;
							}
							sstr.get();
						}
						return true;
					}
					else
					{
						return false;
					}
				}
				else
				{
					return false;
				}
			}
		}
		// add more methods as needed	
};

#endif