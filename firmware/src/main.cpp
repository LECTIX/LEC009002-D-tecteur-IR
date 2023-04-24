#include <Arduino.h>
#include "constants.h"

// Return true if sensor is triggered
bool updateSensor(const int ledPin, const int sensorPin)
{
    bool ret = false;
    digitalWrite(ledPin, HIGH);  /* turn ON IR LED */
    delay(1);                    /* wait for everything to stabilize */
    if (!digitalRead(sensorPin)) /* if sensor pin is low, there is maybe something */
    {
        digitalWrite(ledPin, LOW); /* turn OFF IR LED */
        delay(1);                  /* and repeat test to make sure it wasn't a false trigger */
        if (digitalRead(sensorPin))
        {
            digitalWrite(ledPin, HIGH);
            delay(1);
            if (!digitalRead(sensorPin))
                ret = true;
        }
    }
    digitalWrite(ledPin, LOW);
    return ret;
}

void setup()
{
    pinMode(PIN_IR_LED_1, OUTPUT);
    pinMode(PIN_IR_LED_2, OUTPUT);
    pinMode(PIN_IR_SENSOR_1, INPUT);
    pinMode(PIN_IR_SENSOR_2, INPUT);
    pinMode(PIN_SENSOR1_MODE, INPUT_PULLUP);
    pinMode(PIN_SENSOR2_MODE, INPUT_PULLUP);
    pinMode(PIN_RELAY, OUTPUT);
}

enum STATE
{
    WAITING_TRIGGER,
    TRIGGERED_SENSOR_1,
    TRIGGERED_SENSOR_2,
    WAITING_SENSOR_1_DEACTIVATION,
    WAITING_SENSOR_2_DEACTIVATION
};

STATE state = WAITING_TRIGGER;
uint32_t lastTriggerTmstp = 0;

void loop()
{
    bool sensor1 = updateSensor(PIN_IR_LED_1, PIN_IR_SENSOR_1);
    bool sensor2 = updateSensor(PIN_IR_LED_2, PIN_IR_SENSOR_2);

    if (digitalRead(PIN_SENSOR1_MODE)^digitalRead(PIN_SENSOR2_MODE)) /* only 1 sensor plugged in */
    {
        if (sensor1 || sensor2)
        {
            digitalWrite(PIN_RELAY, HIGH);
            lastTriggerTmstp = millis();
        }
        else if (millis() - lastTriggerTmstp > MODE_1_SENSOR_TIMEOUT)
        {
            digitalWrite(PIN_RELAY, LOW);
        }
    }
    else /* Both sensors are plugged in */
    {
        switch (state)
        {
        case WAITING_TRIGGER:
            if (sensor1)
                state = TRIGGERED_SENSOR_1;
            if (sensor2)
                state = TRIGGERED_SENSOR_2;
            break;

        case TRIGGERED_SENSOR_1:
            digitalWrite(PIN_RELAY, HIGH);
            if (sensor2)
            {
                digitalWrite(PIN_RELAY, LOW);
                lastTriggerTmstp = millis();
                state = WAITING_SENSOR_2_DEACTIVATION;
            }
            break;

        case TRIGGERED_SENSOR_2:
            digitalWrite(PIN_RELAY, HIGH);
            if (sensor1)
            {
                digitalWrite(PIN_RELAY, LOW);
                lastTriggerTmstp = millis();
                state = WAITING_SENSOR_1_DEACTIVATION;
            }
            break;

        case WAITING_SENSOR_1_DEACTIVATION:
            if (sensor1)
                lastTriggerTmstp = millis();
            else if (millis() - lastTriggerTmstp > MODE_2_SENSOR_TIMEOUT)
                state = WAITING_TRIGGER;
            break;

        case WAITING_SENSOR_2_DEACTIVATION:
            if (sensor2)
                lastTriggerTmstp = millis();
            else if (millis() - lastTriggerTmstp > MODE_2_SENSOR_TIMEOUT)
                state = WAITING_TRIGGER;
            break;

        default:
            state = WAITING_TRIGGER;
            break;
        }
    }

    // delay(1000);
    // digitalWrite(PIN_RELAY,!digitalRead(PIN_RELAY));
}