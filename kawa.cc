#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string>
#include <sstream>
#include <iomanip>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
  VideoCapture cap(0);
        int sock;
      struct sockaddr_in addr;

      sock = socket(AF_INET, SOCK_DGRAM, 0);

      addr.sin_family = AF_INET;
      addr.sin_port = htons(12345);
      addr.sin_addr.s_addr = inet_addr("192.168.100.18");
  for(int i=0;;)
    {
      Mat color_img;
      cap >> color_img;
      Mat gray_img;
      cvtColor(color_img, gray_img, CV_BGR2HSV);
      inRange(gray_img, Scalar(150, 70, 70), Scalar(180, 255, 255), gray_img);
      vector<Vec4i> lines;
      HoughLinesP( gray_img, lines, 1, CV_PI/180, 80, 30, 10 );
      double seppen;
      double seppen2;
      double seppen3;
      if(lines.size()>=1){
	i=0;
	line( color_img, Point(lines[0][0], lines[0][1]),Point(lines[0][2], lines[0][3]), Scalar(255,0,0), 3, 8 );
	//circle (color_img,Point(color_img.cols/2,color_img.rows/2),50,Scalar(0,0,0),2,8);
	//circle (color_img,Point(color_img.cols/2,color_img.rows/2),100,Scalar(0,0,0),2,8);
	double katamuki =(((double)-lines[0][3]+lines[0][1])/(lines[0][2]-lines[0][0]));
	line (color_img, Point(color_img.cols/2,0),Point(color_img.cols/2,color_img.rows),Scalar(0,0,0),2,8);
	line (color_img, Point(0,color_img.rows/2),Point(color_img.cols,color_img.rows/2),Scalar(0,0,0),2,8);
	
	seppen = color_img.rows+(-1)*(katamuki*lines[0][0]+lines[0][1]);
	
	seppen2 = katamuki*color_img.cols+seppen;
	seppen3 = (-1)*((seppen2+seppen)/2-color_img.rows/2)/katamuki;
	//cout << "x軸切片"<<seppen3 <<  "y軸切片"<<(seppen2+seppen)/2-color_img.rows/2  <<endl;
	//cout << "x軸切片"<<seppen3 <<endl;
	//cout << "y軸切片"<<(seppen2+seppen)/2-color_img.rows/2  << endl;
	int kakudo = atan(katamuki)*(180/CV_PI);
	if(katamuki<0){
	  kakudo += 180;
	}

	int val1 = (int)seppen3;
	char buf[100];
	sprintf(buf, "L,%03d,%04d", kakudo, val1);
	cout << buf << endl;
	sendto(sock, buf, 10, 0, (struct sockaddr *)&addr, sizeof(addr));
      }
      else{
	i++;
    }
      if(i>=50)
	{
	  char buf[100];
	  sprintf(buf, "Y");
	  cout << buf << endl;
	  sendto(sock, buf, 10, 0, (struct sockaddr *)&addr, sizeof(addr));
	}
      imshow( "ライン検出", color_img );
      waitKey(50);
    }
  close(sock);
  return 0;
}
