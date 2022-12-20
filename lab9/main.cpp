#include <opencv2/aruco.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>

#include <chrono>
#include <list>

const double MARKER_MM = 26;

std::vector<cv::Point2f> fromPixelsToMm(std::vector<cv::Point2f> original) {
    std::vector<cv::Point2f> result;
    double distances = 0;
    for (int i = 0; i < 4; i++) {
        cv::Point2f v = (original[i] - original[(i + 1) % 4]);

        distances += std::sqrt(v.x * v.x + v.y * v.y);
    }
    distances = distances / 4;

    for (int i = 0; i < 4; i++) {
        result.push_back({MARKER_MM * (original[i].x / distances), MARKER_MM * (original[i].y / distances)});
    }
    return result;
}

cv::Point_<float> markId(cv::Mat detected, std::vector<std::vector<cv::Point_<float>>> markerCorners, int foundIdx) {
    auto found = markerCorners.at(foundIdx);

    auto calculated = fromPixelsToMm(found);
    auto r = (calculated[0] + calculated[2]) / 2;

    //std::string txt = " [" + std::to_string(r.x) + "," + std::to_string(r.y) + "]";
    //putText(detected, txt.c_str(), found[0], cv::FONT_HERSHEY_PLAIN, 0.5, {0, 0, 255});

    cv::circle(detected, (found[0] + found[2]) / 2, 1, {0,0,255}, 2);

    return r;
}

int main() {
    using namespace cv;
    using namespace std;

    list<pair<std::chrono::steady_clock::time_point, vector<Point2f>>> detectedPositions;

    VideoCapture cam(0);
    Ptr<aruco::DetectorParameters> parameters = aruco::DetectorParameters::create();
    Ptr<aruco::Dictionary> dictionary = aruco::getPredefinedDictionary(aruco::DICT_7X7_250);
    namedWindow("markers", WINDOW_NORMAL);
    namedWindow("markers_rejected", WINDOW_NORMAL);

    while (waitKey(10) != 27) {
        Mat inputImage;
        Mat detected;

        cam >> inputImage;
        detected = inputImage.clone();

        vector<int> markerIds;
        vector<vector<Point2f>> markerCorners, rejectedCandidates;

        aruco::detectMarkers(inputImage, dictionary, markerCorners,
                             markerIds, parameters, rejectedCandidates);

        Mat outputImage = inputImage.clone();
        aruco::drawDetectedMarkers(detected, markerCorners, markerIds);

        auto foundId0 = find(markerIds.begin(), markerIds.end(), 0);
        auto foundId1 = find(markerIds.begin(), markerIds.end(), 1);

        if (foundId0 != markerIds.end() && foundId1 != markerIds.end()) {
            auto r0 = markId(detected, markerCorners, distance(markerIds.begin(), foundId0));
            auto r1 = markId(detected, markerCorners, distance(markerIds.begin(), foundId1));

            cout << sqrt(pow(r1.x - r0.x, 2) + pow(r1.y - r0.y, 2)) << " mm" << endl;
        }
        imshow("markers", detected);
    }

    return 0;
}