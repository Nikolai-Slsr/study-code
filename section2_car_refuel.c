/* 
 * Lab 6 - Section II: Car Struct with Refuel Function
 * Demonstrates use of structs and pointer-based functions
 */

#include <stdio.h>
#include <string.h>

// Define the Car struct
struct Car {
    float fuel_level;
    float max_fuel_level;
    char model[50];
};

/**
 * Refuel function - adds fuel to a car
 * @param car: Pointer to a Car struct
 * @param amount: Amount of fuel to add (float)
 * @return: 0 on success, 1 if tank would overflow
 */
int refuel(struct Car *car, float amount) {
    // Check if adding fuel would exceed max capacity
    if (car->fuel_level + amount > car->max_fuel_level) {
        printf("Warning: Cannot add %.2f liters. Tank capacity is %.2f liters.\n", 
               amount, car->max_fuel_level);
        printf("Current fuel: %.2f liters. Space available: %.2f liters.\n",
               car->fuel_level, car->max_fuel_level - car->fuel_level);
        
        // Fill to maximum capacity
        float added = car->max_fuel_level - car->fuel_level;
        car->fuel_level = car->max_fuel_level;
        printf("Added %.2f liters to fill tank to maximum.\n", added);
        return 1;
    }
    
    // Add the fuel
    car->fuel_level += amount;
    printf("Added %.2f liters of fuel.\n", amount);
    return 0;
}

/**
 * Display car information
 */
void displayCarInfo(struct Car *car) {
    printf("\n--- Car Information ---\n");
    printf("Model: %s\n", car->model);
    printf("Current Fuel: %.2f liters\n", car->fuel_level);
    printf("Tank Capacity: %.2f liters\n", car->max_fuel_level);
    printf("Fuel Percentage: %.1f%%\n", (car->fuel_level / car->max_fuel_level) * 100);
    printf("----------------------\n");
}

int main() {
    printf("========================================\n");
    printf("Lab 6 - Section II: Car Refuel Demo\n");
    printf("========================================\n");
    
    // Initialize a car with low fuel level
    struct Car myCar;
    strcpy(myCar.model, "Toyota Corolla");
    myCar.fuel_level = 5.0;          // Low fuel level
    myCar.max_fuel_level = 50.0;     // 50 liter tank capacity
    
    // Display initial state
    printf("\n=== Initial State ===\n");
    displayCarInfo(&myCar);
    
    // Test 1: Normal refuel
    printf("\n=== Test 1: Refuel with 20 liters ===\n");
    refuel(&myCar, 20.0);
    displayCarInfo(&myCar);
    
    // Test 2: Refuel again
    printf("\n=== Test 2: Refuel with 15 liters ===\n");
    refuel(&myCar, 15.0);
    displayCarInfo(&myCar);
    
    // Test 3: Try to overfill
    printf("\n=== Test 3: Try to add 20 liters (exceeds capacity) ===\n");
    refuel(&myCar, 20.0);
    displayCarInfo(&myCar);
    
    // Test 4: Create another car
    printf("\n\n=== Creating a Second Car ===\n");
    struct Car sportsCar;
    strcpy(sportsCar.model, "Porsche 911");
    sportsCar.fuel_level = 2.0;      // Very low fuel
    sportsCar.max_fuel_level = 64.0; // 64 liter tank
    
    printf("\n=== Second Car Initial State ===\n");
    displayCarInfo(&sportsCar);
    
    printf("\n=== Refuel Second Car with 50 liters ===\n");
    refuel(&sportsCar, 50.0);
    displayCarInfo(&sportsCar);
    
    printf("\n========================================\n");
    printf("All tests completed successfully!\n");
    printf("========================================\n");
    
    return 0;
}
