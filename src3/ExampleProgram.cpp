#include "ExampleProgram.h"

// Constructor
ExampleProgram::ExampleProgram() {
    this->extendedGeneratedCode = new ExtendedGeneratedCode();
}

// Getter
ExtendedGeneratedCode *ExampleProgram::getExtendedGeneratedCode() {
    return extendedGeneratedCode;
}

//check if option "exclusion" was set
void checkExclusion(ExampleProgram ep){
    if(ep.getExtendedGeneratedCode()->isSetExclusion()){
        printf("The option 'exclusion' was called --> isSetExclusion=true\n");
    } else {
        printf("The option 'exclusion' was not called --> isSetExclusion=false\n");
    }
}

//check if option "arguments" was set
void checkArguments(ExampleProgram ep){
    if(ep.getExtendedGeneratedCode()->isSetArguments()){
        printf("The option 'arguments' was called --> isSetExclusion=true\n");
        printf("The argument is: %d\n", ep.getExtendedGeneratedCode()->getValueOfArguments());
    } else {
        printf("The option 'arguments' was not called --> isSetExclusion=false\n");
    }
}

//--optional=27
//-o27
//check if option "arguments" was set
void checkOptional(ExampleProgram ep){
    if(ep.getExtendedGeneratedCode()->isSetOptional()){
        printf("The option 'optional' was called --> isSetOptional=true\n");
        printf("The argument is: %d\n", ep.getExtendedGeneratedCode()->getValueOfOptional());
    } else {
        printf("The option 'optional' was not called --> isSetOptional=false\n");
    }
}

int main(int argc, char* argv[] ) {
    ExampleProgram exampleProgram = ExampleProgram();
    exampleProgram.getExtendedGeneratedCode()->parseOptions(argc, argv);

    checkExclusion(exampleProgram);
    checkArguments(exampleProgram);
    checkOptional(exampleProgram);

    return 0;
}