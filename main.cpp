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
    
    for(path in : directory_iterator(d)) {
        input.filename = old_extractFilename(in);
        input.extension = extractExtension(in);
        v.insert(v.end(), input);
    }
}

void displayAllFiles(const vector<file> &v) {
    for(int i = 0; i < v.size(); i++) {
        cout << "File " << i + 1 << ": " << v[i].filename << v[i].extension << endl;
    }
}

int main() {
    path maindir = "Z:/fileorg_experimentation - Copy";

    if(!exists(maindir)) {
        cout << "Directory does not exist." << endl;
        return 1;
    }

    vector<file> allFiles;
    directoryfilesToVector(allFiles, maindir);
    displayAllFiles(allFiles);
    unordered_map<string, string> hashedExtensions = buildExtensionMap();

    for(int p = 0; p < allFiles.size(); p++){
        // checks whether extension belongs in the hash map
        auto check = hashedExtensions.find(allFiles[p].extension);
        string category;
        
        // Following comments indicate case
        if (is_directory(maindir / allFiles[p].filename) && categoryGroups.find(allFiles[p].filename) != categoryGroups.end()) {
            // this entry is itself an existing category folder (e.g. "Images"), not a file to sort — skip it so it never gets moved
            continue;
        } else if (check != hashedExtensions.end()) {
            // extension matched an entry in hashedExtensions, so use its mapped category name
            category = (*check).second;
        } else {
            // extension has no known category, so classify as "Other"
            category = "Other";
        }

        if(!exists(maindir / category)){
            create_directory(maindir / category);
        }

        string fullFileName = allFiles[p].filename + allFiles[p].extension; 
        rename(maindir / fullFileName, maindir / category / fullFileName);
    }

}