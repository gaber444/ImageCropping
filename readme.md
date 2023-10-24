# Image Cropping Tool with OpenCV

## Description

This project is a simple image cropping tool that utilizes OpenCV, a popular computer vision library, to load an image, crop a specified region, and save the cropped image. It provides an intuitive graphical interface for users to interact with.

The key features of this tool include:
- Loading an image from your local storage.
- Defining the cropping region using interactive sliders.
- Saving the cropped image to your desired location.

This project serves as a practical example of using OpenCV for basic image processing tasks, and it can be a helpful tool for various applications where cropping is necessary.

## Prerequisites

Before using this tool, ensure you have OpenCV installed on your system. You can follow the provided installation instructions for Mac and Linux in the README.

### Mac
**Homebrew:** You can install Homebrew if you don't have it already. If you already have Homebrew installed, make sure it's up to date by running:
```bash
  brew update

  brew install cmake

  brew install opencv
```
### Linux 
    CMake: You can install CMake using your system's package manager. For Ubuntu/Debian:
```bash
     sudo apt-get install cmake
```
OpenCV: Install OpenCV using your system's package manager. For Ubuntu/Debian:
```bash
     sudo apt-get install libopencv-dev
```
## Installation
    Clone the repository:
```bash
    git clone https://github.com/gaber444/branjeTexta.git
    mkdir build
    cd build
    cmake ..
    make
``` 
Usage: 
```bash
     ./branje-executable <path_to_original_picture> <path_to_save_picture>       
```
