#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  VideoCapture cap0(0);
  VideoCapture cap1(1);
  
   for(int i=0;;i++)
    {
      Mat color_img;
        Mat color_img2;
      cap0 >> color_img;
      cap1 >> color_img2;
  Mat gray_img; //グレースケール画像の変数
   Mat gray_img2;
 
  cvtColor(color_img, gray_img, CV_RGB2GRAY); //グレースケール化
  GaussianBlur(gray_img, gray_img, Size(17,17), 2, 2); //ガウシアンフィルタでノイズの除去
  Canny(gray_img, gray_img, 10, 20, 3); //エッジ検出
  cvtColor(color_img2, gray_img2, CV_RGB2GRAY); //グレースケール化

  GaussianBlur(gray_img2, gray_img2, Size(17,17), 2, 2); //ガウシアンフィルタでノイズの除去
  Canny(gray_img2, gray_img2, 10, 20, 3); //エッジ検出

  vector<Vec3f> circles;
  HoughCircles(gray_img2, circles, CV_HOUGH_GRADIENT, 8,gray_img2.rows, 400, 200  );
  for( size_t i = 0; i < circles.size(); i++ )
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);
   
         circle( color_img2, center, 3, Scalar(0,255,0), -1, 8, 0 );
	 
         circle( color_img2, center, radius, Scalar(0,255,0), 3, 8, 0 );
    }
  
    vector<Vec4i> lines;
    HoughLinesP( gray_img, lines, 1, CV_PI/180, 80, 30, 10 );
    for( size_t i = 0; i < lines.size(); i++ )
      {
       line( color_img, Point(lines[i][0], lines[i][1]),
           Point(lines[i][2], lines[i][3]), Scalar(255,0,0), 3, 8 );
  }
    //imshow("二値化", bin_img);
    //imshow( "エッジ検出", gray_img );
    imshow( "ライン検出", color_img );
    imshow("円検出", color_img2);
    waitKey(50);
  }
  return 0;
}
