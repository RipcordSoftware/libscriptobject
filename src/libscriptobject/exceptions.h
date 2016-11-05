/**
 * @file
 * Declare exception types specific to libscriptobject
 * 
 * @internal
 *  This file is part of libscriptobject.
 *
 *  libscriptobject is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  libscriptobject is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with libscriptobject.  If not, see <http://www.gnu.org/licenses/>.
 * @endinternal
 * 
 * @defgroup Exceptions Exception types specific to libscriptobject
**/

#ifndef RS_LIBSCRIPTOBJECT_EXCEPTIONS_H
#define RS_LIBSCRIPTOBJECT_EXCEPTIONS_H

#include <exception>

namespace rs {
namespace scriptobject {

/**
 * The base exception type for libscriptobject
 * @ingroup Exceptions
 */    
class ScriptObjectException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "A ScriptObject exception occurred";
    }
};

/**
 * An exception type thrown when an invalid type cast has been requested
 * @ingroup Exceptions
 */
class TypeCastException final : public ScriptObjectException {
public:
    virtual const char* what() const noexcept override {
        return "A ScriptObject type cast exception occurred";
    }
};

/**
 * An exception type thrown when an unknown source field has been requested
 * @ingroup Exceptions
 */
class UnknownSourceFieldTypeException final : public ScriptObjectException {
public:
    virtual const char* what() const noexcept override {
        return "Unknown ScriptObjectSource field type";
    }
};

/**
 * An exception type thrown when an unknown field has been requested from a script object instance
 * @ingroup Exceptions
 */
class UnknownScriptObjectFieldException final : public ScriptObjectException {
public:
    virtual const char* what() const noexcept override {
        return "Unknown ScriptObject field";
    }
};

/**
 * An exception type thrown when an unknown index (i.e. out of bounds) has been requested from a script array instance
 * @ingroup Exceptions
 */
class UnknownScriptArrayIndexException final : public ScriptObjectException {
public:
    virtual const char* what() const noexcept override {
        return "Unknown ScriptArray index";
    }
};
    
}}

#endif	/* RS_LIBSCRIPTOBJECT_EXCEPTIONS_H */

