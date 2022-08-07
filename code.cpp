//This code is written under the guidance of Dr.Jaishree Mayank under the design project course on ELctric Vehicle Enrouting.
//Team Members are:-
//1.Anand Kumar
//2.Mayank Kumar
//3.Rohit Kumar Agrahari

// This code is used for single user and multi station charging based
#include <bits/stdc++.h>
using namespace std;
//Class for the Charging Station
int CS = 0;  // this is the Unique number provided to every charging station.
int  UBN=1; //Unique booking number alotted to the user whi has done the booking

class EVS
{
public:
    int station_number;
    // int charging_port;

    map<int, int> waiting;
    EVS(int a)
    {
        station_number = a;
    }

    map<int, int> NATS; //This will store the next time slot availabale.

    // This function is to keep updated the waiting map.

    void update_the_waiting(int current_time)
    {
        auto it = waiting.begin();
        if (!waiting.empty())
        {
            while (it->second < current_time && it != waiting.end())
            {
                waiting.erase(it->first);
                it++;
            }
            NATS = this->Update_the_Next_Available_Time_Slot();
        }
        else
        {
            return;
        }
    }
    map<int, int> Update_the_Next_Available_Time_Slot()
    { //this function is used to update the next available time slot in the charging station.
        map<int, int> ar;
        auto it = waiting.begin();
        auto it2 = waiting.begin();
        it2++;
        while (it2 != waiting.end())
        {
            if ((it->second) - ((it2)->first) > 0)
            {
                ar.insert({it->second, it2->first});
            }
            it++;
            it2++;
        }
        ar.insert({it->second, it->second + 1});
        return ar;
    }
// this function is used to check the waiting queue for the demanded slot
    bool check_the_waiting_queue(int start_time, int end_time)
    {
        for (auto it = NATS.begin(); it != NATS.end(); it++)
        {
            if (it->first <= start_time && it->second >= end_time)
            {
                return true;
            }
            if (it->second <= start_time)
            {
                return true;
            }
        }
        return false;
    }
    // this function is used to book the slot in the charging station
    void book_the_cs(pair<int, int> value)
    {
        this->waiting.insert(value);
        cout << "Your booking has been done" << endl;
        cout<<"Your unique booking code is: "<<UBN<<endl;
        UBN+=1;
    }
};
//This class is made to define a custom datatype for implementing the graph
class node
{
public:
    unordered_map<int, int> nbrs;
};

//Breadth First Traversal Algorithm
vector<int> BFS(unordered_map<int, node>net2, int start_node)
{  

    queue<int> arrui;
    arrui.push(start_node);
    vector<bool>visited(net2.size(),false);
    vector<int> arruiya;// this is the vector which contains all the nodes in BFS traversal pattern
    visited[start_node]=true;   
    while (!arrui.empty())
    {
        int value2 = arrui.front();
        arrui.pop();
        arruiya.push_back(value2);
        for (auto it9 = net2[value2].nbrs.begin(); it9 != net2[value2].nbrs.end(); it9++)
        {
            if(!visited[it9->first]){
            arrui.push(it9->first);
            visited[it9->first]=true;
            }
        }
        
    }

    return arruiya;
}

//This function return the remaining distance the car can travel based upon the remaining charging station
int calculate_remaining_distance(int value)
{
    if (value == 0)
    {
        return 0;
    }
    else
    {
        return (value / 10) ;
    }
}
// Section is to find the nodes in between the path and also find the shortest path
map<int, vector<int>> path_and_distnace_value;
void find_the_path(unordered_map<int, node> &arru, int start, int end, int &value, vector<int> &arr, vector<bool> &isVisited)
{
    if (start == end)
    {
        path_and_distnace_value.insert({value, arr});
        return;
    }
    for (auto it = arru[start].nbrs.begin(); it != arru[start].nbrs.end(); it++)
    {
        if (!isVisited[it->first])
        {
            isVisited[it->first] = true;
            arr.push_back(it->first);
            value += it->second;
            find_the_path(arru, it->first, end, value, arr, isVisited);
            value = value - it->second;
            arr.pop_back();
            isVisited[it->first] = false;
        }
    }
}

