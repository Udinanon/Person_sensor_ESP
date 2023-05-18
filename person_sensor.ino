// directly from https://github.com/usefulsensors/person_sensor_arduino/blob/main/person_sensor_arduino.ino

#include <Wire.h>

#include "person_Sensor.h"

// How long to wait between reading the sensor. The sensor can be read as
// frequently as you like, but the results only change at about 5FPS, so
// waiting for 200ms is reasonable.
const int32_t SAMPLE_DELAY_MS = 200;
// static const uint8_t D0   = 16;
// static const uint8_t D1   = 5;
// static const uint8_t D2   = 4;
// static const uint8_t D3   = 0;
// static const uint8_t D4   = 2;
// static const uint8_t D5   = 14;
// static const uint8_t D6   = 12;
// static const uint8_t D7   = 13;
// static const uint8_t D8   = 15;
// static const uint8_t D9   = 3;
// static const uint8_t D10  = 1;

#define SCL_PIN D1 // YELLOW
#define SDA_PIN D2 // BLUE
#define SENSOR_MAX_FACES 4

void setup() {
  // You need to make sure you call Wire.begin() in setup, or the I2C access
  // below will fail.
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.begin(9600);
}

void loop() {
  person_sensor_results_t results = {};
  // Perform a read action on the I2C address of the sensor to get the
  // current face information detected.
  if (!person_sensor_read(&results)) {
    Serial.println("No person sensor results found on the i2c bus");
    delay(SAMPLE_DELAY_MS);
    return;
  }

  //Serial.println("********");
  Serial.print("{\"n_faces\":");
  Serial.print(results.num_faces);
  Serial.print(", \"faces\":[");
  for (int i = 0; i < SENSOR_MAX_FACES; ++i) {
    const person_sensor_face_t* face = &results.faces[i];
    Serial.print("{");
    Serial.print("\"face\":");
    Serial.print(i);
    Serial.print(", \"conf\":");
    Serial.print(face->box_confidence);
    Serial.print(", \"box\":[");   
    Serial.print(face->box_left);
    Serial.print(", ");
    Serial.print(face->box_top);
    Serial.print(", ");
    Serial.print(face->box_right);
    Serial.print(", ");
    Serial.print(face->box_bottom);
    Serial.print("], \"facing\":");
    if (face->is_facing) {
      Serial.print("1");
    } else {
      Serial.print("0");
    }
    Serial.print("}");
    if(i < SENSOR_MAX_FACES - 1){
      Serial.print(",");
    }
  }
  Serial.println("]}");
  delay(SAMPLE_DELAY_MS);
}
