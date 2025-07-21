// This program sorts audio files in a specified directory based on their filenames.
// It extracts the category and subcategory from the filename, creates directories accordingly and moves the files into these directories.
// Author : Benjamin Hoisne

#include <iostream>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

// Function to get the directory path from user input.
std::string getDirectoryPath() {
    std::string path;
    std::cout << "Enter the path to the directory: ";
    std::getline(std::cin, path);
    return path;
}

int main()
{
	// Get the directory path and list files.
	std::string folderPath = getDirectoryPath();

	// Check if the path exists and is a directory.
    if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
        std::cerr << "The specified path does not exist or is not a directory." << "\n";
        return 1;
    }
	std::cout << "Directory is valid." << "\n";

    // Iterate through the files in the directory.
    for (const auto& entry : fs::directory_iterator(folderPath)) {
        if (fs::is_regular_file(entry)) {
            std::string filename = entry.path().filename().string();

                // Find Underscores
                size_t firstUnderscore = filename.find('_');       
                size_t secondUnderscore = filename.find('_', firstUnderscore + 1);
                size_t thirdUnderscore = filename.find('_', secondUnderscore + 1);

				// Extract Category and SubCategory
                std::string category = "UnknownCategory";
                std::string subCategory = "UnknownSubCategory";

                if (firstUnderscore != std::string::npos &&
                    secondUnderscore != std::string::npos) {
                    category = filename.substr(firstUnderscore + 1, secondUnderscore - firstUnderscore - 1);
                }

                if (secondUnderscore != std::string::npos &&
                    thirdUnderscore != std::string::npos) {
                    subCategory = filename.substr(secondUnderscore + 1, thirdUnderscore - secondUnderscore - 1);
                }
                else if (secondUnderscore != std::string::npos) {
                    subCategory = filename.substr(secondUnderscore + 1, filename.size() - 4 - (secondUnderscore + 1));
                }
				
				// Create target directory based on category and subcategory
                fs::path targetDir = fs::path(folderPath) / category / subCategory;

                if (!fs::exists(targetDir)) {
                    fs::create_directories(targetDir);
                }

				// Move the file to the target directory
                fs::path targetPath = targetDir / filename;
                fs::rename(entry.path(), targetPath);
        }
    }
    std::cout << "Files have been processed." << "\n";
	return 0;
}