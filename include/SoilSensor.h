#ifndef SOIL_SENSOR_H
#define SOIL_SENSOR_H

void initSoil();
int readSoilAveraged();       // averaged raw analog value
int readSoilPercent();   // 0 (dry) to 100 (wet)

#endif