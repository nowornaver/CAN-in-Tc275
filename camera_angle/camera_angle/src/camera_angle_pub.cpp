#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <torch/script.h> // LibTorch를 사용하기 위해 포함해야 함

#include "opencv2/opencv.hpp"
#include "RoadLaneDetector.h"
#include <fstream>  // 파일 입출력을 위한 헤더 추가
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float64.h> // Float64 메시지 타입 추가
using namespace cv;
using namespace std;
int main (int argc , char **argv) {
 ros::init(argc,argv,"camera_node");
 ros::NodeHandle n;
 geometry_msgs::Twist push;
 ros::Publisher publisher_push = n.advertise<std_msgs::Float64>("goal_angle",10);
 RoadLaneDetector roadLaneDetector;
 	Mat img_frame, img_filter, img_edges, img_mask, img_lines, img_result;
	Mat bird_of_eye_view;
 ros::Rate loop_rate(60);
 torch::jit::script::Module model;
std_msgs::Float64 goal_angle;
   try {
        // yolopv2_scripted.pt 파일 경로를 지정
        model = torch::jit::load("/home/adg/test/yolopv2_scripted.pt", torch::kCUDA); // CUDA로 로드
    }
    catch (const c10::Error& e) {
        std::cerr << "Error loading the model\n";
        return -1;
    }

    std::cout << "Model loaded successfully\n";

    // 동영상 파일 열기
    // cv::VideoCapture cap("/home/adg/test/curvature.mp4");
        cv::VideoCapture cap("/dev/video2",cv::CAP_V4L2);
    if (!cap.isOpened()) {
        std::cerr << "Error opening video file\n";
        return -1;
    }

    cv::Mat frame;

    int img_center = 640;
    int frame_count = 0;
 while(ros::ok()) {
    cap.read(frame);
       if (frame.empty()) {
        break;
    }
      // 이미지를 Tensor로 변환
        cv::resize(frame, frame, cv::Size(1280, 1280)); // YOLOPv2 입력 크기에 맞게 조정

        torch::Tensor img_tensor = torch::from_blob(frame.data, {1, frame.rows, frame.cols, 3}, torch::kByte);
        img_tensor = img_tensor.permute({0, 3, 1, 2}); // HWC to CHW
        img_tensor = img_tensor.to(torch::kFloat).div(255.0); // 정규화
        img_tensor = img_tensor.to(torch::kCUDA); // CUDA로 전환

        // 모델 추론
        std::vector<torch::jit::IValue> inputs;
        inputs.push_back(img_tensor);

        // 추론 실행
        torch::jit::IValue output = model.forward(inputs);

        // 출력이 Tuple인지 확인하고 각 요소를 처리
        if (output.isTuple()) {
            auto elements = output.toTuple()->elements();

            // 요소 1: 객체 검출 정보일 가능성 있음
            if (elements.size() > 1 && elements[1].isTensor()) {
                at::Tensor detection_result = elements[1].toTensor();
                // std::cout << "Output tensor 1 shape: " << detection_result.sizes() << "\n";

                // 여기서 객체 검출 결과를 프레임에 시각화하는 후처리 추가 가능
            }

            // 요소 2: 세그멘테이션 정보일 가능성 있음
            if (elements.size() > 2 && elements[2].isTensor()) {
                at::Tensor segmentation_result = elements[2].toTensor();
                // std::cout << "Output tensor 2 shape: " << segmentation_result.sizes() << "\n";

                // 세그멘테이션 마스크 후처리
                auto mask_data = segmentation_result.squeeze().to(torch::kCPU); // 첫 번째 차원 삭제하고 CPU로 이동
                cv::Mat mask(cv::Size(1280, 1280), CV_32FC1, mask_data.data_ptr<float>()); // OpenCV 이미지로 변환
                mask.convertTo(mask, CV_8UC1, 255.0); // 0~1 사이의 값을 0~255로 변환
                // roadLaneDetector.bird_eye_view(frame);
                roadLaneDetector.transformed_frame = roadLaneDetector.bird_eye_view(mask);
                // imshow("mask",mask);
                // imshow("transformed",roadLaneDetector.transformed_frame);
                // imshow("bird",roadLaneDetector.transformed_frame);
//                    Mat s = roadLaneDetector.bird_eye_view(mask);
//                     imshow("s",s);
        vector<int> l = roadLaneDetector.Start_lane_detection(roadLaneDetector.transformed_frame);
        Mat msk = mask.clone();
        Mat result=mask.clone();
            cout <<"Es = " <<roadLaneDetector.es <<endl; 
        result = roadLaneDetector.sliding_window(roadLaneDetector.transformed_frame, roadLaneDetector.transformed_frame, l[0], l[1]);
        imshow("result",result);
        if (roadLaneDetector.currentSize ==16  )  {
            for (int i = 0 ; i <16 ; i ++) { //이전값을 현재값으로 업데이트를 하면 안됀다 표준편차 값을 비교해서 
                roadLaneDetector.prev_lx[i] = roadLaneDetector.lx[i];
                roadLaneDetector.prev_y_vals_left[i] = roadLaneDetector.y_vals_left[i]; //둘다 하면 문제 발생 문제 발생 이유는 polyfit 을 할때 전역변수에 있는 coeffs_vector 가 겹치게 되면서 문제가 발생한다.
                // cout <<"prev_lx = " <<roadLaneDetector.prev_lx[i] <<endl; 
                // cout <<"prev_ly = " <<roadLaneDetector.prev_y_vals_left[i] <<endl; 
            
            }
    roadLaneDetector.currentSize=0;
}
if (roadLaneDetector.currentSize1 ==16 ) { //es 는 현재좌표값으로 계산 
for (int i = 0 ; i <16 ; i ++) {
                roadLaneDetector.prev_rx[i] = roadLaneDetector.rx[i];
                roadLaneDetector.prev_y_vals_right[i] =roadLaneDetector.y_vals_right[i];
                //     cout <<"prev_rx = " <<roadLaneDetector.prev_rx[i] <<endl; 
                // cout <<"prev_ry = " <<roadLaneDetector.prev_y_vals_right[i] <<endl; 


}
roadLaneDetector.currentSize1 = 0;
}
double left_steering_angle =roadLaneDetector.ROC(roadLaneDetector.lx,roadLaneDetector.y_vals_left);
double right_steering_angle = roadLaneDetector.ROC(roadLaneDetector.rx,roadLaneDetector.y_vals_right);

int real_steering_angle = (left_steering_angle+right_steering_angle)/2;
int direction = (   (roadLaneDetector.lx[15]-roadLaneDetector.lx[0])+(roadLaneDetector.rx[15]-roadLaneDetector.rx[0])  )/2;
if (direction <-50) { //좌회전일때 -값 붙혀주기 잘 안돼면 커브쳐 구해서 
    real_steering_angle = real_steering_angle*-1;
}
goal_angle.data = real_steering_angle;
publisher_push.publish(goal_angle);
cout <<"direction = " <<direction <<endl; //튜닝필요 
cout <<"steering_angle = " <<real_steering_angle <<endl; 

                // cv::imshow("Segmentation Mask", mask);
// //                 // imshow("transformed_frame",roadLaneDetector.transformed_frame);
//             }
        } else {
            std::cerr << "Unexpected output format.\n";
            break;
        }

        // 원본 프레임 표시
        cv::imshow("Input Frame", frame);

        // 'q' 키를 누르면 종료
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }
 }
    cap.release();
    cv::destroyAllWindows();

 }
 