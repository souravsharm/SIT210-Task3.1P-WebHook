#include <Grove_Temperature_And_Humidity_Sensor.h>
#include <JsonParserGeneratorRK.h>
#define DELAY_TIME 30000 
#define DHT_PIN D4

DHT dht(DHT_PIN);
double temp;
double hum;

void postEventPayload(double temp,double humidity){
    JsonWriterStatic<256> jw;
    {
        JsonWriterAutoObject obj(&jw);
        jw.insertKeyValue("temp",temp);
        jw.insertKeyValue("hum",hum);
    }
    Particle.publish("Temperature",jw.getBuffer(),PRIVATE);

}

// ------------
//setting the pin D4 as an input pin
void setup() {


    dht.begin();
    pinMode(DHT_PIN,INPUT);

}

//looping the code with a 30 second delay 
//values are inserted into a json file
//time is delayed for 30 seconds
void loop() {
  // To blink the LED, first we'll turn it on...
  temp=dht.getTempCelcius();
  hum=dht.getHumidity();
  postEventPayload(temp,hum);
  delay(DELAY_TIME);
  // And repeat!
}
