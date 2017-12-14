# Metro Train Simple Simulation using C++
Object Oriented Programming Course Assignment.

Exercise 1, part of the 1st groups of exersices (Aeroplana kai Vagonia!)


## Basic Object Classes
-----------------------
Here are the objects I'm going to work with and the data I need to know for each one of these.

#### MetroTrain
Member data might be:
- __trainWaggons__: Maybe an array of objects of type Waggon.
- __totalRevenue__: Money made from passengers paying tickets and fines.

#### Waggon
Member data might be:
- __currentPassengers__:
    Maybe an array of objects of type Passenger.
- __currentPassengersCount__:
    (Has to be smaller than maxCapacity)
Destroyed when the train is destroyed.

### Passenger
Member data might be:
- __hasTicket__ (boolean, randomly selected during object initialization)
- __rightForReducedTicket__ (same as above)
- __busted__ 
    if !hasTicket when ticketInspector enters the Waggon then busted=true
- __disembarkStation__ (When the train gets to this station, get of the train)
    if busted then disembarkStation = nextStation

__Destroyed when?__ After disembarkation:
- Immediately?
- First stored at the station and then destroyed with the station?

__Created when?__
- At the begining of the program, with the stations?
- Right before embarkation?
