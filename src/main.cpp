#include <opencv2/opencv.hpp>
#include <opencv2/face.hpp>
#include <opencv2/face/facemark.hpp>
#include <iostream>
#include <fstream>
#include <vector> 
#include <cstdlib>

using namespace cv;
using namespace face;
using namespace std;

const char* pythonScript = "/home/eyelights/Documents/landmarks/face_landmark_detection.py";
int x;
int y;
int counter = 0;

int main() {
    fstream newfile;
    vector<vector<vector<int>>> coordinates;

    Mat frame;
    VideoCapture cap(0);

    while (cap.read(frame)) {
        imwrite("/home/eyelights/Documents/landmarks/frame.jpg",frame);
        circle(frame,Point(x,y),1,Scalar(150,150,150),1);
        int result = std::system(("python " + std::string(pythonScript)).c_str());

        newfile.open("../landmarks_coordinates.txt",ios::in); //open a file to perform read operation using file object
        if (newfile.is_open()) {
            string tp;
            while (getline(newfile, tp)) {
                //cout << tp << "\n";
                for (int i = 0; i < tp.size(); i++) {
                    if (tp[i] == ';') {
                        x = stoi(tp.substr(0, i));
                        y = stoi(tp.substr(i+1, tp.size()));
                        vector<int> v = {x,y};
                        //cout << x << y << endl;
                        coordinates[counter].push_back(v);
                    }
                }
                circle(frame,Point(x,y),1,Scalar(150,150,150),1);
            }
            newfile.close();
        }
        imshow("frame",frame);
        waitKey(0);

        counter++;
    }

}

