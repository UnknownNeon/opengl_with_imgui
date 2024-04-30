#pragma once
#include <string>
#include <fstream>
#include <sstream>

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/geometric.hpp>
#include <fstream>

namespace Util {

    inline std::string file_read(const std::string& file_path) {
        
        std::ifstream file(file_path);
        std::string str;
        std::string line;
        while (std::getline(file, line)) {
            str += line + "\n";
        }
        return str;
    };

    inline std::string getFileExt(const std::string& s) {

        size_t i = s.rfind('.', s.length());
        if (i != std::string::npos) {
            return(s.substr(i + 1, s.length() - i));
        }
        return("");
    };

    inline bool exist(std::string PATH)
    {
        std::ifstream fin;
        fin.open(PATH.c_str());
        fin.close();
        return bool(fin);
    };
}