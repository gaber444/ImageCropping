#include "Base.h"

Base::Base() : m_currentSorceDIRPath(""), m_currentWorkingDirectoryPath(""),m_width(0),m_height(0),
m_x1(0),m_y1(0),m_printMessage(true),m_originalPicturePath(""),m_pathToSavedPicture(""),m_pictureName("")
{
    setCurrentSorceDirecotryPath();
    setCurrentWorkingDirectoryPath();
}

/**
 * @brief set current working directory, where executable is.
 * 
 */
void Base::setCurrentWorkingDirectoryPath()
{
    m_currentWorkingDirectoryPath = std::filesystem::current_path();
}

/**
 * @brief set working direcotry where .cpp files are.
 * 
 */
void Base::setCurrentSorceDirecotryPath()
{
    std::filesystem::path sourceFilePath(__FILE__);
    m_currentSorceDIRPath = sourceFilePath.parent_path();
}

/**
 * @brief get current working directory, where executable is.
 * 
 */
std::filesystem::path Base::getCurrentWorkingDirectoryPath()
{
    return m_currentWorkingDirectoryPath;
}
        
/**
 * @brief get working direcotry where .cpp files are.
 * 
 */
std::filesystem::path Base::getCurrentSorceDirectoryPath()
{
    return m_currentSorceDIRPath;
}

/**
 * @brief return pointer to retained image.
 * 
 * @return cv::Mat* 
 */
cv::Mat* Base::getCropedImage()
{
    return &m_croppedImage4;
}

/**
 * @brief Set the path to the image that will be cropped. 
 * It is set in the main function.
 * 
 * @param path to the image that will be cropped.
 */
void Base::setPathToOriginalPicture(char *path)
{
    std::filesystem::path spath(path);
    m_originalPicturePath = spath;
}

/**
 * @brief Set the path to the cropped image.
 * 
 * @param path to the cropped image
 */
void Base::setPathToSavePicture(char *path)
{
    std::filesystem::path spath(path);
    m_pictureName = spath.filename().string();
    m_pathToSavedPicture = spath.parent_path();
}

/**
 * @brief Get the path to the image that will be cropped. 
 * 
 * @return std::filesystem::path, path to the image that will be cropped.
 */
std::filesystem::path Base::getPathToOriginalPicture()
{
    return m_originalPicturePath;
}

/**
 * @brief Get the path to the cropped image.
 * 
 * @return std::filesystem::path path to the cropped image.
 */
std::filesystem::path Base::getPathToSavePicture()
{
    return m_pathToSavedPicture;
}

/**
 * @brief Crop the input image and display the result.
 * 
*  This function crops a region of interest (ROI) from the input image and displays
 * the cropped image. It allows the user to save the cropped image to a specific location.
 * 
 * @param x The x-coordinate of the top-left corner of the cropping area.
 * @param y The y-coordinate of the top-left corner of the cropping area.
 * @param width The width of the cropping area.
 * @param height The height of the cropping area.
 */
void Base::cropIMage4(int x, int y, int width, int height)
{
    m_x1 = std::clamp(x,0,m_imageToCrop.cols - 1);
    m_y1 = std::clamp(y,0,m_imageToCrop.rows - 1);
    m_width = std::clamp(width,1,m_imageToCrop.cols - m_x1);
    m_height = std::clamp(height,1,m_imageToCrop.rows - m_y1);

    cv::Rect roi(m_x1,m_y1,m_width,m_height);
    m_croppedImage4 = m_imageToCrop(roi);

    cv::imshow("Cropped image", m_croppedImage4);
    if(m_printMessage){
        std::cout <<"Press 's' or 'S' to save the cropped image to a folder named 'pictures'."<< std::endl;
        m_printMessage = false;
    }
    
    int k = cv::waitKey(0);
    if(k == 's' || k == 'S'){
        bool canWrite = cv::haveImageWriter(m_pictureName);
        if(!canWrite){
            std::cerr<<"Not valid picture name: "<<m_pictureName<<std::endl;
            exit(1);
        }
        if(std::filesystem::exists(getPathToSavePicture())){
            std::filesystem::path cropedImage = getPathToSavePicture() / m_pictureName;
            cv::imwrite(cropedImage.string(), m_croppedImage4);
            std::cerr<<"Image saved successfully to location: "<<cropedImage.string()<<std::endl;
            exit(1);
        }else{
            std::cerr<<"Not valid path: "<<getPathToSavePicture().string()<<" to save a picture\n";
            exit(1);
        }
    }else{
        std::cout<<"Not valid key for saving a picture\n";
    }
}

