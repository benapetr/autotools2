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

#ifndef STRINGTOOL_H
#define STRINGTOOL_H

#include <vector>
#include <string>

namespace StringTool
{
    std::vector<std::string> split(const std::string &s, char delim);
    std::string &ltrim(std::string &s);
    std::string &rtrim(std::string &s);
    std::string &trim(std::string &s);
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::string itos(int i);
    std::string itos(unsigned int i);
}

#endif // STRINGTOOL_H
