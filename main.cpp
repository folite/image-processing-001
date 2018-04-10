#include <iostream>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
  // 檢查是否有指定輸入影像檔案
  if ( argc != 4 ) {
    printf("usage: DisplayImage.out <Image_Path>\n");
    return -1;
  }
  Mat image_raw = imread( argv[1], 0), image_new, image_tmp;
  if ( !image_raw.data ) {
    printf("No image data \n");
    return -1;
  }

  // namedWindow("Display Image", WINDOW_AUTOSIZE);
  imshow("Display Image", image_raw);

  image_new.create(image_raw.cols, image_raw.rows, CV_8UC1);

  if(strcmp(argv[2], "1") == 0){
    int hire = atoi(argv[3]);
    for(int i = 0; i < image_raw.cols; i++){
      for(int j = 0; j < image_raw.rows; j++){
        image_new.at<uchar>(i, j) = image_raw.at<uchar>(i, j) / (256 / hire) * (256 / hire);
      }
    }
  }else if(strcmp(argv[2], "2") == 0){
    int size = atoi(argv[3]), scale = 256 / size;
    //縮小
    for(int i = 0; i < size; i++){
      for(int j = 0; j < size; j++){
        int tmp = 0;
        image_tmp.create(size, size, CV_8UC1);
        for(int ni = i * scale; ni < (i + 1) * scale; ni++){
          for(int nj = j * scale; nj < (j + 1) * scale; nj++){
            tmp += image_raw.at<uchar>(ni, nj);
          }
        }
        image_tmp.at<uchar>(i, j) = tmp / (scale * scale);
      }
    }
    //放大
    for(int i = 0; i < 256; i++){
      for(int j = 0; j < 256; j++){
        image_new.at<uchar>(i, j) = image_tmp.at<uchar>(i / scale, j / scale);
      }
    }
  }
  
  imshow("Display Image2", image_new);
  waitKey(0);
  return 0;
}
