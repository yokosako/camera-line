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
  // Mat bin_img;
  // Mat smooth_video;
  // medianBlur(color_img, smooth_video, 5);
  // cvtColor(color_img, color_img, CV_RGB2GRAY); 
  	cvtColor(color_img, gray_img, CV_BGR2HSV);
	//	imshow("", gray_img);
		inRange(gray_img, Scalar(150, 70, 70), Scalar(180, 255, 255), gray_img);
	
	//	 cvtColor(gray_img, gray_img, CV_RGB2GRAY); 

	//	 GaussianBlur(gray_img, gray_img, Size(17,17), 2, 2);
	//	 Canny(gray_img, gray_img, 10, 20, 3);

	/*        for(int y=0; y<gray_img.rows;y++){
            for(int x=0; x<gray_img.cols; x++){
	      int hue = gray_img.at<Vec3b>(y,x)[0];
 int sat = gray_img.at<Vec3b>(y,x)[1];
 int val = gray_img.at<Vec3b>(y,x)[2];
 if((hue<=160&&hue>=190)&&sat>=150&&val>=0) {         
   gray_img.at<uchar>(y,x)=255;
 }else{
   gray_img.at<uchar>(y,x)=0;
            }
	    }
	}
		imshow("",gray_img);	*/	 
      
	       
 
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
