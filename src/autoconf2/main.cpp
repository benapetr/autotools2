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

#include "Terminal.hpp"
#include "Configuration.hpp"
#include "Filesystem.hpp"
#include "InputFile.hpp"
#include "Exception.hpp"

int main(int argc, char *argv[])
{
    Terminal *terminal_ = new Terminal();
    if (!terminal_->Parse(argc, argv))
    {
        delete terminal_;
        return 0;
    }
    delete terminal_;
    if (Configuration::Configure_Ac == "")
    {
        if (Filesystem::FExists("configure.in"))
        {
            Configuration::Configure_Ac = "configure.in";
        } else if (Filesystem::FExists("configure.ac"))
        {
            Configuration::Configure_Ac = "configure.ac";
        } else if (Filesystem::FExists("configure.ac2"))
        {
            Configuration::Configure_Ac = "configure.ac2";
        } else
        {
            // user didn't provide any input file
            Terminal::Error("no input file");
            return 2;
        }
    }
    InputFile *input_file = new InputFile();
    try
    {
        if (Configuration::Target == "")
        {
            Configuration::Target = "configure";
        }
        if (Filesystem::FExists(Configuration::Target))
        {
            Terminal::Error("target " + Configuration::Target + " already exists");
            return 4;
        }
        input_file->Load(Configuration::Configure_Ac);
        input_file->GenerateConfigure(Configuration::Target);
    } catch (Exception ex)
    {
        // we failed to parse this file
        Terminal::Error(ex.Message + " in " + ex.Source);
        delete input_file;
        return 1;
    }
    delete input_file;
    return 0;
}

