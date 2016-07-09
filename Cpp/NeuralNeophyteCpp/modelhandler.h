#ifndef MODELHANDLER_H
#define MODELHANDLER_H
#include <string>

class ModelHandler
{
public:
    ModelHandler();
    int loadBestModel(std::string gameName);
};

#endif // MODELHANDLER_H
