#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<std::string> readFile(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    }
    return lines;
}

int countLines(const std::vector<std::string>& lines) {
    int count = 0;
    for (const std::string& line : lines) {
        if (!line.empty()) {
            count++;
        }
    }
    return count;
}

/*
int countLines(const std::vector<std::string>& lines) {
    return lines.size();
}
*/

int countCoutCin(const std::vector<std::string>& lines, const std::string& keyword) {
    int count = 0;
    for (const std::string& line : lines) {
        if (line.find(keyword) != std::string::npos) {
            count++;
        }
    }
    return count;
}

int countIfElse(const std::vector<std::string>& lines) {
    int count = 0;
    bool foundIf = false;

    for (const std::string& line : lines) {
        size_t ifPos = line.find("if");
        size_t elsePos = line.find("else");

        if (ifPos != std::string::npos && elsePos != std::string::npos && ifPos < elsePos) {
            count++;
        } else if (elsePos != std::string::npos && foundIf) {
            // Handles the case where 'else' appears without a previous 'if'
            count++;
        }

        if (ifPos != std::string::npos) {
            foundIf = true;
        }
    }
    return count;
}

int countIfStatements(const std::vector<std::string>& lines) {
    int count = 0;

    for (const std::string& line : lines) {
        size_t ifPos = line.find("if");
        size_t elsePos = line.find("else");

        if (ifPos != std::string::npos && (elsePos == std::string::npos || ifPos < elsePos)) {
            count++;
        }
    }
    return count;
}

int countwhileStatements(const std::vector<std::string>& lines) {
    int count = 0;

    for (const std::string& line : lines) {
        size_t ifPos = line.find("while");
        
        if (ifPos != std::string::npos) {
            count++;
        }
    }
    return count;
}

int compareFunctions(const std::vector<std::string>& file1Lines, const std::vector<std::string>& file2Lines) {
    std::vector<std::string> file1Functions;
    std::vector<std::string> file2Functions;

    for (const std::string& line : file1Lines) {
        size_t funcStart = line.find('(');
        size_t funcEnd = line.find(')');
        if (funcStart != std::string::npos && funcEnd != std::string::npos && funcStart < funcEnd) {
            std::string funcSignature = line.substr(0, funcEnd + 1);
            file1Functions.push_back(funcSignature);
        }
    }

    for (const std::string& line : file2Lines) {
        size_t funcStart = line.find('(');
        size_t funcEnd = line.find(')');
        if (funcStart != std::string::npos && funcEnd != std::string::npos && funcStart < funcEnd) {
            std::string funcSignature = line.substr(0, funcEnd + 1);
            file2Functions.push_back(funcSignature);
        }
    }

   
    //std::cout << "Similar named/similar Signature between the two files:\n";
    int ct = 0;
    for (const std::string& funcSig1 : file1Functions) {
        for (const std::string& funcSig2 : file2Functions) {
            if (funcSig1 == funcSig2) {
                //std::cout << "Function signature: " << funcSig1 << " (Similar in both files)\n";

                ct = ct + 1;
                break; // Break after finding a match
            }
        }
    }
    return ct;
}

double calculatePlagiarismPercentage(const std::vector<std::string>& file1, const std::vector<std::string>& file2) {
    int commonLines = 0;

    for (const std::string& line1 : file1) {
        for (const std::string& line2 : file2) {
            if (line1 == line2) {
                commonLines++;
                break; // Break after finding a match
            }
        }
    }

    int Same_func = compareFunctions(file1,file2);

    double plagiarismPercentage = (2.0 * (commonLines + Same_func) )/ (file1.size() + file2.size()) * 100.0;
    return plagiarismPercentage;
}

int main() {
    std::string file1Name, file2Name;

    std::cout << "Enter file 1 name: ";
    std::cin >> file1Name;
    std::cout << "Enter file 2 name: ";
    std::cin >> file2Name;


    std::vector<std::string> file1Lines = readFile(file1Name);
    std::vector<std::string> file2Lines = readFile(file2Name);

    int file1LineCount = countLines(file1Lines);
    int file2LineCount = countLines(file2Lines);

    int file1CoutCount = countCoutCin(file1Lines, "cout");
    int file1CinCount = countCoutCin(file1Lines, "cin");
    int file2CoutCount = countCoutCin(file2Lines, "cout");
    int file2CinCount = countCoutCin(file2Lines, "cin");

    int file1IfElseCount = countIfElse(file1Lines);
    int file2IfElseCount = countIfElse(file2Lines);

    int file1ifcount = countIfStatements(file1Lines);
    int file2ifcount = countIfStatements(file2Lines);

    int file1whilecount = countwhileStatements(file1Lines);
    int file2whilecount = countwhileStatements(file2Lines);

    double plagiarismPercentage = calculatePlagiarismPercentage(file1Lines, file2Lines);

    std::cout<<"---------------------------------------------------"<<std::endl;

    std::cout << "File 1 Line Count: " << file1LineCount << std::endl;
    std::cout << "File 2 Line Count: " << file2LineCount << std::endl;

    std::cout<<"---------------------------------------------------"<<std::endl;
    std::cout<<"---------------------------------------------------"<<std::endl;

    std::cout << "File 1 cout Statements: " << file1CoutCount << std::endl;
    std::cout << "File 1 cin Statements: " << file1CinCount << std::endl;
    std::cout << "File 2 cout Statements: " << file2CoutCount << std::endl;
    std::cout << "File 2 cin Statements: " << file2CinCount << std::endl;

     
    std::cout<<"---------------------------------------------------"<<std::endl;
    std::cout<<"---------------------------------------------------"<<std::endl;

    std::cout << "File 1 if-else Count: " << file1IfElseCount << std::endl;
    std::cout << "File 2 if-else Count: " << file2IfElseCount << std::endl;

    std::cout<<"---------------------------------------------------"<<std::endl;
    std::cout<<"---------------------------------------------------"<<std::endl;

    std::cout << "File 1 if Count: " << file1ifcount << std::endl;
    std::cout << "File 2 if Count: " << file2ifcount << std::endl;

    std::cout<<"---------------------------------------------------"<<std::endl;
    std::cout<<"---------------------------------------------------"<<std::endl;

    std::cout << "File 1 while Count: " << file1whilecount << std::endl;
    std::cout << "File 2 while Count: " << file2whilecount << std::endl;

    std::cout<<"---------------------------------------------------"<<std::endl;
    std::cout<<"---------------------------------------------------"<<std::endl;

    int out = compareFunctions(file1Lines, file2Lines);
    std::cout <<"number of Similiar signature is both files is :   "<< out<< std::endl;

    std::cout<<"---------------------------------------------------"<<std::endl;
    std::cout<<"---------------------------------------------------"<<std::endl;

    std::cout << "Plagiarism Percentage: "<< plagiarismPercentage << "%" << std::endl;

    return 0;
}
