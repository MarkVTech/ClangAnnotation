#ifndef _CLANG_UTIL_H_
#define _CLANG_UTIL_H_

#include <ostream>
#include <string>

#include <Index.h>

struct LocationInfo
{
    LocationInfo() :
        filePath(""),
        line(0),
        column(0),
        offset(0)
    {
    }

    LocationInfo(const std::string& _filePath, unsigned int _line,
           unsigned int _column, unsigned int _offset) :
        filePath(_filePath),
        line(_line),
        column(_column),
        offset(_offset)
    {
    }

    std::string filePath;
    unsigned int line;
    unsigned int column;
    unsigned int offset;
};

std::ostream& operator<<(std::ostream& stream, const LocationInfo& location);

std::string getClangString(CXString cxstr);

LocationInfo getLocationInfo(const CXCursor& cursor);

std::string toStdString(CXString str);

std::string toStdString(CXCursor cursor);

std::string toStdString(CXToken token, CXTranslationUnit tu);

std::string toStdString(CXCursorKind kind);

std::string toStdString(CXType type);

LocationInfo getLocationInfo(const CXSourceLocation& location);

#endif
