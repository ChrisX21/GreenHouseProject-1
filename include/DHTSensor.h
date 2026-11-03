#ifndef DHT_SENSOR_H
#define DHT_SENSOR_H

void initDht();
bool readDht();          // true if a new reading succeeded
float getTemperature();    // last good reading, Celsius
int getHumidity();         // last good reading, percent

#endif