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

#ifndef OUTPUTSCRIPT_BASH_H
#define OUTPUTSCRIPT_BASH_H

#include <string>
#include "OutputScript.hpp"

class OutputScript_Bash : public OutputScript
{
    public:
        OutputScript_Bash();
        virtual ~OutputScript_Bash() {}
        std::string GenerateHeader();
        std::string GenerateInit(std::string product, std::string version);
    protected:
    private:
};

#endif // OUTPUTSCRIPT_BASH_H
