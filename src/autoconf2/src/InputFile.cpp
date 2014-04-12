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

#include <fstream>
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "Exception.hpp"
#include "InputFile.hpp"

InputFile::InputFile()
{
    this->sourceCode = "";
}

InputFile::InputFile(const InputFile& other)
{
    this->sourceCode = other.sourceCode;
}

void InputFile::Load(std::string path)
{
    std::ifstream infile(path.c_str());
    if (!infile.is_open())
    {
        throw Exception("unable to open file for reading: " + path, "void InputFile::Load(std::string path)");
    }
    std::string line;
    while (std::getline(infile, line))
    {


    }
    infile.close();
}

void InputFile::GenerateConfigure(std::string path)
{
    if (this->sourceCode == "")
    {
        throw Exception("trying to generate configure which wasn't compiled", "void InputFile::GenerateConfigure(std::string path)");
    }
    const char *c_path = path.c_str();
    std::ofstream out(c_path);
    out << this->sourceCode << std::endl;
    out.close();
    if (chmod(c_path, strtol("0755", 0, 8)) < 0)
    {
        throw Exception("unable to change permissions of " + path + " to 755, chmod() returned " + std::string(strerror(errno)),
                        "void InputFile::GenerateConfigure(std::string path)");
    }
}
