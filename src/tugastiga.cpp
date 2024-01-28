#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap("/home/bimo/code/project 1/media/mov.mp4");

    if (!cap.isOpened()) {
        cout << "Error opening video file" << endl;
        return -1;
    }

    Mat frame, gray, hasil, plastik;

    bool boladiPlastik = false;

    while (cap.read(frame)) {
        frame.copyTo(hasil);

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        medianBlur(gray, gray, 15);

        threshold(gray, plastik, 150, 255, THRESH_BINARY);

        vector<vector<Point>> contours;
        findContours(plastik, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        for (size_t i = 0; i < contours.size(); i++) {
            drawContours(hasil, contours, static_cast<int>(i), Scalar(157, 104, 129), 2);
        }

        vector<Vec3f> circles;
        HoughCircles(gray, circles, HOUGH_GRADIENT, 1, gray.rows / 16, 100, 20, 27, 50);

        for (size_t i = 0; i < circles.size(); i++) {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);

            if (radius > 0) {
                circle(hasil, center, radius, Scalar(0, 0, 255), 3, 8, 0);

                string koordinat = "(" + to_string(center.x) + ", " + to_string(center.y) + ")";
                cout << koordinat << endl;

                for (size_t j = 0; j < contours.size(); j++) {
                    if (pointPolygonTest(contours[j], center, false) > 0) {
                        boladiPlastik = true;
                        break;
                    }
                }
            }
        }

        string status = boladiPlastik ? "Bola Masuk" : "Bola Keluar";
        putText(hasil, status, Point(20, 30), FONT_HERSHEY_SIMPLEX, 1, Scalar(68, 37, 31), 2);

        imshow("plastik", plastik);
        imshow("Output", hasil);

        if (waitKey(30) == 27) {
            // Tekan tombol Esc untuk keluar dari loop
            break;
        }

        boladiPlastik = false;
    }

    cap.release();
    destroyAllWindows();

    return 0;
}
