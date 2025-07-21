#include "opencv2/opencv.hpp"
#include <opencv2/highgui/highgui.hpp>
#include "RoadLaneDetector.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <numeric>
//전역변수로 두개를 호출하면 문제가 생긴다고 gpt 선생님께서 말씀해주셨다. 전역변수를 두개 호출하게 되면 문제가 발생할 수 있데
//값을 찍어보니까 전역변수 두개를 호출해서 문제가 생긴것 같다. 지역변수로 바꿔주는 작업을 해주어야할거같다. 
//coeffs_vector라는 변수가 전역변수로 선언이 되어있어서 왼쪽 오른쪽 둘다 하게될 경우에 충돌이 일어남.
//문제 알아냄 currentSize1 은 12까지 커짐 왜인지는 모르겠으나 원래는 11까지만 커져야함; 
//오류 2 슬라이딩 윈도우 네모는 제일 아래가자꾸 사라졋다가 위로 올라가고 그러는데 그러는 이유도 알아내야함;
// L = 75cm

void RoadLaneDetector::left_polyfit(const int* x_vals, const int* y_vals, int degree) {
     


    int n = 16; //n 행의 수 

    // cout <<"n = " <<n <<endl; 
    Mat X(n, degree + 1, CV_64F); //degree+1 열
    Mat Y(n, 1, CV_64F);

    for (int i = 0; i < n; i++) {


        if (x_vals[i]!= 0) {
        Y.at<double>(i, 0) = static_cast<double>(y_vals[i]);
        for (int j = 0; j <= degree; j++) {
            X.at<double>(i, j) = pow(x_vals[i], j); //x_vals[i]^j
        }

        }
    }

    // (X^T * X) * a = X^T * Y 를 풀어서 회귀계수 a를 구함
    Mat Xt = X.t(); //행렬 x의 전치행렬 
    Mat XtX = Xt * X;
    Mat XtY = Xt * Y;
    Mat coeffs = XtX.inv() * XtY;
    for (int i = 0; i < coeffs.rows; i++) {
            // cout <<"coeffs.at =" <<coeffs.at<double> (i,0) <<endl; 

       left_coeffs_array[i] = (coeffs.at<double>(i, 0));
    
    }

    
    
    }
    void RoadLaneDetector::right_polyfit(const int* x_vals, const int* y_vals, int degree) {
     


    int n = 16; //n 행의 수 

    // cout <<"n = " <<n <<endl; 
    Mat X(n, degree + 1, CV_64F); //degree+1 열
    Mat Y(n, 1, CV_64F);

    for (int i = 0; i < n; i++) {
            // cout <<"x_vals[i] = " <<x_vals[i] <<endl; 

        if (x_vals[i]!= 0) {
        Y.at<double>(i, 0) = static_cast<double>(y_vals[i]);
        for (int j = 0; j <= degree; j++) {
            X.at<double>(i, j) = pow(x_vals[i], j); //x_vals[i]^j
        }

        }
    }

    // (X^T * X) * a = X^T * Y 를 풀어서 회귀계수 a를 구함
    Mat Xt = X.t(); //행렬 x의 전치행렬 
    Mat XtX = Xt * X;
    Mat XtY = Xt * Y;
    Mat coeffs = XtX.inv() * XtY;
    for (int i = 0; i < coeffs.rows; i++) {
            // cout <<"coeffs.at =" <<coeffs.at<double> (i,0) <<endl; 

        right_coeffs_array[i] = (coeffs.at<double>(i, 0));
    
    }

    
    
    }
void RoadLaneDetector::L_blindLane(const int*prev_lx, const int*prev_y_vals_left ) { //이전 차선좌표로 다항회귀 한 값을 받아서 x=ay^2+by+c 방정식을 풀어서 x값을 예측하기. 이전 x값과 y값을 받아서 

left_polyfit(prev_y_vals_left ,prev_lx,2);


}
void RoadLaneDetector::R_blindLane(const int*prev_rx, const int*prev_y_vals_right ) { //이전 차선좌표로 다항회귀 한 값을 받아서 x=ay^2+by+c 방정식을 풀어서 x값을 예측하기. 이전 x값과 y값을 받아서 

right_polyfit(prev_y_vals_right ,prev_rx,2);



}



