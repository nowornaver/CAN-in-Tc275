#include<iostream>
#include <string>
#include <vector>
#include "opencv2/opencv.hpp"
#include <opencv2/dnn.hpp>  // DNN 모듈을 포함합니다.
#include <opencv2/video/tracking.hpp>  // KalmanFilter를 위한 헤더 파일 추가

using namespace std;
using namespace cv;

class RoadLaneDetector
{
private:
KalmanFilter kf; 
    double previous_heading_error = 0.0; // 이전 헤딩 에러
double wheelbase = 0.75;


public:
int lastSize = 0 ;
int RastSize = 0 ;
KalmanFilter kalmanFilter_a, kalmanFilter_b, kalmanFilter_c;
Mat state_a, state_b, state_c;  // 상태값 저장용 행렬
Mat measurement_a, measurement_b, measurement_c;  // 측정값 저장용 행렬
float initial_measure_a, initial_measure_b, initial_measure_c;  // 초기 측정값
void initKalmanFilters();
void applyKalmanFilter();
double kalmanFilter1D(double measurement, double& x_est, double& P_est, double Q, double R);
vector<double> solveQuadratic(double a, double b, double c);
int standard = 0 ;
bool laneDetect = true;
double es =28 ;
double calculateStandardDeviation(const int * differences);
int differences[16] = {0};
int non_zero_count =0;
int non_zero_count1 = 0 ;
int prev_rx[16] = {0}; 
int prev_y_vals_right[16] = {0};
int prev_lx[16] = {0}; 
int prev_y_vals_left[16] = {0};
// 이전 픽셀 값들을 저장하고 있다가 두 차선 모두 안보이면 이전 차선으로 대체함 .
double left_coeffs_array[3] = {0}; // 왼쪽 차선 계수
double right_coeffs_array[3] = {0}; // 오른쪽 차선 계수
double steering_angle = 0 ;
 double coeffs_vector[3] = {0};

    int currentSize = 0; 
    int currentSize1 = 0 ;
    vector<int> ry_cluster_indicies; 
// int y = 720;
    bool stopDetection;
    int lx[16] = {0} ; 
    int rx[16] = {0} ;
    int count = 0 ; 
Mat transformed_frame;
    // x, y 값을 저장할 벡터 생성
    vector<int> x_vals;
    vector<int> y_vals;
    int y_vals_left[16] = {0};
    int y_vals_right[16] = {0};
    int Radius_Of_Curvature ;
vector<int> histogram;
Mat transform_matrix;
double ROC(const int *x_vals , const int*y_vals);

void L_blindLane(const int*prev_lx, const int*prev_y_vals_left );
void R_blindLane(const int*prev_rx, const int*prev_y_vals_right );

double calculateRadius(double a, double b, double x);
Mat Reverse_transformed(Mat result , Mat transfrom_matrix);
Mat bird_eye_view (Mat img_frame);
vector <int> Start_lane_detection (Mat mask);
Mat sliding_window(Mat img_frame,Mat mask,int left_base,int right_base);
Mat blind_sliding_window(Mat img_frame ,Mat msk );

Mat img_filter(Mat transformed_frame);
void polyfit(const int* x_vals, const int* y_vals, int degree);
// double calculateCurvature(double a, double b, double x);
void right_polyfit(const int* x_vals, const int* y_vals, int degree);
void left_polyfit(const int* x_vals, const int* y_vals, int degree);


};