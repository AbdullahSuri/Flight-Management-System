#include "flighthashtable.h"
#include<fstream>


FlightHASHTABLE::FlightHASHTABLE() 
{
    size = 0;
    capacity = 31;
    buckets = new MyList<HashNode>[capacity];
}

FlightHASHTABLE::~FlightHASHTABLE() 
{
    delete[] buckets;
}

// //polynomial hash function with division compression function
// long FlightHASHTABLE::hashCode(string key)
// {
//     long hashcode = 0;
//     int key_length = key.length();
//     for (int i = 0; i < key_length; i++) 
//     {
//         if(isdigit(key[i]))
//         {
//             hashcode += key[i] - 48;
//         }
//         else
//         {
//             hashcode += key[i];
//             hashcode *= 2;  //a=2
//         }
//     }
//     return hashcode % capacity;  //compression function: division
// }

// //polynomial hash function with the mad method compression function
// long FlightHASHTABLE::hashCode(string key)
// {
//     long hashcode = 0;
//     int key_length = key.length();
//     for (int i = 0; i < key_length; i++) 
//     {
//         hashcode += (unsigned int) key[i];
//         hashcode *= 3;     //a=3
//     }
//     return ((hashcode*2+3) % capacity);   //compression function: mad method
// }

//cycle-shift hash function
long FlightHASHTABLE::hashCode(string key)
{
    long hashcode = 0;
    int key_length = key.length();
    for (int i = 0; i < key_length; i++) 
    {
        hashcode = (hashcode << 5) | (hashcode >> 27);  //5-bit shift
        hashcode += (unsigned int) key[i]; 
    }
    return hashcode % capacity;   //compression function: division function
}


int FlightHASHTABLE::add(Flight_Ticket* data)
{
    string key = data->getcompanyName() + ',' + to_string(data->getflightNumber());
    string hashcodekey = data->getcompanyName() + to_string(data->getflightNumber());
    HashNode hashnode(key, *data);
    int index = hashCode(hashcodekey);
    //case for if bucket is not empty, it then sorts the list on the basis of country of destination
    if (buckets[index].size != 0)
    {
        MyList<HashNode>::iterator it = buckets[index].begin();
        while (it != buckets[index].end())
        {
            if (hashnode.value.getcompanyName()==(*it).value.getcompanyName() && hashnode.value.getflightNumber()==(*it).value.getflightNumber() && hashnode.value.getcountry_of_origin()==(*it).value.getcountry_of_origin() && hashnode.value.getcountry_of_destination()==(*it).value.getcountry_of_destination() && hashnode.value.getstopOver()==(*it).value.getstopOver() && hashnode.value.getprice()==(*it).value.getprice() && hashnode.value.gettime_of_departure()==(*it).value.gettime_of_departure() && hashnode.value.gettime_of_arrival()==(*it).value.gettime_of_arrival() && hashnode.value.getdate()==(*it).value.getdate())
            {
                return 0;
            }
            
            if (hashnode.value.getcountry_of_destination() < (*it).value.getcountry_of_destination())
            {
                buckets[index].addBefore(it.getnode(), hashnode);
                break;
            }
            else
            {
                ++it;
            }
        }
    }    
    //simpley adds to the front if list is epmty 
    else
    {
        buckets[index].addFront(hashnode);
    }
    
    size++;
    return 1;
}

void FlightHASHTABLE::update_capacity(string path)
{
    int count = 0;
    ifstream fin(path);
    if (fin.is_open())
    {
        string line;
        getline(fin, line);
        while (getline(fin,line))
        {
            count++;
        }
    }
    fin.close();
    
    if (count >= capacity) 
    {
        // Create a new array of buckets
        int new_capacity = count * 1.3;
        MyList<HashNode>* new_buckets;
        new_buckets = new MyList<HashNode>[new_capacity];
        int temp = capacity;
        capacity = new_capacity;
        // Rehash all the elements into the new array
        for (int i = 0; i < temp; i++) 
        {
            for (MyList<HashNode>::iterator it = buckets[i].begin(); it != buckets[i].end(); ++it) 
            {
                HashNode newhash = (*it);
                int index = hashCode((*it).value.getcompanyName() + to_string((*it).value.getflightNumber()));
                new_buckets[index].addFront(newhash);
            }
        }
        

        delete[] buckets;
        

        
        buckets = new_buckets;
    }
    
}

