#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv )
{
VideoCapture capture(0);
// カメラが使えない場合はプログラムを止める
if(!capture.isOpened())
    return -1;

 Mat frame, src_video;
char windowName[] = "カメラ画像";
namedWindow(windowName, CV_WINDOW_AUTOSIZE);

while(waitKey(1) == -1){
    capture >> frame;
    src_video = frame;
    imshow(windowName,src_video);
}
destroyAllWindows();
return 0;
}
