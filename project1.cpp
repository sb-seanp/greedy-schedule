//
// Created by Sean on 4/20/2015.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <queue>
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

int main(int argc, char **argv) {
    vector<Job *> jobs;
    string word;
    string line;
    getline(cin,line);
    int jobs_length = stoi(line);

    int index;
    int release;
    int size;

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

    sort(jobs.begin(), jobs.end(), compare);
    priority_queue<Job*, vector<Job*>, QCompare> job_queue;
    priority_queue<Job*, vector<Job*>, QCompare> temp_queue;
    vector<int> schedule;
    queue<Job*> q_s;

    while (!jobs.empty()) {
        Job* temp = jobs.back();
        job_queue.push(temp);
        jobs.pop_back();
    }

    int time = 0;
    while (!job_queue.empty()) {
        Job* top = job_queue.top();
        if (top->getRelease() <= time) {
            schedule.push_back(top->getIndex());
            q_s.push(top);
            top->setSize(top->getSize() - 1);
            cerr << top->getIndex() << " ";
            cerr << top->getRelease() << " ";
            cerr << top->getSize() << endl;
            while (!temp_queue.empty()) {
                job_queue.push(temp_queue.top());
                temp_queue.pop();
            }
            time++;
        }
        else {
            temp_queue.push(top);
            job_queue.pop();
            if (job_queue.empty()) {
                while (!temp_queue.empty()) {
                    job_queue.push(temp_queue.top());
                    temp_queue.pop();
                }
                time++;
            }
            continue;
        }
        if (top->getSize() == 0) {
            job_queue.pop();
            continue;
        }
    }

    /*for (int i = 0; i < schedule.size(); i++) {
        cout << schedule[i] << endl;
    }*/

    /*for (int i = 0; i < jobs_length; i++) {
        Job *temp;
        cout << job_queue.top()->getIndex() << " ";
        cout << job_queue.top()->getRelease() << " ";
        cout << job_queue.top()->getSize() << endl;
        job_queue.pop();
    }*/

    return 0;
}

// Class Job functions
Job::Job(int i, int r, int l) {
    index = i;
    release = r;
    size = l;
}

int compare (Job* a, Job* b) {
    return ( a->getRelease() > b->getRelease() );
}

// Class ParseInput functions
/*void pushJob(int i, int r, int l) {
    Job *job = new Job(i, r, l);
    jobs.push_back(job);
}*/

/*void ParseInput::parse() {
    string line;
    cin >> line;
    int jobs_length;
    stringstream(line) >> jobs_length;

    int index;
    int release;
    int length;

    int number;

    while (getline(cin, line)) {
        stringstream(line) >> number;
        index = number;
        stringstream(line) >> number;
        release = number;
        stringstream(line) >> number;
        length = number;

        pushJob(index, release, length);
    }
}*/