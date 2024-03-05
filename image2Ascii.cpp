#include <chrono>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char *argv[])
{
  // Start the timer
  auto start = chrono::steady_clock::now();

  // Check if the input file name is provided
  if (argc < 2)
  {
    cout << "Usage: " << argv[0] << " <input_file_name>" << endl;
    return 1;
  }

  // Define the input file name
  string inputFileName = argv[1];

  // Load the image
  Mat img = imread(inputFileName, IMREAD_GRAYSCALE);
  if (img.empty())
  {
    cout << "Failed to read the image: " << inputFileName << endl;
    return 1;
  }

  // Define the output file name
  string outputFileName =
      "./ascii/" + inputFileName.substr(inputFileName.find_last_of("/") + 1);
  outputFileName =
      outputFileName.substr(0, outputFileName.find_last_of(".")) + ".txt";

  // Calculate the aspect ratio
  double aspectRatio = static_cast<double>(img.cols) / img.rows;

  // Define the desired width of the output text file
  int desiredWidth = 80;

  // Calculate the corresponding height based on the aspect ratio
  int desiredHeight = static_cast<int>(desiredWidth / aspectRatio);

  // Open the output file
  ofstream outputFile(outputFileName);
  if (!outputFile.is_open())
  {
    cout << "Failed to open the output file: " << outputFileName << endl;
    return 1;
  }

  // Convert the image to ASCII representation
  const string asciiChars =
      "@%#*+=-:. "
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
  const int reductionFactor =
      4; // Reduce the number of characters by a factor of 4
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

  // Close the output file
  outputFile.close();

  // Stop the timer and calculate the duration
  auto end = chrono::steady_clock::now();
  auto duration =
      chrono::duration_cast<chrono::milliseconds>(end - start).count();

  // Print the output
  cout << "ASCII image recreation saved to: " << outputFileName << endl;
  cout << "Execution time: " << duration << " milliseconds" << endl;

  return 0;
}
