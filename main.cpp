/*******************************************************************************
 [*] ToDo1:     Implement MetroTrain operate for N stations
 [*] 1.5:       Implement MetroTrain inStation
 [ ] 1.6:       Put first the public part in every class
 [*] ToDo2:     Passenger Constructor first implementation
 [ ] 2.5:       Passenger Destructor: do I need one?
 [ ] 2.6:       Modify Passenger constructor calls since now it accepts arguments
 [ ] 2.7:       Implement MetroTrain betweenStations
 [ ] ToDo3:     Study more examples of dynamic memory allocation, pointers to 
                pointers etc
 [ ] ToDo4:     Get the stationsCount from command line
 [ ] ToDo5:     Delete m_currentStation from MetroTrain class if not needed
 [ ] ToDo6:     Decide if stationsCount will be given in MetroTrain constructor or
                in operate 
 [ ] ToDo7:     Create an accessor for Passenger's busted variabl

*******************************************************************************/
#include <iostream>

using std::cout;


#include <cassert>

// Returns randomly true with a given probability between 0 and 1
// Assumes srand() has already been called
bool randomBoolWithProb(double probability)
{
    assert(probability>=0 && probability<=1);
    
    return rand()/(RAND_MAX+1.0) < probability;
}


// Generate a random number between min and max (inclusive)
// Assumes srand() has already been called
// Assumes max - min <= RAND_MAX
int getRandomNumber(int min, int max)
{
    // static used for efficiency, so we only calculate this value once
    static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);  
    // evenly distribute the random number across our range
    return min + static_cast<int>((max - min + 1) * (rand() * fraction));
}

class Passenger
{
private:
    bool m_hasTicket;
    bool m_rightForReducedTicket;
    //When the train gets to disembarkStation station, get off the train
    //if busted betweenStations then disembarkStation = nextStation
    int m_disembarkStation; 
    //if !hasTicket when ticketInspector enters the Waggon then busted=true
    bool m_busted;        //ToDo7: I will need an accessor for this one
    
public:
    //Temporary default constructor till constructor calls modification
    Passenger() { } 
    Passenger
    (
        const int disembarkStation,
        const double probHasTicket = 0.5,
        const double probReducedTicket = 0.5
    ):
       m_disembarkStation(disembarkStation),
       m_hasTicket(randomBoolWithProb(probHasTicket)),
       m_rightForReducedTicket(randomBoolWithProb(probReducedTicket)),
       m_busted(false)
    {
        
    }
    
    ~Passenger()
    {
        
    }
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
        //Tickets inspection process gets triggered here
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