double RoadLaneDetector::calculateStandardDeviation(const int * differences) {
    size_t n = 12;
     double mean = 0.0;
        for (size_t i = 0; i < n; ++i) {
            mean += differences[i];
        }
        mean /= n;

        // 분산 계산
        double variance = 0.0;
        for (size_t i = 0; i < n; ++i) {
            variance += std::pow(differences[i] - mean, 2);
        }
        variance /= n;
         es = sqrt(variance);
        // 표준편차 계산
        return sqrt(variance);
}



void RoadLaneDetector::polyfit(const int* x_vals, const int* y_vals, int degree) {
     


    int n = 16; //n 행의 수 

    // cout <<"n = " <<n <<endl; 
    Mat X(n, degree + 1, CV_64F); //degree+1 열
    Mat Y(n, 1, CV_64F);

    for (int i = 0; i < n; i++) {
            // cout <<"x_vals[i] = " <<x_vals[i] <<endl; 

        if (x_vals[i]!= 0) {
        Y.at<double>(i, 0) = static_cast<double>(y_vals[i]);
        for (int j = 0; j <= degree; j++) {
            X.at<double>(i, j) = pow(x_vals[i], j); //x_vals[i]^j
        }

        }
    }

    // (X^T * X) * a = X^T * Y 를 풀어서 회귀계수 a를 구함
    Mat Xt = X.t(); //행렬 x의 전치행렬 
    Mat XtX = Xt * X;
    Mat XtY = Xt * Y;
    Mat coeffs = XtX.inv() * XtY;
    for (int i = 0; i < coeffs.rows; i++) {
            // cout <<"coeffs.at =" <<coeffs.at<double> (i,0) <<endl; 

        coeffs_vector[i]= (coeffs.at<double>(i, 0));
    
    }

    
    
    }
    

Mat RoadLaneDetector::Reverse_transformed(Mat result , Mat transfrom_matrix) {
Mat a ; 
cv::warpPerspective(result, a, transfrom_matrix, cv::Size(640, 480));



    return a;
}


Mat RoadLaneDetector::bird_eye_view(Mat img_frame) {
    int width = 1280;
    int height = 1280;
    Point2f src_vertices[4];

    src_vertices[0] = Point(0, height * 0.65);  // Bottom-left
    src_vertices[1] = Point(width, height * 0.65);  // Bottom-right
    src_vertices[2] = Point(width * 0.85, height * 0.50);  // Top-right
    src_vertices[3] = Point(width * 0.06, height * 0.50);  // Top-left
	// cv::circle(img_frame,src_vertices[0],5,(0,0,255),-1);
	// cv::circle(img_frame,src_vertices[1],5,(0,0,255),-1);
	// cv::circle(img_frame,src_vertices[2],5,(0,0,255),-1);
	// cv::circle(img_frame,src_vertices[3],5,(0,0,255),-1);
    Point2f dst_vertices[4];
    dst_vertices[0] = Point(0, height);  // Bottom-left
    dst_vertices[1] = Point(width, height);  // Bottom-right
    dst_vertices[2] = Point(width, 0);  // Top-right
    dst_vertices[3] = Point(0, 0);  // Top-left
    // cv::circle(img_frame,dst_vertices[0],5,(0,0,255),-1);
	// cv::circle(img_frame,dst_vertices[1],5,(0,0,255),-1);
	// cv::circle(img_frame,dst_vertices[2],5,(0,0,255),-1);
	// cv::circle(img_frame,dst_vertices[3],5,(0,0,255),-1);
    Mat matrix = cv::getPerspectiveTransform(src_vertices, dst_vertices);
    transform_matrix = cv::getPerspectiveTransform(dst_vertices, src_vertices);
    Mat transformed_frame;
    cv::warpPerspective(img_frame, transformed_frame, matrix, cv::Size(1280, 1280));
    Mat mask = Mat::zeros(img_frame.size(), CV_8UC1);

    Point poly[1][4];

    poly[0][0] = dst_vertices[0];
    poly[0][1] = dst_vertices[1];
    poly[0][2] = dst_vertices[2];
    poly[0][3] = dst_vertices[3];
    const Point* pts[1] = { poly[0] };
    int npts = 4;

    // 다각형 영역을 1로 채우기
    // cv::fillPoly(mask, pts, &npts, 1, Scalar(255));



    return transformed_frame;
}

