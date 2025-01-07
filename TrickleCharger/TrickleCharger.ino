

const unsigned long INTERVAL_6_HOURS_IN_MILLISECONDS = 6UL * 60UL * 60UL * 1000UL; // 6 hours in milliseconds
const unsigned long INTERVAL_3_HOURS_IN_MILLISECONDS = 3UL * 60UL * 60UL * 1000UL; // 6 hours in milliseconds
const unsigned long INTERVAL_1_SECOND_IN_MILLISECONDS = 1UL * 1000UL; // 1 second  in milliseconds


const int BASE = 4 ;  //The first relay is connected to the I / O port
const int NUM_RELAYS = 4;   //Total number of relays


unsigned int RELAY1 = BASE + 3;
unsigned int RELAY2 = BASE + 2;
unsigned int RELAY3 = BASE + 1;
unsigned int RELAY4 = BASE + 0;

//unsigned int RELAYS[NUM_RELAYS] =  {BASE + 0, BASE + 1, BASE + 2, BASE + 3};// relay 4, relay3, relay2, relay1
unsigned int Relays[NUM_RELAYS] =  {BASE + 3, BASE + 2, BASE + 1, BASE + 0};  // relay1, relay2, relay3, relay4

const unsigned int NUM_RELAYS_TO_USE = 2; // use the first N relays in the Relay array

unsigned long lastWriteTime;

unsigned int currentRelay;

void setup()
{
   unsigned int port;

  currentRelay = 0;
  
  for (int i = BASE; i < BASE + NUM_RELAYS; i ++) 
  {
    pinMode(i, OUTPUT);   //Set the number I/O port to outputs
  }
  
  all_relays_off();

  port = Relays[currentRelay];
  digitalWrite(port, HIGH);
  lastWriteTime = millis();

}

void loop()
{
  unsigned long currentMillis;
  unsigned long time_milliseconds;
  unsigned int port;

  currentMillis = millis();
  time_milliseconds = subtractUnsignedLong(currentMillis, lastWriteTime);
  
  //if (time_milliseconds >= INTERVAL_1_SECOND_IN_MILLISECONDS)
  //if (time_milliseconds >= INTERVAL_3_HOURS_IN_MILLISECONDS)
  if (time_milliseconds >= INTERVAL_6_HOURS_IN_MILLISECONDS)
  {
    // Reset the timer for the next write
    lastWriteTime = currentMillis;
      
    all_relays_off();
    currentRelay++;
    if(currentRelay >= NUM_RELAYS_TO_USE)
    {
      currentRelay = 0;
    }
    port = Relays[currentRelay];
    //port = BASE + currentRelay;
    digitalWrite(port, HIGH);
    
    
    //digitalWrite(RELAY1, !digitalRead(RELAY1));  // This will toggle the LED on each cycle
  }
}

void all_relays_off(void)
{
  for (int i = BASE; i < BASE + NUM_RELAYS; i ++) 
  {
      digitalWrite(i, LOW);    //Set the number I/O port outputs to "low", that is, gradually turn off the relay.
      delay(10);        
  }
}

//subtract a - b. 
//a shoulc typically be larger than b
//When b is larger than a, as when b is a millisecond count and roles over, it still works
unsigned long subtractUnsignedLong(unsigned long a, unsigned long b)
{
  unsigned long difference;
  if( a >=b )
  {
    difference = a - b;
  }
  else
  {
    difference = (0xFFFFFFFF - b) + a + 1;
  }
  return difference;


}


// //Turn on realy. relay num is 1 through 4
// void turn_on_relay(unsigned int relayNum)
// {
//   unsigned int port;

//   port = relayNum - 1 + BASE;
//   digitalWrite(port, HIGH);
// }


// void loop()
// {
//    for (int i = BASE; i < BASE + NUM; i ++) 
//    {
//      digitalWrite(i, LOW);    //Set the number I/O port outputs to "low", that is, gradually turn off the relay.
//      delay(500);        //delay 0.2S
//    }
//    for (int i = BASE; i < BASE + NUM; i ++) 
//    {
//      digitalWrite(i, HIGH);    //Set the number I/O port outputs to "high", that is, gradually turn on relay.
//      delay(500);        //delay 0.2S
//    }  
// }