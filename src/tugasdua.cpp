#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;


int main() {
    Mat image = imread("/home/bimo/code/project 1/media/Bola.jpeg");

    resize(image, image, Size(400, 400));

    Mat color, gray, hasil;

    image.copyTo(hasil);

    cvtColor(image, color, COLOR_BGR2GRAY);

    medianBlur(color, gray, 5);

    vector<Vec3f> circles;

    HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 16, 100, 20, 50, 75);

    for (size_t i = 0; i < circles.size(); i++) {
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        int radius = cvRound(circles[i][2]);

        if (radius > 0) {
            circle(hasil, center, radius, Scalar(0, 0, 255), 3, 8, 0);
        }
    }


    string teks = "Jumlah Bola adalah: " + to_string(circles.size());
    putText(hasil, teks, Point(20, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(0, 0, 225), 2);
    
    imshow("Input", image);
    imshow("Output", hasil);
    waitKey(0);

    return 0;
}