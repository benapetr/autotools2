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
        // user didn't provide any input file
        //! \todo Check if there isn't some in current folder
        Terminal::Error("no input file");
        return 2;
    }
    InputFile *input_file = new InputFile();
    try
    {
        input_file->Load(Configuration::Configure_Ac);
    } catch (Exception ex)
    {
        Terminal::Error(ex.Message + " in " + ex.Source);
    }
    delete input_file;
    return 0;
}

