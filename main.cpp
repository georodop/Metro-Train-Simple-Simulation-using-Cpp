/*******************************************************************************
 [*] ToDo1:     Implement MetroTrain operate for N stations
 [*] 1.5:       Implement MetroTrain inStation
 [ ] 1.6:       Put first the public part in every class
 [*] ToDo2:     Passenger Constructor first implementation
 [*] 2.3:       Change Passenger to PassengerSeat and hold if the seat is empty
 [*] 2.4:       REVERT! A seat is empty when set to nullptr. Passengers should
                be created during Wagon's embarkation
 [*] 2.45:      Wagon's embarkation() first implementation
 [*] 2.47:      Wagon's disembarkation() first implementation
 [*] 2.48:      Modify embarkation() to check in a loop every seat if it is empty
 [*] 2.6:       Modify Passenger constructor calls since now it accepts arguments
 [*] 2.8:       Implement MetroTrain betweenStations
 [*] ToDo4:     Get the stationsCount from command line
 [*] ToDo5:     Delete m_currentStation from MetroTrain class if not needed
 [*] ToDo6:     Decide if stationsCount will be given in MetroTrain constructor or
                in operate. Answer: in operate.
 [*] ToDo7:     printStatistics:+ train's total revenue from ticket inspections
 [ ] ToDo10:    Separate .cpp and .h files

*******************************************************************************/
#include <iostream>
#include <cassert>
#include <cstdlib>       //For c++98 compatible rand()

using std::cout;
using std::cin;

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
    bool m_busted;        //ToDo7: I'll need an accessor and a mutator for this
    
public:
    //Temporary default constructor till constructor calls modification
    Passenger() { } 
    Passenger
    (
        const int disembarkStation,
        const double probHasTicket = 0.7,
        const double probReducedTicket = 0.5
    ):
        m_disembarkStation(disembarkStation),
        m_hasTicket(randomBoolWithProb(probHasTicket)),
        m_rightForReducedTicket(randomBoolWithProb(probReducedTicket)),
        m_busted(false)
    {
        static int passengerId(0);
        passengerId++;
        // cout << "New Passenger with id: " 
        //     << passengerId << " and destination: " << m_disembarkStation << "\n";
        
    }
    
    ~Passenger()
    {
        
    }
    
    int getDisembarkStation() { return m_disembarkStation; }
    int getHasTicket() { return m_hasTicket; }
    void setDestination(int station) {  m_disembarkStation = station; }
    
};
    
//Auxiliary data type to be used by Wagon and MetroTrain objects
struct Statistics
{
    int totalWithoutTicket;
    int totalBusted;
    int totalGotAway;
    
    Statistics(): totalWithoutTicket(0), totalBusted(0), totalGotAway(0) {  }
};

Statistics operator+(const Statistics &stat1, const Statistics &stat2)
{
    Statistics stats;
	stats.totalWithoutTicket = stat1.totalWithoutTicket + stat2.totalWithoutTicket;
	stats.totalBusted = stat1.totalBusted + stat2.totalBusted;
	stats.totalGotAway = stat1.totalGotAway + stat2.totalGotAway;
 
	return stats;
}

class Wagon
{
private:
    Passenger** m_passengers;    //Pointer to a passengers array
    
    //Zero initialized at the constructor. Has to stay smaller than maxCapacity
    int m_passengersCount; 
    int m_maxCapacity;
    int m_totalWithoutTicket;
    int m_totalBusted;
    
public:
    //This constructor should create a wagon with empty Passenger seats 
    //An empty seat is marked with a nullptr.
    Wagon(int maxCapacity): 
        m_maxCapacity(maxCapacity),
        m_passengersCount(0),
        m_totalWithoutTicket(0),
        m_totalBusted(0)
    {
        m_passengers = new Passenger*[maxCapacity];
        for(int i(0); i<maxCapacity; i++)
        {
            // m_passengers[i] = new Passenger(7); //ToDo: New argument
            m_passengers[i] = NULL;
        }
        //Old: m_passengers = new Passenger[maxCapacity];
        cout << "A wagon with capacity for " << maxCapacity  
            << " passengers, was created \n";
    }
    
