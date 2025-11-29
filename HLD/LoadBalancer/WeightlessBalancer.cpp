#include <bits/stdc++.h>
using namespace std;

struct Server {
    int id;
    int weight;         // processing capacity
    int activeRequests; // current load

    // priority: lowest activeRequests, if tie → highest weight
    bool operator<(const Server &other) const {
        if(activeRequests == other.activeRequests)
            return weight < other.weight;  // stronger first
        return activeRequests > other.activeRequests;
    }
};

class LoadBalancer {
private:
    priority_queue<Server> pq; // min based on load, max based on weight

public:
    LoadBalancer(vector<pair<int,int>> serverInfo){
        for(auto &s : serverInfo){
            pq.push({s.first, s.second, 0});
        }
    }

    int routeRequest(){
        Server top = pq.top(); pq.pop();

        top.activeRequests++;       // assign request
        pq.push(top);

        return top.id;
    }

    void completeRequest(int serverId){
        vector<Server> temp;

        // pull servers until target found
        while(!pq.empty()){
            Server s = pq.top(); pq.pop();
            if(s.id == serverId){
                s.activeRequests--;
            }
            temp.push_back(s);
        }
        for(auto &s : temp) pq.push(s);
    }

    void displayState(){
        vector<Server> v;
        while(!pq.empty()){
            v.push_back(pq.top()); pq.pop();
        }

        cout << "\nServer Status (load | weight): ";
        for(auto &s : v){
            cout << "[ID:" << s.id << " Load:" << s.activeRequests 
                 << " W:" << s.weight << "] ";
            pq.push(s);
        }
        cout << "\n";
    }
};

int main(){
    // {ServerID, Weight}
    LoadBalancer lb({{1,4},{2,3},{3,1}});

    cout << "\nIncoming 10 requests:\n";
    for(int i = 1; i <= 10; i++){
        int assigned = lb.routeRequest();
        cout << "Request " << i << " → Server " << assigned << "\n";
    }

    lb.displayState();

    cout << "\nCompleting requests on Server 1 + 2\n";
    lb.completeRequest(1);
    lb.completeRequest(2);

    lb.displayState();
}
