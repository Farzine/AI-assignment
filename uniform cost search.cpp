// Farzine --> 2020831007

#include <bits/stdc++.h>

using namespace std;

// graph
unordered_map<string, vector<string>> graph;

// map to store cost of edges
map<pair<string, string>, int> cost;

// returns the minimum cost in a vector( if
// there are multiple goal states)
vector<int> uniform_cost_search(vector<string> goal, string start)
{
    // minimum cost up to
    // goal state from starting
    // state
    vector<int> answer;

    // create a priority queue
    priority_queue<pair<int, string>> queue;

    // set the answer vector to max value
    for (int i = 0; i < goal.size(); i++)
        answer.push_back(INT_MAX);

    // insert the starting index
    queue.push(make_pair(0, start));

    // map to store visited node
    map<string, int> visited;

    // count
    int count = 0;

    // while the queue is not empty
    while (queue.size() > 0) {

        // get the top element of the
        // priority queue
        pair<int, string> p = queue.top();

        // pop the element
        queue.pop();

        // get the original value
        int costSoFar = -p.first;
        string node = p.second;

        // check if the element is part of
        // the goal list
        if (find(goal.begin(), goal.end(), node) != goal.end()) {

            // get the position
            int index = find(goal.begin(), goal.end(),
                node) - goal.begin();

            // if a new goal is reached
            if (answer[index] == INT_MAX)
                count++;

            // if the cost is less
            if (answer[index] > costSoFar)
                answer[index] = costSoFar;

            // pop the element
            queue.pop();

            // if all goals are reached
            if (count == goal.size())
                return answer;
        }

        // check for the non visited nodes
        // which are adjacent to present node
        if (visited[node] == 0)
            for (int i = 0; i < graph[node].size(); i++) {
                string neighbor = graph[node][i];

                // value is multiplied by -1 so that
                // least priority is at the top
                queue.push(make_pair(-(cost[{node, neighbor}] + costSoFar), neighbor));
            }

        // mark as visited
        visited[node] = 1;
    }

    return answer;
}

// main function
int main()
{
    // add edges to the graph
    graph["S"] = {"A", "G"};
    graph["A"] = {"C", "B"};
    graph["C"] = {"D", "G"};
    graph["D"] = {"G"};
    graph["B"] = {"D"};
    graph["D"] = {"G"};

    // add the cost
    cost[{"S", "A"}] = 1;
    cost[{"S", "G"}] = 12;
    cost[{"A", "C"}] = 1;
    cost[{"A", "B"}] = 3;
    cost[{"C", "D"}] = 1;
    cost[{"C", "G"}] = 2;
    cost[{"D", "G"}] = 3;
    cost[{"B", "D"}] = 3;
    cost[{"D", "G"}] = 3;

    // goal state
    vector<string> goal = {"G"};

    // get the answer
    vector<int> answer = uniform_cost_search(goal, "S");

    // print the answer
    cout << "Minimum cost from S to G is = "
        << answer[0] << endl;

    return 0;
}
