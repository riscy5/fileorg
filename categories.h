#ifndef categoriesh
#define categoriesh

#endif

#include <string>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

const map<string, vector<string>> categoryGroups = {
    {"Documents", {".pdf", ".doc", ".docx", ".txt", ".rtf", ".odt", ".md", ".csv", ".xls", ".xlsx", ".ppt", ".pptx", ".pages", ".key", ".numbers"}},
    {"Images",    {".jpg", ".jpeg", ".png", ".gif", ".bmp", ".svg", ".webp", ".tiff", ".tif", ".ico", ".heic", ".raw", ".psd"}},
    {"Videos",    {".mp4", ".mov", ".avi", ".mkv", ".wmv", ".flv", ".webm", ".m4v", ".mpg", ".mpeg", ".3gp"}},
    {"Audio",     {".mp3", ".wav", ".flac", ".aac", ".ogg", ".wma", ".m4a", ".aiff", ".mid", ".midi"}},
    {"Archives",  {".zip", ".rar", ".7z", ".tar", ".gz", ".bz2", ".xz", ".iso"}},
    {"Code",      {".cpp", ".c", ".h", ".hpp", ".py", ".java", ".js", ".ts", ".html", ".css", ".php", ".rb", ".go", ".rs", ".swift", ".sh", ".bat", ".json", ".xml", ".yaml", ".yml", ".sql"}},
    {"Executables", {".exe", ".msi", ".app", ".dmg", ".deb", ".rpm", ".apk", ".bin"}},
    {"Fonts",     {".ttf", ".otf", ".woff", ".woff2"}}
};