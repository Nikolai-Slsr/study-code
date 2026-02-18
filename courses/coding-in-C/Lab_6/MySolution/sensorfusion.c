#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct SensorData
{
    double time;
    double probability;
};

struct DetectionInterval
{
    double start;
    double end;
};


struct Sensor
{
    int id;
    double threshold;
    unsigned char objectDetection[3000];
    struct DetectionInterval detectionIntervals[3000];
    struct SensorData data[3000];
};

int printDetectionIntervals(struct Sensor *sensor, unsigned char length){

    printf("Detection Intervals of Sensor %d: \n", sensor->id);

    for (short index = 0; index < length; index++)
    {
        printf("%1d. Detection from %fs to %fs. \n", index, sensor->data[(int)sensor->detectionIntervals[index].start].time, sensor->data[(int)sensor->detectionIntervals[index].end].time);
    }
    return(0);
}

int printSensorDetections(struct Sensor *sensor, int length){
    printf("Sensor %d Detections: \n", sensor->id);
    for (int index = 0; index < length; index++)
    {
        if (sensor->objectDetection[index] == 1)
        {
            printf("Detection at index %d (time: %f, probability: %f)\n", index, sensor->data[index].time, sensor->data[index].probability);
        }
    }
    return(0);
}


int importSensorData(struct Sensor *sensor){
    FILE *sensorData;
    if (sensor->id == 1)
    {
        sensorData = fopen("sensor1.txt", "r");
    }
    else{
        sensorData = fopen("sensor2.txt", "r");
    }
    if(sensorData == NULL){
        printf("An error occurred when trying to read file.");
        return(1);
    }
    char line[100];
    int currentLine = 0;
    const char split[] = " ";
    while (fgets(line,sizeof(line), sensorData) != NULL)
    {
        char *rest;
        char *pTime = strtok(line, split);
        char *pValue = strtok(NULL, split);
        double time = strtod(pTime, &rest);
        double probability = strtod(pValue, &rest);
        sensor->data[currentLine].time = time;
        sensor->data[currentLine].probability = probability;
        currentLine ++;
    }
    fclose(sensorData);
    return(0);
}
int generateDetectionInterval(struct Sensor *sensor, short length){ // returns the amount of detected intervals
    short numberOfIntervals = 0; //gets updated as more Intervals are Detected

    unsigned short lastValue = 0; // value of Index - 1
    unsigned short trailingIndex = 0; // first Index of a detection interval
    for (short index = 0; index < length -1; index++)
    {
        if(lastValue == 0 && sensor->objectDetection[index] == 1){
            trailingIndex = index;
        }
        else if (lastValue == 1 && sensor->objectDetection[index] == 0)
        {
            sensor->detectionIntervals[numberOfIntervals].start = trailingIndex;
            sensor->detectionIntervals[numberOfIntervals].end = index-1;
            numberOfIntervals++;
        }

        lastValue = sensor->objectDetection[index];
    }
    if(sensor->objectDetection[length - 1] == 1){ // Edge case: detection ends with an interval
        sensor->detectionIntervals[numberOfIntervals].start = trailingIndex;
        sensor->detectionIntervals[numberOfIntervals].end = length - 1;
        numberOfIntervals++;
    }
    return numberOfIntervals;
}
int generateDetectionSignal(struct Sensor *sensor){
    int length = sizeof(sensor->data) / sizeof(sensor->data[0]);
    for (int index = 0; index < length; index++)
    {
        if(sensor->data[index].probability >= sensor->threshold){
            sensor->objectDetection[index] = 1;
        }
        else
        {
            sensor->objectDetection[index] = 0;
        }
        
    }
    return(0);
}
struct Sensor sensorFusion(struct Sensor *sensor1, struct Sensor *sensor2, short length){
    struct Sensor fusedSensor;
    for (short index = 0; index < length; index++)
    {
        fusedSensor.objectDetection[index] = sensor1->objectDetection[index] & sensor2->objectDetection[index];
        fusedSensor.data[index].time = sensor1->data[index].time;
        fusedSensor.data[index].probability = sensor1->objectDetection[index] & sensor2->objectDetection[index];
    }
    short intervals = generateDetectionInterval(&fusedSensor, length);
    return(fusedSensor);
}



int main(){
    struct Sensor sensor1;
    sensor1.id = 1;
    sensor1.threshold = 0.8;
    importSensorData(&sensor1);

    generateDetectionSignal(&sensor1);
    short intervals1 = generateDetectionInterval(&sensor1, 3000);
    printDetectionIntervals(&sensor1, intervals1);

    struct Sensor sensor2;
    sensor2.id = 2;
    sensor2.threshold = 0.7;
    importSensorData(&sensor2);

    generateDetectionSignal(&sensor2);
    short intervals2 = generateDetectionInterval(&sensor2, 3000);
    printDetectionIntervals(&sensor2, intervals2);

    struct Sensor fusedSensor = sensorFusion(&sensor1, &sensor2, 3000);
    fusedSensor.id = 3;
    printDetectionIntervals(&fusedSensor, intervals2);
}