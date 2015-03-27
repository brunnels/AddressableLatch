#include <AddressableLatch.h>

AddressableLatch latch((uint8_t[8]){
  B00000000, // Q0 000 BT1
  B00000001, // Q4 001 BT2
  B00000010, // Q2 010 BT3
  B00000011, // Q6 011 BT4
  B00000100, // Q1 100 BT5
  B00000101, // Q5 101 BT6
  B00000110, // Q3 110 BT7 
  B00000111, // Q7 111 BT8
});

static const uint8_t testMap[23] = {
  B11111111,
  B11111110,
  B11111100,
  B11111000,
  B11110000,
  B11100000,
  B11000000,
  B10000000,
  B00000000,
  B01010101,
  B10101010,
  B00000000,
  B11110000,
  B00001111,
  B00000000,
  B00000011,
  B00001100,
  B00110000,
  B11000000,
  B00110000,
  B00001100,
  B00000011,
  B00000000,
};

void setup() 
{ 
  latch.ResetMemory();
  delay(500);
}

void test1()
{
  latch.ResetMemory();
  delay(500);
  latch.AllLow();
  delay(500);
  latch.AllHigh();
  delay(500);
  latch.AllLow();
  delay(500);
  latch.AllHigh();
  delay(500);
  latch.AllLow();
  delay(500);
}

void test2()
{
  latch.ResetMemory();
  delay(500);
  for(uint8_t j = 1; j < 3; j++)
  {
    for (uint8_t i = 0; i < 24; i++) 
	{
      latch.SetOutputs((j % 2 == 0) ? ~testMap[i] : testMap[i]);
      delay(500);
    }
  }
}

void test3()
{
  latch.ResetMemory();
  delay(500);
  for (uint8_t i = 0; i <= 7; i++)
  {
    latch.DemuxOutput(i, LOW);
    delay(500);
  }
}

void test4()
{
  latch.ResetMemory();
  delay(500);
  for (uint8_t i = 0; i <= 7; i++)
  {
    latch.SetOutput(i, LOW);
    delay(500);
  }
  
  for (int8_t i = 7; i >= 0; i--)
  {
    latch.SetOutput(i, HIGH);
    delay(500);
  }
}

void loop() 
{
  test4();
  test3();
  test1();
  test2();
}