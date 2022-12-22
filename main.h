#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <pthread.h>
#include <bits/stdc++.h>
#include <unistd.h>

using namespace std;

#define MACHINE_NUMBER 10
#define COMPANY_NUMBER 10
#define MAX_LINE_LENGTH 256
#define MAX_FILE_NAME_LENGTH 256


map<string, int> companyIndexMap = {{"Kevin",0},
                                    {"Bob",1},
                                    {"Stuart",2},
                                    {"Otto",3},
                                    {"Dave",4}};

struct Request {
    int machine,sleep,amount,number;
    string companyName;
};

int lineNumber;

pthread_t threads[lineNumber];
Request *requests[lineNumber];

FILE *pInputFile;
FILE *pOutputFile;

#endif