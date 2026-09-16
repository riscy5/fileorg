#ifndef categoriesh
#define categoriesh

#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

const map<string, vector<string>> categoryGroups = {
    {"Documents", {".pdf", ".doc", ".docx", ".txt", ".rtf", ".odt", ".md", ".csv", ".xls", ".xlsx", ".ppt", ".pptx", ".pages", ".key", ".numbers", ".odp", ".ods", ".epub", ".tex", ".xps", ".log"}},
    {"Images",    {".jpg", ".jpeg", ".png", ".gif", ".bmp", ".svg", ".webp", ".tiff", ".tif", ".ico", ".heic", ".raw", ".psd", ".avif", ".heif", ".ai", ".eps", ".indd", ".cr2", ".nef", ".arw", ".dng"}},
    {"Videos",    {".mp4", ".mov", ".avi", ".mkv", ".wmv", ".flv", ".webm", ".m4v", ".mpg", ".mpeg", ".3gp", ".ts", ".m2ts", ".vob", ".ogv"}},
    {"Audio",     {".mp3", ".wav", ".flac", ".aac", ".ogg", ".wma", ".m4a", ".aiff", ".mid", ".midi", ".opus", ".amr"}},
    {"Archives",  {".zip", ".rar", ".7z", ".tar", ".gz", ".bz2", ".xz", ".iso", ".cab", ".tgz", ".zst", ".lz", ".arj"}},
    {"Code",      {".cpp", ".c", ".h", ".hpp", ".py", ".java", ".js", ".html", ".css", ".php", ".rb", ".go", ".rs", ".swift", ".sh", ".bat", ".json", ".xml", ".yaml", ".yml", ".sql", ".cs", ".kt", ".lua", ".pl", ".scss", ".sass", ".jsx", ".tsx", ".vue", ".ini", ".toml", ".r", ".m"}},
    {"Executables", {".exe", ".msi", ".app", ".dmg", ".deb", ".rpm", ".apk", ".bin", ".com", ".jar", ".run", ".appimage", ".msix"}},
    {"Fonts",     {".ttf", ".otf", ".woff", ".woff2", ".pfb", ".pfm", ".eot"}},
    {"Shortcuts", {".lnk", ".url", ".pif"}},
    {"System Library", {".dll", ".sys", ".ocx", ".drv", ".cpl", ".icl", ".fon", ".vxd", ".tlb", ".olb", ".mui", ".efi"}},
};

unordered_map<string,string> buildExtensionMap() {
    unordered_map<string,string> extensionMap;

    for(auto catIt = categoryGroups.begin(); catIt != categoryGroups.end(); ++catIt) {
        string cat = (*catIt).first;
        vector<string> ext = (*catIt).second;

        for(auto extIt = ext.begin(); extIt != ext.end(); ++extIt) {
            extensionMap[*extIt] = cat;
        }
    }

    return extensionMap;
}

unordered_map<string, string> hashedExtensions = buildExtensionMap();

#endif