vector<int> RoadLaneDetector::Start_lane_detection(Mat mask) {

    vector<int> lane(2, 0); // 크기가 2인 벡터로 초기화 (왼쪽과 오른쪽 차선 위치)
 histogram.resize(mask.cols, 0); // 멤버 변수 histogram 초기화
         for (int i = 0; i < mask.cols; i++) {
            histogram[i] = countNonZero(mask.col(i));
        }

        // 히스토그램 출력
  
		int midpoint = histogram.size() / 2; //midpoint = 320

// // 4. 왼쪽 차선의 시작 위치를 찾습니다.
int left_base = 0;
for (int i = 0; i < midpoint; i++) {
    if (histogram[i] > histogram[left_base]) {
        left_base = i;
        lane[0] = left_base;
    }
}

// // 5. 오른쪽 차선의 시작 위치를 찾습니다.
int right_base = midpoint;
for (int i = midpoint; i < histogram.size(); i++) {
    if (histogram[i] > histogram[right_base]) {
        right_base = i;
        lane[1]= right_base;
    }
}


    return lane;
}

Mat RoadLaneDetector::sliding_window(Mat img_frame, Mat mask, int left_base, int right_base) {
    // cout <<"left_base" <<left_base<<endl ; 
    Mat msk = mask.clone();
    int y = 1280;
 
// cout <<"count " <<count << endl; 

    while (y > 0 ) { //6번 실행됌 while 문  //720 660 600 540 480 420 360 300 240 180 120 60 0
  //y = 720 600 480 
        // 왼쪽 차선 범위 설정
        cout <<"y =" <<y <<endl; 
        // cout <<"currentSize = " <<currentSize <<endl;
        // cout <<"currentSize1 = " <<currentSize1 <<endl; 
        int left_start = max(0, left_base - 80);  // 윈도우 너비 확장 
        int left_end = min(mask.cols, left_base + 80);  // 윈도우 너비 확장
         cout <<"left_start =" <<msk.cols <<endl;

 cout <<"left_end = " <<msk.rows <<endl;
        if (left_start >= left_end) break; // 유효한 범위가 없으면 종료
        Mat img_left = mask.rowRange(y - 80, y).colRange(left_start, left_end);  // 윈도우 높이 확장 (120 픽셀로 증가)
            
                // cout <<"Y1 =" <<y <<endl; 
        // vector<vector<Point>> contours_left;
            // cout <<"y1 = " <<y <<endl ; //720
        non_zero_count = countNonZero(img_left);
        //문제가 표준편차로 노이즈 제거한다 OK 근데 이전값을 계전 계속 받아서 결국에는 안돼
 
        if (non_zero_count> 100  ) { //이 if문에 걸리면서 y값이 내려간 상태에서  이 if문을 만족 할 경우에만 슬라이딩 윈도우를 진행해볼까

            // cout <<"CurrentSIze = " <<currentSize <<endl;
            // cout <<"y = " <<y <<endl; 
            Moments M = moments(img_left,true);  //슬라이딩 윈도우 첫번째 y1 = 660 , y2 = 540 y3= 420 y3 = 300 y4 = 180 y5 = 60
  
            // cout <<"M.m00 = " <<M.m00 <<endl; 
            if (M.m00 != 0) {  //이유를 알아버림 if문에 걸려서 if문때문에 조건을 만족하지 않은거지 그렇게 되면서 이제 y값은 계쏙 내려가잖아 그러니까 그런거네 ;;
                
                int cx = static_cast<int>(M.m10 / M.m00);
         
            
                if (currentSize <16) {  //currentSize 여기서 012345 까지 돔
                // cout <<"left_start+cx" <<left_start+cx <<endl;
                // cout <<"currentSize = " <<currentSize <<endl; 
                lx[currentSize]=(left_start + cx); //lx 차선 픽셀 중심의 좌표
                // cout <<"currentSize = " <<currentSize <<endl; 
                // cout <<"Y = " <<y <<endl; 
                y_vals_left[currentSize] = y-80; // y 값 추가 (중앙으로)

                // x_vals.push_back(left_start+cx)
                left_base = lx[currentSize];

                            currentSize++;


                }

                
            // if (currentSize ==12) {
            //     currentSize = 0 ;
            // }

            }

        cv::rectangle(msk, Point(left_base - 80, y), Point(left_base + 80, y - 80), Scalar(255, 255, 255), 1);

        }
//이전값을 받는것이 어렵사옵니다.
        else if (non_zero_count <=100  ) {  //차선이 끊겨있을 경우. 
      L_blindLane(prev_lx , prev_y_vals_left);
        

        
if (currentSize <16 ) {
        // y_vals_left[currentSize] = y-60;           
        for (int i = 0 ; i <3 ; i ++) {
        //     //  left_coeffs_array[i]=coeffs_vector[i];
        // cout <<"left_coeffs_array = " <<left_coeffs_array[i] <<endl;  //x= ay^2+by+c
        }
    double a =left_coeffs_array[2]; // a 계수
    double b =left_coeffs_array[1]; // b 계수
    double c = left_coeffs_array[0]; // c 계수

    // y 값이 660일 때 x 값을 계산하는 코드
        y_vals_left[currentSize] = y-80;
        // cout <<"y = " <<y <<endl; 
        // cout <<"y_vals_left[currentSize] = "<< y_vals_left[currentSize] <<endl;
        double x = a * y_vals_left[currentSize] * y_vals_left[currentSize] + b * y_vals_left[currentSize] + c; // x = ay^2 + by + c 식에 따라 계산
if (x <640 && x>0) {
        lx[currentSize] = x;
         left_base = x;
        currentSize++;
        // circle(transformed_frame , Point(0 ,y) ,5 , (0,0,255),-1);
        // circle(transformed_frame , Point(0 ,y_vals_left[currentSize]) ,5 , (0,0,255),-1);
        //         circle(transformed_frame , Point(0 ,720) ,5 , (0,255,255),5);
        // circle(transformed_frame , Point(0 ,660) ,5 , (0,255,255),5);


        cv::rectangle(msk, Point(left_base - 80, y), Point(left_base + 80, y-80), cv::Scalar(255, 255, 255), 10);
}
        }
    
    }   // cout <<"CurrentSIze = "<< currentSize <<endl; 


//데이터 보정은 나중에 하고 일단은 그냥 곡률로 넘어가야겠다.. ㅅ1ㅂ

        // // 오른쪽 차선 범위 설정
        int right_start = max(0, right_base - 80);  // 윈도우 너비 확장
        int right_end = min(mask.cols, right_base + 80);  // 윈도우 너비 확장
        if (right_start >= right_end) break; // 유효한 범위가 없으면 종료
        cout <<"right_start = " <<right_start <<endl;
        cout <<"right_end = " <<right_end <<endl; 
        cout <<"non_zero_count1 = " <<non_zero_count1 <<endl; 
        Mat img_right = mask.rowRange(y - 80, y).colRange(right_start, right_end);  // 윈도우 높이 확장 (120 픽셀로 증가)
        non_zero_count1 = countNonZero(img_right);
        // cout <<"non_zero_count1 = " <<non_zero_count1 <<endl; 
        // 오른쪽 차선의 중심 계산
        // if (non_zero_count1 == 0 ) {
        //     y_vals_right[currentSize1] = y-60;
        //     rx[currentSize1];

        // }
// cout <<"y = " <<y <<endl; 
// cout <<"currentSize1 =" <<currentSize1 <<endl;
        // cout <<"non_zero_count1 = " <<non_zero_count1 <<endl; 
    
        if (non_zero_count1 > 100) { // 차선을 다항회귀 한 다음에 
            Moments M = moments(img_right , true);
            // cout <<"M.m00 = " <<M.m00<<endl; 
            if (M.m00 != 0) {
                int cx = static_cast<int>(M.m10 / M.m00);
                if (currentSize1 <16 ) {
                
                rx[currentSize1]=(right_start + cx);
                // cout <<"right_start + cx" << right_start + cx <<endl ; 
                right_base = rx[currentSize1];
                y_vals_right[currentSize1]=(y - 80); // y 값 추가 (중앙으로)
                // cout <<"rx[currentSize] = " << rx[currentSize] <<endl ; 
                // cout <<"y_vals_right[currentSize] = " << y_vals_right[currentSize] <<endl ; 
                // circle(transformed_frame, Point(rx[currentSize1], y_vals_right[currentSize1]) ,5 , (0,0,255),-1);  //720 이랑의 교점 y= 720 이랑의 교점

                currentSize1++;

            }
        }               
                                // cout <<"currentSize =" <<currentSize <<endl; 

                        // cout <<"currentSize1 =" <<currentSize1 <<endl; 
                       //non_zero_count1 오른쪽 non_zero_count 가 왼쪽 es 가 70보다 작은 경우에는 차선이 아님
        cv::rectangle(msk, Point(right_base - 80, y), Point(right_base + 80, y - 80), Scalar(255, 255, 255), 1);

        }


    
        else if (non_zero_count1<=100  ) { //es 가 80보다 작으면 차선이 아님.
            // if (currentSize1 >=10)
          R_blindLane(prev_rx , prev_y_vals_right);
    
        //   cout <<"currentSize1 = " <<currentSize1 <<endl; 
 
          
if (currentSize1 <16) {
    // cout <<"currentSize1=" <<currentSize1 <<endl; 
        // y_vals_left[currentSize] = y-60;           
        for (int i = 0 ; i <3 ; i ++) {
            //  right_coeffs_array[i]=coeffs_vector[i];
        // cout <<"right_coeffs_array = " <<right_coeffs_array[i] <<endl;  //x= ay^2+by+c
        // cout <<"left_coeffs_array = " <<left_coeffs_array[i] <<endl;  //x= ay^2+by+c

        }
    double a1 =right_coeffs_array[2]; // a 계수
    double b1 =right_coeffs_array[1]; // b 계수
    double c1 = right_coeffs_array[0]; // c 계수

    // y 값이 660일 때 x 값을 계산하는 코드
        y_vals_right[currentSize1] = y-80;
        
        double x1 = a1 * y_vals_right[currentSize1] * y_vals_right[currentSize1] + b1 * y_vals_right[currentSize1] + c1; // x = ay^2 + by + c 식에 따라 계산
        if (x1 >640 && x1>0) {
        rx[currentSize1] = x1;
         right_base = x1;
        currentSize1++;
        cv::rectangle(msk, Point(right_base - 80, y), Point(right_base + 80, y-80), cv::Scalar(255, 255, 255), 10);
        }
        }


        }
                // differences[currentSize] = lx[currentSize]-rx[currentSize1];

        // if (non_zero_count1 != 0  && non_zero_count ==0 ) { //오른쪽 차선은 보이고 왼쪽 차선은 안보이는 경우.
        //     if (currentSize1<12) {

        //     rx[currentSize1] =lx[currentSize1]+640;
        //     y_vals_right[currentSize1] = y-60;
        //     // right_base = rx[currentSize1];

        //     currentSize1++;

        //     }
        // }
        if (es >27) {

            laneDetect=true;
        }

        else {
            laneDetect = false;
        }

            



        // 현재 윈도우 표시
        // cv::rectangle(msk, Point(right_base - 80, y), Point(right_base + 80, y - 60), Scalar(255, 255, 255), 2);

        // 다음 윈도우로 이동
        // cout <<"Y"<<y <<endl;
        // cout <<"CurrentSize" <<currentSize <<endl;



        y -= 80;  // 윈도우가 큰 만큼 더 많이 이동

        //왜 lx[0] 이 0이 나오는지?

    


    }
    

    return msk;
}

