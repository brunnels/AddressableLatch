#ifndef __ADDRESSABLE_LATCH_H__
#define __ADDRESSABLE_LATCH_H__
#include <Arduino.h>

#define HC259_A 8
#define HC259_B 7
#define HC259_C 6
#define HC259_D 16
#define HC259_LE 3
#define HC259_MR 9

class AddressableLatch
{
  public:
  AddressableLatch();
  AddressableLatch(uint8_t digitLatchMap[8]);
  void Setup();
  void SetOutput(uint8_t output, uint8_t value);
  void SetOutputs(uint8_t values);
  void DemuxOutput(uint8_t output, uint8_t value);
  void AllHigh();
  void AllLow();
  void ResetMemory();

  private:
  const uint8_t _digitLatchMap[8];
  void _setLatch(uint8_t latch);
};

#endif
