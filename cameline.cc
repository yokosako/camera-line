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

  Mat gray_img; 
  Mat bin_img; 
  cvtColor(color_img, gray_img, CV_RGB2GRAY); 

  GaussianBlur(gray_img, gray_img, Size(17,17), 2, 2);
  Canny(gray_img, gray_img, 10, 20, 3);
  vector<Vec4i> lines;
    HoughLinesP( gray_img, lines, 1, CV_PI/180, 80, 30, 10 );
    for( size_t i = 0; i < lines.size(); i++ )
    {
        line( color_img, Point(lines[i][0], lines[i][1]),
            Point(lines[i][2], lines[i][3]), Scalar(255,0,0), 3, 8 );
    }

    imshow( "ライン検出", color_img );    
  waitKey(50);
   }
  return 0;
}
