//
// Created by Philipp Küst on 20.07.22.
//

//"database" of strings we can use to generate Code

#include <string>

const string includeSpecific = "#include \"<COptionParser.h>\""; //here
const string includeGeneral = "#include <cstring>";
const string nameSpaceStart = "namespace <DHBW> {"; //here
const string end = "}";
const string semicolon = ";";
const string parserStart = "void <COptionParser>::parse(Args args) {"; //here
//2 mal --> bei printHelp und printVersion
const string parserIf = "if (<args.help> && !(<args.version>)) {\n"
                        "            <printHelp>();\n"
                        "        }";
//2 mal --> bei printHelp und printVersion
const string internalMethod = "void <COptionParser>::<ParseXml>() {\n"
                              "}";                          //here
const string startMain = "int main(int argc, char* argv[]) {";
const string usingNamespace = "using namespace <DHBW>;";    //here
const string declareDigitOptind = "int digit_optind = 0;";
const string declareArgs = "Args args;";
const string whileTrue = "while (true) {";
const string startOfWhile = "int c;\n"
                            "int this_option_optind = optind ? optind : 1;\n"
                            "int option_index = 0;"
const string startOfStaticStruct = "static struct option long_options[] = {"
//für alle options ausfüllen
//beim letzten ohne Komma am Ende
//dynamisch generieren, je nach option
//ReqFunc21-24
const string onePartOfStaticStruct = "{\"help\", no_argument, 0,  0 },";   //here
const string declareGetOptLong = "c = getopt_long(argc, argv, \"hv\", long_options, &option_index);";
const string ifGetOptLong = "if (c == -1) {\n"
                            "   break;\n"
                            "}";
const string startOfSwitch = "switch (c) {";
const string startOfCaseLongOpts = "case <0>:";
const string  = "";




