#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

Mat quantization(Mat, int);
Mat resolution(Mat, int);

int main(int argc, char* argv[]) {
  // 檢查是否有指定輸入影像檔案
  if ( argc != 4 ) {
    printf("usage: DisplayImage.out <Image_Path> <Mode> <select>\n");
    return -1;
  }
  Mat image_raw = imread( argv[1], 0);
  if ( !image_raw.data ) {
    printf("No image data \n");
    return -1;
  }

  imshow("RAW Image", image_raw);

  if(strcmp(argv[2], "1") == 0){

    imshow("quantization Image", quantization(image_raw, atoi(argv[3])));
  
  }else if(strcmp(argv[2], "2") == 0){

    imshow("resolution Image", resolution(image_raw, atoi(argv[3])));

  }
  
  // imshow("Display Image2", image_new);
  waitKey(0);
  return 0;
}

Mat quantization(Mat raw, int res){
  Mat image;
  image.create(raw.cols, raw.rows, CV_8UC1);
  for(int i = 0; i < raw.cols; i++){
    for(int j = 0; j < raw.rows; j++){
      image.at<uchar>(i, j) = raw.at<uchar>(i, j) / (256 / res) * (256 / res);
    }
  }
  return image;
}

Mat resolution(Mat raw, int size){
  Mat image, image_tmp;
  image.create(raw.cols, raw.rows, CV_8UC1);
  int scale = 256 / size, tmp;
  //縮小
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      tmp = 0;
      image_tmp.create(size, size, CV_8UC1);
      for(int ni = i * scale; ni < (i + 1) * scale; ni++){
        for(int nj = j * scale; nj < (j + 1) * scale; nj++){
          tmp += raw.at<uchar>(ni, nj);
        }
      }
      image_tmp.at<uchar>(i, j) = tmp / (scale * scale);
    }
  }
  //放大
  for(int i = 0; i < 256; i++){
    for(int j = 0; j < 256; j++){
      image.at<uchar>(i, j) = image_tmp.at<uchar>(i / scale, j / scale);
    }
  }
  return image;
}
