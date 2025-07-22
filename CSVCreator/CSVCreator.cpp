// This program create a CSV file containing the list of files in a specified directory.
// Author : Benjamin Hoisne

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>

namespace fs = std::filesystem;

// Function to get the directory path from user input.
std::string getDirectoryPath() {
    std::string path;
    std::cout << "Enter the path to the directory: ";
    std::getline(std::cin, path);
    return path;
}

// Function to get the CSV file name from user input.
std::string inputFileName() {
    std::string fileName;
    std::cout << "Enter the CSV file name (without extension): ";
    std::getline(std::cin, fileName);
	return fileName + ".csv";
}

// Function to ask the user for a path for the CSV file. 
std::string getCSVFilePath() {
    std::string csvPath;
    std::cout << "Enter the path where you want to save the CSV file: ";
    std::getline(std::cin, csvPath);
    return csvPath;
}

int main()
{
    // Get the directory path and list files.
    std::string folderPath = getDirectoryPath();
	std::string csvFileName = inputFileName();
	std::string csvFilePath = getCSVFilePath() + "\\" + csvFileName;

    // Check if the path exists and is a directory.
    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "The specified path does not exist or is not a directory." << "\n";
        return 1;
    }
    std::cout << "Directory is valid." << "\n";

    // Create a CSV file to store the file names. 
    std::ofstream file(csvFilePath);
    if (!file.is_open()) {
        std::cerr << "Could not create or open the file." << "\n";
        return 1;
	}

	// Write the header to the CSV file.
    file << "Filename, ObjectPath \n";

    // Iterate through the directory and write file names to the CSV.
    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
        if (fs::is_regular_file(entry.status())) {

            if (entry.path().extension() != ".wav" && entry.path().extension() != ".ogg" && entry.path().extension() != ".txt") {
                continue; // Skip files that are not .wav or .ogg
			}
            
			// Get the file path and extension.
            fs::path filepath = entry.path();
            std::string ext = filepath.extension().string();
            std::string filename = filepath.filename().string();

			// Retrieve the file path and filename.
            fs::path relativePath = fs::relative(filepath.parent_path(), folderPath);

			// Convert the path to a string and replace slashes with backslashes.
            std::string objectPath = "\\Actor-Mixer Hierarchy\\" + relativePath.string();
            std::replace(objectPath.begin(), objectPath.end(), '/', '\\');

            file << filename << "," << objectPath << "\n";
        }
	}

	file.close();

	// Check if the file was written successfully.
    if (!file) {
        std::cerr << "Error writing to the file." << "\n";
        return 1;
	}
    else {
		std::cout << "File created successfully: " << csvFileName << "\n";
	}

	// Notify the user that the files have been processed.
    std::cout << "Files have been processed." << "\n";
    return 0;
}