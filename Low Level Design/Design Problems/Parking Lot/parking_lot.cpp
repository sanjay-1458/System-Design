#include <iostream>
#include <string>
#include <ctime> 
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

enum class VehicleType {

    BIKE,
    CAR,
    TRUCK
};

class Vehicle {

private:

    string numberPlate;
    VehicleType type;

public:

    Vehicle(string numberPlate, VehicleType type) {

        this -> numberPlate = numberPlate;
        this -> type = type;
    }

    string getNumberPlate() {

        return numberPlate;
    }

    VehicleType getType() const {

        return type;
    }
};

enum class SlotType {

    SMALL,
    MEDIUM,
    BIG
};

class ParkingSpot {

private:

    int id;
    SlotType type;
    Vehicle* parkedVehicle;

public:

    ParkingSpot(int id, SlotType type) {

        this -> id = id;
        this -> type = type;
        parkedVehicle = nullptr;
    }

    int getId() const {

        return id;
    }

    bool isOccupied() const {

        return parkedVehicle != nullptr;
    }

    SlotType getSlotType() const {

        return type;
    }

    bool parkVehicle(Vehicle* vehicle) {

        if(isOccupied()) {

            return false;
        }
        parkedVehicle = vehicle;

        return true;
    }

    void removeVehicle() {

        parkedVehicle = nullptr;
    }
};


enum class TicketStatus {

    ACTIVE,
    CLOSED
};

class Ticket {
    
private:
    
    int id;
    time_t entryTime;
    TicketStatus status;
    Vehicle* vehicle;
    ParkingSpot* spot;


public:

    Ticket(int id, Vehicle* vehicle, ParkingSpot* spot)  {

        this -> id = id;
        entryTime = time(nullptr);
        status = TicketStatus::ACTIVE;
        this -> vehicle = vehicle;
        this -> spot = spot;
    }

    double getParkingDurationInMinutes() const {

        time_t exitTime = time(nullptr);

        double seconds = difftime(exitTime, entryTime);

        return seconds / 60.0;
    }

    TicketStatus getStatus() const {

        return status;
    }

    int getId() const {

        return id;
    }

    void closeTicket() {

        status = TicketStatus::CLOSED;
    }

    ParkingSpot* getParkingSpot() {

        return spot;
    }
};


class SpotAllocationStrategy {

public:


    virtual ParkingSpot* findAvailableSpot(VehicleType type, vector<ParkingSpot*> spots) = 0;
    virtual ~SpotAllocationStrategy() = default;
};

class SimpleSearch : public SpotAllocationStrategy {

    bool canFitVechile(SlotType slot, VehicleType vechile) {

        if(vechile == VehicleType::BIKE) {

            return true;
        }
        if(vechile == VehicleType::CAR) {

            return (slot == SlotType::MEDIUM || slot == SlotType::BIG);
        }
        if(vechile == VehicleType::TRUCK) {

            return slot == SlotType::BIG;
        }

        return false;
    }

public:


    ParkingSpot* findAvailableSpot(VehicleType type, vector<ParkingSpot*> spots) override {

        for(auto spot : spots) {

            if(spot -> isOccupied() == false && canFitVechile(spot -> getSlotType(), type)) {

                return spot;
            }
        }

        return nullptr;
    }    
};

class ParkingLevel {

private:

    int floorNumber;
    vector<ParkingSpot*> spots;
    

public: 

    ParkingLevel(int floorNumber) {

        this -> floorNumber = floorNumber;
    }

    void addParkingSpot(ParkingSpot* spot) {

        spots.push_back(spot);
    }


    int getAvailableSpotCount() const {

        int freeSpots = 0;

        for(auto spot : spots) {

            if(spot -> isOccupied() == false) {

                freeSpots++;
            }
        }

        return freeSpots;
    }

    vector<ParkingSpot*> getParkingSpots() {

        return spots;
    }
};


class ParkingLot {

private:    

    vector<ParkingLevel*> floorNumbers;
    string address;

public:

