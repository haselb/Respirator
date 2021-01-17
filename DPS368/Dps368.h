#ifndef DPS368_H_INCLUDED
#define DPS368_H_INCLUDED

#define DPS_DISABLESPI 1  // disable SPI-Bus and enable I2C-Bus

#include "DPS368\DpsClass.h"
#include "DPS368\dps368_config.h"

class Dps368 : public DpsClass
{
public:
  int16_t getContResults(float *tempBuffer, uint8_t &tempCount, float *prsBuffer, uint8_t &prsCount);

  /**
   * @brief Set the source of interrupt (FIFO full, measurement values ready)
   * 
   * @param intr_source Interrupt source as defined by Interrupt_source_310_e
   * @param polarity 
   * @return status code 
   */
  int16_t setInterruptSources(uint8_t intr_source, uint8_t polarity = 1);

protected:
  uint8_t m_tempSensor;

  //compensation coefficients
  int32_t m_c0Half;
  int32_t m_c1;

  /////// implement pure virtual functions ///////

  void init(void);
  int16_t configTemp(uint8_t temp_mr, uint8_t temp_osr);
  int16_t configPressure(uint8_t prs_mr, uint8_t prs_osr);
  int16_t readcoeffs(void);
  int16_t flushFIFO();
  float calcTemp(int32_t raw);
  float calcPressure(int32_t raw);
};

#endif