int FlightHASHTABLE::importCSV(string path)
{
    int count = 0;
    update_capacity(path);
    string companyName, flightNumber, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date, flightnum_string;
    ifstream fin(path);
    if (!fin.is_open()) 
    {
        cout << "Error opening file, check your path or file name! " << endl;
        return -1;
    }
    string line;
    getline(fin, line);
    //uses string stream to store all elements into variables
    while (getline(fin, line)) 
    {
        stringstream sstr(line);
        getline(sstr, companyName, ',');
        getline(sstr, flightNumber, ',');
        getline(sstr, country_of_origin, ',');
        getline(sstr, country_of_destination, ',');
        getline(sstr, stopOver, ',');
        getline(sstr, price, ',');
        getline(sstr, time_of_departure, ',');
        getline(sstr, time_of_arrival, ',');
        getline(sstr, date, '\r');
        
        if (validcompanyName(companyName) && validflightnumber(flightNumber) && validcoo(country_of_origin) && validcod(country_of_destination) && validstopover(stopOver) && validprice(price) && validtod(time_of_departure) && validtoa(time_of_arrival) && validdate(date))
        {
            Flight_Ticket* this_ticket = new Flight_Ticket(companyName, stoi(flightNumber), country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);
			this->add(this_ticket);
            count++;
        }
    }
    fin.close();
    return count;
}



int FlightHASHTABLE::count_collisions()
{
    int collisions = 0;
    //iterates over the entire hash table and checks in each bucket if there are more than one unique keys.
    for (int i = 0; i < capacity; i++)
    {   
        int key_unique = 0;
      
        for (MyList<HashNode>::iterator itr = buckets[i].begin(); itr != buckets[i].end(); ++itr)
        {
            bool uniquekey = true;
            for (MyList<HashNode>::iterator itr2 = itr; itr2 != buckets[i].end(); ++itr2)
            {
                if(itr==itr2) 
                {
                    continue;
                }
                else if((*itr).getkey() == (*itr2).getkey())
                {
                    uniquekey = false;
                    break;
                }
            }
            if(uniquekey)
            {
                key_unique++;
            }
        }
        //if more than one unique keys collision is the number of unique keys -1
        collisions += max(0,key_unique-1);
        
    }
    return collisions;
}



void FlightHASHTABLE::printASC(string companyName, int flightNumber)
{
    //simply prints, as we already sorted in the add function on the basis of destination of flight
    string key = companyName + ',' + to_string(flightNumber);
    string hashcodekey = companyName + to_string(flightNumber);
    int index = hashCode(hashcodekey);
    for(MyList<HashNode>::iterator itr = buckets[index].begin(); itr != buckets[index].end(); ++itr)
    {
        if ((*itr).getkey() == key)
        {
            cout<<(*itr).value.getcompanyName()<<","<<(*itr).value.getflightNumber()<<","<<(*itr).value.getcountry_of_origin()<<","<<(*itr).value.getcountry_of_destination()<<","<<(*itr).value.getstopOver()<<","<<(*itr).value.getprice()<<","<<(*itr).value.gettime_of_departure()<<","<<(*itr).value.gettime_of_arrival()<<","<<(*itr).value.getdate()<<","<<endl;
        }
    }
}

