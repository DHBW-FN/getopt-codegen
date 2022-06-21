#ifndef CODEGENERATOR_GETOPTSETUP_H
#define CODEGENERATOR_GETOPTSETUP_H


#include "Author.h"
#include "Option.h"
#include <vector>

class GetOptSetup {
public:
    // Constructors
    GetOptSetup();

    // Getters
    const Author &getAuthor() const;
    const string &getHeaderFileName() const;
    const string &getSourceFileName() const;
    const string &getNamespaceName() const;
    const string &getClassName() const;
    const vector<string> &getOverAllDescriptions() const;
    const vector<string> &getSampleUsages() const;
    const vector<Option> &getOptions() const;

    // Setters
    void setAuthor(const Author &author);
    void setHeaderFileName(const string &headerFileName);
    void setSourceFileName(const string &sourceFileName);
    void setNamespaceName(const string &namespaceName);
    void setClassName(const string &className);
    void setOverAllDescriptions(const vector<string> &overAllDescriptions);
    void setSampleUsages(const vector<string> &sampleUsages);
    void setOptions(const vector<Option> &options);

    // Adders
    void addOverAllDescription(const string &overAllDescription);
    void addSampleUsage(const string &sampleUsage);
    void addOption(const Option &option);

private:
    /**
     * @brief author
     * Author of the program.
     */
    Author author;
    /**
     * @brief headerFileName
     * Name of the header file.
     */
    string headerFileName;
    /**
     * @brief sourceFileName
     * Name of the source file.
     */
    string sourceFileName;
    /**
     * @brief namespaceName
     * Name of the namespace.
     */
    string namespaceName;
    /**
     * @brief className
     * Name of the class.
     */
    string className;
    /**
     * @brief overAllDescriptions
     * Description of the program.
     */
    vector<string> overAllDescriptions;
    /**
     * @brief sampleUsages
     * Sample usages of the program.
     */
    vector<string> sampleUsages;
    /**
     * @brief options
     * Options of the program.
     */
    vector<Option> options;
};


#endif //CODEGENERATOR_GETOPTSETUP_H
