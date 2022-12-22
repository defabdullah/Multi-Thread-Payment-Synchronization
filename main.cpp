#include "main.h"

using namespace std;

pthread_mutex_t mutexes[MACHINE_NUMBER];
int companyAmounts[COMPANY_NUMBER];

void *payment(void* arg){
    struct Request *payment_request = (struct Request*)arg;
    pthread_mutex_lock(&(mutexes[payment_request->machine]));

    sleep(payment_request->sleep/1000);
    
    int companyIndex = companyIndexMap[payment_request->companyName];
    companyAmounts[companyIndex]+=payment_request->amount;
    
    fprintf(pOutputFile,"Customer%d,%dTL,%s\n", payment_request->number,
                                                payment_request->amount,
                                                payment_request->companyName.c_str());
    
    pthread_mutex_unlock(&(mutexes[payment_request->machine]));
    return NULL;    
}

int main(int argc,char *argv[]){
    char line[MAX_LINE_LENGTH];
    pInputFile = fopen(argv[1], "r");

    //if file couldn't open
    if(pInputFile == NULL) {
        printf("Cannot open %s\n",argv[1]);
        return 1;
    }

    string fileName;
    stringstream inputstr(argv[1]);
    getline(inputstr, fileName, '.');

    char outputFileName[MAX_FILE_NAME_LENGTH];
    strcpy(outputFileName, fileName.c_str());
    strcat(outputFileName, "_log.txt");
    
    pOutputFile=fopen(outputFileName,"w");
    
    //if file couldn't open
    if(pOutputFile == NULL) {
        printf("Cannot open %s\n",outputFileName);
        return 1;
    }
    
    fgets(line,MAX_LINE_LENGTH,pInputFile);

    lineNumber=atoi(line);

    for (int i=0;i<lineNumber;i++){

        fgets(line,MAX_LINE_LENGTH,pInputFile);
        stringstream strstream(line);
        string temp;
        requests[i] = new Request();
        getline(strstream, temp, ',');
        requests[i]->sleep = atof(temp.c_str());
        
        getline(strstream, temp, ',');
        requests[i]->machine = atoi(temp.c_str());
        
        getline(strstream, temp, ',');
        requests[i]->companyName = temp.c_str();
        
        getline(strstream, temp, ',');
        requests[i]->amount = atoi(temp.c_str());
        requests[i]->number = i+1;

        pthread_create(&threads[i],NULL,payment,(void*)(requests[i]));
    }

    for (int i=0;i<lineNumber;i++){
        pthread_join(threads[i],NULL);
    }
    
    fprintf(pOutputFile,"All prepayments are completed.\n");

    for(map<string,int>::iterator it = companyIndexMap.begin(); it != companyIndexMap.end(); ++it) {
            fprintf(pOutputFile,"%s: %dTL\n",it->first.c_str(),companyAmounts[it->second]);
    }

    fclose(pOutputFile);
    fclose(pInputFile);

    return 0;
}