void FlightHASHTABLE::removeRecord(string companyName, int flightNumber)
{
    string key = companyName + ',' + to_string(flightNumber);
    string hashcodekey = companyName + to_string(flightNumber);
    int index = hashCode(hashcodekey);
    int num_record = 0;
    string del_record;
    //gets the number of records and prints them out
    for(MyList<HashNode>::iterator itr = buckets[index].begin(); itr != buckets[index].end(); ++itr)
    {
        if ((*itr).getkey() == key)
        {
            num_record++;
            cout<<num_record<<"."<<(*itr).value.getcompanyName()<<","<<(*itr).value.getflightNumber()<<","<<(*itr).value.getcountry_of_origin()<<","<<(*itr).value.getcountry_of_destination()<<","<<(*itr).value.getstopOver()<<","<<(*itr).value.getprice()<<","<<(*itr).value.gettime_of_departure()<<","<<(*itr).value.gettime_of_arrival()<<","<<(*itr).value.getdate()<<","<<endl;
        }
    }
    //ask user which record to delete and then removes that record on the basis of userinput
    if (num_record >= 1)
    {
        cout<<num_record<<" records found"<<endl;
        
        do
        {
            cout<<"Please select the record you want to delete: ";
            getline(cin, del_record);
            bool is_digit = all_of(del_record.begin(), del_record.end(),::isdigit);
            if (is_digit && stoi(del_record)<=num_record)
            {
                break;
            }
            else
            {
                cout<<"Please enter a valid number"<<endl;
                continue;
            }
        } 
        while (true);
        int delrecord = stoi(del_record);
        int tempcount = 0;
        for(MyList<HashNode>::iterator itr = buckets[index].begin(); itr != buckets[index].end(); ++itr)
        {
            if ((*itr).getkey() == key)
            {
                tempcount++;
                if(tempcount == delrecord)
                {
                    buckets[index].erase(itr);
                    size--;
                    break;
                }
            }
        }
    }
    else
    {
        cout<<"no records found!!"<<endl;
    }
}

void FlightHASHTABLE::find(string companyName, int flightNumber)
{
    string key = companyName + ',' + to_string(flightNumber);
    string hashcodekey = companyName + to_string(flightNumber);
    int index = hashCode(hashcodekey);
    
    int num_record = 0;
    //goes to the specific bucket, iterates through the bucket and lists all the objects with same key
    for(MyList<HashNode>::iterator itr = buckets[index].begin(); itr != buckets[index].end(); ++itr)
    {
        if ((*itr).getkey() == key)
        {
            num_record++;
            cout<<num_record<<". "<<(*itr).value.getcompanyName()<<","<<(*itr).value.getflightNumber()<<","<<(*itr).value.getcountry_of_origin()<<","<<(*itr).value.getcountry_of_destination()<<","<<(*itr).value.getstopOver()<<","<<(*itr).value.getprice()<<","<<(*itr).value.gettime_of_departure()<<","<<(*itr).value.gettime_of_arrival()<<","<<(*itr).value.getdate()<<","<<endl;
        }
    }
    if(num_record == 0)
    {
        cout << "Not found!!" << endl;
    }
    cout<<num_record<<" records found!!"<<endl;
}

void FlightHASHTABLE::allinday(string date)
{
    int count = 0;
    //iterates through all buckets and lists all the objects with same date
    for (int i = 0; i < capacity; i++)
    {
        for(MyList<HashNode>::iterator itr = buckets[i].begin(); itr != buckets[i].end(); ++itr)
        {
            string fileDate = (*itr).value.getdate();
            bool check = (fileDate == date);
            if(check)
            {
                count++;
                cout<<count<<". "<<(*itr).value.getcompanyName()<<","<<(*itr).value.getflightNumber()<<","<<(*itr).value.getcountry_of_origin()<<","<<(*itr).value.getcountry_of_destination()<<","<<(*itr).value.getstopOver()<<","<<(*itr).value.getprice()<<","<<(*itr).value.gettime_of_departure()<<","<<(*itr).value.gettime_of_arrival()<<","<<(*itr).value.getdate()<<"\n";
            }
        }
    }
    cout<< count<< " records found!!"<<endl;
    
}

int FlightHASHTABLE::exportCSV(string path)
{
    // Open the output file and prints all tickets into it
    
    ofstream file(path);
    int count = 0;
    if (!file.is_open()) 
    {
        return -1; 
    }
    
    if (size == 0)
    {
        return 0;
    }
    else
    {
        for (int i = 0; i < capacity; i++) 
        {
            if (buckets[i].size>0)
            {
                for(MyList<HashNode>::iterator itr = buckets[i].begin(); itr != buckets[i].end(); ++itr)
                {
                    file<<(*itr).value.getcompanyName()<<","<<(*itr).value.getflightNumber()<<","<<(*itr).value.getcountry_of_origin()<<","<<(*itr).value.getcountry_of_destination()<<","<<(*itr).value.getstopOver()<<","<<(*itr).value.getprice()<<","<<(*itr).value.gettime_of_departure()<<","<<(*itr).value.gettime_of_arrival()<<","<<(*itr).value.getdate()<<"\n";
                    count++;
                }
            }
        }
    }
    file.close();

    return count; 
}





