#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
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
      cvtColor(color_img, gray_img, CV_BGR2HSV);
      inRange(gray_img, Scalar(150, 70, 70), Scalar(180, 255, 255), gray_img);
      vector<Vec4i> lines;
      HoughLinesP( gray_img, lines, 1, CV_PI/180, 80, 30, 10 );
      if(lines.size()>=1){
	line( color_img, Point(lines[0][0], lines[0][1]),Point(lines[0][2], lines[0][3]), Scalar(255,0,0), 3, 8 );
	double katamuki =(((double)-lines[0][3]+lines[0][1])/(lines[0][2]-lines[0][0]));
	line (color_img, Point(color_img.cols/2,0),Point(color_img.cols/2,color_img.rows),Scalar(0,0,0),2,8);
	line (color_img, Point(0,color_img.rows/2),Point(color_img.cols,color_img.rows/2),Scalar(0,0,0),2,8);
	double seppen;
	seppen = color_img.rows+(-1)*(katamuki*lines[0][0]+lines[0][1]);
	double seppen2;
	seppen2 = katamuki*color_img.cols+seppen;
	double seppen3;
	seppen3 = (-1)*((seppen2+seppen)/2-color_img.rows/2)/katamuki;
	//cout << "x軸切片"<<seppen3 <<  "y軸切片"<<(seppen2+seppen)/2-color_img.rows/2  <<endl;
	//cout << "x軸切片"<<seppen3 <<endl;
	//cout << "y軸切片"<<(seppen2+seppen)/2-color_img.rows/2  << endl;
	if(katamuki>=0){
	  cout << "角度:"<<atan(katamuki)*(180/CV_PI) <<endl;
	}else{
	  cout << "角度:"<<180+atan(katamuki)*(180/CV_PI) <<endl;
	}
      }
      imshow( "ライン検出", color_img );
      waitKey(50);
    }
  return 0;
}