pair<int, vector<int>> find_the_nodes(unordered_map<int, node> &arru, int start, int end)
{ // this function is used to find the nodes which will be
    //there in the shortest path
    vector<int> nodes_visited;
    vector<bool> isVisited(arru.size(), false);
    int value = 0;
    nodes_visited.push_back(start);
    find_the_path(arru, start, end, value, nodes_visited, isVisited);
    auto it = path_and_distnace_value.begin();
    return {it->first, it->second};
}
int counting=1;
void make_the_graph(unordered_map<int,node>&arru,vector<EVS>&net3){  // this function is used to intialise the graph using which we can do the analysis
// 
 //Initialisation of a graph.
    ifstream cin("input.txt");
    int number;//this variables represents the number of vertices are there in the graph
    cin >> number;
    for (int a = 0; a < number; a++)
    {
        node n1;
        arru.insert({CS, n1});   //CS is the gloabal variable and it is the the unique charging station number.
        int nv;   // this variable shows the number neighnour vertices to the different vertices 
        cin >> nv;
        while (nv--)
        {
            int node, weight;
            cin >> node >> weight;    //Enter the neigjbour node value and then the weight associated with it.
            arru[CS].nbrs.insert({node, weight});
        }
         EVS newer_node(CS);
         net3.push_back(newer_node);
         CS += 1;

      }
       cout<<"Network has been created"<<endl;
       return;
}


