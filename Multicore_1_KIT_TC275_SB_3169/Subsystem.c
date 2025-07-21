/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem.c
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

#include "Subsystem.h"
#include "rtwtypes.h"
#include <math.h>
#include <string.h>

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Real-time model */
static RT_MODEL rtM_;
RT_MODEL *const rtM = &rtM_;
extern void microKernel15987887916607304347(int32_T K, const real32_T *A,
  int32_T LDA, const real32_T *B_5, real32_T *C);
extern void microKernel7469625569240486418(int32_T K, const real32_T *A, int32_T
  LDA, const real32_T *B_4, real32_T *C);
extern void microKernel2537396214410276889(int32_T K, const real32_T *A, int32_T
  LDA, const real32_T *B_3, int32_T LDB, real32_T *C, int32_T LDC);
extern void microKernel3460086449071067493(int32_T K, const real32_T *A, int32_T
  LDA, const real32_T *B_2, int32_T LDB, real32_T *C, int32_T LDC);
extern void macroKernel11141464106932832455(int32_T M, int32_T K, int32_T N,
  const real32_T *A, int32_T LDA, const real32_T *B_1, int32_T LDB, real32_T *C,
  int32_T LDC);
extern void matrixMultiply11141464106932832455(int32_T M, int32_T K, int32_T N,
  int32_T blockSizeM, int32_T blockSizeK, int32_T blockSizeN, const real32_T *A,
  const real32_T *B_0, real32_T *C);
static int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator);

/* Forward declaration for local functions */
static real32_T DeepLearningNetwork_callPredict(c_coder_internal_ctarget_DeepLe *
  obj, const real32_T inputsT_0_f1[8]);
static real32_T DeepLearningNetwork_predict(c_coder_internal_ctarget_DeepLe *obj,
  const real_T varargin_1[8]);
static int32_T div_nde_s32_floor(int32_T numerator, int32_T denominator)
{
  return (((numerator < 0) != (denominator < 0)) && (numerator % denominator !=
           0) ? -1 : 0) + numerator / denominator;
}

void microKernel15987887916607304347(int32_T K, const real32_T *A, int32_T LDA,
  const real32_T *B_5, real32_T *C)
{
  int32_T idxA;
  int32_T idxB;
  int32_T k;
  real32_T c;
  idxA = 0;
  idxB = 0;
  c = C[0];
  for (k = 0; k < K; k++) {
    c += A[idxA] * B_5[idxB];
    idxA += LDA;
    idxB++;
  }

  C[0] = c;
}

void microKernel7469625569240486418(int32_T K, const real32_T *A, int32_T LDA,
  const real32_T *B_4, real32_T *C)
{
  int32_T idxA;
  int32_T idxB;
  int32_T k;
  real32_T c;
  real32_T c_0;
  idxA = 1;
  idxB = 0;
  c = C[0];
  c_0 = C[1];
  for (k = 0; k < K; k++) {
    real32_T bTemp;
    bTemp = B_4[idxB];
    c += A[idxA - 1] * bTemp;
    c_0 += A[idxA] * bTemp;
    idxA += LDA;
    idxB++;
  }

  C[0] = c;
  C[1] = c_0;
}

void microKernel2537396214410276889(int32_T K, const real32_T *A, int32_T LDA,
  const real32_T *B_3, int32_T LDB, real32_T *C, int32_T LDC)
{
  int32_T idxA;
  int32_T idxB;
  int32_T k;
  real32_T c;
  real32_T c_0;
  idxA = 0;
  idxB = 0;
  c = C[0];
  c_0 = C[LDC];
  for (k = 0; k < K; k++) {
    real32_T a;
    a = A[idxA];
    c += a * B_3[idxB];
    c_0 += B_3[idxB + LDB] * a;
    idxA += LDA;
    idxB++;
  }

  C[0] = c;
  C[LDC] = c_0;
}