    ParkingLot(string address) {

        this -> address = address;
    }

    void addLevel(ParkingLevel* floorNumber) {

        floorNumbers.push_back(floorNumber);
    }

    vector<ParkingLevel*> getFloors() {

        return floorNumbers;
    }
};

class ParkingManager {

private:

    ParkingLot* parkingLot;

    int ticketCounter = 0;

    SpotAllocationStrategy* strategy;


    Ticket* checkAndBook(ParkingLevel* floor, ParkingSpot* spot, Vehicle* vehicle) {

        if(spot -> parkVehicle(vehicle)) {

            Ticket* ticket = new Ticket(++ticketCounter, vehicle, spot);

            return ticket;
        }

        return nullptr;
    }

    map<Vehicle*, Ticket*> ticketsVehicleMap;
    map<int, Ticket*> ticketMap;

public:

    ParkingManager(ParkingLot* parkingLot, SpotAllocationStrategy* strategy) {

        this -> parkingLot = parkingLot;
        this -> strategy = strategy;
    }

    void parkVechile(Vehicle* vehicle) {

        vector<ParkingLevel*> floors = parkingLot -> getFloors();

        ParkingSpot* spot = nullptr;
    
        for(auto floor : floors) {

            if(floor -> getAvailableSpotCount() != 0) {

                spot = strategy->findAvailableSpot(vehicle -> getType(), floor -> getParkingSpots());

                if(spot != nullptr) {

                    Ticket* ticket = checkAndBook(floor, spot, vehicle);

                    if(ticket == nullptr) {

                        continue;
                    }

                    cout<<"Vehicle is Parked Successfully"<<endl;
                    cout<<"Ticket is generated with ID: "<<ticket -> getId()<<endl;

                    ticketMap[ticket -> getId()] = ticket;
                    ticketsVehicleMap[vehicle] = ticket;
                    return;
                }
            }
        }

        cout<<"No parking spot is available"<<endl;
    }

    void removeVechile(Vehicle* vehicle) {


        if(ticketsVehicleMap.find(vehicle) == ticketsVehicleMap.end()) {

            cout<<"This vehicle does not exist"<<endl;

            return;
        }

        Ticket* ticket = ticketsVehicleMap[vehicle];

        double cost = ticket -> getParkingDurationInMinutes();

        cout<<"Cost for parking is: "<<cost<<endl;

        ticket -> closeTicket();

        ParkingSpot* spot = ticket -> getParkingSpot();

        spot -> removeVehicle();
    }

    int getAvailableSpotCount() {

        int emptySlots = 0;

        vector<ParkingLevel*> floors = parkingLot -> getFloors();

        for(auto floor : floors) {

            emptySlots += floor -> getAvailableSpotCount();
        }

        return emptySlots;
    }

    Ticket* findTicketById(int id) {

        return ticketMap[id];
    }

};


int main() {

    ParkingLot parkingLot("Location 1");

    ParkingLevel parkingLevel1(1);
    ParkingLevel parkingLevel2(2);
    
    parkingLot.addLevel(&parkingLevel1);
    parkingLot.addLevel(&parkingLevel2);

    ParkingSpot spot1(1, SlotType::BIG);
    ParkingSpot spot2(2, SlotType::SMALL);
    ParkingSpot spot3(3, SlotType::MEDIUM);

    parkingLevel1.addParkingSpot(&spot1);
    parkingLevel1.addParkingSpot(&spot2);
    parkingLevel2.addParkingSpot(&spot3);

    SpotAllocationStrategy* strategy = new SimpleSearch();

    ParkingManager parkingManager(&parkingLot, strategy);

    Vehicle car1("cat-1200", VehicleType::CAR);
    Vehicle car2("cat-1201", VehicleType::CAR);
    Vehicle bike1("cat-1202", VehicleType::BIKE);

    parkingManager.parkVechile(&car1);
    parkingManager.parkVechile(&car2);
    parkingManager.parkVechile(&bike1);
    
    delete strategy;

    return 0;

}