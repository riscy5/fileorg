// Z:/fileorg_experimentation will be used for desktop directory experimentation

#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <map>
#include "categories.h"

using namespace std::filesystem;
using namespace std;

// will NOT include extension in name, extracts SOLELY the filename
string old_extractFilename(const path& f) {
    string filenameWithExt = f.filename().string();
    string filenameNoExt;
    int extIndex = -1;

    for(int i = filenameWithExt.size() - 1; i > 0; i--) {
        if(filenameWithExt[i] == '.') {
            extIndex = i;
            break;
        }
    }

    if (extIndex == -1) {
        return filenameWithExt;
    }

    for(int p = 0; p < extIndex; p++) {
        filenameNoExt += filenameWithExt[p];
    }

    return filenameNoExt;
}

struct file {
    string filename;
    string extension;
};

// const so it doesn't modify
// call by reference (&) to indicate file struct won't be modified due to const

string extractExtension(const path &f) {
    return f.extension().string();
}

string extractFilename(const path &f) {
    return f.stem().string();
}

void directoryfilesToVector(vector<file> &v, const path &d) {
    file input;
    
    for(path it : directory_iterator(d)) {
        input.filename = old_extractFilename(it);
        input.extension = extractExtension(it);
        v.insert(v.end(), input);
    }
}

void displayAllFiles(const vector<file> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << "File " << i + 1 << ": " << v[i].filename << v[i].extension << endl;
    }
}

// Do not include file name in destination directory path!
bool isDuplicate(const file &c, const path &d) {
    string fullFileName = c.filename + c.extension;
    
    for(auto it : directory_iterator(d)) {
        if(fullFileName == it.path().filename()) {
            return true;
        }
    }

    return false;
}

// Do not include file name in destination directory path!
path duplicatePathCreator(const file &c, const path &d) {
    // start as a int return as string: (n)
    path fileWDir = d / (c.filename + c.extension);

    int n = 1;

    // Example: test.txt, test (1).txt, ...., test (n).txt
    // Structure: <filename> + <extension>, <filename> + " (" + 1 + ")"
    while(exists(fileWDir)) {
        fileWDir = d / (c.filename + (" (" + to_string(n) + ")" + c.extension) );
        cout << c.filename + (" (" + to_string(n) + ")" + c.extension);
        n++;
    }

    // debug print for identifying duplicates
    // cout << fileWDir;

    return fileWDir;
}

void createAndMoveFiles(const vector<file> &allFiles, const path main_directory) {
    unordered_map<string, string> hashedExtensions = buildExtensionMap();
    
    for(int p = 0; p < allFiles.size(); p++){
        // checks whether extension belongs in the hash map
        auto check = hashedExtensions.find(allFiles[p].extension);
        string category;
        
        // Following comments indicate case
        if (is_directory(main_directory / allFiles[p].filename) && categoryGroups.find(allFiles[p].filename) != categoryGroups.end()) {
            // this entry is itself an existing category folder (e.g. "Images"), not a file to sort — skip it so it never gets moved
            continue;
        } else if (check != hashedExtensions.end()) {
            // extension matched an entry in hashedExtensions, so use its mapped category name
            category = (*check).second;
        } else {
            // extension has no known category, so classify as "Other"
            category = "Other";
        }

        if(!exists(main_directory / category)){
            create_directory(main_directory / category);
        }

        string fullFileName = allFiles[p].filename + allFiles[p].extension; 
        
        // check if its a self-nesting directory
        if(main_directory / fullFileName / fullFileName == main_directory / category / fullFileName) {
            continue;
        }

        if(isDuplicate(allFiles[p], main_directory / category)) {
            rename(main_directory / fullFileName, duplicatePathCreator(allFiles[p], main_directory / category));
        } else {
            rename(main_directory / fullFileName, main_directory / category / fullFileName);
        }
    }
}

int main() {
    path maindir = "Z:/fileorg_duplicate_test";

    if(!exists(maindir)) {
        cout << "Directory does not exist." << endl;
        return 1;
    }

    vector<file> allFiles;
    directoryfilesToVector(allFiles, maindir);
    displayAllFiles(allFiles);
    createAndMoveFiles(allFiles, maindir);

}