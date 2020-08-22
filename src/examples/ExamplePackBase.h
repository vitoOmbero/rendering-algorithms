#ifndef EXAMPLEPACKBASE_H
#define EXAMPLEPACKBASE_H

#include <string>
#include <vector>

#include "examples_types.h"

namespace ra_examples
{

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
    std::vector<canvas2d_example_ft>* examples;
    std::vector<std::string_view>*    names;
};
} // namespace ra_examples
#endif // EXAMPLEPACKBASE_H
