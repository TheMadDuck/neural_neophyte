/*   Copyright (C) 2016 by Daniel M.H. Noll                                *
 *   Author: Daniel Noll                                                   *
 *                                                                         *
 *   Email: sport.mann@gmx.de                                              *
 *                                                                         *
 *                                                                         *
 *                                                                         *
 * Redistribution and use in source and binary forms, with or without      *
 * modification, are permitted provided that the following conditions are  *
 *  met:                                                                   *
 *                                                                         *
 *     * Redistributions of source code must retain the above copyright    *
 *       notice, this list of conditions and the following disclaimer.     *
 *     * Redistributions in binary form must reproduce the above copyright *
 *       notice, this list of conditions and the following disclaimer in   *
 *       the documentation and/or other materials provided with            *
 *       the distribution.                                                 *
 *     * Neither the name of the author nor the names of its contributors  *
 *       may be used to endorse or promote products derived from this      *
 *       software without specific prior written permission.               *
 *                                                                         *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       *
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   *
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    *
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        *
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   *
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   *
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     *
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   *
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    *
 ***************************************************************************/

#include "modelhandler.h"

ModelHandler::ModelHandler()
{
}

std::vector<std::string> ModelHandler::folderHandler(std::string gameName)
{
    // http://stackoverflow.com/questions/18100097/portable-way-to-check-if-directory-exists-windows-linux-c
    struct stat info;
    if( stat( gameName.c_str(), &info ) != 0 )
        std::cout << "cannot access " << gameName << std::endl;
        //printf( "cannot access %s\n", gameName );
    else if( info.st_mode & S_IFDIR )  // S_ISDIR() doesn't exist on my windows
        std::cout << "cannot access " << gameName << std::endl;
        //printf( "%s is a directory\n", gameName );
    else
        std::cout << "cannot access " << gameName << std::endl;
        //printf( "%s is no directory\n", gameName );


    /*
    // http://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
    inline bool exists_test0 (const std::string& name) {
        ifstream f(name.c_str());
        return f.good();
    }

    inline bool exists_test1 (const std::string& name) {
        if (FILE *file = fopen(name.c_str(), "r")) {
            fclose(file);
            return true;
        } else {
            return false;
        }
    }

    inline bool exists_test2 (const std::string& name) {
        return ( access( name.c_str(), F_OK ) != -1 );
    }

    inline bool exists_test3 (const std::string& name) {
      struct stat buffer;
      return (stat (name.c_str(), &buffer) == 0);
    }
    */

}

int ModelHandler::loadBestModel(LogisticSgd classifier, std::string gameName)
{
    return -2;  // only for testing purpose. should be removed!
    std::vector<std::string> filePaths = folderHandler(gameName);
    if(filePaths.size() != 0){  // TESTEN!
        std::cout << "best model exist" << std::endl;
        for(auto path: filePaths){
            //classifier.loadBestModel(path);
        }
        return filePaths.size(); //???
    }
    else{
        return 0;
    }
}