void microKernel3460086449071067493(int32_T K, const real32_T *A, int32_T LDA,
  const real32_T *B_2, int32_T LDB, real32_T *C, int32_T LDC)
{
  int32_T idxA;
  int32_T idxB;
  int32_T k;
  real32_T c;
  real32_T c_0;
  real32_T c_1;
  real32_T c_2;
  idxA = 1;
  idxB = 0;
  c = C[0];
  c_0 = C[1];
  c_1 = C[LDC];
  c_2 = C[LDC + 1];
  for (k = 0; k < K; k++) {
    real32_T a;
    real32_T a_0;
    real32_T bTemp;
    real32_T bTemp_0;
    a = A[idxA - 1];
    a_0 = A[idxA];
    bTemp = B_2[idxB];
    bTemp_0 = B_2[idxB + LDB];
    c += a * bTemp;
    c_0 += a_0 * bTemp;
    c_1 += a * bTemp_0;
    c_2 += a_0 * bTemp_0;
    idxA += LDA;
    idxB++;
  }

  C[0] = c;
  C[1] = c_0;
  C[LDC] = c_1;
  C[LDC + 1] = c_2;
}

void macroKernel11141464106932832455(int32_T M, int32_T K, int32_T N, const
  real32_T *A, int32_T LDA, const real32_T *B_1, int32_T LDB, real32_T *C,
  int32_T LDC)
{
  int32_T i;
  int32_T idxA;
  int32_T idxB;
  int32_T idxC;
  int32_T j;
  j = 0;
  idxB = 0;
  while (j <= N - 2) {
    idxC = LDC * j;
    i = 0;
    idxA = 0;
    while (i <= M - 2) {
      microKernel3460086449071067493(K, &A[idxA], LDA, &B_1[idxB], LDB, &C[idxC],
        LDC);
      idxA += 2;
      idxC += 2;
      i += 2;
    }

    while (i <= M - 1) {
      microKernel2537396214410276889(K, &A[idxA], LDA, &B_1[idxB], LDB, &C[idxC],
        LDC);
      idxA++;
      idxC++;
      i++;
    }

    idxB += LDB << 1;
    j += 2;
  }

  while (j <= N - 1) {
    idxC = LDC * j;
    i = 0;
    idxA = 0;
    while (i <= M - 2) {
      microKernel7469625569240486418(K, &A[idxA], LDA, &B_1[idxB], &C[idxC]);
      idxA += 2;
      idxC += 2;
      i += 2;
    }

    while (i <= M - 1) {
      microKernel15987887916607304347(K, &A[idxA], LDA, &B_1[idxB], &C[idxC]);
      idxA++;
      idxC++;
      i++;
    }

    idxB += LDB;
    j++;
  }
}

void matrixMultiply11141464106932832455(int32_T M, int32_T K, int32_T N, int32_T
  blockSizeM, int32_T blockSizeK, int32_T blockSizeN, const real32_T *A, const
  real32_T *B_0, real32_T *C)
{
  int32_T K2;
  int32_T N2;
  int32_T i;
  int32_T i0;
  int32_T i0_ub;
  int32_T j1;
  int32_T k;
  int32_T k0;
  int32_T k0_ub;
  int32_T tmp;
  memset(C, 0, (uint32_T)((M * N) << 2));
  if (blockSizeM >= M) {
    blockSizeM = M;
  } else {
    blockSizeM = (blockSizeM >> 1) << 1;
    if (blockSizeM <= 0) {
      blockSizeM = 1;
    }
  }

  if (blockSizeN >= N) {
    blockSizeN = N;
  } else {
    blockSizeN = (blockSizeN >> 1) << 1;
    if (blockSizeN <= 0) {
      blockSizeN = 1;
    }
  }

  i0_ub = div_nde_s32_floor(M - 1, blockSizeM);
  k0_ub = div_nde_s32_floor(K - 1, blockSizeK);
  for (j1 = 0; j1 < N; j1 += blockSizeN) {
    if (j1 > N - blockSizeN) {
      N2 = N - j1;
    } else {
      N2 = blockSizeN;
    }

    for (k0 = 1; k0 <= k0_ub + 1; k0++) {
      k = (k0 - 1) * blockSizeK;
      if (k > K - blockSizeK) {
        K2 = K - k;
      } else {
        K2 = blockSizeK;
      }

      for (i0 = 1; i0 <= i0_ub + 1; i0++) {
        i = (i0 - 1) * blockSizeM;
        if (i > M - blockSizeM) {
          tmp = M - i;
        } else {
          tmp = blockSizeM;
        }

        macroKernel11141464106932832455(tmp, K2, N2, &A[i + M * k], M, &B_0[k +
          K * j1], K, &C[i + M * j1], M);
      }
    }
  }
}