    ~Wagon()
    {
        for(int i(0); i<m_maxCapacity; i++)
        {
            delete m_passengers[i];
        }
        delete[] m_passengers;
        
        cout << "A wagon was destroyed \n";
    }
    
    //Disembark the Passengers whose disembarkStation == currentStation.
    //Passenger objects will be deleted here after disembarkation
    //Returns the count of disembarked passengers
    int disembarkation(const int &currentStation)
    {
        if (currentStation == 1)    //No passengers yet if it's the 1st station
            return 0;
        int initialCount = m_passengersCount;       //Before disembarkation
        for(int i(0); i<m_maxCapacity; i++)
        {
            if(m_passengers[i]!=NULL)            //The seat is not empty
            {
                if(currentStation == m_passengers[i]->getDisembarkStation())
                {
                    delete m_passengers[i];
                    m_passengers[i] = NULL;
                    m_passengersCount--;
                }
            }
        }
        int disembarkedCount = initialCount - m_passengersCount;
        // cout << disembarkedCount << " passengers disembarked \n";
        return disembarkedCount;
    }
    
    //Here create and embark a random count of new Passengers
    //We also set the destination station for every new passenger
    //Returns the count of passengers that just embarked
    int embarkation(const int &currentStation, const int &stationsCount)
    {
        if(currentStation == stationsCount)
            return 0;                       //No embarkation at the last station
        int emptySeatsCount = (m_maxCapacity - m_passengersCount);
        int newPassengersCount = getRandomNumber(0, emptySeatsCount);
        
        for
        (
            int seat(0), passenger(0);
            seat < m_maxCapacity && passenger < newPassengersCount; 
            seat++
        )
        {
            if(m_passengers[seat] == NULL)
            {
                int destination = getRandomNumber(currentStation+1, stationsCount);
                m_passengers[seat] = new Passenger(destination);
                m_passengersCount++;
                passenger++;
                
                if(!m_passengers[seat]->getHasTicket())     //No ticket !
                {
                    m_totalWithoutTicket++;
                }
            }
        }
        // cout << emptySeatsCount << " empty seats. \t" << newPassengers <<" / "<< newPassengersMax
        //     << " new passengers. \t" << m_passengersCount << " pre-existing passengers. \n";
        return newPassengersCount;
    }
    
    //Loops through all the wagon's passengers to check if they have ticket
    //For passengers found without ticket disembarkStation=nextStation
    int ticketsInspection(const int &nextStation)
    {
        int bustedCount(0);
        for(int seat(0); seat<m_maxCapacity; seat++)
        {
            if(m_passengers[seat] != NULL)           //The seat is not emtpy
            {
                if(!m_passengers[seat]->getHasTicket())     //No ticket !
                {
                    //cout << "Busted !!!\n";
                    m_passengers[seat]->setDestination(nextStation);
                    bustedCount++;
                    m_totalBusted++;
                }
            }
        }
        return bustedCount;
    }

    Statistics printStatistics()
    {
        /***********************************************************************
         * ToDo: Store in the Wagon instances the statistics needed bellow
         * ToDo: Print statistics about:
         * - How many passengers entered this wagon without a ticket throughout
         *   its whole operation
         * - How many of the above were busted.
         * Optionaly:
         * - What is the total count of passengers that entered the wagon
         * - How many had a reduced ticket
         * ********************************************************************/
        Statistics wagonStatistics;
        wagonStatistics.totalWithoutTicket = m_totalWithoutTicket;
        wagonStatistics.totalBusted = m_totalBusted;
        wagonStatistics.totalGotAway = m_totalWithoutTicket - m_totalBusted;
        cout << "Embarked without a ticket: " << m_totalWithoutTicket << "\n";
        cout << "Busted: " << m_totalBusted ;
        cout << " Got away: " << wagonStatistics.totalGotAway << "\n";
                    
        return wagonStatistics;
    }
    
};

class MetroTrain
{
private:
    //Pointer to a dynamically allocated array of pointers to wagons
    Wagon** m_wagons;       
    int m_wagonsCount;      //Length of the array. Represents the wagons count
    
