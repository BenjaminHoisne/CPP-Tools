# C++ Tools

This repository contains small C++ utilities built to assist with audio file management, naming, and documentation for game development and technical sound design.  

## Utilities

### AudioSorter

- **Purpose**: Automatically organizes audio files into folders based on their names.
- **Naming convention required**:  
  `SW_Category_SubCategory_FileName_VariationNumber`
- **Functionality**:  
  - Scans a directory for audio files  
  - Parses each filename according to the naming convention  
  - Sorts and moves files into corresponding `Category/SubCategory` folders  
- **Use case**: Preparing assets for integration into Unreal projects.

### CSVCreator

- **Purpose**: Scans a directory and generates a CSV file listing all contained audio files, extracting key metadata from their names and hierarchy.
- **Extracted fields**:  
  - Filename  
  - Category 
  - Subcategory  
  - Duration 
- **Use case**: Useful for documentation, auditing and organization of rendered assets. 