/* Function for MATLAB Function: '<S2>/MLFB' */
static real32_T DeepLearningNetwork_callPredict(c_coder_internal_ctarget_DeepLe *
  obj, const real32_T inputsT_0_f1[8])
{
  int32_T dim1;
  real32_T outT_f3_0_f1[32];
  real32_T outT_f5_0_f1[16];
  real32_T d;
  real32_T outT_f5_0_f1_0;
  real32_T outputs_0;
  static const real32_T tmp[256] = { 0.0545655377F, -3.14395E-41F, 0.070171386F,
    1.4129E-40F, 1.50809E-40F, -6.66766E-41F, 0.0474498F, 0.0814832598F,
    -0.0818630904F, -1.24574E-40F, -7.96302E-41F, -0.0294027198F, 0.044564262F,
    -0.00756102335F, -1.71759E-40F, -0.0462916866F, 0.00206919084F, 3.17058E-41F,
    -0.0181625206F, -8.99634E-43F, 8.6718E-41F, 0.00346736563F, 0.0253240895F,
    1.70874E-41F, 0.0010746934F, 0.0013343388F, 0.00787421F, 7.29628E-41F,
    0.0413942784F, -0.0209574364F, -0.0394143239F, -0.0109311426F,
    -0.0189574361F, 1.20657E-40F, 0.00137375563F, 2.12423E-41F, -3.45658E-41F,
    -6.09719E-41F, -0.0974885F, 0.0342543423F, -0.0232658423F, 1.21081E-40F,
    -9.81049E-41F, 0.0118716415F, -0.02761635F, 0.00780023355F, 5.95776E-41F,
    0.0173225086F, -0.00661422033F, -5.91264E-41F, 0.0991034061F, -5.47389E-41F,
    3.56448E-41F, -0.000895856356F, -0.00785385817F, -1.4877E-40F,
    0.000898369646F, 0.0029706452F, 0.0091759162F, -4.32441E-42F, -0.0611498915F,
    -0.0188920964F, 0.0467170924F, 0.0279331058F, 0.00210918346F, -5.56526E-41F,
    -0.0299906153F, 1.21219E-40F, 2.64817E-41F, -6.98603E-41F, 0.104262307F,
    0.0513432324F, 0.00229510036F, -2.92661E-41F, 9.76173E-41F, 0.00930557586F,
    -0.00506033702F, 0.00490104407F, -1.74742E-40F, -0.120994754F,
    -0.00819420069F, -8.61518E-42F, -0.0521065779F, -1.65789E-40F, 2.24376E-41F,
    0.00511266F, 0.00767028332F, 9.12484E-41F, -0.000472581713F, -0.0270953495F,
    0.00498744147F, 4.71803E-41F, 0.000996484538F, -0.0014009343F, 0.0975638F,
    -0.0207338147F, -0.0132061271F, 7.91411E-41F, 0.0229572468F, -1.07648E-40F,
    -1.556E-41F, -7.61396E-41F, -0.0889857411F, 0.0182364564F, 0.0425028242F,
    -4.63942E-41F, -6.87463E-41F, 0.0649428368F, -0.00925984234F, 0.00792495813F,
    -5.6569E-41F, 0.0909130946F, 0.016511092F, -5.85491E-41F, -0.0684971586F,
    -2.70395E-41F, -4.82201E-41F, 0.00429363409F, 0.0531741194F, -3.78351E-42F,
    0.00139751693F, 0.00291410531F, -0.021502208F, 1.21416E-40F, -0.018764047F,
    0.0110626956F, 0.0637085289F, 0.0184699744F, 0.248900145F, 2.65602E-41F,
    -0.163458213F, 2.8089E-41F, -1.74485E-40F, 6.47078E-41F, 0.263841271F,
    0.336912781F, 0.21107249F, 6.38992E-41F, -1.76844E-41F, -0.262257129F,
    0.241595358F, -0.10327334F, -6.65463E-41F, 0.402277738F, 0.0943667665F,
    7.60359E-41F, 0.495053589F, 9.98103E-41F, 1.00987E-40F, 0.0432041772F,
    0.0755129829F, -5.10241E-41F, -0.0169899482F, 0.16907385F, 0.038432F,
    -1.6253E-40F, 0.307366788F, 0.109816901F, 0.372093976F, 0.213304788F,
    0.0950963125F, -1.02673E-41F, -0.0689031631F, -1.23044E-40F, 7.66426E-41F,
    -4.54315E-41F, 0.267950177F, 0.180587873F, 0.132588193F, -7.84895E-41F,
    6.84394E-41F, -0.185001701F, 0.125206128F, -0.0479903705F, 2.01086E-41F,
    0.214527354F, 0.0697048157F, 4.81668E-41F, 0.374795496F, 1.8029E-40F,
    4.57594E-41F, 0.0259555746F, 0.0603234F, -8.56656E-41F, -0.00549502624F,
    0.117379069F, 0.0269714892F, -1.64517E-40F, 0.225559339F, 0.0684503F,
    0.12659815F, 0.109856263F, 0.0343592353F, 2.59436E-41F, 0.0370355211F,
    1.10806E-40F, 1.07957E-40F, -1.65465E-41F, 0.0759952292F, 0.036265932F,
    0.0461778678F, 1.76003E-42F, -6.19976E-41F, 0.0495394841F, 0.0633215308F,
    0.0372138731F, 1.69594E-40F, 0.144189939F, 0.0496714972F, 5.16168E-41F,
    0.0759970918F, 1.65818E-40F, 9.04342E-41F, 0.0118347052F, 0.0457770117F,
    7.23841E-41F, 0.00240133121F, 0.0367085487F, 0.0169732347F, -1.76199E-40F,
    0.0363844037F, 0.0423480459F, -0.0313987583F, 0.0519405082F, -0.0833838284F,
    1.15743E-40F, 0.0919422507F, -1.39463E-40F, 7.84026E-42F, -2.82922E-41F,
    -0.0430272035F, -0.0372345F, 0.0716999695F, -1.2508E-41F, 3.16988E-41F,
    0.0600118861F, -0.0215022471F, 0.0691216886F, -1.8595E-40F, -0.119553052F,
    0.0349267162F, -1.64678E-40F, -0.193716109F, 1.37026E-40F, -7.18726E-42F,
    0.00314665F, 0.0316653661F, -1.11571E-41F, 0.00736843515F, -0.0154740037F,
    0.0081173908F, 5.20723E-41F, -0.0317316055F, 0.0177887026F, 0.053137213F,
    -0.00363247329F };

  static const real32_T b[32] = { -0.226227179F, -0.00327778864F, 0.138868213F,
    -7.75286753E-5F, -0.0101692425F, -8.27131225E-6F, -0.207234457F,
    0.105866887F, -0.505423963F, -0.000459817908F, -1.16899009E-5F, 0.525726F,
    -0.243714809F, 0.0850291625F, -1.96732557E-7F, -0.211692154F, -0.330376744F,
    -0.0447738469F, -0.126526952F, -9.09779E-5F, -0.101737961F, 0.284867346F,
    -0.383185565F, -0.000128987769F, 0.0200337283F, -0.303724945F, -0.11092408F,
    -0.0491293F, -0.158422619F, -0.260249227F, -0.193179876F, -0.18839471F };

  static const real32_T tmp_0[512] = { 0.082654871F, -0.0543885194F,
    0.0650420338F, -0.0233690944F, -1.3226E-40F, 0.0632705539F, -4.83392E-41F,
    0.165942311F, -0.0357500277F, 0.0388082266F, 3.32612E-41F, 0.0887160674F,
    -0.0351654552F, 0.112167627F, -0.0233361535F, -1.74187E-40F, -9.64121E-41F,
    2.90209E-41F, -3.46751E-41F, 6.42495E-41F, -1.53026E-40F, -6.08626E-41F,
    4.82915E-41F, 4.91716E-41F, -2.73197E-41F, 9.74463E-42F, -1.28998E-40F,
    -8.11001E-41F, -9.27547E-41F, -4.16536E-41F, 4.22309E-41F, 3.93527E-41F,
    -0.048972372F, 0.0434295833F, -0.0437513404F, 0.0147401989F, -1.45284E-40F,
    -0.0369407311F, 1.9927E-40F, -0.109122336F, 0.0229691062F, -0.0223365072F,
    2.98701E-41F, -0.0511619113F, 0.0268101096F, -0.076300852F, 0.0143305622F,
    -1.32936E-40F, -5.29719E-41F, -1.20303E-40F, 1.85088E-40F, 8.8733E-41F,
    -1.88912E-40F, 1.91333E-40F, 5.18452E-41F, -8.82678E-42F, 5.83641E-42F,
    -1.13945E-40F, 1.98893E-40F, -5.62635E-41F, 1.65101E-40F, -9.5605E-41F,
    -1.16854E-40F, -1.39495E-40F, -1.06796E-40F, -3.84825E-41F, -1.16092E-40F,
    1.34724E-40F, 1.85616E-41F, 1.14353E-40F, 2.18504E-41F, -1.28777E-40F,
    1.01869E-40F, -1.57147E-40F, 1.69633E-40F, -1.83146E-40F, 1.58783E-40F,
    -2.03342E-41F, 1.52758E-40F, 1.83038E-40F, -9.30322E-42F, -3.36564E-41F,
    -7.32865E-41F, 2.95436E-41F, 9.78064E-41F, 1.10188E-40F, -1.47005E-40F,
    -7.61816E-41F, 5.19545E-41F, 1.92777E-41F, -5.2197E-41F, -3.98011E-41F,
    -4.08044E-41F, -2.36721E-41F, -2.12773E-41F, 1.59252E-40F, 0.12361832F,
    -0.0597837232F, 0.0924195871F, -0.0286113843F, -2.3724E-42F, 0.0967281461F,
    -1.80393E-40F, 0.176154763F, -0.0414919741F, 0.0574678145F, 1.0049E-40F,
    0.145725816F, -0.039454475F, 0.166389167F, -0.0284695588F, -1.61975E-40F,
    0.074054122F, -0.0789400265F, 0.135623097F, -0.0425290316F, -1.63052E-40F,
    0.0720475689F, 1.29731E-40F, 0.200999513F, -0.0614968613F, 0.0414723456F,
    -4.8611E-41F, 0.0623399056F, -0.0580722913F, 0.251610041F, -0.0425590128F,
    1.71908E-40F, 0.0924705118F, -0.0592197292F, 0.0726308376F, -0.0220903493F,
    1.76564E-42F, 0.0716534853F, -1.99283E-40F, 0.176882431F, -0.0346326679F,
    0.0427838415F, 1.5304E-40F, 0.104090407F, -0.0380300656F, 0.12717101F,
    -0.0224717092F, 1.94116E-40F, 9.87999E-41F, -3.16273E-42F, 7.54781E-41F,
    -8.118E-41F, 1.05306E-40F, -2.18883E-42F, -1.76662E-41F, 6.77948E-41F,
    -8.04443E-41F, -3.31477E-41F, 4.26415E-42F, 1.26878E-40F, -7.01112E-41F,
    1.53708E-41F, -3.905E-41F, -1.35342E-40F, 2.04828E-41F, 2.32924E-41F,
    -2.99906E-41F, 4.68706E-41F, 1.7996E-40F, -1.64218E-41F, 1.23875E-40F,
    -2.16543E-41F, 1.90759E-41F, 4.67683E-41F, -1.15931E-40F, -2.45283E-41F,
    -4.77478E-41F, 7.88118E-41F, 6.54476E-41F, 9.23161E-41F, -0.101616152F,
    0.0744599551F, -0.0880293548F, 0.0255321413F, -3.87627E-41F, -0.0731179F,
    -1.07967E-40F, -0.201002628F, 0.0405438282F, -0.0463124923F, -1.2876E-40F,
    -0.106109522F, 0.0456850827F, -0.147044852F, 0.0246357843F, -3.36045E-41F,
    0.0881117284F, -0.0380266756F, 0.0595843717F, -0.0193764661F, 1.46223E-40F,
    0.0688409F, 1.77072E-40F, 0.160838097F, -0.0284441542F, 0.0421335474F,
    3.49302E-41F, 0.0990779474F, -0.0260463618F, 0.110844262F, -0.0194044858F,
    -1.40989E-40F, -0.02524787F, 0.0325198695F, -0.0257010739F, 0.0117323166F,
    -1.09824E-40F, -0.018202588F, -1.47789E-40F, -0.0633851662F, 0.0182869956F,
    -0.0116412453F, 1.13032E-40F, -0.0252965372F, 0.020078931F, -0.0440396219F,
    0.011351157F, -1.26125E-40F, -5.1565E-41F, -6.39581E-41F, -1.85494E-40F,
    1.23045E-40F, -6.26731E-41F, -1.95344E-40F, 1.98429E-40F, 1.8843E-40F,
    -7.84307E-41F, 1.08291E-40F, 1.16305E-40F, 2.16613E-41F, -1.77271E-40F,
    -1.03555E-40F, -4.68454E-42F, -1.49971E-40F, 0.14545384F, -0.0843539089F,
    0.116998971F, -0.0382064134F, -4.73569E-41F, 0.121227428F, 1.29158E-41F,
    0.250707924F, -0.055736348F, 0.0735568479F, 1.49425E-40F, 0.181915447F,
    -0.0555805713F, 0.201027855F, -0.037754409F, 1.42396E-40F, 0.0396468416F,
    -0.0258979909F, 0.0313744619F, -0.0110285589F, 1.65755E-40F, 0.0308104064F,
    1.79934E-40F, 0.0753354281F, -0.0172133595F, 0.0187482852F, -5.29298E-41F,
    0.0441757292F, -0.0171169303F, 0.0544259325F, -0.0121782459F, -1.62038E-40F,
    -6.81844E-41F, 6.21672E-41F, 4.35341E-41F, -1.58158E-40F, -1.5159E-40F,
    -3.20953E-41F, 8.63648E-41F, -7.90879E-41F, 1.76083E-40F, 1.97681E-41F,
    1.24952E-40F, -1.14297E-40F, -1.10149E-40F, -1.44063E-40F, 8.78754E-41F,
    1.44957E-40F, 0.184504256F, -0.150554135F, 0.181307375F, -0.0630917F,
    1.44046E-40F, 0.149237752F, -1.84009E-40F, 0.353339732F, -0.0933843106F,
    0.0934819505F, -9.45442E-41F, 0.216364816F, -0.0976776481F, 0.313412398F,
    -0.0619957F, 1.60875E-40F, 2.39384E-41F, -5.99307E-41F, -9.01259E-41F,
    -8.26164E-41F, 1.42813E-40F, 1.91323E-40F, 8.17419E-41F, -4.28237E-41F,
    -1.29714E-40F, 6.14988E-41F, -5.21227E-41F, 9.55896E-41F, 7.65964E-41F,
    5.24562E-41F, -3.98025E-41F, -9.04888E-41F, -1.16908E-40F, -1.74728E-41F,
    7.39956E-41F, 6.25007E-41F, -2.98322E-41F, -5.65998E-41F, -5.85561E-41F,
    3.83437E-41F, 6.18323E-41F, -1.25247E-40F, -1.27751E-40F, -1.35681E-40F,
    1.53906E-40F, -3.34518E-41F, -1.33013E-40F, 4.58505E-41F, -0.0159689467F,
    0.0212685019F, 0.0246652681F, 0.00316042709F, -1.50132E-40F, 0.0080458438F,
    -1.98415E-40F, -0.012498986F, 0.00639480725F, -0.00170727703F, -1.84065E-40F,
    0.0215733629F, 0.0141788516F, 0.0862104222F, 0.00251192856F, 8.34123E-41F,
    0.0410487279F, -0.0299165938F, 0.0324587971F, -0.0137761021F, -7.87754E-41F,
    0.0320144854F, 1.31101E-40F, 0.0770676658F, -0.0215726346F, 0.0198061336F,
    -1.21158E-40F, 0.0454831384F, -0.0205329116F, 0.0555307455F, -0.0150722014F,
    -5.3908E-42F, -9.70707E-41F, 1.61065E-41F, 9.84202E-41F, 6.64944E-41F,
    7.16484E-42F, 2.92731E-41F, -5.32143E-41F, -3.06534E-41F, 7.41833E-41F,
    9.16968E-41F, 6.77948E-42F, 3.70868E-41F, -6.12381E-41F, -9.84552E-42F,
    -8.64671E-41F, -1.82197E-41F, -0.00192171766F, 0.00332951639F,
    -0.0018848998F, 0.00118215871F, -1.70193E-40F, -0.0014596855F, 1.68433E-40F,
    -0.00477354042F, 0.00190217502F, -0.00128267962F, 2.1381E-41F,
    -0.00188056228F, 0.00211278792F, -0.0031047035F, 0.00114357402F,
    -1.05417E-40F, 0.0632232577F, -0.0418065861F, 0.0492014624F, -0.0164542105F,
    -6.64664E-41F, 0.04876F, -9.02688E-41F, 0.124100789F, -0.0260948204F,
    0.0295536183F, 9.00937E-41F, 0.0705294311F, -0.0266780909F, 0.0836837366F,
    -0.0166573469F, -6.14974E-41F, 0.00980324F, -0.00887926575F, 0.00785111263F,
    -0.00432782108F, 1.68257E-40F, 0.00768652698F, -1.60592E-40F, 0.0191143118F,
    -0.00688968878F, 0.00490329973F, -1.32374E-40F, 0.0109644225F,
    -0.00640725065F, 0.013607882F, -0.00498066703F, 9.14067E-41F, 9.6087E-42F,
    -1.35814E-40F, 3.64898E-41F, -7.94816E-42F, 7.48938E-41F, -1.41411E-40F,
    1.5318E-40F, -4.09025E-41F, 3.03451E-41F, 1.02841E-40F, -1.21811E-40F,
    -6.09565E-43F, -1.83071E-40F, 1.96236E-40F, 1.52334E-40F, 8.55773E-41F,
    0.119049095F, -0.0682230741F, 0.0987958536F, -0.0316303149F, 1.7515E-40F,
    0.0956006423F, -1.36599E-41F, 0.185429096F, -0.046058055F, 0.0580231F,
    -1.87675E-40F, 0.13996768F, -0.0444667861F, 0.174885616F, -0.0313486047F,
    -1.88026E-40F, 0.0404827073F, -0.0261442196F, 0.0318007022F, -0.0102641173F,
    3.27385E-41F, 0.0311311577F, -6.23326E-41F, 0.0783747584F, -0.015972428F,
    0.018505238F, 9.66181E-41F, 0.0454130732F, -0.0170439202F, 0.0563808754F,
    -0.0110222492F, -1.67581E-41F, 0.114501834F, -0.0441081561F, 0.0815866143F,
    -0.0286698919F, 5.75892E-41F, 0.0990220383F, -1.73177E-40F, 0.226365656F,
    -0.0400137603F, 0.0553370416F, 8.67109E-41F, 0.126263931F, -0.0269524828F,
    0.178606838F, -0.0291024614F, 1.30272E-40F, 0.0721043646F, -0.0290171895F,
    0.053057652F, -0.0163705703F, -1.23639E-40F, 0.0636283085F, 1.01678E-41F,
    0.103939183F, -0.0236472096F, 0.036243584F, -1.19454E-40F, 0.0927088484F,
    -0.0207338501F, 0.114444301F, -0.0164987762F, 8.17251E-41F };

  static const real32_T c[16] = { -0.310140342F, 0.585733175F, 0.0440797396F,
    0.288824558F, -3.03808974E-7F, -0.293033153F, -0.0418545492F, -0.32647717F,
    0.419034749F, -0.162591353F, -1.67703518E-10F, -0.475503564F, 0.390267789F,
    0.0585332252F, 0.285449922F, -2.58817382E-12F };

  static const real32_T d_0[16] = { 0.403147757F, -0.334593743F, 0.322025895F,
    -0.12892589F, -5.1167E-41F, 0.314412266F, -4.2968E-41F, 0.762746334F,
    -0.197543487F, 0.19102408F, 5.11306E-41F, 0.450201303F, -0.212614983F,
    0.557655931F, -0.125448629F, 9.71674E-41F };

  if (!obj->IsNetworkInitialized) {
    obj->IsNetworkInitialized = true;
  }

  matrixMultiply11141464106932832455(32, 8, 1, 128, 128, 128, &(&tmp[0])[0],
    &inputsT_0_f1[0], &outT_f3_0_f1[0]);
  for (dim1 = 0; dim1 < 32; dim1++) {
    outT_f3_0_f1[dim1] = fmaxf(0.0F, outT_f3_0_f1[dim1] + b[dim1]);
  }

  matrixMultiply11141464106932832455(16, 32, 1, 128, 128, 128, &(&tmp_0[0])[0],
    &outT_f3_0_f1[0], &outT_f5_0_f1[0]);
  d = 0.0F;
  for (dim1 = 0; dim1 < 16; dim1++) {
    outT_f5_0_f1_0 = fmaxf(0.0F, outT_f5_0_f1[dim1] + c[dim1]);
    outT_f5_0_f1[dim1] = outT_f5_0_f1_0;
    d += d_0[dim1] * outT_f5_0_f1_0;
  }

  outputs_0 = d - 0.186301082F;
  return outputs_0;
}

