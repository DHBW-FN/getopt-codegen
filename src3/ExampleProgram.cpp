#include "ExampleProgram.h"

// Constructor
ExampleProgram::ExampleProgram() {
    this->extendedGeneratedCode = new ExtendedGeneratedCode();
}

// Getter
ExtendedGeneratedCode *ExampleProgram::getExtendedGeneratedCode() {
    return extendedGeneratedCode;
}

int main(int argc, char* argv[] ) {
    ExampleProgram exampleProgram = ExampleProgram();
    exampleProgram.getExtendedGeneratedCode()->parseOptions(argc, argv);
    return 0;
}