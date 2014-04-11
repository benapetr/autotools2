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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define PROGRAM_VERSION "2.0.0.0"
#define PROGRAM_AUTHORS "Petr Bena"

#include <string>

class Configuration
{
    public:
        static unsigned int Verbosity;
        static std::string Configure_Ac;
        //static string Version;
    protected:
    private:
};

#endif // CONFIGURATION_H
