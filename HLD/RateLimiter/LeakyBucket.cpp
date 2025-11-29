#include <bits/stdc++.h>
using namespace std;

void leakyBucket(int bucketCapacity, int leakRate, vector<int>& packets) {
    int filled = 0; // current packets stored in bucket

    for(int t = 0; t < packets.size(); t++) {
        cout << "\nTime " << t << " | Incoming packet size = " << packets[t];

        // new packet arrival
        if(filled + packets[t] <= bucketCapacity) {
            filled += packets[t];
            cout << "  --> Accepted";
        } else {
            cout << "  --> Overflow! Dropped";
        }

        // leaking (sending out)
        int sent = min(leakRate, filled);
        filled -= sent;

        cout << " | Sent: " << sent << " | Remaining in bucket: " << filled;
    }

    // After last packet, continue leaking left content
    while(filled > 0) {
        int sent = min(leakRate, filled);
        filled -= sent;
        cout << "\nDraining... Sent: " << sent << " | Remaining: " << filled;
    }
}
 
int main() {
    int n, capacity, leak;
    cout << "Enter number of packets: ";
    cin >> n;

    vector<int> packets(n);
    cout << "Enter packet sizes:\n";
    for(int i = 0; i < n; i++) cin >> packets[i];

    cout << "Bucket capacity: ";
    cin >> capacity;

    cout << "Leak rate per time unit: ";
    cin >> leak;

    leakyBucket(capacity, leak, packets);
}
