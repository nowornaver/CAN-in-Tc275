#ifndef DRIVER_CAN
#define DRIVER_CAN

/***********************************************************************/
/*Include*/ 
/***********************************************************************/
#include "Ifx_Types.h"
#include "IfxCpu.h"
#include "IfxMultican_Can.h"
#include <stdint.h>  // <-- 직접 추가

/***********************************************************************/
/*Define*/ 
/***********************************************************************/
#define ECU1_TX_OBJ_NUM     10u
#define ECU1_RX_OBJ_NUM     10u

/***********************************************************************/
/*Typedef*/ 
/***********************************************************************/
//typedef struct
//{
//    struct
//    {
//        IfxMultican_Can        can;          /**< \brief CAN driver handle */
//        IfxMultican_Can_Node   canSrcNode;   /**< \brief CAN Source Node */
//        IfxMultican_Can_MsgObj canSrcMsgObj; /**< \brief CAN Source Message object */
//    }drivers;
//} App_MulticanBasic;
typedef struct
{

    IfxMultican_Can        CanEcu1;
    IfxMultican_Can_Node   CanEcu1Node;
    IfxMultican_Can_MsgObj CanEcu1MsgTxObj[ECU1_TX_OBJ_NUM];
    IfxMultican_Can_MsgObj CanEcu1MsgRxObj[ECU1_RX_OBJ_NUM];
} Ecu1Can;

//typedef struct
//{
//    IfxMultican_Message data[ECU1_RX_OBJ_NUM];
//} stRxMsgData1;
/***********************************************************************/
/*External Variable*/ 
/***********************************************************************/
//IFX_EXTERN App_MulticanBasic g_MulticanBasic;
IFX_EXTERN Ecu1Can stEcu1Can;

/***********************************************************************/
/*Global Function Prototype*/ 
/***********************************************************************/
extern void Driver_Can_Init(void);
extern void Driver_Can_TxTest(void);
extern void Driver_Can_TxTest1(void);
extern void CAN_RxInt0Handler(void);
#endif /* DRIVER_STM */
