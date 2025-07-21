/***********************************************************************/
/*Include*/ 
/***********************************************************************/
#include "Driver_Can.h"
#include "SharedVariables.h"
#include <string.h>


/***********************************************************************/
///*Define*/ 일단 CAN OE 에서 쏘는 메세지 받기
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
//App_MulticanBasic g_MulticanBasic; /**< \brief Demo information */
Ecu1Can stEcu1Can;
/***********************************************************************/
/*Function*/ 
/***********************************************************************/
static void Driver_Can_EnrollObject(int32_t msgObjId, uint32_t msgId, uint8_t frameType, uint8_t msgDlc, uint32_t extendedFrame, IfxMultican_Can_MsgObj* pArrObjNum);


void Driver_Can_Init(void)
{
//    processingFlag=1;
    /* create module config */
    IfxMultican_Can_Config canConfig;
    IfxMultican_Can_initModuleConfig(&canConfig, &MODULE_CAN);

    /* initialize module */
    IfxMultican_Can_initModule(&stEcu1Can.CanEcu1, &canConfig);

    /* create CAN node config */
    IfxMultican_Can_NodeConfig canNodeConfig;
    IfxMultican_Can_Node_initConfig(&canNodeConfig, &stEcu1Can.CanEcu1);

    canNodeConfig.baudrate = 500000;
    canNodeConfig.nodeId    = (IfxMultican_NodeId)((int)IfxMultican_NodeId_0);
    canNodeConfig.rxPin     = &IfxMultican_RXD0B_P20_7_IN;
    canNodeConfig.rxPinMode = IfxPort_InputMode_pullUp;
    canNodeConfig.txPin     = &IfxMultican_TXD0_P20_8_OUT;
    canNodeConfig.txPinMode = IfxPort_OutputMode_pushPull;

    IfxMultican_Can_Node_init(&stEcu1Can.CanEcu1Node, &canNodeConfig);

    /*Object Enrollment*/
    Driver_Can_EnrollObject(0u, 0x200, IfxMultican_Frame_transmit,  IfxMultican_DataLengthCode_8, FALSE, &stEcu1Can.CanEcu1MsgTxObj[0]);
    Driver_Can_EnrollObject(1u, 0x201, IfxMultican_Frame_transmit,  IfxMultican_DataLengthCode_8, FALSE, &stEcu1Can.CanEcu1MsgTxObj[1]);
//    Driver_Can_EnrollObject(2u, 0x102, IfxMultican_Frame_transmit,  IfxMultican_DataLengthCode_8, FALSE, &stEcu1Can.CanEcu1MsgTxObj[2]);
    Driver_Can_EnrollObject(10u, 0x300, IfxMultican_Frame_receive,  IfxMultican_DataLengthCode_8, FALSE, &stEcu1Can.CanEcu1MsgRxObj[0]);
    Driver_Can_EnrollObject(11u, 0x400, IfxMultican_Frame_receive,  IfxMultican_DataLengthCode_8, FALSE, &stEcu1Can.CanEcu1MsgRxObj[1]);


}
static void Driver_Can_EnrollObject(int32_t msgObjId,  uint32_t msgId, uint8_t frameType, uint8_t msgDlc,  uint32_t extendedFrame, IfxMultican_Can_MsgObj* pArrObjNum)
{
    /* create message object config */
    IfxMultican_Can_MsgObjConfig canMsgObjConfig;
    IfxMultican_Can_MsgObj_initConfig(&canMsgObjConfig, &stEcu1Can.CanEcu1Node);

    canMsgObjConfig.msgObjId              = msgObjId;
    canMsgObjConfig.messageId             = msgId;
    canMsgObjConfig.frame                 = frameType;
    canMsgObjConfig.control.messageLen    = msgDlc;
    canMsgObjConfig.control.extendedFrame = extendedFrame;
    canMsgObjConfig.acceptanceMask        = 0x7FFFFFFFUL;
    canMsgObjConfig.control.matchingId    = TRUE;
   if (frameType == IfxMultican_Frame_receive) {
       canMsgObjConfig.rxInterrupt.enabled = TRUE;
       canMsgObjConfig.rxInterrupt.srcId = 0u;
       SRC_CAN_CAN0_INT0.B.SRPN = 30u;
       SRC_CAN_CAN0_INT0.B.TOS = 0u;
       SRC_CAN_CAN0_INT0.B.SRE = 1u;
   }
    /* initialize message object */
    IfxMultican_Can_MsgObj_init(pArrObjNum, &canMsgObjConfig);
}
IFX_INTERRUPT(CAN_RxInt0Handler, 0,30);
uint32_t u32nuCanRxcnt = 0u;


