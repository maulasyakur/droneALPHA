#include "Map.h"
#include <fstream>
#include <iostream>
#include <sstream>

Map::Map() {
    // Initialize all distances to a value representing no direct connection
    for (int i = 0; i < MAX_SIZE; i++){
        for (int j = 0; j < MAX_SIZE; j++){
            distanceMatrix[i][j] = -1;
        }
    }

    // Initialize all provinces as unvisited
    for (int i = 0; i < MAX_SIZE; i++){
        visited[i] = false;
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
    if (distanceMatrix[provinceA][provinceB] <= maxDistance && provinceA < 81 && provinceB < 81 && provinceA >= 0 && provinceB >= 0){
        return true;
    }
    return false; 
}

// Marks a province as visited
void Map::markAsVisited(int province) {
    visited[province] = true;
}

// Checks if a province has already been visited
bool Map::isVisited(int province) const {
    return visited[province];
}

// Resets all provinces to unvisited
void Map::resetVisited() {
    for (int i = 0; i < MAX_SIZE; i++){
        visited[i] = false;
    }
}

// Function to count the number of visited provinces
int Map::countVisitedProvinces() const {
    int count;
    for (int i = 0; i < MAX_SIZE; i++){
        if (visited[i] == true){
            count++;
        }
    }
    return count;
}

// Function to get the distance between two provinces
int Map::getDistance(int provinceA, int provinceB) const {
    if (provinceA < 81 && provinceB < 81){
        return distanceMatrix[provinceA][provinceB];
    }
    return -1;
}