Mat RoadLaneDetector::blind_sliding_window(Mat img_frame ,Mat msk ) {
// L_blindLane(prev_lx,prev_y_vals_left);
// R_blindLane(prev_rx, prev_y_vals_right);
 //이전 값이 계속 똑같아. 현재 값에다가 넣고 
cout <<"함수 실행 완료" <<endl; 
int y = 720 ; 
while (y>0) {

if (lastSize <12 ) {
        // y_vals_left[currentSize] = y-60;           
        for (int i = 0 ; i <3 ; i ++) {
            //  left_coeffs_array[i]=coeffs_vector[i];
        // cout <<"left_coeffs_array = " <<left_coeffs_array[i] <<endl;  //x= ay^2+by+c
        }
    double a =left_coeffs_array[2]; // a 계수
    double b =left_coeffs_array[1]; // b 계수
    double c = left_coeffs_array[0]; // c 계수

    // y 값이 660일 때 x 값을 계산하는 코드
        // cout <<"y = " <<y <<endl; 
        // cout <<"y_vals_left[currentSize] = "<< y_vals_left[currentSize] <<endl;
        double x = a * y * y + b * y + c; // x = ay^2 + by + c 식에 따라 계산
if (x <640 && x>0) {
        lx[lastSize] = x;
        y_vals_left[lastSize] = y;
        prev_lx[lastSize] =x;
        prev_y_vals_left[lastSize] =y;
        lastSize++;
        // circle(transformed_frame , Point(0 ,y) ,5 , (0,0,255),-1);
        // circle(transformed_frame , Point(0 ,y_vals_left[currentSize]) ,5 , (0,0,255),-1);
        //         circle(transformed_frame , Point(0 ,720) ,5 , (0,255,255),5);
        // circle(transformed_frame , Point(0 ,660) ,5 , (0,255,255),5);


        cv::rectangle(msk, Point(x- 80, y), Point(x + 80, y-60), cv::Scalar(255, 255, 255), 10);
}
        }

if (RastSize <12 ) {
        // y_vals_left[currentSize] = y-60;           
        for (int i = 0 ; i <3 ; i ++) {
        //     //  left_coeffs_array[i]=coeffs_vector[i];
        // cout <<"left_coeffs_array = " <<left_coeffs_array[i] <<endl;  //x= ay^2+by+c
        }
        // a1 b1 c1 이 똑같아 값이 똑같으니깐 
    double a1 =right_coeffs_array[2]; // a 계수
    double b1 =right_coeffs_array[1]; // b 계수
    double c1 = right_coeffs_array[0]; // c 계수
    // cout <<"a1 = " <<a1 <<endl;  
    //     cout <<"b1 = " <<b1 <<endl;  
    // cout <<"c1 = " <<c1 <<endl;  

    // y 값이 660일 때 x 값을 계산하는 코드
        // cout <<"y = " <<y <<endl; 
        // cout <<"y_vals_left[currentSize] = "<< y_vals_left[currentSize] <<endl;
        double x1 = a1 * y * y + b1 * y + c1; // x = ay^2 + by + c 식에 따라 계산
if (x1 >640 && x1>0) {
            // cout <<"X1 = " <<x1 <<endl; 

        rx[RastSize] = x1;
        y_vals_right[lastSize] = y;
        prev_rx[lastSize] =x1;
        prev_y_vals_right[lastSize] =y;
        RastSize++;
        // circle(transformed_frame , Point(0 ,y) ,5 , (0,0,255),-1);
        // circle(transformed_frame , Point(0 ,y_vals_left[currentSize]) ,5 , (0,0,255),-1);
        //         circle(transformed_frame , Point(0 ,720) ,5 , (0,255,255),5);
        // circle(transformed_frame , Point(0 ,660) ,5 , (0,255,255),5);

        cv::rectangle(msk, Point(x1- 80, y), Point(x1 + 80, y-60), cv::Scalar(255, 255, 255), 10);
}
        }





y-=60;
}

return msk;
}
double RoadLaneDetector::ROC(const int *x_vals , const int*y_vals) {
    //R = h/2 + w^2/8H
    double steering_angle = 0;
    const double meters_per_pixel_x = 0.00001; // 가로 방향의 픽셀당 미터
    const double meters_per_pixel_y = 0.00001; // 세로 방향의 픽셀당 미터

    // W 계산
    double W = sqrt(pow((meters_per_pixel_x * (x_vals[0] - x_vals[15])), 2) + pow(1280 * meters_per_pixel_y, 2));
    if (W == 0) {
        W = std::numeric_limits<double>::epsilon(); // W가 0이 되는 경우를 방지
    }

    // 중점 M 계산
    Point M = Point(meters_per_pixel_x * (x_vals[0] + x_vals[15]) / 2, 640 * meters_per_pixel_y); // A B 의 중점

    if (x_vals[0] - x_vals[15] != 0) {
        // 기울기 m 계산
        double m = 1280.0 / (x_vals[0] - x_vals[11]);
        double m_inv = 0;

        if (m != 0) {
            m_inv = -1.0 / m; // 기울기 m의 역수
        }

        double min_difference = std::numeric_limits<double>::max();
        Point C = Point(x_vals[0], y_vals[0]); // 중점 C 초기화

        // Arc 위의 점들 중에서 기울기 -m_inv와 가장 가까운 점을 찾음
        for (int i = 0; i < 16; i++) {
            if (x_vals[i] != M.x) { // x값이 M.x와 같지 않은 경우
                double denominator = (meters_per_pixel_x * x_vals[i] - M.x);
                if (denominator == 0) {
                    denominator = std::numeric_limits<double>::epsilon(); // 0으로 나누기 방지
                }

                double m_candidate = static_cast<double>((meters_per_pixel_y * y_vals[i]) - M.y) / denominator;
                double difference = std::abs(m_candidate - m_inv);

                if (difference < min_difference) {
                    min_difference = difference;
                    C = Point(x_vals[i], y_vals[i]);
                }
            }
        }

        // H 값 계산: 중점 M과 점 C 사이의 거리
        double H = sqrt(pow((C.x * meters_per_pixel_x) - M.x, 2) + pow((meters_per_pixel_y * C.y) - M.y, 2));
        if (H == 0) {
            H = std::numeric_limits<double>::epsilon(); // H가 0이 되는 경우를 방지
        }

        // 곡률 R 계산
        double R = (H / 2.0) + (pow(W, 2) / (8.0 * H));
        if (R == 0) {
            R = std::numeric_limits<double>::epsilon(); // R이 0이 되는 경우를 방지
        }

        // 조향 각도 계산
        double wheelbase = 2.5; // 차량의 축간 거리 예시값
        steering_angle = tan(wheelbase / R);
    } else {
        steering_angle = 0; // x_vals[0]과 x_vals[15]가 같을 때 조향 각도 초기화
    }

    return steering_angle;
}

