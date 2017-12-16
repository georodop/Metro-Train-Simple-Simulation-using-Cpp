#include <iostream>

using std::cout;

/*******************************************************************************
 [*] ToDo1: Implement MetroTrain operate for N stations
 [*] 1a:    Implement MetroTrain inStation
 [ ] 2a:    Implement MetroTrain betweenStations
 [ ] ToDo2: Implement Passenger constructor/destructor
 [ ] ToDo3: Study more examples of dynamic memory allocation, pointers to 
            pointers etc
 [ ] ToDo4: Get the stationsCount from command line
 [ ] ToDo5: Delete m_currentStation from MetroTrain class if not needed
 [ ] ToDo6: Decide if stationsCount will be given in MetroTrain constructor or
            in operate 

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
    Wagon(int maxCapacity): 
        m_maxCapacity(maxCapacity),
        m_passengersCount(0)
    {
        m_passengers = new Passenger[maxCapacity];
        //ToDo: set to nullptr every seat
        cout << "A wagon with capacity for " << maxCapacity  
            << " passengers, was created \n";
    }
    
    ~Wagon()
    {
        delete[] m_passengers;
        
        cout << "A wagon was destroyed \n";
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
        // static int count;
        // count++;
        // cout << "Embarkation count " << count << "\n";
    }

    //inStation(currentStation) Probably I'll implement this in MetroTrain class
};

class MetroTrain
{
private:
    //Pointer to a dynamically allocated array of pointers to wagons
    Wagon** m_wagons;       
    int m_wagonsCount;      //Length of the array. Represents the wagons count
    
    //ToDo5: Delete if redundant
    //Holds the current station id every time the train stops. Initialized to 0
    int m_currentStation;
    //int nextStation;
    
    //Money from passengers paying a fine after being found without a ticket.
    int m_totalRevenue;
    
    
    //Here I need to know if this is the last station in order to disembark all
    void inStation(const int &currentStation, const bool &isLastStation)
    {
        cout << "inStation: " << currentStation << "\n";
        
        const bool isFirstStation = (currentStation == 1);
        if(!isFirstStation)     //First disembark
        {
            //Here loop through the wagons and call Wagon's disembarkation()
            for(int i(0); i<m_wagonsCount; i++)
            {
                m_wagons[i]->disembarkation();
            }
        }
        if(!isLastStation)      //Then embark
        {
            //Here loop through the wagons and call Wagon's embarkation()
            for(int i(0); i<m_wagonsCount; i++)
            {
                m_wagons[i]->embarkation();
            }
        }
        
    }
    
    void betweenStations()
    {
        
    }
    
    
public:
    MetroTrain(int wagonsCount, int wagonMaxCapacity): 
        m_wagonsCount(wagonsCount), m_currentStation(0), m_totalRevenue(0)
    {
        m_wagons = new Wagon*[wagonsCount];
        for(int i=0; i<wagonsCount; i++)
        {
            m_wagons[i] = new Wagon(wagonMaxCapacity);
        }
        
        cout << "A metro train with " << wagonsCount << " wagons, was created \n";
    }
    
    ~MetroTrain()
    {
        for(int i=0; i<m_wagonsCount; i++)
        {
            delete m_wagons[i];
        }
        delete[] m_wagons;
        //we don't need to set m_wagons to null or m_wagonsCount to 0 here, 
        //since the object will be destroyed immediately after this function anyway
        
        cout << "A metro train was destroyed \n";
    }
    
    void operate(int stationsCount)
    {
        cout << "Train operates now \n";
        for(int i(1); i<=stationsCount; i++)
        {
            int &currentStation = i;    //Just an alias
            
            bool isLastStation = (currentStation == stationsCount) ;
            inStation(currentStation, isLastStation);
            if(!isLastStation)
            {
                betweenStations();
            }
        }
    }
    
    void printStatistics()
    {
        
    }
        
};

int main()
{
    const int wagonsCount(10), wagonMaxCapacity(50), stationsCount(7);
    
    //Create a metroTrain that will operate for N stations
    MetroTrain metroTrain1(wagonsCount, wagonMaxCapacity);
    
    metroTrain1.operate(stationsCount);
    
    return 0;
}
