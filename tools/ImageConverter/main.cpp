#include <iostream>
#include "../../Include/raylib.h"

int main() {
    std::string _filename;
    std::cout << "Place the image file into this directory and enter the name -> myimage.png" << std::endl;
    std::cin >> _filename;

    Image image = LoadImage(_filename.c_str());

    std::string _export_filename = _filename + "_raw.h";
    ExportImageAsCode(image, _export_filename.c_str());

    return 0;
}