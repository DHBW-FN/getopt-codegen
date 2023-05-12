# Code Generator for Evaluating Command Line Arguments
This repository contains a code generator that creates a class for evaluating command line arguments based on options specified in an XML configuration file. The configuration file includes information such as the author, examples, descriptions, and locations.

The generated class can be either directly instantiable or abstract, depending on the options specified in the configuration file. The formatting of the generated header and source files is not part of the program design, but can be done using the command line program astyle.

The main function is not included in the code generation, and an instance of the generated class must be created in the application to evaluate the options using a function for reading them.

If an abstract element is present in the generated class, it must be derived in the target application and the abstract method implemented.