// double RoadLaneDetector::ROC(const int* x_vals, const int* y_vals) {
//     // 픽셀당 미터 비율 정의
//     double steering_angle = 0;
//     const double meters_per_pixel_x = 0.0005; // 예: 1픽셀 당 0.05미터
//     const double meters_per_pixel_y = 0.0005; // 예: 1픽셀 당 0.05미터

//     // W 계산: 두 점 사이의 거리 (픽셀 단위)
//     double W_pixels = sqrt(pow(x_vals[0] - x_vals[11], 2) + pow(720, 2));

//     // H 계산: 곡률 중심의 y 좌표 (픽셀 단위)
//     Point M((x_vals[0] + x_vals[11]) / 2, 360); // A와 B의 중점
//     double m = static_cast<double>(720) / (x_vals[0] - x_vals[11]); // 기울기
//     double m_inverse = -1.0 / m; // -m^-1

//     // 최적의 Arc 중점 C 찾기
//     double min_difference = std::numeric_limits<double>::max();
//     int optimal_index = 0;
//     for (int i = 0; i < 12; i++) {
//         double m_candidate = static_cast<double>(y_vals[i] - 360) / (x_vals[i] - M.x);
//         double difference = fabs(m_candidate - m_inverse);
//         if (difference < min_difference) {
//             min_difference = difference;
//             optimal_index = i;
//         }
//     }

