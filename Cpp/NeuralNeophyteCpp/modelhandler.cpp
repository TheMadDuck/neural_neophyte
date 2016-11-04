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
