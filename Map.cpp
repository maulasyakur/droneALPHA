#include "Map.h"
#include <fstream>
#include <iostream>
#include <sstream>

Map::Map() {
    // Initialize all distances to a value representing no direct connection
    for (int i = 0; i < MAX_SIZE; i++){
        distanceMatrix[i][i] = 0;
    }

    // Initialize all provinces as unvisited
    for (int i = 0; i < MAX_SIZE; i++){
        visited[i] = 0;
    }
}

// Loads distance data from a file and fills the distanceMatrix
void Map::loadDistanceData(const std::string& filename) {
    // TODO: Your code here
    // Read each line in the CSV file
    // Read each cell separated by a comma
    // Convert cell to an integer and store in distanceMatrix
    std::ifstream file(filename);

    if (!file.is_open()){
        std::cerr << "Cannot open " << filename;
    }

    std::string line;
    int i = 0;
    while (std::getline(file, line)){
        std::string val;
        std::stringstream ss(line);
        int j = 0;
        while (std::getline(ss, val, ',')){
            distanceMatrix[i][j] = std::stoi(val);
            j++;
        }
        i++;
    }
}

// Checks if the distance between two provinces is within the allowed maxDistance
bool Map::isWithinRange(int provinceA, int provinceB, int maxDistance) const {
    if (distanceMatrix[provinceA][provinceB] <= maxDistance){
        return true;
    }
    return false; 
}

// Marks a province as visited
void Map::markAsVisited(int province) {
    visited[countVisitedProvinces()] = province;
}

// Checks if a province has already been visited
bool Map::isVisited(int province) const {
    for (int i = 0; i < MAX_SIZE; i++){
        if (visited[i] == province){
            return true;
        }
    }
    return false;
}

// Resets all provinces to unvisited
void Map::resetVisited() {
    for (int i = 0; i < MAX_SIZE; i++){
        visited[i] = 0;
    }
}

// Function to count the number of visited provinces
int Map::countVisitedProvinces() const {
    for (int i = 0; i < MAX_SIZE; i++){
        if (visited[i] == 0){
            return i;
        }
    }
    return MAX_SIZE;
}

// Function to get the distance between two provinces
int Map::getDistance(int provinceA, int provinceB) const {
    // TODO: Your code here
    return 0;
}