//     // 최적의 H 계산 (픽셀 단위)
//     double H_pixels = sqrt(pow(x_vals[optimal_index] - M.x, 2) + pow(y_vals[optimal_index] - M.y, 2));

//     // 픽셀 단위를 미터 단위로 변환
//     double W_meters = W_pixels * meters_per_pixel_x;
//     double H_meters = H_pixels * meters_per_pixel_y;

//     // 곡률 반경 R 계산
//     double R = H_meters / 2 + pow(W_meters, 2) / (8 * H_meters);
//     steering_angle = tan(wheelbase/R);
//    return steering_angle;
// }

Mat RoadLaneDetector::img_filter (Mat transformed_frame) {



namedWindow("Trackbars");

   
    // 트랙바 값 읽기

        Mat hsv_transformed_frame;
		
        cvtColor(transformed_frame, hsv_transformed_frame, COLOR_BGR2HSV);
    int l_h = getTrackbarPos("L - H", "Trackbars");
    int l_s = getTrackbarPos("L - S", "Trackbars");
    int l_v = getTrackbarPos("L - V", "Trackbars");
    int u_h = getTrackbarPos("U - H", "Trackbars");
    int u_s = getTrackbarPos("U - S", "Trackbars");
    int u_v = getTrackbarPos("U - V", "Trackbars");

    Mat hls_transformed_frame;
    cvtColor(transformed_frame,hls_transformed_frame,COLOR_BGR2HLS);


    int l_h_hls = getTrackbarPos("L - H1", "Trackbars");
    int l_l = getTrackbarPos("L - L1", "Trackbars");
    int l_s_hls = getTrackbarPos("L - S1", "Trackbars");
    int u_h_hls = getTrackbarPos("U - H1", "Trackbars");
    int u_l = getTrackbarPos("U - L1", "Trackbars");
    int u_s_hls = getTrackbarPos("U - S1", "Trackbars");

    Mat mask1;

    Scalar lower1(l_h_hls , l_l , l_s_hls);
    Scalar upper1(u_h_hls,u_l,u_s_hls);
    cv::inRange(hls_transformed_frame , lower1 , upper1,mask1);

        // Create mask using the trackbar values
        Mat mask;
        Scalar lower(l_h, l_s, l_v);
        Scalar upper(u_h, u_s, u_v);
        cv::inRange(hsv_transformed_frame,lower, upper,mask);
Mat combined;
    cv::bitwise_or(mask, mask1, combined);


return combined;
}


