#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

#define CV_COLOR_GREEN cv::Scalar(0, 255, 0)
CascadeClassifier faceCascade;


int main(int argc, char** argv)
{
  //Open the camera
  VideoCapture cap(0);
  if(!cap.isOpened())
  {
    return -1;
  }
  //load classification
  CascadeClassifier faceDetector("lbpcascade_frontalface.xml");
  vector<Rect> objects;
  Mat frame;
  Mat edges;
  bool stop = false;
  while(!stop){
    cap >> frame;
    if (frame.empty())
      stop = true;
    double scaleFactor=1.1;
    int minNeighbors = 3;
    //int flags = 1;
    //cvtColor(frame, edges, CV_BGR2GRAY);
    //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
    faceDetector.detectMultiScale(frame, objects,scaleFactor, minNeighbors);
    for(int i = 0; i < objects.size(); i++){
      rectangle(frame, objects[i], CV_COLOR_GREEN);
      //rectangle(edges, objects[i], CV_COLOR_GREEN);
    }
    //imshow("edge", edges);
    imshow("frame", frame);
    if (waitKey(5) >= 0)
      stop = true;
  }
  return 0;
}
