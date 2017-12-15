#include <iostream>

using std::cout;
static const int maxCapacity(50);
//ToDo: Dynamic allocation of every Wagon object in order to
//      accept maxCapacity as an argument of the constructor
//      http://lists.di.uoa.gr/showthread.php?t=4104
//      http://www.cplusplus.com/forum/general/52820/

/*******************************************************************************

*******************************************************************************/
class Passenger
{
private:
    //The following 3 variables get a suitable random value 
    //during initialiazation at the constructor
    bool hasTicket;
    bool rightForReducedTicket;
    int disembarkStation; 
    //When the train gets to disembarkStation station, get off the train
    //if busted betweenStations then disembarkStation = nextStation
    
    //if !hasTicket when ticketInspector enters the Waggon then busted=true
    bool busted;
};
class Wagon
{
private:
    Passenger *m_passengers;    //Pointer to a passengers array
    
    //Zero initialized at the constructor. Has to stay smaller than maxCapacity
    int m_passengersCount; 
    int m_maxCapacity;

public:
    //This constructor should create a wagon with empty Passenger seats 
    //Empty seats count should be 
    Wagon(): 
        m_maxCapacity(maxCapacity),     //ToDo:
        m_passengersCount(0)
    {
        m_passengers = new Passenger[maxCapacity];
        //ToDo: set to nullptr every seat
        cout << "A waggon with capacity for " << maxCapacity  
            << " passengers, was created \n";
    }
    
    ~Wagon()
    {
        delete[] m_passengers;
        
        cout << "A waggon was destroyed \n";
    }
    
    //Disembark the Passengers whose disembarkStation = currentStation.
    //Passenger objects will be deleted here after disembarkation
    void disembarkation()
    {
        
    }
    
    //Here create and embark a random count of new Passengers
    //newPassengersCount < emptySeats = (maxCapacity - currentPassengersCount)
    void embarkation()
    {
        
    }

    //inStation(currentStation) Probably I'll implement this in MetroTrain class
};
class MetroTrain
{
private:
    Wagon *m_wagons;        //Pointer to a dynamically allocated wagons array
    int m_wagonsCount;      //Length of the array. Represents the wagons count
    
    //Holds the current station id every time the train stops. Initialized to 0
    int m_currentStation;
    //int nextStation;
    
    //Money from passengers paying a fine after being found without a ticket.
    int m_totalRevenue;
    
public:
    MetroTrain(int wagonsCount): 
        m_wagonsCount(wagonsCount), m_currentStation(0), m_totalRevenue(0)
    {
        m_wagons = new Wagon[wagonsCount];  //ToDo
        cout << "A metro train with " << wagonsCount << " wagons, was created \n";
    }
    
    ~MetroTrain()
    {
        delete[] m_wagons;
        //we don't need to set m_wagons to null or m_wagonsCount to 0 here, 
        //since the object will be destroyed immediately after this function anyway
        
        cout << "A metro train was destroyed \n";
    }
    
    void operate(int stationsCount)
    {
        //inStation(currentStation);
        //betweenStations(previousStation, nextStation);
    }
    
    void printStatistics()
    {
        
    }
        
};

int main()
{
    
//Create a metroTrain that will operate for N stations
    MetroTrain testTrain(10);
    
    return 0;
}
