# Image to ASCII Converter

This project is a simple command-line utility that converts images into ASCII art. It is written in C++ and utilizes the OpenCV library for image processing, allowing users to transform any given image into a unique piece of ASCII art.

## Prerequisites

Before you can build and run this project, you need to ensure you have the following installed on your system:

- A C++17 compiler
- OpenCV 4.x. Ensure that OpenCV is installed in `/opt/homebrew/include/opencv4`.

## Building

The project uses a `Makefile` for easy building. To compile the project, navigate to the project's root directory in your terminal and run:

```sh
make
```

This command compiles the source code and generates an executable.

## Usage

After building, you can convert an image to ASCII art by running the following command in the terminal:

```sh
./image2ascii <path_to_your_image>
```
Please replace <path_to_your_image> with the actual filesystem path to the image you want to convert. The generated ASCII art will be saved in the ascii directory, under the same name as the input image file, but with a .txt extension.

## Project Structure

The project consists of the following key files and directories:

- image2Ascii.cpp: The main C++ source file that contains the logic for converting images to ASCII art.
- Makefile: A makefile for building the project with minimal effort.
- .vscode: A directory containing settings for Visual Studio Code, useful if you're using this editor for development.
- ascii/: The directory where the generated ASCII art files are saved.

## License
This project is open source and available under the MIT license. If you're planning to share this project, consider adding a LICENSE file to your repository with the MIT license text.