    //Money from passengers paying a fine after being found without a ticket.
    int m_totalRevenue;
    
    //This will be set every time during inStation and accessed betweenStations
    int m_wagonForNextInspection;               //min=0, max = m_wagonsCount -1
    
    
    //Here I need to know if this is the last station in order to disembark all
    void inStation (const int &currentStation, const int &stationsCount)
    {
        cout << "inStation: " << currentStation << "\n";
        
        //ToDo: Find a way to mark a wagon as m_wagonForNextInspection. This can be
        //      an int var of MetroTrain class or a boolean of the Wagon class
        //Here loop through the wagons and disembark first/embark then
        for(int i(0); i<m_wagonsCount; i++)
        {
            int disembarked = m_wagons[i]->disembarkation(currentStation);
            int embarked = m_wagons[i]->embarkation(currentStation, stationsCount);
            // cout << "Wagon " << i+1 << " / " << m_wagonsCount << "\n";
            // cout << disembarked << " disembarked. \t" << embarked << " embarked.\n";
        }
        //Choose a wagon for the next ticket inspection
        m_wagonForNextInspection = getRandomNumber(0, m_wagonsCount-1);
        
    }
    
    void betweenStations(const int nextStation)
    {
        //Tickets inspection process gets triggered here:
        //- Get from a MetroTrain int var, e.g. m_wagonForNextInspection, which 
        //wagon should be checked.
        //- Call a Wagon's function, e.g. ticketsInspection, in order to change
        //the destination of the busted passengers. This function should
        //return the count of the passengers found without ticket
        assert(m_wagonForNextInspection<m_wagonsCount);
        assert(!(m_wagonForNextInspection < 0));
        int countBusted = m_wagons[m_wagonForNextInspection]->ticketsInspection(nextStation);
        // cout << "Tickets Inspection in wagon " << m_wagonForNextInspection+1
        //         << ". " << countBusted << " Busted !\n";
    }
    
    
public:
    MetroTrain(int wagonsCount, int wagonMaxCapacity): 
        m_wagonsCount(wagonsCount), 
        m_totalRevenue(0), m_wagonForNextInspection(-1)
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
        //since the object will be destroyed immediately after this function 
        
        cout << "A metro train was destroyed \n";
    }
    
    void operate(int stationsCount)
    {
        cout << "Train operates now \n";
        for(int i(1); i<=stationsCount; i++)
        {
            int &currentStation = i;    //Just an alias
            
            bool isLastStation = (currentStation == stationsCount) ;
            inStation(currentStation, stationsCount);
            if(!isLastStation)
            {
                betweenStations(currentStation+1);
            }
        }
    }
    
    void printStatistics()
    {
        /***********************************************************************
         * ToDo: Should print the following statistics for the metroTrain:
         * - Money collected during ticket inspections
         * Should call Wagon's printStatistics for every wagon.
         * ********************************************************************/
         
        Statistics trainStats; 
        for(int i(0); i<m_wagonsCount; i++)
        {
            cout << "\nWagon num. " << i+1 << " of " << m_wagonsCount << "\n";
            Statistics wagonStats = m_wagons[i]->printStatistics();
            trainStats = trainStats + wagonStats;
        }
        
        
        cout << "\nStatistics for the whole train: \n";
        cout << "Embarked without a ticket: " ;
        cout << trainStats.totalWithoutTicket << "\n";
        cout << "Busted: " << trainStats.totalBusted ;
        cout << " Got away: " << trainStats.totalGotAway << "\n";
        cout << "Total income from fines: " << trainStats.totalBusted * 60 << " Euro\n";
    }
        
};

int main()
{
    srand(time(0));         //In order to use rand in many different places
    
    cout << "How many stations do you want the train to operate for?\n";
    cout << "Please enter an integer: ";
    int inputN;
    cin >> inputN;
    const int wagonsCount(10), wagonMaxCapacity(30), stationsCount(inputN);
    
    //Create a metroTrain that will operate for N stations
    MetroTrain metroTrain1(wagonsCount, wagonMaxCapacity);
    
    metroTrain1.operate(stationsCount);
    metroTrain1.printStatistics();
    
    return 0;
}
