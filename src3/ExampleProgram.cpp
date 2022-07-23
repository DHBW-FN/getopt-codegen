#include "ExampleProgram.h"

// Constructor
ExampleProgram::ExampleProgram() {
    this->extendedGeneratedCode = new ExtendedGeneratedCode();
}

// Getter
ExtendedGeneratedCode *ExampleProgram::getExtendedGeneratedCode() {
    return extendedGeneratedCode;
}

void checkExclusion(ExampleProgram ep){
    if(ep.getExtendedGeneratedCode()->isSetExclusion()){
        printf("The option 'exclusion' was called --> isSetExclusion=true");
    } else {
        printf("The option 'exclusion' was not called --> isSetExclusion=false");
    }
}

int main(int argc, char* argv[] ) {
    ExampleProgram exampleProgram = ExampleProgram();
    exampleProgram.getExtendedGeneratedCode()->parseOptions(argc, argv);

    checkExclusion(exampleProgram);

    return 0;
}