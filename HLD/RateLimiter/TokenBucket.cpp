#include <bits/stdc++.h>
using namespace std;

void tokenBucket(int bucketSize, int tokenRate, vector<int>& packets){
    int tokens = 0;                 // available tokens
    queue<int> q;

    for(int t = 0; t < packets.size(); t++){
        
        // token generation per time unit
        tokens = min(bucketSize, tokens + tokenRate);

        cout << "\nTime " << t << " → Tokens available: " << tokens;

        int required = packets[t];   // packet size = tokens required

        if(required <= tokens){
            tokens -= required;
            cout << " | Packet " << required << " transmitted";
        } else {
            cout << " | Not enough tokens → Packet queued/dropped";
            q.push(required);
        }
    }
}
 
int main(){
    int n,b,r;
    cout << "Total packets: "; cin >> n;
    vector<int> packets(n);

    cout << "Enter packet token requirement values:\n";
    for(int i = 0; i < n; i++) cin >> packets[i];

    cout << "Bucket capacity: "; cin >> b;
    cout << "Token generation rate per time unit: "; cin >> r;

    tokenBucket(b, r, packets);

    return 0;
}