IfxMultican_Message stRxMsgData[ECU1_RX_OBJ_NUM];
void CAN_RxInt0Handler(void) {
    IfxMultican_Status readStatus , readStatus1;


    IfxCpu_enableInterrupts();
    readStatus = IfxMultican_Can_MsgObj_readMessage(&stEcu1Can.CanEcu1MsgRxObj[0], &stRxMsgData[0]);
    if(readStatus == IfxMultican_Status_newData) {
        u32nuTemp1 = stRxMsgData[0].data[0]; //이 부분에서 받는 데이터를 QUEUE 형태로 만들어서 데이터가 4개 될때마다 처리하기.
        u32nuTemp2 = stRxMsgData[0].data[1];
        u32nuCanRxcnt++;
    }
    readStatus1 = IfxMultican_Can_MsgObj_readMessage(&stEcu1Can.CanEcu1MsgRxObj[1], &stRxMsgData[1]);
    if (readStatus1 == IfxMultican_Status_newData) {
        u32nuTemp3 = stRxMsgData[1].data[0];
        u32nuTemp4 = stRxMsgData[1].data[1];
        u32nuCanRxcnt++;
    }
//    memcpy(&f32nuTemp1 , &u32nuTemp1,sizeof(f32nuTemp1)); //u32 ->f32
//    memcpy(&f32nuTemp2 , &iq , sizeof(f32nuTemp2)); // u32 ->f32
    processingFlag = 1;
    combine = ((uint64_t)u32nuTemp2 << 32) | u32nuTemp1; //<< 이러면 64비트로 바꾼거임;;
    combine1 = ((uint64_t)u32nuTemp4 << 32) | u32nuTemp3; //<< 이러면 64비트로 바꾼거임;;
    memcpy(&IQ , &combine , sizeof(IQ));
    memcpy(&POS , &combine1 , sizeof(combine1));




}
void Driver_Can_TxTest(void)
{

    memcpy(&Force , &processedValue , sizeof(Force));

    const uint32_t dataLow  = Force;;
    const uint32_t dataHigh = 0;

//    combined = ((uint64_t)high << 32) | low;
//    memcpy(&combine1 , &IQ , sizeof(IQ));
    /* Transmit Data */
    {
        IfxMultican_Message msg;
        IfxMultican_Message_init(&msg, 0x200, dataLow, dataHigh, IfxMultican_DataLengthCode_8);

        while (IfxMultican_Can_MsgObj_sendMessage(&stEcu1Can.CanEcu1MsgTxObj[0], &msg) == IfxMultican_Status_notSentBusy)
        {}
    }
}
//void Driver_Can_TxTest1(void)
//{
//    const uint32 dataLow1  = u32nuTemp3;
//    const uint32 dataHigh2 = u32nuTemp4;
////지금 현재는 iq 값도 2개 pos 값도 2개 필요함 , iq 값이랑 pos 값 신호를 쪼갤 필요가 있음.
//
//    /* Transmit Data */
//    {
//        IfxMultican_Message msg1;
//        IfxMultican_Message_init(&msg1, 0x201, dataLow1, dataHigh2, IfxMultican_DataLengthCode_8);
//
//        while (IfxMultican_Can_MsgObj_sendMessage(&stEcu1Can.CanEcu1MsgTxObj[1], &msg1) == IfxMultican_Status_notSentBusy)
//        {}
//    }
//}
