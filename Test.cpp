#include "Map.h"
#include <iostream>

int main(int argc, char const *argv[])
{
    Map map;
    map.loadDistanceData(argv[3]);
    return 0;
}
