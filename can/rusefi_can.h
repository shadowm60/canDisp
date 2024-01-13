#ifndef _RUSEFI_CAN_H_
#define _RUSEFI_CAN_H_

#include "ch.h"

//Can Ids
//Base as default is 512 dec set in TS
#define BASE0	0x200
#define BASE1   (BASE0+0x1)
#define BASE2   (BASE0+0x2)	//Throttle position
#define BASE3   (BASE0+0x3)
#define BASE4   (BASE0+0x4)
#define BASE5   (BASE0+0x5)
#define BASE6   (BASE0+0x6)
#define BASE7   (BASE0+0x7)
#define BASE8   (BASE0+0x8)

typedef struct {
	uint16_t WarningCounter; // BASE0 -  0 - 16 
	uint16_t LastError;      // BASE0 - 16 - 16
	uint16_t RPM;            // BASE1 -  0 - 16
	uint16_t PPS;            // BASE2 -  0 - 16 - 0.01
	uint16_t TPS1;           // BASE2 - 16 - 16 - 0.01
	uint16_t TPS2;           // BASE2 - 32 - 16 - 0.01
	uint16_t Wastegate;      // BASE2 - 48 - 16 - 0.01
	uint16_t MAP;            // BASE3 -  0 - 16 - 0.03
	uint16_t OilPress;       // BASE4 - 16 - 16 - 0.03 - kPa
	uint16_t BattVolt;       // BASE4 - 48 - 16 - 0.001 - mV
	uint16_t CylAM;          // BASE5 -  0 - 16 - mg
	uint16_t EstMAF;         // BASE5 - 16 - 16 - 0.01 - kg/h
	uint16_t InjPW;          // BASE5 - 32 - 16 - 0.003 - ms
	uint16_t KnockCt;        // BASE5 - 48 - 16
	uint16_t FuelUsed;       // BASE6 -  0 - 16 - g
	uint16_t FuelFlow;       // BASE6 - 16 - 16 - 0.005 - g/s
	uint16_t FuelTrim1;      // BASE6 - 32 - 16 - 0.01 - -50
	uint16_t FuelTrim2;      // BASE6 - 48 - 16 - 0.01 - -50
	uint16_t Lam1;           // BASE7 -  0 - 16 - 0.0001 Lambda
	uint16_t Lam2;           // BASE7 - 16 - 16 - 0.0001 Lambda
	uint16_t FpLow;          // BASE7 - 32 - 16 - 0.03 kPa
	uint16_t FpHigh;         // BASE7 - 48 - 16 - 0.1 bar
	int16_t  IgnitionTiming; // BASE1 - 16 - 16 - 0.02
	uint8_t RevLimitAct:1;   // BASE0 - 32 - 1
	uint8_t MainRelayAct:1;  // BASE0 - 33 - 1
	uint8_t FuelPumpAct:1;   // BASE0 - 34 - 1
	uint8_t CELAct:1;        // BASE0 - 35 - 1
	uint8_t EGOHeatAct:1;    // BASE0 - 36 - 1
	uint8_t Reserved1:1;     // BASE0 - 37 - 1
	uint8_t Reserved2:1;     // BASE0 - 38 - 1
	uint8_t Reserved3:1;     // BASED - 39 - 1
	uint8_t CurrentGear;     // BASE0 - 40 - 1
	uint8_t InjDuty;         // BASE1 - 32 - 8
	uint8_t IgnDuty;         // BASE1 - 40 - 8
	uint8_t VehicleSpeed;    // BASE1 - 48 - 8
	uint8_t FlexPct;         // BASE1 - 56 - 8
    uint8_t CoolantTemp;     // BASE3 - 16 - 8 - -40
    uint8_t IntakeTemp;      // BASE3 - 24 - 8 - -40
    uint8_t AUX1Temp;        // BASE3 - 32 - 8 - -40
    uint8_t AUX2Temp;        // BASE3 - 40 - 8 - -40
    uint8_t MCUTemp;         // BASE3 - 48 - 8 - -40	
	uint8_t FuelLevel;       // BASE3 - 56 - 8 - %
	int8_t Cam1I;            // BASE8 -  0 - 8 - deg
	int8_t Cam1Itar;         // BASE8 -  8 - 8 - deg
	int8_t Cam1E;            // BASE8 - 16 - 8 - deg
	int8_t Cam1Etar;         // BASE8 - 24 - 8 - deg
	int8_t Cam2I;            // BASE8 - 32 - 8 - deg
	int8_t Cam2Itar;         // BASE8 - 40 - 8 - deg
	int8_t Cam2E;            // BASE8 - 48 - 8 - deg
	int8_t Cam2Etar;         // BASE8 - 56 - 8 - deg
	
} CanInfo_Type;

void rusefi_can_process();
void process_BASE0();
void process_BASE1();
void process_BASE2();
void process_BASE3();
void process_BASE4();
void process_BASE5();
void process_BASE6();
void process_BASE7();
void process_BASE8();

#endif