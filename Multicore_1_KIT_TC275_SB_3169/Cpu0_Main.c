/***********************************************************************/
/*Include*/
/***********************************************************************/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "Driver_Watchdog.h"
#include "Driver_Stm.h"
#include "Driver_Port.h"
#include "Driver_Adc.h"
#include "Driver_Asc.h"
#include "Driver_Gtm.h"
#include "Driver_Can.h"
#include "SharedVariables.h"
#include <string.h>

#include "AppScheduling.h"
extern void core1_main(void);  // 반드시 선언 필요

/***********************************************************************/
/*Typedef*/
/***********************************************************************/

/***********************************************************************/
/*Static Function Prototype*/
/***********************************************************************/


/***********************************************************************/
/*Variable*/
/***********************************************************************/
IfxCpu_syncEvent g_cpuSyncEvent = 0;

/***********************************************************************/
/*Function*/
/***********************************************************************/
int core0_main(void)
{

//    volatile int processingFlag  __attribute__((section(".shared"))) = 1;
//    IfxCpu_startCore(&Cpu1_m, (uint32)core1_main);
    //해야할거 일단 지금 변수 2개로 받고 있는데 can 데이터를 1개 변수를 활용해서만 받기
    IfxCpu_startCore(&MODULE_CPU1, (uint32)&core1_main);
    /*Driver Init*/
    Driver_Watchdog_Init();
    Driver_Port_Init();

    Driver_Stm_Init();
    Driver_Adc_Init();
    Driver_Asc_Init();
//    Driver_Gtm_Init();
    Driver_Can_Init();
    /*Global Interrupt Enable*/
    IfxCpu_enableInterrupts();
    IfxCpu_emitEvent(&g_cpuSyncEvent);
    IfxCpu_waitEvent(&g_cpuSyncEvent, 1);

    while(1)
    {
        AppScheduling();
    }
    return (1);
}
