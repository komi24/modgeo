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


#ifndef EXCEPTION_PROJ_HPP
#define EXCEPTION_PROJ_HPP

#include <iostream>
#include <string>

/** \brief Namespace for PROJ classes */
namespace proj
{
    /** \brief General exception class */
    class exception_proj
    {
    public:

        /** \brief empty constructor */
        exception_proj();
        /** \brief constructor with error information */
        exception_proj(const std::string& msg,const std::string& file,const std::string& caller,const int& line);

        /** \brief return error message */
        std::string info() const;

    private:

        /** \brief error message storage */
        std::string message;
        /** \brief caller name storage */
        std::string caller;
        /** \brief file name storage */
        std::string file;
        /** \brief error line storage */
        std::string line;

    };
}

#endif
