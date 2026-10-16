#ifndef LIGHT_SENSOR_H
#define LIGHT_SENSOR_H

void initLight();
int readLight();         // 0 (very bright) to 1023 (dark)
bool isDark();           // true if reading is above LIGHT_DARK_THRESHOLD

#endif