/* Function for MATLAB Function: '<S2>/MLFB' */
static real32_T DeepLearningNetwork_predict(c_coder_internal_ctarget_DeepLe *obj,
  const real_T varargin_1[8])
{
  int32_T i;
  real32_T varargin_1_0[8];
  real32_T varargout_1;
  for (i = 0; i < 8; i++) {
    varargin_1_0[i] = (real32_T)varargin_1[i];
  }

  varargout_1 = DeepLearningNetwork_callPredict(obj, varargin_1_0);
  return varargout_1;
}

/* Model step function */
void Subsystem_step(void)
{
  real_T tmp[8];
  real_T rtb_Delay;
  real_T rtb_Delay1;
  real_T rtb_Delay1_p;
  real_T rtb_Delay_k;

  /* Delay: '<S3>/Delay' */
  rtb_Delay = rtDW.Delay_DSTATE;

  /* Delay: '<S3>/Delay1' */
  rtb_Delay1 = rtDW.Delay1_DSTATE;

  /* Delay: '<S4>/Delay' */
  rtb_Delay_k = rtDW.Delay_DSTATE_d;

  /* Delay: '<S4>/Delay1' */
  rtb_Delay1_p = rtDW.Delay1_DSTATE_o;

  /* MATLAB Function: '<S2>/MLFB' incorporates:
   *  Delay: '<S3>/Delay'
   *  Delay: '<S3>/Delay1'
   *  Delay: '<S3>/Delay2'
   *  Delay: '<S4>/Delay'
   *  Delay: '<S4>/Delay1'
   *  Delay: '<S4>/Delay2'
   *  Inport: '<Root>/In1'
   *  Inport: '<Root>/In2'
   */
  if (!rtDW.network_not_empty) {
    rtDW.network.IsNetworkInitialized = false;
    rtDW.network.matlabCodegenIsDeleted = false;
    rtDW.network_not_empty = true;
  }

  tmp[0] = rtU.In1;
  tmp[1] = rtDW.Delay_DSTATE;
  tmp[2] = rtDW.Delay1_DSTATE;
  tmp[3] = rtDW.Delay2_DSTATE;
  tmp[4] = rtU.In2;
  tmp[5] = rtDW.Delay_DSTATE_d;
  tmp[6] = rtDW.Delay1_DSTATE_o;
  tmp[7] = rtDW.Delay2_DSTATE_e;

  /* Outport: '<Root>/output' incorporates:
   *  MATLAB Function: '<S2>/MLFB'
   */
  rtY.output = DeepLearningNetwork_predict(&rtDW.network, tmp);

  /* Update for Delay: '<S3>/Delay' incorporates:
   *  Inport: '<Root>/In1'
   */
  rtDW.Delay_DSTATE = rtU.In1;

  /* Update for Delay: '<S3>/Delay1' */
  rtDW.Delay1_DSTATE = rtb_Delay;

  /* Update for Delay: '<S3>/Delay2' */
  rtDW.Delay2_DSTATE = rtb_Delay1;

  /* Update for Delay: '<S4>/Delay' incorporates:
   *  Inport: '<Root>/In2'
   */
  rtDW.Delay_DSTATE_d = rtU.In2;

  /* Update for Delay: '<S4>/Delay1' */
  rtDW.Delay1_DSTATE_o = rtb_Delay_k;

  /* Update for Delay: '<S4>/Delay2' */
  rtDW.Delay2_DSTATE_e = rtb_Delay1_p;
}

/* Model initialize function */
void Subsystem_initialize(void)
{
  /* SystemInitialize for MATLAB Function: '<S2>/MLFB' */
  rtDW.network.matlabCodegenIsDeleted = true;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
