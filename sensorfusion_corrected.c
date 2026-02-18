#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SAMPLES 3000
#define LINE_BUFFER_SIZE 100

struct SensorData
{
    double time;
    double probability;  // Fixed: was "probablity"
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
    unsigned char object_detection[MAX_SAMPLES];
    struct detectionInterval detectionIntervals[MAX_SAMPLES];
    struct SensorData data[MAX_SAMPLES];
};

int importSensorData(struct Sensor * Sensor){
    FILE *sensorData;
    if (Sensor->id == 1)
    {
        sensorData = fopen("sensor1.txt", "r");
    }
    else{
        sensorData = fopen("sensor2.txt", "r");
    }
    if(sensorData == NULL){
        printf("An error occurred when trying to read file.\n");
        return(1);
    }
    char line[LINE_BUFFER_SIZE];
    int currentLine = 0;
    const char split[] = " ";
    while (fgets(line, sizeof(line), sensorData) != NULL)
    {
        char *rest;
        char *ptime = strtok(line, split);
        char *pvalue = strtok(NULL, split);
        double time = strtod(ptime, &rest);
        double probability = strtod(pvalue, &rest);
        Sensor->data[currentLine].time = time;
        Sensor->data[currentLine].probability = probability;  // Fixed: was "probablity"
        currentLine++;
    }
    fclose(sensorData);  // Fixed: Added missing fclose()
    return(0);
}

int generateDetectionInterval(struct Sensor * Sensor, short length){
    short numberOfIntervals = 0;

    unsigned short lastValue = 0;
    unsigned short trailingIndex = 0;
    for (short Index = 0; Index < length - 1; Index++)
    {
        if(lastValue == 0 && Sensor->object_detection[Index] == 1){
            trailingIndex = Index;
        }
        else if (lastValue == 1 && Sensor->object_detection[Index] == 0)
        {
            Sensor->detectionIntervals[numberOfIntervals].start = trailingIndex;
            Sensor->detectionIntervals[numberOfIntervals].end = Index - 1;
            numberOfIntervals++;
        }

        lastValue = Sensor->object_detection[Index];
    }
    if(Sensor->object_detection[length - 1] == 1){
        Sensor->detectionIntervals[numberOfIntervals].start = trailingIndex;
        Sensor->detectionIntervals[numberOfIntervals].end = length - 1;
        numberOfIntervals++;
    }
    return numberOfIntervals;
}

int generateDetectionSignal(struct Sensor * Sensor){
    int length = MAX_SAMPLES;  // Fixed: Use constant instead of sizeof calculation
    for (int Index = 0; Index < length; Index++)
    {
        if(Sensor->data[Index].probability > Sensor->threshold){  // Fixed: Changed >= to >
            Sensor->object_detection[Index] = 1;
        }
        else
        {
            Sensor->object_detection[Index] = 0;
        }
    }
    return(0);
}

int sensorFusion(struct Sensor * Sensor1, struct Sensor * Sensor2, struct Sensor * fusedSensor, short length){
    // Fixed: Changed to use pointer parameter instead of returning large struct
    fusedSensor->id = 0;  // Fused sensor has ID 0
    for (short index = 0; index < length; index++)
    {
        fusedSensor->object_detection[index] = Sensor1->object_detection[index] & Sensor2->object_detection[index];
        fusedSensor->data[index].time = Sensor1->data[index].time;  // Copy time data
    }
    return generateDetectionInterval(fusedSensor, length);
}

int printSingleDetectionIntervals(struct Sensor * Sensor, unsigned char length){
    if (Sensor->id == 0) {
        printf("\nFused signal (both sensors):\n");
    } else {
        printf("\nSensor %d detections:\n", Sensor->id);
    }

    for (short index = 0; index < length; index++)
    {
        int startIdx = (int)Sensor->detectionIntervals[index].start;
        int endIdx = (int)Sensor->detectionIntervals[index].end;
        printf("Start: %.2f s  End: %.2f s\n", 
               Sensor->data[startIdx].time, 
               Sensor->data[endIdx].time);
    }
    return(0);
}

int printSensorDetections(struct Sensor * Sensor, int length){
    printf("Sensor %d Detections: \n", Sensor->id);
    for (int index = 0; index < length; index++)
    {
        if (Sensor->object_detection[index] == 1)
        {
            printf("Detection at index %d (time: %f, probability: %f)\n", 
                   index, Sensor->data[index].time, Sensor->data[index].probability);
        }
    }
    return(0);
}

int main(){
    printf("--- Object Detection Results ---\n");
    
    // Sensor 1
    struct Sensor sensor1;
    sensor1.id = 1;
    sensor1.threshold = 0.8;
    
    if (importSensorData(&sensor1) != 0) {  // Fixed: Check return value
        return 1;
    }
    
    generateDetectionSignal(&sensor1);
    short intervals1 = generateDetectionInterval(&sensor1, MAX_SAMPLES);
    printSingleDetectionIntervals(&sensor1, intervals1);

    // Sensor 2
    struct Sensor sensor2;
    sensor2.id = 2;
    sensor2.threshold = 0.7;
    
    if (importSensorData(&sensor2) != 0) {  // Fixed: Check return value
        return 1;
    }
    
    generateDetectionSignal(&sensor2);
    short intervals2 = generateDetectionInterval(&sensor2, MAX_SAMPLES);
    printSingleDetectionIntervals(&sensor2, intervals2);
    
    // Sensor Fusion - Fixed: Now actually called!
    struct Sensor fusedSensor;
    short fusedIntervals = sensorFusion(&sensor1, &sensor2, &fusedSensor, MAX_SAMPLES);
    printSingleDetectionIntervals(&fusedSensor, fusedIntervals);
    
    return 0;
}