/**
 * @brief Trackbar callback for updating cropping parameters.
 * 
 * This function is a callback for trackbar events that allow users to interactively
 * adjust the cropping parameters for the image. When called, it updates the cropping
 * coordinates (x1, y1, width, and height) and invokes the image cropping function.
 *
 * 
 * @param value The value associated with the trackbar event
 * @param userdata A pointer to the 'Base' instance to access its member variables and methods.
 */
void Base::trackbarCallback4(int value, void* data)
{
    Base* update = static_cast<Base*>(data);

    update->m_x1 = cv::getTrackbarPos("upperX","image to crop");
    update->m_y1 = cv::getTrackbarPos("upperY","image to crop");
    update->m_width = cv::getTrackbarPos("Width","image to crop");
    update->m_height = cv::getTrackbarPos("Height","image to crop");

    update->cropIMage4(update->m_x1,update->m_y1,update->m_width,update->m_height);

}

/**
 * @brief Manage cropping and user interaction with an image.
 * 
 * This function loads an image from the specified path and displays it in a window with
 * interactive trackbars for defining the cropping region. Users can select the region to
 * be cropped by adjusting the trackbars. After cropping, they are provided with the option
 * to save the cropped image. The user is informed of the success or failure of the save
 * operation.
 * 
 * @param pathToImage The file path to the image to be cropped.
 */
void Base::manageCropImage4(std::string pathToImage)
{
    m_imageToCrop = cv::imread(pathToImage,cv::IMREAD_UNCHANGED);
    if(m_imageToCrop.empty()){
        std::cerr<<"Error loading image, with path: "<<pathToImage<<std::endl;
        return;
    }

    int m_width = m_imageToCrop.size().width;
    int m_height = m_imageToCrop.size().height;

    std::cout<<"Width: "<<m_width<<std::endl;
    std::cout<<"Height: "<<m_height<<std::endl;

    //create window
    cv::namedWindow("image to crop",cv::WINDOW_AUTOSIZE); 

    //create four tracbars
    cv::createTrackbar("upperX","image to crop", nullptr,(m_width - 1),trackbarCallback4, this);
    cv::createTrackbar("upperY","image to crop",nullptr,(m_height - 1),trackbarCallback4,this);
    cv::createTrackbar("Width","image to crop",nullptr,m_width,trackbarCallback4,this);
    cv::createTrackbar("Height","image to crop",nullptr,m_height,trackbarCallback4,this);

    //set min for trackbars
    cv::setTrackbarMin("upperX","image to crop",0);
    cv::setTrackbarMin("upperY","image to crop",0);
    cv::setTrackbarMin("Width","image to crop",1);
    cv::setTrackbarMin("Height","image to crop",1);

    std::string text = "Press 's' or 'S' to save the cropped image.";

    cv::Point textPosition(50, 150);
    int fontFace = cv::FONT_HERSHEY_SIMPLEX;
    double fontScale = 1.0;
    cv::Scalar textColor(255, 255, 255);  // White color
    int thickness = 4;
    cv::putText(m_imageToCrop, text, textPosition, fontFace, fontScale, textColor, thickness);

    cv::imshow("image to crop",m_imageToCrop);
    int k = cv::waitKey(0);
    if(k != 's' && k != 'S'){
        std::cout<<"End without saving cropped picture\n";
    }else{
        std::cout<<"Picture not saved because it is the same as original picture\n";
    }
}

