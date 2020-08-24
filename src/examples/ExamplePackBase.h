#ifndef EXAMPLEPACKBASE_H
#define EXAMPLEPACKBASE_H

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

    ~ExamplePackBase();

    typedef std::vector<canvas2d_example_ft>::const_iterator exampleCIterator;
    typedef std::vector<std::string_view>::const_iterator    nameCIterator;

    exampleCIterator GetExamplesCBegin() const;
    exampleCIterator GetExamplesCEnd() const;
    nameCIterator    GetNamesCBegin() const;
    nameCIterator    GetNamesCEnd() const;

protected:
    /**
     * @brief AddExample - must be called from child class constuctor
     * @param example_func_ptr - pointer to function (it can be free) with
     * example
     * @param example_description - name for example
     */
    void AddExample(canvas2d_example_ft exampleFuncPtr,
                    std::string_view    exampleDescription) const;

private:
    std::vector<canvas2d_example_ft>* examples;
    std::vector<std::string_view>*    names;
};
} // namespace ra_examples
#endif // EXAMPLEPACKBASE_H
