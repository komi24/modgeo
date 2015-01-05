/*
**    This program is free software: you can redistribute it and/or modify
**    it under the terms of the GNU General Public License as published by
**    the Free Software Foundation, either version 3 of the License, or
**    (at your option) any later version.
**
**   This program is distributed in the hope that it will be useful,
**    but WITHOUT ANY WARRANTY; without even the implied warranty of
**    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**    GNU General Public License for more details.
**
**    You should have received a copy of the GNU General Public License
**    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <exception_proj.hpp>
#include <sstream>

namespace proj
{
    exception_proj::exception_proj(){}

    exception_proj::exception_proj(const std::string& _msg,const std::string& _file,const std::string& _caller,const int& _line)
        :message(_msg),caller(_caller),file(_file)
    {
        std::ostringstream stream;
        stream<<_line;
        line=stream.str();
    }

    std::string exception_proj::info() const
    {
        return message+" in file ["+file+"] in function ["+caller+"] at line "+line+" \n";
    }

}
