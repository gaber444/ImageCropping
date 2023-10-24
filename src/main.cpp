#include "Base.h"

int main(int argc,char *argv[])
{
    Base p;
    //First argument path to original picture.
    // Second argument path the place where we want to save a picture
    if(argc < 3){
        std::cerr << "Usage: " << argv[0] << " <path_to_original_picture> <path_to_save_picture>" << std::endl;
        return 1;
    }else{
        try{
            p.setPathToOriginalPicture(argv[1]);
            p.setPathToSavePicture(argv[2]);
        }catch(const std::exception &error){
            std::cerr << "Error: " << error.what() << std::endl;
            return 1;
        }
    }
    p.manageCropImage4(p.getPathToOriginalPicture());


    return 0;
}