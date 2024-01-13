#include "can_types.h"
#include "rusefi_can.h"


#define maskAll   0xffffffffffffffff
#define getBits(src, start, length) ((*(uint64_t*)src) >> start)& (maskAll >> (64 - (start + length + 1)))

long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[8];
CanInfo_Type rusefiCanData;


void rusefi_can_process()
{
  //apply 11 bit filter
  rxId &= 0x7ff;
  switch (rxId)
  {
    case BASE0:
      process_BASE0();
      break;
    case BASE1:
      process_BASE1();
      break;
    case BASE2:
      process_BASE2();
      break;
    case BASE3:
      process_BASE3();
      break;
    case BASE4:
      process_BASE4();
      break;
    case BASE5:
      process_BASE5();
      break;
    case BASE6:
      process_BASE6();
      break;
    case BASE7:
      process_BASE7();
      break;
    case BASE8:
      process_BASE8();
      break;
    default: 
      //normal traffic, we do not need it
      break;
  }
}


void process_BASE0()
{
  rusefiCanData.WarningCounter = getBits(rxBuf,0,16);
  rusefiCanData.LastError =  getBits(rxBuf,16,16);
  rusefiCanData.RevLimitAct =  getBits(rxBuf,32,1);
  rusefiCanData.MainRelayAct = getBits(rxBuf,33,1);
  rusefiCanData.FuelPumpAct =  getBits(rxBuf,34,1);
  rusefiCanData.CELAct = getBits(rxBuf,35,1);
  rusefiCanData.EGOHeatAct = getBits(rxBuf,36,1);
  rusefiCanData.CurrentGear = getBits(rxBuf,40,8);
}
void process_BASE1()
{
  rusefiCanData.RPM = getBits(rxBuf,0,16);
  rusefiCanData.IgnitionTiming = getBits(rxBuf,16,16);
  rusefiCanData.InjDuty = getBits(rxBuf,32,8);
  rusefiCanData.IgnDuty = getBits(rxBuf,40,8);
  rusefiCanData.VehicleSpeed = getBits(rxBuf,48,8);
  rusefiCanData.FlexPct = getBits(rxBuf,56,8);
}
void process_BASE2()
{
  rusefiCanData.PPS = getBits(rxBuf,0,16);
  rusefiCanData.TPS1 = getBits(rxBuf,16,16);
  rusefiCanData.TPS2 = getBits(rxBuf,32,16);
  rusefiCanData.Wastegate = getBits(rxBuf,48,16);
}
void process_BASE3()
{
  rusefiCanData.MAP = getBits(rxBuf,0,16);
  rusefiCanData.CoolantTemp = getBits(rxBuf,16,8);
  rusefiCanData.IntakeTemp = getBits(rxBuf,24,8);
  rusefiCanData.AUX1Temp = getBits(rxBuf,32,8);
  rusefiCanData.AUX2Temp = getBits(rxBuf,40,8);
  rusefiCanData.MCUTemp = getBits(rxBuf,48,8);
  rusefiCanData.FuelLevel = getBits(rxBuf,56,8);
}
void process_BASE4()
{
  rusefiCanData.OilPress = getBits(rxBuf,16,16);
  rusefiCanData.BattVolt = getBits(rxBuf,48,16);
}
void process_BASE5()
{
  rusefiCanData.CylAM = getBits(rxBuf,8,16);
  rusefiCanData.EstMAF = getBits(rxBuf,16,16);
  rusefiCanData.InjPW = getBits(rxBuf,32,16);
  rusefiCanData.KnockCt = getBits(rxBuf,48,16);
}
void process_BASE6()
{
  rusefiCanData.FuelUsed = getBits(rxBuf,0,16);
  rusefiCanData.FuelFlow = getBits(rxBuf,16,16);
  rusefiCanData.FuelTrim1 = getBits(rxBuf,32,16);
  rusefiCanData.FuelTrim2 = getBits(rxBuf,48,16);
  
}
void process_BASE7()
{
  rusefiCanData.Lam1 = getBits(rxBuf,0,16);
  rusefiCanData.Lam2 = getBits(rxBuf,16,16);
  rusefiCanData.FpLow = getBits(rxBuf,32,16);
  rusefiCanData.FpHigh = getBits(rxBuf,48,16);  
}

void process_BASE8()
{
  rusefiCanData.Cam1I = getBits(rxBuf,0,8);
  rusefiCanData.Cam1Itar = getBits(rxBuf,8,8);
  rusefiCanData.Cam1E = getBits(rxBuf,16,8);
  rusefiCanData.Cam1Etar = getBits(rxBuf,24,8);
  rusefiCanData.Cam2I = getBits(rxBuf,32,8);
  rusefiCanData.Cam2Itar = getBits(rxBuf,40,8);
  rusefiCanData.Cam2E = getBits(rxBuf,48,8);
  rusefiCanData.Cam2Etar = getBits(rxBuf,56,8);  
}
