//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 2 of the License, or
//  (at your option) version 3.

//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.

//  You should have received a copy of the GNU Lesser General Public License
//  along with this program; if not, write to the
//  Free Software Foundation, Inc.,
//  51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

#ifndef INPUTFILE_H
#define INPUTFILE_H

#include <string>
#include <vector>
#include "OutputScript.hpp"
#include "StringTool.hpp"

class InputFile
{
    public:
        InputFile();
        InputFile(const InputFile& other);
        void Load(std::string path);
        void GenerateConfigure(std::string path);
    protected:
    private:
        void processLine(std::string text);
        void ac_init(std::vector<std::string> parameters);
        std::string solutionName;
        std::string solutionVersion;
        std::string sourceCode;
        OutputScript *output_script;
        unsigned int currentLine;
        unsigned int warningCount;
};

#endif // INPUTFILE_H
