#include <phpcpp.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <xls.h>
#include "XlsReader.h"

using namespace xls;
using namespace std;
class Xavxls : public Php::Base {
    public:
        Xavxls()
        {
            
            
        }
        Php::Value setfilename(Php::Parameters &params)
        {
            std::string var1 = params[0];
            const char *characterSet= params[1];
            WB=new WorkBook(var1,0,characterSet);
            return true;
        }
        void inititerator(Php::Parameters &params)
        {
            int p=params[0];
            uint32_t sheetnum=(uint32_t)p;
            WB->InitIterator(sheetnum);
        }
        void savecsvfile(Php::Parameters &params);
        Php::Value getversion()
        {
            return WB->GetLibraryVersion();
        }
        Php::Value getsheetname(Php::Parameters &params)
        {
            int p=params[0];
            uint32_t sheetnum=(uint32_t)p;
            return WB->GetSheetName(sheetnum);
        }
        Php::Value getsheetvisible(Php::Parameters &params)
        {
            int p=params[0];
            uint32_t sheetnum=(uint32_t)p;
            return WB->GetSheetVisible(sheetnum);
        }
        Php::Value getsheetcount()
        {
            return (int)WB->GetSheetCount();
        }
        Php::Value GetRowCount(Php::Parameters &params)
        {
            int p=params[0];
            uint32_t sheetnum=(uint32_t)p;
            return (int)WB->GetRowCount(sheetnum);
        }
        Php::Value GetColCount(Php::Parameters &params)
        {   
            int p=params[0];
            uint32_t sheetnum=(uint32_t)p;
            return (int)WB->GetColCount(sheetnum);
        }
        Php::Value GetCell(Php::Parameters &params)
        {   
            int w=params[0];
            uint32_t workSheetIndex=(uint32_t)w;
            int r=params[1];
            uint32_t row=(uint32_t)r;
            int c=params[2];
            uint32_t col=(uint32_t)c;
            cellContent content=WB->GetCell(workSheetIndex,  row, col);
            return content.str.c_str();
        }
    private:
        WorkBook *WB;
};

/**
 *  tell the compiler that the get_module is a pure C function
 */
extern "C" {
    
    /**
     *  Function that is called by PHP right after the PHP process
     *  has started, and that returns an address of an internal PHP
     *  strucure with all the details and features of your extension
     *
     *  @return void*   a pointer to an address that is understood by PHP
     */
    PHPCPP_EXPORT void *get_module() 
    {
        // static(!) Php::Extension object that should stay in memory
        // for the entire duration of the process (that's why it's static)
        static Php::Extension extension("Xavxls", "0.1");
        Php::Class<Xavxls> customClass("Xavxls");
        
        // add methods to it
        customClass.method<&Xavxls::getsheetcount>("getsheetcount");
        customClass.method<&Xavxls::getsheetcount>("getversion");
        customClass.method<&Xavxls::setfilename>("setfilename", {
            Php::ByVal("filename", Php::Type::String),
            Php::ByVal("string", Php::Type::String)
        });
        customClass.method<&Xavxls::inititerator>("inititerator", {
            Php::ByVal("i", Php::Type::Numeric)
        });
        customClass.method<&Xavxls::getsheetname>("getsheetname", {
            Php::ByVal("i", Php::Type::Numeric)
        });
        customClass.method<&Xavxls::GetRowCount>("GetRowCount", {
            Php::ByVal("i", Php::Type::Numeric)
        });
        customClass.method<&Xavxls::GetColCount>("GetColCount", {
            Php::ByVal("i", Php::Type::Numeric)
        });
        customClass.method<&Xavxls::GetCell>("GetCell", {
            Php::ByVal("wordindex", Php::Type::Numeric),
            Php::ByVal("row", Php::Type::Numeric),
            Php::ByVal("col", Php::Type::Numeric),
        });

        
        // add the class to the extension
        extension.add(customClass);
        // @todo    add your own functions, classes, namespaces to the extension
        
        // return the extension
        return extension;
    }
}
