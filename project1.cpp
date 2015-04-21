//
// Created by Sean on 4/20/2015.
//

#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "project1.h"

using namespace std;

int main(int argc, char **argv) {
    return 0;
}

// Class Job functions
Job::Job(int i, int r, int l) {
    index = i;
    release = r;
    length = l;
}

int Job::getIndex() const { return index; }

int Job::getRelease() const { return release; }

int Job::getLength() const { return length; }

// Class ParseInput functions
void ParseInput::pushJob(int i, int r, int l) {
    Job *job = new Job(i, r, l);
    jobs.push_back(job);
}

void ParseInput::parse() {
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
}