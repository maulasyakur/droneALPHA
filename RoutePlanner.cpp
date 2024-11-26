#include "RoutePlanner.h"
#include <iostream>
#include <fstream>

// Array to help you out with name of the cities in order
const std::string cities[81] = { 
    "Adana", "Adiyaman", "Afyon", "Agri", "Amasya", "Ankara", "Antalya", "Artvin", "Aydin", "Balikesir", "Bilecik", 
    "Bingol", "Bitlis", "Bolu", "Burdur", "Bursa", "Canakkale", "Cankiri", "Corum", "Denizli", "Diyarbakir", "Edirne", 
    "Elazig", "Erzincan", "Erzurum", "Eskisehir", "Gaziantep", "Giresun", "Gumushane", "Hakkari", "Hatay", "Isparta", 
    "Mersin", "Istanbul", "Izmir", "Kars", "Kastamonu", "Kayseri", "Kirklareli", "Kirsehir", "Kocaeli", "Konya", "Kutahya", 
    "Malatya", "Manisa", "Kaharamanmaras", "Mardin", "Mugla", "Mus", "Nevsehir", "Nigde", "Ordu", "Rize", "Sakarya", 
    "Samsun", "Siirt", "Sinop", "Sivas", "Tekirdag", "Tokat", "Trabzon", "Tunceli", "Urfa", "Usak", "Van", "Yozgat", 
    "Zonguldak", "Aksaray", "Bayburt", "Karaman", "Kirikkale", "Batman", "Sirnak", "Bartin", "Ardahan", "Igdir", 
    "Yalova", "Karabuk", "Kilis", "Osmaniye", "Duzce" 
};

// Constructor to initialize and load constraints
RoutePlanner::RoutePlanner(const std::string& distance_data, const std::string& priority_data, const std::string& restricted_data, int maxDistance)
    : maxDistance(maxDistance), totalDistanceCovered(0), numPriorityProvinces(0), numWeatherRestrictedProvinces(0) {

    // Load map data from file
    // Mark all provinces as unvisited initially
    map.loadDistanceData(distance_data);

    // Load priority provinces
    loadPriorityProvinces(priority_data);

    // Load restricted provinces
    loadWeatherRestrictedProvinces(restricted_data);
}

// Load priority provinces from txt file to an array of indices
void RoutePlanner::loadPriorityProvinces(const std::string& filename) {
    std::ifstream file(filename);

    // Handle error
    if (!file.is_open()){
        std::cerr << "Cannot open file " << filename << std::endl;
    }

    std::string line;
    int i = 0;
    // Parse each line
    while (std::getline(file, line)){
        // Find the opening and closing parentheses
        size_t start = line.find('(');
        size_t end = line.find(')');

        if (start != std::string::npos && end != std::string::npos) {
            // Extract the number between the parentheses
            int province_number = std::stoi(line.substr(start + 1, end - start - 1));
            priorityProvinces[i] = province_number;
            i++;
        }
    }
    numPriorityProvinces = i; // Set the number of priority provinces in the array
}

// Load weather-restricted provinces from txt file to an array of indices
void RoutePlanner::loadWeatherRestrictedProvinces(const std::string& filename) {
    std::ifstream file(filename);

    // Handle error
    if (!file.is_open()){
        std::cerr << "Cannot open file " << filename << std::endl;
    }

    std::string line;
    int i = 0;
    // Parse each line
    while (std::getline(file, line)){
        // Find the opening and closing parentheses
        size_t start = line.find('(');
        size_t end = line.find(')');

        if (start != std::string::npos && end != std::string::npos) {
            // Extract the number between the parentheses
            int province_number = std::stoi(line.substr(start + 1, end - start - 1));
            weatherRestrictedProvinces[i] = province_number;
            i++;
        }
    }
    numWeatherRestrictedProvinces = i; // Set the number of restricted provinces in the array
}

// Checks if a province is a priority province
bool RoutePlanner::isPriorityProvince(int province) const {
    // Loop through the priorityProvince array and check
    for (int i = 0; i < numPriorityProvinces; i++){
        if (priorityProvinces[i] == province){ 
            return true; // found
        }
    }
    return false; // not found
}

// Checks if a province is weather-restricted
bool RoutePlanner::isWeatherRestricted(int province) const {
    // Loop through the weatherRestrictedProvinces array and check
    for (int i = 0; i < numWeatherRestrictedProvinces; i++){
        if (weatherRestrictedProvinces[i] == province){
            return true; // found
        }
    }
    return false; // not found
}

// Begins the route exploration from the starting point
void RoutePlanner::exploreRoute(int startingCity) {
    // Initialize the starting point into the visited array, stack, and route
    map.markAsVisited(startingCity);
    stack.push(startingCity);
    route.push_back(startingCity);

    while (!isExplorationComplete()){
        int current_city = stack.peek();
        exploreFromProvince(current_city);
    }
}

// Helper function to explore from a specific province
void RoutePlanner::exploreFromProvince(int province) {
    enqueueNeighbors(province);

    while (!isExplorationComplete()){
        int next_city = queue.dequeue();

        if (map.isWithinRange(province, next_city, maxDistance)){
            stack.push(next_city);
            map.markAsVisited(next_city);
            route.push_back(next_city);
            return;
        }
    }

    backtrack(); // No valid neighbours, backrack
}

void RoutePlanner::enqueueNeighbors(int province) {
    for (int i = 0; i < 81; i++){
        // Skip invalid neighbors
        if (i == province || isWeatherRestricted(i) || map.isVisited(i)){
            if (isWeatherRestricted(i)){
                std::cout << "Province " << cities[province] << " is weather-restricted. Skipping.\n";
            }
            continue;
        }

        if (isPriorityProvince(i)){
            queue.enqueuePriority(i);
        } else {
            queue.enqueue(i);
        }
    }
}

void RoutePlanner::backtrack() {
    while (!isExplorationComplete()){
        int current_city = stack.pop();
    }
}

bool RoutePlanner::isExplorationComplete() const {
    return (stack.isEmpty() && queue.isEmpty());
}

void RoutePlanner::displayResults() const {
    // Display "Journey Completed!" message
    std::cout << "----------------------------\n"
              << "Journey Completed!\n"
              << "----------------------------\n\n";

    // Display the total number of provinces visited
    std::cout << "Total Number of Provinces Visited: " << map.countVisitedProvinces() << "\n";

    // Display the total distance covered
    std::cout << "Total Distance Covered: " << totalDistanceCovered << " km\n\n";

    // Display the route in the order visited
    std::cout << "Route Taken:\n";
    for (size_t i = 0; i < route.size(); i++) {
        std::cout << cities[route[i]];
        if (i < route.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n\n";

    // Priority Province Summary
    std::cout << "Priority Provinces Status:\n";
    int priority_prov_visited = 0;
    for (int i = 0; i < numPriorityProvinces; i++) {
        int curr_prov = priorityProvinces[i];
        bool curr_prov_visited = map.isVisited(curr_prov);
        std::cout << "- " << cities[curr_prov] << " (" << (curr_prov_visited ? "Visited" : "Not Visited") << ")\n";
        if (curr_prov_visited) {
            priority_prov_visited++;
        }
    }
    std::cout << "\n";

    // Display the total priority provinces visited
    std::cout << "Total Priority Provinces Visited: " << priority_prov_visited << " out of " << numPriorityProvinces << "\n";

    // Warning or success message
    if (priority_prov_visited < numPriorityProvinces) {
        std::cout << "Warning: Not all priority provinces were visited.\n";
    } else {
        std::cout << "Success: All priority provinces were visited.\n";
    }

    std::cout << std::endl;
}


