#include <iostream>
#include <iomanip>

#include <Index.h>
#include "ClangUtil.h"

using namespace std;

string path = "";
string className = "";

CXChildVisitResult visitor(CXCursor cursor, CXCursor parent,
    CXClientData clientData)
{
    //
    // For now, only want to process the main file of interest...
    //
    //if ( !clang_Location_isFromMainFile(clang_getCursorLocation(cursor)) )
        //return CXChildVisit_Continue;

    string cursorSpelling = toStdString(cursor);

    CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
    CXSourceRange range = clang_getCursorExtent(cursor);

    if ( cursor.kind == CXCursor_ClassDecl )
    {
        if ( className == "" || className == cursorSpelling )
        {
            cout << "Found class " << cursorSpelling << endl;

            //
            // Now we'll tokenize the range, which encompasses the whole class,
            // and annotate it.
            //
            CXToken* tokens = 0;
            unsigned int numTokens;
            clang_tokenize(tu, range, &tokens, &numTokens);

            CXCursor cursors[numTokens];
            clang_annotateTokens(tu, tokens, numTokens, cursors);
    
            cout << std::left << setw(18) << "Token" << setw(18) << "Cursor" << setw(25) <<
                "Cursor Kind"  << setw(24) << "Cursor Type" << endl;
            cout << "=================================================================================" <<
                endl;
            for ( unsigned int idx=0; idx<numTokens; ++idx )
            {
                CXType type = clang_getCursorType(cursors[idx]);
                string cursorSpelling = toStdString(cursors[idx]);
                string tokenSpelling = toStdString(tokens[idx], tu);
                string typeSpelling = toStdString(type);
                cout << std::left << setw(18) << tokenSpelling << setw(18) << cursorSpelling << 
                    setw(25) << toStdString(cursors[idx].kind) << setw(24) <<  typeSpelling << endl;
            }
            if ( numTokens > 0 )
                cout << endl << endl;
        }
    }

    return CXChildVisit_Continue;
}

int
main(int argc, char** argv)
{
    if ( argc < 2 || argc > 3 )
    {
        cerr << "Usage: ClangAutomation <path to header file> [class name]" << endl;
        return 1;
    }

    path = string(argv[1]);
    if ( argc == 3 )
    {
        className = string(argv[2]);
    }

    const char* args[] = { "-c", "-x", "c++", "-D", "MYEXPORTDECL=", "-D", "slots=", "-D", "signals=public", "-D", "Q_OBJECT=", "-D", "Q_PROPERTY(...)=", "-I", "/usr/local/Trolltech/Qt-4.8.5/include", "-I", "/usr/local/Trolltech/Qt-4.8.5/include/QtCore" };

    CXIndex index = clang_createIndex(0,0);

    CXTranslationUnit TU = clang_parseTranslationUnit(index,
        "example.h", args, 17, 0, 0,
                CXTranslationUnit_None);

    CXCursor startCursor = clang_getTranslationUnitCursor(TU);
    clang_visitChildren(startCursor, visitor, 0);

}
