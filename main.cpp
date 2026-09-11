// Z:/fileorg_experimentation will be used for desktop directory experimentation

#include <string>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <map>
#include <categories.h>

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
// & call by reference to indicate file won't be modified due to const

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

int main() {
    path maindir = "Z:/fileorg_experimentation";

    if(!exists(maindir)) {
        cout << "Directory does not exist." << endl;
        return 1;
    }

    vector<file> allFiles;

    directoryfilesToVector(allFiles, maindir);

    for(int i = 0; i < allFiles.size(); i++) {
        cout << "File " << i + 1 << ": " << allFiles[i].filename << allFiles[i].extension << endl;
    }
}