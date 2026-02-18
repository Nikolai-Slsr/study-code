#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct SensorData
{
    double time;
    double probablity;
};

struct detectionInterval
{
    double start;
    double end;
};


struct Sensor
{
    int id;
    double threshold;
    unsigned char object_detection[3000];
    struct detectionInterval detectionIntervals[3000];
    struct SensorData data[3000];
};

int importSensorData(struct Sensor * Sensor){
    FILE *sensorData;
    if (Sensor->id == 1)
    {
        FILE *sensorData = fopen("sensor1.txt", "r");
    }
    else{
        FILE *sensorData = fopen("sensor2.txt", "r");
    }
    if(sensorData == NULL){
        printf("An error occured when trying to read file.");
        return(1);
    }
    char line[100];
    int currentLine = 0;
    const char split[] = " ";
    while (fgets(line,sizeof(line), sensorData) != NULL)
    {
        char *rest;
        char *ptime = strtok(line, split);
        char *pvalue = strtok(NULL, split);
        double time = strtod(ptime, &rest);
        double probability = strtod(pvalue, &rest);
        Sensor->data[currentLine].time = time;
        Sensor->data[currentLine].probablity = probability;
        currentLine ++;
    }
    return(0);
}
int generateDetectionInterval(struct Sensor * Sensor, short length){
    unsigned char numberOfIntervals = 0; //gets updated as more Intervals are Detected

    unsigned char lastValue = 0; // value if Index - 1
    unsigned char trailingIndex = 0; // first Index of an detection interval
    for (short Index = 0; Index < length -1; Index++)
    {
        if(lastValue == 0 && Sensor->object_detection[Index] == 1){
            trailingIndex = Index;
        }
        else if (lastValue == 1 && Sensor->object_detection[Index] == 0)
        {
            Sensor->detectionIntervals[numberOfIntervals].start = trailingIndex;
            Sensor->detectionIntervals[numberOfIntervals].end = Index-1;
            numberOfIntervals++;
        }

        lastValue = Sensor->object_detection[Index];
    }
    if(Sensor->object_detection[length - 1] == 1){ // Edgecase: Detections ends with an interval
        Sensor->detectionIntervals[numberOfIntervals].start = trailingIndex;
        Sensor->detectionIntervals[numberOfIntervals].end = length;
        numberOfIntervals++;
    }
    return(0);
}
int generateDetectionSignal(struct Sensor * Sensor){
    if (Sensor->data[0].time == 0)
    {
        printf("There is no data to interpret!");
        return(1);
    }
    int length = sizeof(Sensor->data) / sizeof(Sensor->data[0]);
    for (int Index = 0; Index < length; Index++)
    {
        if(Sensor->data[Index].probablity >= Sensor->threshold){
            Sensor->object_detection[Index] = 1;
        }
        else
        {
            Sensor->object_detection[Index] = 0;
        }
        
    }
    return(0);
}
int printSingleDetectionIntervals(struct Sensor * Sensor, unsigned char length){

    printf("Detection Intervals of Sensor %d \n", Sensor->id);

    for (short index = 0; index < length - 1; index++)
    {
        printf("%-3d.Detection from %d seconds to %d seconds. \n", index, Sensor->detectionIntervals[index].start, Sensor->detectionIntervals[index].end);
    }
    return(0);
}

int main(){
    struct Sensor sensor1;
    sensor1.id = 1;
    sensor1.threshold = 0.8;
    importSensorData(&sensor1);
    struct Sensor sensor2;
    sensor2.id = 2;
    sensor2.threshold = 0.7;
    importSensorData(&sensor2);
}