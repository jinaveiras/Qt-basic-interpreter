#ifndef EEXECABORTED_H
#define EEXECABORTED_H

#include <string>
#include <stdexcept>

using namespace std;

/// Excepción que se lanza cuando se aborta la ejecución del programa
class EExecAborted : public runtime_error
{
    public:
        EExecAborted() : runtime_error("Ejecución abortada") {};
    private:
};

#endif // EEXECABORTED_H
