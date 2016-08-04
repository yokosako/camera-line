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
  waitKey(50);
   }
  return 0;
}
