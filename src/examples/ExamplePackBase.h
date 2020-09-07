#ifndef EXAMPLEPACKBASE_H
#define EXAMPLEPACKBASE_H

#include <sstream>
#include <string>
#include <vector>

#include "examples_types.h"

namespace ra_examples
{

/**
 * @brief The ExamplePackBase class - to be inherited by all ExamplePacks
 * @details Base class provides references to example routines for ExampleRunner
 * via const iterators.
 */
class ExamplePackBase
{
public:
    ExamplePackBase();

    virtual ~ExamplePackBase();

    typedef std::vector<canvas2d_example_ft>::const_iterator exampleCIterator;
    typedef std::vector<std::string>::const_iterator         nameCIterator;

    exampleCIterator GetExamplesCBegin() const;
    exampleCIterator GetExamplesCEnd() const;
    nameCIterator    GetNamesCBegin() const;
    nameCIterator    GetNamesCEnd() const;

    virtual std::string getName() const;

protected:
    /**
     * @brief AddExample - must be called from child class constuctor
     * @param example_func_ptr - pointer to function (it can be free) with
     * example
     * @param example_description - name for example
     */
    void AddExample(canvas2d_example_ft exampleFuncPtr,
                    std::string         exampleDescription) const;

    /**
     * @brief name - viewable name of pack will be added to the example samples
     * names
     */
    std::string name;

private:
    std::vector<canvas2d_example_ft>* examples;
    std::vector<std::string>*         names;
    std::ostringstream*               oss;
};
} // namespace ra_examples
#endif // EXAMPLEPACKBASE_H
