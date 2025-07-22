# LaneDetection

## 

## 목차

- 이미지 전처리
- 슬라이딩 윈도우 기법
- 다항회귀
- steering_angle 계산
- 데이터 전처리
- 카메라 켈리브레이션
- yolo pv2
- 카메라 하드웨어 위치
- 느낀점

# 이미지 전처리

동영상을 실행했을때의 이미지 입니다.

- 차선의 왜곡을 없애기 위해서 bird_eye_view 를 사용해 이미지를 바꿔줍니다

<img width="1278" height="752" alt="Screenshot from 2024-10-12 16-36-05" src="https://github.com/user-attachments/assets/c75703f0-1fee-4740-ad1d-fd7de7b99f14" />


- HSV 필터를 사용해서 필요없는 이미지를 모두 제거합니다.
- HSV 필터란?
    
    아무 처리도 하지않은 이미지(동영상)필터는 RGB(Red , Green ,Blue ) 형태로 되어있습니다.
    
    HSV 필터는 RGB가 아닌 HSV 로 바꿔서 보겠다는 것 입니다. 색조(hue) , 명도(Saturation) , 채도 (Value)
    
    H가 일정한 범위를 갖는 순수한 색 정보를 가지고 있기 때문에 RGB보다 색을 쉽게 분류 할 수 있습니다.
    
<img width="1278" height="760" alt="Screenshot from 2024-10-12 16-36-13" src="https://github.com/user-attachments/assets/2516d0a5-026b-4792-a955-ef3e6265ac3f" />


<img width="1281" height="761" alt="Screenshot from 2024-10-12 16-47-33" src="https://github.com/user-attachments/assets/a0c2887a-185d-42a8-bf3a-88c1bf1f5ced" />



# 슬라이딩 윈도우

## 목적:이미지 전처리 과정을 통해 남긴 차선의 좌표를 얻기위함.

- histogram
    <img width="966" height="317" alt="image (3)" src="https://github.com/user-attachments/assets/355ede1d-2b0f-46e5-96d3-693089cf8ab6" />

    
    히스토그램으로 보게되면 왼쪽 차선의 시작 위치 , 오른쪽 차선의 시작 위치를 알 수 있다.
    

히스토그램으로 차선 시작 위치를 알아낸 뒤에 (시작위치,720) 부터 y값을 줄이기 시작하면서 무게 중심 값을 계산해 차선의 좌표를 알아냄
<img width="1284" height="755" alt="Screenshot from 2024-10-12 17-04-39" src="https://github.com/user-attachments/assets/9a58490d-1d07-4656-a980-3fb9d0abefa2" />


# 다항회귀(polynomial)

슬라이딩 윈도우 방식으로 알아낸 차선의 좌표를 2차 다항식 형태로 피팅 한다.

- 피팅 이유
    1. 차선의 곡률을 계산하기 위함.
    2. 후에 차선 데이터를 보정하기 위함.
    

# Steering_angle(조향각)
<img width="614" height="308" alt="Screenshot from 2024-10-12 17-09-53" src="https://github.com/user-attachments/assets/ba7180bb-cf6a-4f36-acde-9facb06407ea" />

<img width="523" height="430" alt="image (3)" src="https://github.com/user-attachments/assets/0e116315-2f52-4465-bd4c-0031298d7d13" />


곡률계산은 lx[0] 번째와 lx[배열 끝] 사이의 거리가 w 가 되는것이고 lx[0] 과 lx[배열끝] 사이의 중점을 구하고 배열 lx 사이에 있는 점 과 중점 사이의 거리가 최소가 되는 값이 H가 되는것이다.

L 은 wheelbase 로 이미 알고 있는 값이다.

tan^-1(L/R) 을 사용해서 조향각을 구한다. 

# 데이터 전처리

위의 방식을 활용해서 차선의 곡률을 구할 시에는 다항회귀를 해서 허프만 공식을 사용  할 필요가 없음을 알게 되었다. 

데이터의 노이즈를 최대한 제거하는 방향으로 나아갔다.

우선 그전까지는 vector 를 사용해 데이터를 넣었다면 데이터 관리를 좀 더 용이하게 하기위해 슬라이딩 윈도우 한칸한칸을 배열로 만들게 되었고 나는 12칸으로 나누었기 때문에 배열도 12칸이 되었다.

차선이 끊겨 있거나 , 흰색 픽셀 임계값을 넘지 못하는 경우에는 이전 차선 값을 가지고 있다가 다항회귀 x = ay^2+by+c 를 풀어서 x값을 예측 하게된다.
<img width="1258" height="773" alt="Screenshot from 2024-10-12 17-23-08" src="https://github.com/user-attachments/assets/75e3bc71-8961-493f-bfb7-d89f1d34ae50" />


구분하기 위해서 예측 한 차선은 진한 흰색으로 바꿔주게 되었다.
<img width="1295" height="773" alt="Screenshot from 2024-10-12 17-27-23" src="https://github.com/user-attachments/assets/8b1f151b-045e-4741-8f91-7ba43a655af3" />


아직도 완벽하지 않았다.

표준편차를 이용해서 필터링을 한번 더 거쳐준다.

일반적인 차선이라면 표준편차 값이 일정한데 이상한 차선을 잡게 되면 표준편차 값이 이상하게 튄다.


<img width="1280" height="756" alt="Screenshot from 2024-10-14 18-46-11" src="https://github.com/user-attachments/assets/941fa137-04f1-41c7-b3be-0ce99d19c1e0" />


## 방향

<img width="638" height="243" alt="image (3)" src="https://github.com/user-attachments/assets/605695c8-e047-4c4f-a6eb-35e7e0b00e0c" />



방향은 왼쪽으로 꺽는게 + 오른쪽으로 꺽는게 - 이다. 

왼쪽/오른쪽 여부는 Sliding Window Search로 얻은 차선 x 좌표 배열의 인덱스 0 값과 인덱스 -1 값을 비교하여 판별했습니다.

## YOLO PV2

저기 있는걸 모두 사용하더라도 밖에 나가보면 아예 차선 자체가 안보이는 경우가 많기 때문에 YOLO PV2 를 사용해서 환경에 대한 변화에 민감 하지 않게 만든다.

- 책에 소개된 방법을 이용해 본인 컴퓨터에 맞는 cuda 를 설치해준다.
- C++ 로 코드를 작성을 했다면 libtorch 를 다운한다.
- libtorch 를 사용해서 [yolopv2.pt](http://yolopv2.pt) 파일을 [yolopv2.scripted.pt](http://yolopv2.scripted.pt) 파일로 바꿔준다.
- libtorch 코드 및 사용법 https://pytorch.org/cppdocs/installing.html
- [yolopv2](http://yolopv2.scripted.pt) c++ 에서 사용하는 방법

```jsx
#include <torch/script.h> // LibTorch를 사용하기 위해 포함해야 함
   try {
        // yolopv2_scripted.pt 파일 경로를 지정
        model = torch::jit::load("/home/adg/test/yolopv2_scripted.pt", torch::kCUDA); // CUDA로 로드
    }
    catch (const c10::Error& e) {
        std::cerr << "Error loading the model\n";
        return -1;
    }
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

```

## 카메라 하드웨어의 위치

카메라는 무조건 높은 곳에 위치 시켜야한다. 카메라가 너무 낮을경우 차선 자체가 인식이 안되기 때문이다.

