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
    unsigned char object_detection[6000];
    struct detectionInterval detectionIntervals[3000];
    struct SensorData data[6000];
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
int generateDetectionSignal(struct Sensor * Sensor){
    if (Sensor->data == NULL)
    {
        printf("There is no data to interprete!");
        return(1);
    }
    int length = sizeof(Sensor->data);
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