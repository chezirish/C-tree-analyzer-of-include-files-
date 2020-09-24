class HeaderTreeNode : public std::map<std::string, HeaderTreeNode*>
{
public:
    std::string filename;
    std::string filepath;
    bool exists = true;

    static std::map<std::string, uint32_t> RefCount;
    

    HeaderTreeNode(std::string filename, std::string filepath) : filename(filename), filepath(filepath)
    {

        std::map<std::string, uint32_t>::iterator it = RefCount.find(filepath);
        if (it != RefCount.end())
        {
            ++it->second;
        }
        else
        {
            RefCount[filepath] = 1;
        }
    }

    HeaderTreeNode* addChild(std::string filename, std::string filepath)
    {

        HeaderTreeNode* child = new HeaderTreeNode(filename, filepath);
        (*this)[filename, filepath] = child;

        return child;
        
    }


    void RecursivelistNodesSorted(int depth = 0) {

        for (uint32_t i = 0; i < depth; ++i)
        {
            std::cout << "|..";
        }

        std::cout << filename;
        if (!exists) std::cout << " (!)";
        //std::cout << " " << RefCount[filepath]<< " \t"<< filepath;
        //std::cout << " " << RefCount[filepath];

        using KVType = std::pair<std::string, HeaderTreeNode*>;

        std::vector<KVType> children;

        for (KVType kv : *this)
            children.push_back(kv);

        std::sort(children.begin(), children.end(), [](KVType a, KVType b)
        {

            ghc::filesystem::path pathA = a.first;
            ghc::filesystem::path pathB = b.first;

            std::string fileNameA = pathA.filename();
            std::string fileNameB = pathB.filename();

            return (fileNameA.compare(fileNameB) < 0);
        });


        std::sort(children.begin(), children.end(), [](KVType a, KVType b)
        {
            uint32_t v1 = 0;
            uint32_t v2 = 0;

            if (RefCount.count(a.first))
                v1 = RefCount[a.first];

            if (RefCount.count(b.first))
                v2 = RefCount[b.first];


            return v1 < v2;
        });

        for (KVType kv : children) {
            std::cout << "\n";
            kv.second->RecursivelistNodesSorted(depth + 1);
        }
     
    }

    void listFrequency() 
    {

        using KVType = std::pair<std::string, uint32_t>;
        std::vector<KVType> children;

        std::map<std::string, uint32_t>::iterator it;

        for (KVType child : RefCount) {
            children.push_back(std::make_pair(child.first, child.second));
        }

        
        std::stable_sort(children.begin(), children.end(), [](KVType a, KVType b)
        {
            uint32_t v1 = 0;
            uint32_t v2 = 0;

            if (RefCount.count(a.first))
                v1 = RefCount[a.first];
                    
            if (RefCount.count(b.first))
                v2 = RefCount[b.first];

            return v1 > v2;
        });


        for (KVType kv : children) {
            if (kv.first.compare("root") == 0) continue;
            ghc::filesystem::path keyFileName = kv.first;
            std::cout << "\n";
            std::cout << keyFileName.filename() << " " << kv.second;
        }
    }


    void RecursivelistNodes(uint32_t depth = 0)
    {
        for (uint32_t i = 0; i < depth; ++i)
        {
            std::cout << "|..";
        }

        std::cout << filename;
        if (!exists) std::cout << " (!)";

        using KVType = std::pair<std::string, HeaderTreeNode*>;


        for (KVType kv : *this) {
            std::cout << "\n";
            kv.second->RecursivelistNodes(depth + 1);
        }
    }
};
