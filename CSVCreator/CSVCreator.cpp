// This program create a CSV file containing the list of files in a specified directory, their categories, subcategories and durations. 
// Author : Benjamin Hoisne

#include <iostream>
#include <filesystem>
#include <string>
#include <fstream>
#include <algorithm> 
#include <SFML/Audio.hpp>

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

// Function to get the duration of an audio file.
double getDuration(auto filePath){
    sf::Music music;
    double duration = music.getDuration().asSeconds();
    if (music.openFromFile(filePath)) {
        return music.getDuration().asSeconds();
    }
    return duration;
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
    std::cout << "Directory is valid.\n";

	// Create or open the CSV file.
    std::ofstream file(csvFilePath);
    if (!file.is_open()) {
        std::cerr << "Could not create or open the file.\n";
        return 1;
    }

    // Write the header to the CSV file.
    file << "Filename,Category,Subcategory,Duration\n";

    // Iterate through the directory and its subdirectories.
    for (const auto& entry : fs::recursive_directory_iterator(folderPath)) {
        if (!fs::is_regular_file(entry.status())) continue;

        // Get the file path and extension.
        fs::path filepath = entry.path();
        std::string ext = filepath.extension().string();
        if (ext != ".wav" && ext != ".ogg" && ext != ".txt") continue;

		// Extract the filename, category, and subcategory.
        std::string filename = filepath.filename().string();
        fs::path relativePath = fs::relative(filepath.parent_path(), folderPath);
        std::string category = "None";
        std::string subcategory = "None";

		// If the relative path has at least one component, use it as category.
        auto it = relativePath.begin();
        if (it != relativePath.end()) {
            category = it->string();
            ++it;
            if (it != relativePath.end()) {
                subcategory = it->string();
            }
        }

		// Get the duration of the file in seconds.
        std::string duration = std::to_string(static_cast<int>(getDuration(entry) * 100) / 100.0);

		// Write the data to the CSV file.
        file << filename << "," << category << "," << subcategory << "," << duration << "\n";
    }

    file.close();

	// Check if the file was successfully written.
    if (!file) {
        std::cerr << "Error writing to the file.\n";
        return 1;
    }
    else
    {
        std::cout << "CSV created successfully: " << csvFileName << "\n";
    }
    return 0;
}