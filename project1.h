//
// Created by Sean on 4/20/2015.
//

#ifndef GREEDY_SCHEDULE_PROJECT1_H
#define GREEDY_SCHEDULE_PROJECT1_H

#include <vector>

using namespace std;

class Job {
private:
    int index;
    int release;
    int length;

public:
    Job(int i, int r, int l);

    int getIndex() const;
    int getRelease() const;
    int getLength() const;
};

class ParseInput {
private:
    vector<Job *> jobs;
public:
    void pushJob(int i, int r, int l);
    void parse();
};

#endif //GREEDY_SCHEDULE_PROJECT1_H
