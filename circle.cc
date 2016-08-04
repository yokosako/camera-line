#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  VideoCapture cap(0);
  for(int i=0;;i++)
    {
      Mat color_img;
     cap >> color_img;
      // char fname[1024];
      // sprintf(fname, "/media/ykzk/ボリューム/rc/rc2015_log/tumsat_pool3/dimg%05d.jpg", i);
           // Mat color_img = imread(fname); //画像読み込み
  Mat gray_img; //グレースケール画像の変数
  Mat bin_img; //二値化画像の変数
  cvtColor(color_img, gray_img, CV_RGB2GRAY); //グレースケール化
 // threshold(gray_img, bin_img, 100, 255, THRESH_BINARY); //二値化（今回は関係なし）
  GaussianBlur(gray_img, gray_img, Size(17,17), 2, 2); //ガウシアンフィルタでノイズの除去
 Canny(gray_img, gray_img, 10, 20, 3); //エッジ検出
  //imshow("y", gray_img);

     vector<Vec3f> circles;
     HoughCircles(gray_img, circles, CV_HOUGH_GRADIENT, 8,gray_img.rows, 400, 200  );
    for( size_t i = 0; i < circles.size(); i++ )
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
         // 円の中心を描画します．
         circle( color_img, center, 3, Scalar(0,255,0), -1, 8, 0 );
         // 円を描画します．
         circle( color_img, center, radius, Scalar(0,255,0), 3, 8, 0 );
    }
  

    imshow( "ライン検出", color_img );    
    waitKey(50);
  }
  return 0;
}
