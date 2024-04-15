#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

int ix, iy, k = -1;

void mouse(int event, int x, int y, int flags, void * param) 
{
  if (event == cv::EVENT_LBUTTONDOWN) 
  {
    ix = x;
    iy = y;
    k = 1;
  }
}

int main() 
{
  cv::namedWindow("draw");
  cv::setMouseCallback("draw", mouse);

  cv::VideoCapture cap(0);

  while (true) 
  {
    cv::Mat frm;
    cap.read(frm);
    cv::flip(frm, frm, 1);
    cv::imshow("draw", frm);

    int key = cv::waitKey(1);
    if (key == 27 || k == 1) 
    {
      cv::Mat old_gray;
      cv::cvtColor(frm, old_gray, cv::COLOR_BGR2GRAY);
      cv::Mat mask = cv::Mat::zeros(frm.size(), frm.type());
      break;
    }
  }

  cv::destroyWindow("draw");

  std::vector < cv::Point2f > old_pts = 
  {
    cv::Point2f(ix, iy)
  };

  cv::Scalar color(0, 255, 0);
  int c = 0;
  while (true) 
  {
    cv::Mat new_frm;
    cap.read(new_frm);
    cv::flip(new_frm, new_frm, 1);

    cv::Mat new_gray;
    cv::cvtColor(new_frm, new_gray, cv::COLOR_BGR2GRAY);

    std::vector < cv::Point2f > new_pts;
    std::vector < uchar > status;
    std::vector < float > err;
    cv::calcOpticalFlowPyrLK(old_gray, new_gray, old_pts, new_pts, status, err, cv::Size(15, 15), 1,
      cv::TermCriteria(cv::TermCriteria::COUNT + cv::TermCriteria::EPS, 15, 0.08));

    int key = cv::waitKey(1);

    if (key == 'e') 
    {
      mask = cv::Mat::zeros(new_frm.size(), new_frm.type());
    } 
    else
    if (key == 'c') 
    {
      color = cv::Scalar(0, 0, 0);
      c = (c + 1) % 3;
      color[c] = 255;
    } 
    else 
    if (key == 'g') 
    {
      // do nothing
    } 
    else 
    {
      for (size_t i = 0; i < old_pts.size(); i++)
      {
        cv::line(mask, old_pts[i], new_pts[i], color, 15);
        cv::circle(new_frm, new_pts[i], 3, cv::Scalar(255, 255, 0), 2);
      }
    }

    cv::addWeighted(new_frm, 0.8, mask, 0.2, 0.1, new_frm);
    cv::imshow("", new_frm);
    cv::imshow("drawing", mask);

    old_gray = new_gray.clone();
    old_pts = new_pts;

    if (key == 27) 
    {
      break;
    }
  }
  cv::destroyAllWindows();
  cap.release();
  return 0;
}
