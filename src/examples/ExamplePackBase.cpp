#include "ExamplePackBase.h"

namespace ra_examples
{

ExamplePackBase::ExamplePackBase()
    : examples{ new std::vector<canvas2d_example_ft>() }
    , names{ new std::vector<std::string>() }
    , oss{ new std::ostringstream() }
{
}

ExamplePackBase::~ExamplePackBase()
{
    delete examples;
    delete names;
    delete oss;
}

ExamplePackBase::nameCIterator ExamplePackBase::GetNamesCEnd() const
{
    return names->cend();
}

std::string ExamplePackBase::getName() const
{
    return name;
}

// TODO: provide function name with preprocessor macros ADD + __func__?
void ExamplePackBase::AddExample(canvas2d_example_ft example_func_ptr,
                                 std::string         example_description) const
{
    static unsigned int counter = 1;
    examples->push_back(example_func_ptr);
    *oss << "example_";
    *oss << getName();
    *oss << "_";
    if (counter < 10)
        *oss << "0";
    *oss << counter;
    *oss << "__";
    *oss << example_description;

    std::string fullname = oss->str();

    names->push_back(fullname);

    oss->str(std::string());
    ++counter;
}

ExamplePackBase::exampleCIterator ExamplePackBase::GetExamplesCBegin() const
{
    return examples->cbegin();
}

ExamplePackBase::exampleCIterator ExamplePackBase::GetExamplesCEnd() const
{
    return examples->cend();
}

ExamplePackBase::nameCIterator ExamplePackBase::GetNamesCBegin() const
{
    return names->cbegin();
}

} // namespace ra_examples