int main()
{
    vector<EVS> arru;                 //vector of charging station as object
    unordered_map<int, node> network; //This is our core graph
    make_the_graph(network,arru);     // initialising the graph
    int i;
    do
    {   
        cout << "Press 1 if you want to add some new Charging Station" << endl;
        cout << "Press 2 if you want to do travel some from one point to the other" << endl;
        cout << "Press 3 for just Charging the EV in nearby Places according to your EV's remaining charge" << endl;
        cin >> i;
        if (i == 1)
        {   
            cout << "Please enter the password if you want to insert any charging station into it" << endl;
            int pass = 12345;
            int password;
            cin >> password;
            if (password == pass)
            { 
                cout << "How many Charging Station you want to insert" << endl;
                int number;
                cin >> number;
                for (int a = 0; a < number; a++)
                {
                    node n1;
                    network.insert({CS, n1});
                    cout << "Enter the number of Charging Station which are adjacent to the given Charging Station number" << CS << endl;
                    int nv;
                    cin >> nv;
                    while (nv--)
                    {
                        cout << "Enter the nodes nearby value and then the weight associated with it" << endl;
                        int node, weight;
                        cin >> node >> weight;
                        network[CS].nbrs.insert({node, weight});
                    }

                    EVS newer_node(CS);
                    arru.push_back(newer_node);
                    CS += 1;
                }

                cout << "Nodes have been succesfully inserted" << endl;
            }
            else
            {
                cout << "You Entered the wrong password" << endl;
                continue;
            }
            
        }
        if (i == 2)
        {
            cout << "Enter the source point and the destination point" << endl;
            int start, last;
            cin >> start >> last;
            cout << "Enter the charging perecent" << endl;
            int charge_percent;
            cin >> charge_percent;
            int remaining_distance = calculate_remaining_distance(charge_percent); // calculating the remaining distance the car can travel using the remaining charging percent.
            cout << "Remaining Distance it can travel is on the basis of left out charging of EV" << remaining_distance << endl;
            vector<int> reachable_charging_station_in_journey;                 // this will store the charging station numbers which can be reached depending upon the remaining charging percent.
            pair<int, vector<int>> arr=find_the_nodes(network, start, last); //This will first help us to know the intermediate charging station which will come in
            // journey from starting point to the destination point
            cout << "These are  the charging station which will come in the route" << endl;
            for (auto it5 = arr.second.begin(); it5 != arr.second.end(); it5++)
            {
                cout << *it5 << " ";
            }
            cout << endl;
            for (auto it44 = arr.second.begin(); it44 != arr.second.end(); it44++)
            {
                pair<int, vector<int>> checking = find_the_nodes(network, start, *it44); //This loops checks all the intermediate nodes present in the journey and
                cout<<"Start Node: "<<start<<"      "<<"End Node"<<*it44<<"Distance between them"<<checking.first<<endl;
                if (checking.first <= remaining_distance)
                {                                                          // stations which are reachable are stored in the vector named
                    reachable_charging_station_in_journey.push_back(*it44); // reachable_charging_station_in_journey
                }
                path_and_distnace_value.clear();
            }
            
            cout << "These are the charging station where you can reach" << endl;
            for (auto it6 = reachable_charging_station_in_journey.begin(); it6 != reachable_charging_station_in_journey.end(); it6++)
            {
                cout << *it6 << " ";
            }
            cout << endl;
            auto it8 = reachable_charging_station_in_journey.begin();
            multimap<int, int> waiting_time; // in this we will store the key as the waiting time and the value as the station number
            while (it8 != reachable_charging_station_in_journey.end())
            {
                time_t now = time(0);
                tm *ltm = localtime(&now);
                int current_time = ltm->tm_hour;
                int end_time = current_time + 1;
                arru[*it8].update_the_waiting(current_time);
                if (arru[*it8].NATS.size() > 0)
                {
                    auto iterate = arru[*it8].NATS.begin();
                    waiting_time.insert({iterate->first - current_time, *it8});
                    it8++;
                }
                else
                {
                    arru[*it8].NATS.insert({current_time, current_time + 1});
                }
            }

            //This outputs those charging station which are in the in the route of our journey and its showing in the increasing order of waiting time. :)
            for (auto it2 = waiting_time.begin(); it2 != waiting_time.end(); it2++)
            {
                cout << "Waiting time is: " << it2->first << " for the station number: " << it2->second << "and the other next available time slot are as follows:" << endl;
                if (arru[it2->second].NATS.size() > 0)
                {
                    for (auto it3 = arru[it2->second].NATS.begin(); it3 != arru[it2->second].NATS.end(); it3++)
                    {
                        cout << "Starting time: " << it3->first<< "End Time: " << it3->second << endl;
                    }
                }
                else
                {
                    cout << "All the slots are free in the station number" << it2->second << "you can book any time for the day" << endl;
                }
                cout << "-------------------------------------------------------------" << endl;
            }

            cout << "Enter the charging station number on which you want to book the slot" << endl;
            int input;   // taking the input of the station number
            cin >> input;  
            cout << "Please enter the start time and end time" << endl;
            int st, et; //st->starting time,et->end time
            cin >> st >> et;   
            if (arru[input].check_the_waiting_queue(st, et))
            {
                arru[input].book_the_cs({st, et});
            }
            else
            {
                cout << "Oops the available time slot is not available" << endl;
            }
        }
        if (i == 3)
        {
            cout << "Enter the station number where you are standing" << endl;
            int cst; //current station  number
            cin >> cst;
            vector<int> nearest_station = BFS(network, cst);
            cout << "Enter the charging percentage of your EV" << endl;
            int charge_percent;
            cin >> charge_percent;
            
            int RD = calculate_remaining_distance(charge_percent); //This is the remaining distance that we can travel from the remaining charging of the EV
            multimap<int, int> nearest_distance_CS;
            for (auto it = nearest_station.begin(); it != nearest_station.end(); it++)
            {
                pair<int, vector<int>> find1 = find_the_nodes(network, cst, *it);
                int value2 = find1.first;
                if (value2 <= RD)
                {
                    nearest_distance_CS.insert({value2, *it});
                }
                 path_and_distnace_value.clear();
            }
            if (nearest_distance_CS.size() == 0)
            {
                cout << "Sorry we cannot help you beacuse you remaining charge cannot take you to any CS" << endl;
            }
            else
            {
                time_t now = time(0);
                tm *ltm = localtime(&now);
                int current_time = ltm->tm_hour;
                int end_time = current_time + 1;
                for (auto it2 = nearest_distance_CS.begin(); it2 != nearest_distance_CS.end(); it2++)
                {
                    cout <<"For the station number:--> " << it2->second << " and the other next available time slot are as follows:" << endl;
                    if (arru[it2->second].NATS.size() != 0)
                    {
                        for (auto it3 = arru[it2->second].NATS.begin(); it3 != arru[it2->second].NATS.end(); it3++)
                        {
                            cout << "Starting time:--> " << it3->first << "End Time:-->" << it3->second%24 << endl;
                        }
                    }
                    else
                    {
                        cout << "All the slots are free in the station number:--> " << it2->second << "  you can book any time for the day" << endl;
                    }
                    cout << "-------------------------------------------------------------" << endl;
                }

                cout << "Enter the charging station number on which you want to book the slot" << endl;
                int input;
                cin >> input;
                cout << "Please enter the start time and end time" << endl;
                int st, et;
                cin >> st >> et;
                if (arru[input].check_the_waiting_queue(st, et))
                {
                    arru[input].book_the_cs({st, et});
                }
                else
                {
                    cout << "Oops the available time slot is not available" << endl;
                }
            }
        }
    } while (i == 1 || i == 2 || i == 3);

    
    return 0;
}