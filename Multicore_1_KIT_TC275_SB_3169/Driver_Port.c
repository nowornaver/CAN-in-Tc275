/***********************************************************************/
/*Include*/ 
/***********************************************************************/
#include "Driver_Port.h"

/***********************************************************************/
/*Define*/ 
/***********************************************************************/

/***********************************************************************/
/*Typedef*/ 
/***********************************************************************/


/***********************************************************************/
/*Static Function Prototype*/ 
/***********************************************************************/


/***********************************************************************/
/*Variable*/ 
/***********************************************************************/


/***********************************************************************/
/*Function*/ 
/***********************************************************************/
void Driver_Port_Init(void)
{
    /*P00_5    Digital Output*/
//    IfxPort_setPinModeOutput(IfxPort_P00_5.port, IfxPort_P00_5.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
//    IfxPort_setPinLow(IfxPort_P00_5.port, IfxPort_P00_5.pinIndex);

    /*P20_6    Digital Output*/
    IfxPort_setPinModeOutput(IfxPort_P20_6.port, IfxPort_P20_6.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
    IfxPort_setPinLow(IfxPort_P20_6.port, IfxPort_P20_6.pinIndex);
}
void test(void) {
    IfxPort_setPinModeOutput(IfxPort_P00_5.port, IfxPort_P00_5.pinIndex, IfxPort_OutputMode_pushPull, IfxPort_OutputIdx_general);
      IfxPort_setPinLow(IfxPort_P00_5.port, IfxPort_P00_5.pinIndex);

}
