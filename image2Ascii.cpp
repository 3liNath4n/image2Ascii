#include <chrono>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace chrono;

int main(int argc, char *argv[])
{
  auto start = steady_clock::now();

  if (argc < 2)
  {
    cout << "Usage: " << argv[0] << " <input_file_name>" << endl;
    return 1;
  }

  string inputFileName = argv[1];

  Mat img = imread(inputFileName, IMREAD_GRAYSCALE);
  if (img.empty())
  {
    cout << "Failed to read the image: " << inputFileName << endl;
    return 1;
  }

  string outputFileName = "./ascii/" + inputFileName.substr(inputFileName.find_last_of("/") + 1);
  outputFileName = outputFileName.substr(0, outputFileName.find_last_of(".")) + ".txt";

  double aspectRatio = static_cast<double>(img.cols) / img.rows;
  int desiredWidth = 80;
  int desiredHeight = static_cast<int>(desiredWidth / aspectRatio);

  ofstream outputFile(outputFileName);
  if (!outputFile.is_open())
  {
    cout << "Failed to open the output file: " << outputFileName << endl;
    return 1;
  }

  const string asciiChars = "@%#*+=-:. "
                            "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  const int reductionFactor = 4;
  int asciiCharsSize = asciiChars.size();
  int asciiCharsReducedSize = asciiCharsSize / reductionFactor;
  int imgRows = img.rows;
  int imgCols = img.cols;
  for (int i = 0; i < imgRows; i += imgRows / desiredHeight)
  {
    for (int j = 0; j < imgCols; j += imgCols / desiredWidth)
    {
      unsigned char pixel = img.at<unsigned char>(i, j);
      int asciiIndex = pixel / (256 / asciiCharsReducedSize);
      outputFile << asciiChars[asciiIndex];
    }
    outputFile << '\n';
  }

  outputFile.close();

  auto end = steady_clock::now();
  auto duration = duration_cast<milliseconds>(end - start).count();

  cout << "ASCII image recreation saved to: " << outputFileName << endl;
  cout << "Execution time: " << duration << " milliseconds" << endl;

  return 0;
}
