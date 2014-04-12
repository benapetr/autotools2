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
#include "OutputScript_Bash.hpp"
#include "Exception.hpp"
#include "InputFile.hpp"

InputFile::InputFile()
{
    this->output_script = NULL;
    this->sourceCode = "";
    this->solutionName = "";
    this->solutionVersion = "";
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
    //! \todo We really want to make it possible to pick a different output format
    output_script = new OutputScript_Bash();
    this->sourceCode += output_script->GenerateHeader();
    this->currentLine = 0;
    while (std::getline(infile, line))
    {
        this->currentLine++;
        this->processLine(line);
    }
    infile.close();
    delete output_script;
}

void InputFile::processLine(std::string text)
{
    text = StringTool::trim(text);
    // skip if it's a comment line
    if (text.size() > 1 && text[0] == '/' && text[1] == '/')
    {
        return;
    }
    // get a command
    std::string command = text;
    std::string parameters_line = "";
    unsigned int position = text.find_first_of('(');
    std::vector<std::string> parameters;
    if (position != std::string::npos)
    {
        command = command.substr(0, position);
        // so we have an opening bracket here, let's get the closing one as well
        unsigned int start = position;
        position = text.find_first_of(')');
        if (position == std::string::npos)
        {
            throw Exception("syntax error: expected ')' at line " + StringTool::itos(currentLine),
                            "void InputFile::processLine(std::string text)");
        }
        if (position < start)
        {
            throw Exception("syntax error: closing bracket must not precede opening bracket '(' at line " + StringTool::itos(currentLine),
                            "void InputFile::processLine(std::string text)");
        }
        parameters_line = text.substr(start + 1, position - start - 1);
        parameters = StringTool::split(parameters_line, ',');
    }

    // now that we have the command we can handle it
    if (command == "AC_INIT")
    {
        this->ac_init(parameters);
    }
}

void InputFile::ac_init(std::vector<std::string> parameters)
{
    if (parameters.size() > 0)
        this->solutionName = StringTool::trim(parameters[0]);
    if (parameters.size() > 1)
        this->solutionVersion = StringTool::trim(parameters[1]);

    this->sourceCode += this->output_script->GenerateInit(this->solutionName, this->solutionVersion);
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
