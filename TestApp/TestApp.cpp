// TestApp.cpp : Defines the entry point for the application.
//

#include "TestApp.h"


//using namespace std;
namespace fs = ghc::filesystem;
std::vector<std::string> srcV;
std::vector<std::string> libV;
std::map<std::string, uint32_t> HeaderTreeNode::RefCount;



static inline void ltrim(std::string& s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](int ch) {
        return !isspace(ch);
        }));
}

static inline void rtrim(std::string& s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](int ch) {
        return !isspace(ch);
        }).base(), s.end());
}

std::vector<std::string> RecursivelistFiles(const std::string path) {
  
    const fs::path pathToShow = path;
    std::string pattern;
    std::vector<std::string> items;

    
    for (const auto& entry : fs::recursive_directory_iterator(pathToShow)) {
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_regular_file()) {
            if (entry.path().extension() == ".cpp") {
                items.push_back(entry.path());
            }
        }

    }
    return items;
};

void parseFlags(int argc, char* argv[]) {
    if (argc < 2) {
        //MessageBox(NULL, TEXT("ERROR: No Command Line Option Found."), TEXT("Error"), MB_ICONERROR | MB_OK);
        printf("ERROR: No Command Line Option Found. \n");
    }

    for (int i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-i") || !strcmp(argv[i], "I")) {
            if (!argv[i + 1] || argv[i + 1][0] == '-') {
                printf("ERROR: Invalid Command Line Option Found: \"%s\".\n", argv[i]);
                //MessageBox(NULL, TEXT("ERROR: Invalid Command Line Option Found: \"%s\".\n", argv[i]), TEXT("Error"), MB_ICONERROR | MB_OK);
                
            }
            libV.push_back(argv[i + 1]);
            ++i;
            continue;
        }
        else if (argv[i][0] != '-') {
            srcV.push_back(argv[i]);
        }
        else {
            if (i == argc - 1) {
                break;
            }
            printf("ERROR: Invalid Command Line Option Found: \"%s\".\n", argv[i]);
            //MessageBox(NULL, TEXT("ERROR: Invalid Command Line Option Found: \"%s\".\n", argv[i]), TEXT("Error"), MB_ICONERROR | MB_OK);
            
        }
    }
    if (srcV.empty()) {
        printf("ERROR: Command Line Option Source path not found \n");
    }
};


void parseIncludes(std::string path, HeaderTreeNode* TreeNode, fs::path parentFilePath = "NULL")  {

    
    fs::path pathToShow = path;
    std::string currentFileName = pathToShow.filename();
    std::string currentPath = fs::absolute(pathToShow.parent_path());
    std::string currentPathFull = fs::absolute(pathToShow);
    currentPath.push_back('/');

    HeaderTreeNode* ChildNode = TreeNode->addChild(currentFileName, fs::absolute(pathToShow));

    
    bool isCommented = false;
    std::regex includePattern("^\\s*#\\s*include\\s*(?:<[^>]*>|\"[^\"]*\")\\s*");
    char delimiterLib = '<';
    char delimiterSrc = '"';
    std::ifstream input(path);
    if (!input.is_open()) ChildNode->exists = false;

    for (std::string line; getline(input, line); )
    {

        for (std::string::size_type i = 0; i < line.size(); ++i) {
            if (line[i] == '/' && line[i+1] == '*') {
                isCommented = true;
            }
            if (line[i] == '*' && line[i + 1] == '/') {
                isCommented = false;
            }
            if (line.size() - i == 1 && !isCommented && regex_search(line, includePattern)) {  

                if (line.npos == line.find(delimiterLib)) {

                    std::string includePath = line.substr(line.find(delimiterSrc)+1);
                    ltrim(includePath);
                    rtrim(includePath);
                    includePath = includePath.substr(0, includePath.length() - 1);
                    
                    fs::path includePathFull = fs::absolute(currentPath + includePath);
                    // prevent recursive inlcude
                    if (includePathFull != parentFilePath) {
                        parseIncludes(includePathFull, ChildNode, currentPathFull);
                    }

                    
                    
                }
                if (line.npos == line.find(delimiterSrc)) {
                    std::string includePath = line.substr(line.find(delimiterLib) + 1);
                    ltrim(includePath);
                    rtrim(includePath);
                    includePath = includePath.substr(0, includePath.length() - 1);

                    bool fileFound = false;
                    for (std::string libPath : libV) {
                        std::fstream fileStream;
                        fs::path fullPath = fs::absolute(libPath + "/" + includePath);
                        fileStream.open(fullPath);
                        if (fileStream.is_open()) {
                            fileFound = true;
                            // prevent recursive inlcude
                            if (fullPath != parentFilePath) {
                                parseIncludes(fullPath, ChildNode, currentPathFull);
                            }
                            break;
                        }
                    }
                    if (!fileFound) {
                        fs::path includePathFs = includePath;
                        std::string fileName = includePathFs.filename();
                        HeaderTreeNode* SubChildNode = ChildNode->addChild(fileName, fs::absolute(includePathFs));
                        SubChildNode->exists = false;
                    }
                }       
            }
        }
    }
}


int main(int argc, char* argv[])
{

    parseFlags(argc, argv);

    HeaderTreeNode* headerTree = new HeaderTreeNode("root", "root");

  

    for (std::string path : srcV) {
        std::vector<std::string> filesPathV = RecursivelistFiles(path);
        for (std::string path : filesPathV) {
            parseIncludes(path, headerTree);
        }
    }


    headerTree->RecursivelistNodesSorted();
    std::cout << std::endl;
    std::cout << std::endl;
    headerTree->listFrequency();


	return 0;
}
