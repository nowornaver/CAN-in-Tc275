/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem.h
 *
 * Code generated for Simulink model 'Subsystem'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 25.1 (R2025a) 21-Nov-2024
 * C/C++ source code generated on : Wed Jun  4 09:28:02 2025
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Infineon->TriCore
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#ifndef Subsystem_h_
#define Subsystem_h_
#ifndef Subsystem_COMMON_INCLUDES_
#define Subsystem_COMMON_INCLUDES_
#include "rtwtypes.h"
//#include "rtw_continuous.h"
//#include "rtw_solver.h"
#include "math.h"
#endif                                 /* Subsystem_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM RT_MODEL;

/* Custom Type definition for MATLAB Function: '<S2>/MLFB' */
#ifndef struct_tag_va7AlAd3Cdhv5TjMxVQeyD
#define struct_tag_va7AlAd3Cdhv5TjMxVQeyD

struct tag_va7AlAd3Cdhv5TjMxVQeyD
{
  boolean_T matlabCodegenIsDeleted;
  boolean_T IsNetworkInitialized;
};

#endif                                 /* struct_tag_va7AlAd3Cdhv5TjMxVQeyD */

#ifndef typedef_c_coder_internal_ctarget_DeepLe
#define typedef_c_coder_internal_ctarget_DeepLe

typedef struct tag_va7AlAd3Cdhv5TjMxVQeyD c_coder_internal_ctarget_DeepLe;

#endif                             /* typedef_c_coder_internal_ctarget_DeepLe */

/* Block signals and states (default storage) for system '<Root>' */
typedef struct {
  c_coder_internal_ctarget_DeepLe network;/* '<S2>/MLFB' */
  real_T Delay_DSTATE;                 /* '<S3>/Delay' */
  real_T Delay1_DSTATE;                /* '<S3>/Delay1' */
  real_T Delay2_DSTATE;                /* '<S3>/Delay2' */
  real_T Delay_DSTATE_d;               /* '<S4>/Delay' */
  real_T Delay1_DSTATE_o;              /* '<S4>/Delay1' */
  real_T Delay2_DSTATE_e;              /* '<S4>/Delay2' */
  boolean_T network_not_empty;         /* '<S2>/MLFB' */
} DW;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T In1;                          /* '<Root>/In1' */
  real_T In2;                          /* '<Root>/In2' */
} ExtU;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real32_T output;                     /* '<Root>/output' */
} ExtY;

/* Real-time Model Data Structure */
struct tag_RTM {
  const char_T * volatile errorStatus;
};

/* Block signals and states (default storage) */
extern DW rtDW;

/* External inputs (root inport signals with default storage) */
extern ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY rtY;

/* Model entry point functions */
extern void Subsystem_initialize(void);
extern void Subsystem_step(void);

/* Real-time Model object */
extern RT_MODEL *const rtM;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('firstmodel1234/Subsystem')    - opens subsystem firstmodel1234/Subsystem
 * hilite_system('firstmodel1234/Subsystem/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'firstmodel1234'
 * '<S1>'   : 'firstmodel1234/Subsystem'
 * '<S2>'   : 'firstmodel1234/Subsystem/Predict'
 * '<S3>'   : 'firstmodel1234/Subsystem/Subsystem'
 * '<S4>'   : 'firstmodel1234/Subsystem/Subsystem1'
 * '<S5>'   : 'firstmodel1234/Subsystem/Predict/MLFB'
 */
#endif                                 /* Subsystem_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
