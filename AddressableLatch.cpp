#include "AddressableLatch.h"

AddressableLatch::AddressableLatch() : _digitLatchMap({
  B00000000, // Q0 000
  B00000100, // Q1 100
  B00000010, // Q2 010
  B00000110, // Q3 110
  B00000001, // Q4 001
  B00000101, // Q5 101
  B00000011, // Q6 011
  B00000111, // Q7 111
}) {
  Setup();
}

AddressableLatch::AddressableLatch(uint8_t digitLatchMap[8]) : _digitLatchMap({
  digitLatchMap[0],
  digitLatchMap[1],
  digitLatchMap[2],
  digitLatchMap[3],
  digitLatchMap[4],
  digitLatchMap[5],
  digitLatchMap[6],
  digitLatchMap[7]
  })
{
  Setup();
}
  
/**
* Output value should be 1 through 8
*
*/
void AddressableLatch::SetOutput(uint8_t output, uint8_t value)
{
  //Setup();
  digitalWrite(HC259_LE, HIGH);
  digitalWrite(HC259_MR, !HIGH);
  digitalWrite(HC259_D, !value);
  _setLatch(output - 1);
  digitalWrite(HC259_LE, LOW);
  digitalWrite(HC259_LE, HIGH);
  digitalWrite(HC259_D, HIGH);
}

void AddressableLatch::SetOutputs(uint8_t values)
{
  //Setup();
  digitalWrite(HC259_LE, HIGH);
  digitalWrite(HC259_MR, !HIGH);
  for (uint8_t i = 0; i <= 7; i++)
  {
    digitalWrite(HC259_D, !bitRead(values, i));
    _setLatch(i);
    digitalWrite(HC259_LE, LOW);
    digitalWrite(HC259_LE, HIGH);
    digitalWrite(HC259_D, HIGH);
  }
}

void AddressableLatch::DemuxOutput(uint8_t output, uint8_t value)
{
  //Setup();  
  digitalWrite(HC259_LE, LOW);
  digitalWrite(HC259_MR, !LOW);  
  digitalWrite(HC259_D, !value);
  _setLatch(output);
}

void AddressableLatch::AllHigh()
{
  ResetMemory();
}

void AddressableLatch::AllLow()
{
  SetOutputs(0);
}

void AddressableLatch::Setup()
{
  pinMode(HC259_MR, OUTPUT);
  pinMode(HC259_LE, OUTPUT);
  pinMode(HC259_A, OUTPUT);
  pinMode(HC259_B, OUTPUT);
  pinMode(HC259_C, OUTPUT);
  pinMode(HC259_D, OUTPUT);
//  digitalWrite(HC259_LE, HIGH);
}

void AddressableLatch::ResetMemory()
{
  //Setup();
//  pinMode(HC259_MR, OUTPUT);
//  pinMode(HC259_LE, OUTPUT);
  digitalWrite(HC259_LE, HIGH);
  digitalWrite(HC259_MR, !HIGH);
  
  digitalWrite(HC259_MR, !LOW);
  digitalWrite(HC259_MR, !HIGH);
}

void AddressableLatch::_setLatch(uint8_t latch)
{
  digitalWrite(HC259_A, bitRead(_digitLatchMap[latch], 0));
  digitalWrite(HC259_B, bitRead(_digitLatchMap[latch], 1));
  digitalWrite(HC259_C, bitRead(_digitLatchMap[latch], 2));
}
