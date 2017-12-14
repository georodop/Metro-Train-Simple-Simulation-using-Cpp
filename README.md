# Metro Train Simple Simulation using C++
Object-Oriented Programming Course Assignment.

Exercise 1, part of the 1st groups of exercises (Aeroplana kai Vagonia!)


## First attempt to describe the required Classes, data members, and functions.
-----------------------------------------------------------------------------

#### MetroTrain
Member data might be:
- __trainWaggons__: Maybe an array of objects of type Waggon.
- __totalRevenue__: Money made from passengers paying tickets and fines.

Member functions might be:
- __operate(int stationsCount)__: Operate the train and its waggons for stationsCount = N.
    - inStation
    - betweenStations
- __printStatistics()__

#### Waggon
Member data might be:
- __currentPassengers__:
    Maybe an array of objects of type Passenger.
- __currentPassengersCount__:
    (Zero initialized. Has to stay smaller than maxCapacity)

Destroyed when the train is destroyed.

Member functions might be:
- __inStation(currentStation)__
    - disembarkation(): Disembark the Passengers whose disembarkStation = currentStation.
    - embarkation(): Embark newPassengers random newPassengersCount < emptySeats = (maxCapacity - currentPassengersCount).
    Problem: should I create here the newPassengers or create them at the stations and just move them.
    


### Passenger
Member data might be:
- __hasTicket__ (boolean, randomly selected during object initialization)
- __rightForReducedTicket__ (same as above)
- __busted__ 
    if !hasTicket when ticketInspector enters the Waggon then busted=true
- __disembarkStation__ (When the train gets to this station, get off the train)
    if busted betweenStations then disembarkStation = nextStation

__Destroyed when?__ After disembarkation:
- Immediately?
- First stored at the station and then destroyed with the station?

__Created when?__
- At the beginning of the program, with the stations?
- Right before embarkation?


## Open Questions
-----------------
- Where to create and destroy the Passengers.
    - Let the embarkation/disembarkation processes of the Wagon objects handle this?
    - Create them at the stations and just move them on/off the train wagons?
- Which class should be responsible for tickets inspection.
    - MetroTrain if I want the train to control how many wagons can be checked at the same time.
    - Waggon if I don't care for the above and just want to implement this as a possibility per wagon.
    - A separate class TicketsInspector if I want more flexibility to create as many TicketsInspector objects as I want and 
