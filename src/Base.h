#ifndef BASE_H
#define BASE_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/core.hpp>

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iostream>


class Base {
    public:
        Base();
        virtual ~Base() = default;

    protected:
        void setCurrentWorkingDirectoryPath();
        void setCurrentSorceDirecotryPath();
    public:
        std::filesystem::path getCurrentWorkingDirectoryPath();
        std::filesystem::path getCurrentSorceDirectoryPath();
        cv::Mat* getCropedImage();
        void setPathToOriginalPicture(char *path);
        void setPathToSavePicture(char *path);
        std::filesystem::path getPathToOriginalPicture();
        std::filesystem::path getPathToSavePicture();
        void cropIMage4(int x, int y, int width, int height);
        void manageCropImage4(std::string pathToImage);
        static void trackbarCallback4(int value, void* data);
    public:
        int m_width;
        int m_height;
        int m_x1;
        int m_y1;

    private:
        cv::Mat m_imageToCrop;
        cv::Mat m_croppedImage4;
        std::filesystem::path m_currentWorkingDirectoryPath;
        std::filesystem::path m_currentSorceDIRPath;
        std::filesystem::path m_originalPicturePath;
        std::filesystem::path m_pathToSavedPicture;
        std::string m_pictureName;
        bool m_printMessage;


};


#endif //BASE_H