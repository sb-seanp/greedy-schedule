//
// Created by Sean on 4/20/2015.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;

class Job {
private:
    int index;
    int release;
    int size;

public:
    Job(int i, int r, int l);

    int getIndex() const { return Job::index; }

    int getRelease() const { return Job::release; }

    int getSize() const { return Job::size; }

    void setIndex(int index) {
        Job::index = index;
    }

    void setRelease(int release) {
        Job::release = release;
    }

    void setSize(int size) {
        Job::size = size;
    }
};

class QCompare {
public:
    bool operator() (Job* a, Job* b) {
        return (a->getSize() > b->getSize());
    }
};

int compare (Job* a, Job* b);


// Main function
int main(int argc, char **argv) {

    // Vector to hold jobs data
    vector<Job *> jobs;

    // Parsing variables
    string word;
    string line;
    getline(cin,line);

    int index;
    int release;
    int size;

    // Parse piped input
    while (getline(cin, line)) {
        istringstream ss(line);
        ss >> word;
        index = stoi(word);
        ss >> word;
        release = stoi(word);
        ss >> word;
        size = stoi(word);

        Job *job = new Job(index, release, size);
        jobs.push_back(job);
    }

    // Sort jobs vector
    sort(jobs.begin(), jobs.end(), compare);

    // Two queues to handle choosing the right job
    priority_queue<Job*, vector<Job*>, QCompare> job_queue;
    priority_queue<Job*, vector<Job*>, QCompare> temp_queue;

    // Vector to store final schedule
    vector<int> schedule;

    // Move from sorted vector into initial queue
    while (!jobs.empty()) {
        Job* temp = jobs.back();
        job_queue.push(temp);
        jobs.pop_back();
    }

    // Time-related variables
    int time = 0;
    int optimal = 0;

    // Job scheduling algorithm
    while (!job_queue.empty()) {
        Job* top = job_queue.top();

        // If it's at the lowest size (which it will by priority queue rules)
        // and it can be released, add it to the schedule and increment time.
        if (top->getRelease() <= time) {
            schedule.push_back(top->getIndex());
            top->setSize(top->getSize() - 1); // Decrease size

            // Put everything back into the main queue.
            while (!temp_queue.empty()) {
                job_queue.push(temp_queue.top());
                temp_queue.pop();
            }
            time++;
        }
        // If no valid job is found, pop from main queue and move to temp queue.
        else {
            temp_queue.push(top);
            job_queue.pop();

            // If no job could be found at all, put everything back in the main queue and increment time.
            if (job_queue.empty()) {
                while (!temp_queue.empty()) {
                    job_queue.push(temp_queue.top());
                    temp_queue.pop();
                }
                schedule.push_back(-1);
                time++;
            }
            continue;
        }
        if (top->getSize() == 0) {
            job_queue.pop();
            optimal += time;
        }
    }

    // Print the stuff.
    cout << optimal;

    for (int i = 0; i < schedule.size(); i++) {
        if (schedule[i] == -1) cerr << "*";
        else cerr << schedule[i];
    }

    return 0;
}

// Job constructor
Job::Job(int i, int r, int l) {
    index = i;
    release = r;
    size = l;
}

// Function that sorts jobs by release time
int compare (Job* a, Job* b) {
    return ( a->getRelease() > b->getRelease() );
}
