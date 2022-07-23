#include "ExampleProgram.h"
#include "generatedCode.h"

/**
 * @brief Constructor, that generates a object of ExtendedGeneratedCode
 */
ExampleProgram::ExampleProgram(GC::GeneratedClass *generatedClass) {
    this->generatedClass = generatedClass;
}

/**
 * @brief Getter for generatedClass
 * @return object of class ExtendedGeneratedCode
 */
GC::GeneratedClass *ExampleProgram::getExtendedGeneratedCode() {
    return generatedClass;
}


/**
 * @brief prints in command line if option 'exclusion' was set
 * @param ep object of class ExampleProgram
 */
void checkExclusion(ExampleProgram ep){
    if(ep.getExtendedGeneratedCode()->isSetExclusion()){
        printf("The option 'exclusion' was called --> isSetExclusion=true\n");
    } else {
        printf("The option 'exclusion' was not called --> isSetExclusion=false\n");
    }
}

/**
 * @brief prints in command line if option 'arguments' was set and depending on it the argument
 * @param ep object of class ExampleProgram
 */
void checkArguments(ExampleProgram ep){
    if(ep.getExtendedGeneratedCode()->isSetArguments()){
        printf("The option 'arguments' was called --> isSetExclusion=true\n");
        printf("The argument is: %d\n", ep.getExtendedGeneratedCode()->getValueOfArguments());
    } else {
        printf("The option 'arguments' was not called --> isSetExclusion=false\n");
    }
}

/**
 * @brief prints in command line if option 'arguments' was set and depending on it the argument
 * @param ep object of class ExampleProgram
 */
void checkOptional(ExampleProgram ep){
    if(ep.getExtendedGeneratedCode()->isSetOptional()){
        printf("The option 'optional' was called --> isSetOptional=true\n");
        printf("The argument is: %d\n", ep.getExtendedGeneratedCode()->getValueOfOptional());
    } else {
        printf("The option 'optional' was not called --> isSetOptional=false\n");
    }
}

/**
 * @brief Generates object of class ExampleProgram, calls parseOptions and checks which options were set
 * @param argc amount of arguments
 * @param argv array of arguments
 */
int main(int argc, char* argv[] ) {
    ExampleProgram exampleProgram = ExampleProgram(new ExtendedGeneratedCode());
    exampleProgram.getExtendedGeneratedCode()->parseOptions(argc, argv);

    checkExclusion(exampleProgram);
    checkArguments(exampleProgram);
    checkOptional(exampleProgram);

    return 0;
}