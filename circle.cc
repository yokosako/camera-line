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


     vector<Vec3f> circles;
     HoughCircles(gray_img, circles, CV_HOUGH_GRADIENT, 8,gray_img.rows, 400, 200  );
    for( size_t i = 0; i < circles.size(); i++ )
    {
         Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
         int radius = cvRound(circles[i][2]);

         circle( color_img, center, 3, Scalar(0,255,0), -1, 8, 0 );

         circle( color_img, center, radius, Scalar(0,255,0), 3, 8, 0 );
    }
  

    imshow( "円検出", color_img );    
    waitKey(50);
  }
  return 0;
}
