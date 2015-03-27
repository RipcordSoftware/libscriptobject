#ifndef RS_LIBSCRIPTOBJECT_EXCEPTIONS_H
#define RS_LIBSCRIPTOBJECT_EXCEPTIONS_H

#include <exception>

namespace rs {
namespace scriptobject {
    
class ScriptObjectException : public std::exception {
public:
    virtual const char* what() const noexcept override {
        return "A ScriptObject exception occurred";
    }
};

class TypeCastException : public ScriptObjectException {
public:
    virtual const char* what() const noexcept override {
        return "A ScriptObject type cast exception occurred";
    }
};

class UnknownSourceFieldTypeException : public ScriptObjectException {
public:
    virtual const char* what() const noexcept override {
        return "Unknown ScriptObjectSource field type";
    }
};

class UnknownScriptObjectFieldException : public ScriptObjectException {
public:
    virtual const char* what() const noexcept override {
        return "Unknown ScriptObject field";
    }
};

class UnknownScriptArrayIndexException : public ScriptObjectException {
public:
    virtual const char* what() const noexcept override {
        return "Unknown ScriptObject field index";
    }
};
    
}}

#endif	/* RS_LIBSCRIPTOBJECT_EXCEPTIONS_H */

