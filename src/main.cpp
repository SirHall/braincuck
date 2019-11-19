#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

std::string GetIndent(std::size_t levels)
{
    std::string indent = "";
    for (std::size_t i = 0; i < levels; i++)
        indent += "    ";
    return indent;
}

std::size_t GetRepetitions(const std::vector<char>::iterator &begin,
                           const std::vector<char>::iterator &end,
                           char                               character)
{
    std::size_t repetitions = 0;
    for (auto i = begin; i < end; i++)
    {
        if (*i == character)
            repetitions++;
        else
            break;
    }
    return repetitions;
}

int main(int argc, char *argv[])
{
    auto inCode    = std::vector<char>();
    auto outStream = std::stringstream();
    // std::string outCode   =
    outStream << "#include <stdio.h>\n"
                 "unsigned char array[65535] = {0};\n"
                 "unsigned short ptr = 0;\n"
                 "int main(int argc, char *argv)\n{\n";

    std::size_t indentLevels = 1;

    {
        char        srcChar   = '\0';
        auto        fin       = std::fstream(argv[1], std::fstream::in);
        std::string codeChars = "+-.,><[]";
        while (fin >> std::noskipws >> srcChar)
        {
            if (std::find(codeChars.begin(), codeChars.end(), srcChar) !=
                codeChars.end())
            {
                inCode.push_back(srcChar);
            }
        }
    } // File closes here

    std::size_t inCodeIndex = 0;

    while (inCodeIndex < inCode.size())
    {
        char        c = inCode[inCodeIndex];
        std::size_t repetitions =
            GetRepetitions(inCode.begin() + inCodeIndex, inCode.end(), c);

        switch (c)
        {
            case '+':
                outStream << GetIndent(indentLevels);
                outStream << "array[ptr] += " << repetitions << ";\n";
                inCodeIndex += repetitions;
                break;
            case '-':
                outStream << GetIndent(indentLevels);
                outStream << "array[ptr] -= " << repetitions << ";\n";
                inCodeIndex += repetitions;
                break;
            case '>':
                outStream << GetIndent(indentLevels);
                outStream << "ptr += " << repetitions << ";\n";
                inCodeIndex += repetitions;
                break;
            case '<':
                outStream << GetIndent(indentLevels);
                outStream << "ptr -=" << repetitions << ";\n";
                inCodeIndex += repetitions;
                break;
            case '.':
                outStream << GetIndent(indentLevels);
                outStream << "putchar(array[ptr]);\n";
                inCodeIndex += 1;
                break;
            case ',':
                outStream << GetIndent(indentLevels);
                outStream << "array[ptr] = getchar();\n";
                inCodeIndex += 1;
                break;
            case '[':
                outStream << GetIndent(indentLevels) + "while(array[ptr])\n" +
                                 GetIndent(indentLevels) + "{\n";
                indentLevels++;
                inCodeIndex += 1;
                break;
            case ']':
                indentLevels--;
                outStream << GetIndent(indentLevels);
                outStream << "}\n";
                inCodeIndex += 1;
                break;
            default:
                inCodeIndex += 1;
                break;
        }
    }

    outStream << "    return 0;\n}";

    auto outFile = std::ofstream(argv[2]);
    outFile << outStream.str();

    return 0;
}