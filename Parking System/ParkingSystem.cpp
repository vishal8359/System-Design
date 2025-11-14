#include <bits/stdc++.h>
using namespace std;

// ---------------- GROUND ----------------
class Ground {
public:
    string name;
    string location;
    int totalSlots;
    vector<bool> slots;

    Ground(string name, string location, int totalSlots)
        : name(name), location(location), totalSlots(totalSlots) {
        slots.resize(totalSlots, false);
    }
};

// ---------------- VEHICLE ----------------
class Vehicle {
public:
    string type; 
    int number;

    Vehicle(string type, int number) : type(type), number(number) {}
};

// ---------------- FEE POLICY (OCP) ----------------
class FeePolicy {
public:
    virtual int calculateFee() = 0;
    virtual ~FeePolicy() {}
};

class TwoWheelFee : public FeePolicy {
public:
    int calculateFee() override { return 30; }
};

class FourWheelFee : public FeePolicy {
public:
    int calculateFee() override { return 50; }
};

class HeavyVehicleFee : public FeePolicy {
public:
    int calculateFee() override { return 100; }
};

// Factory for FeePolicy
class FeeFactory {
public:
    static FeePolicy* getPolicy(string type) {
        if (type == "2-wheeler") return new TwoWheelFee();
        if (type == "4-wheeler") return new FourWheelFee();
        if (type == "Truck" || type == "Bus") return new HeavyVehicleFee();
        return nullptr;
    }
};

// ---------------- SLOT STRATEGY (OCP) ----------------
class SlotStrategy {
public:
    virtual int findSlot(Ground* g) = 0;
    virtual ~SlotStrategy() {}
};

class FirstAvailableSlot : public SlotStrategy {
public:
    int findSlot(Ground* g) override {
        for (int i = 0; i < g->totalSlots; i++)
            if (!g->slots[i]) return i;
        return -1;
    }
};

// ---------------- PARKING MANAGER ----------------
class ParkingManager {
public:
    unordered_map<int, int> vehicleToSlot;
    SlotStrategy* strategy;

    ParkingManager(SlotStrategy* strategy) : strategy(strategy) {}

    int parkVehicle(Vehicle* v, Ground* g) {

        int slot = strategy->findSlot(g);
        if (slot == -1) {
            cout << "No empty slots available\n";
            return -1;
        }
        if(vehicleToSlot.count(v->number)){

            cout << "Vehicle Already Parked" << endl;
            return 0;

        }
        g->slots[slot] = true;
        vehicleToSlot[v->number] = slot;

        FeePolicy* policy = FeeFactory::getPolicy(v->type);
        int fee = policy->calculateFee();
        delete policy;

        cout << "Vehicle " << v->number << " parked at slot " << slot
             << " | Fee: " << fee << endl;

        return slot;
    }

    void emptySlot(Vehicle* v, Ground* g) {
        if (!vehicleToSlot.count(v->number)) {
            cout << "Vehicle not parked\n";
            return;
        }

        int slot = vehicleToSlot[v->number];
        g->slots[slot] = false;
        vehicleToSlot.erase(v->number);

        cout << "Slot " << slot << " emptied for vehicle " << v->number << endl;
    }
};

// ---------------- USER ----------------
class User {
public:
    string name;
    Vehicle* vehicle;

    User(string name, Vehicle* vehicle)
        : name(name), vehicle(vehicle) {}
};

// ---------------- MAIN FUNCTION ----------------
int main() {

    Ground* ground = new Ground("Brij Parking", "Shani bajar", 150);

    Vehicle* bike = new Vehicle("2-wheeler", 5985);
    User* user1 = new User("Vishal", bike);

    SlotStrategy* strategy = new FirstAvailableSlot();
    ParkingManager* manager = new ParkingManager(strategy);

    cout << "\n--- PARKING PROCESS STARTED ---\n\n";

    manager->parkVehicle(user1->vehicle, ground);

    // cout << "\n--- WITHDRAW PROCESS ---\n\n";

    // manager->emptySlot(user1->vehicle, ground);

    // cout << "\n--- PARKING PROCESS STARTED ---\n\n";

    manager->parkVehicle(user1->vehicle, ground);

    cout << "\n--- WITHDRAW PROCESS ---\n\n";

    manager->emptySlot(user1->vehicle, ground);

    delete manager;
    delete strategy;
    delete user1;
    delete bike;
    delete ground;

    return 0;
}
