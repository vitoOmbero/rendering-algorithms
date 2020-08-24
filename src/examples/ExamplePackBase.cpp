#include "ExamplePackBase.h"

namespace ra_examples
{

ExamplePackBase::ExamplePackBase()
    : examples{ new std::vector<canvas2d_example_ft>() }
    , names{ new std::vector<std::string_view>() }
{
}

ExamplePackBase::~ExamplePackBase()
{
    delete examples;
    delete names;
}

ExamplePackBase::nameCIterator ExamplePackBase::GetNamesCEnd() const
{
    return names->cend();
}

void ExamplePackBase::AddExample(canvas2d_example_ft example_func_ptr,
                                 std::string_view    example_description) const
{
    // TODO: provide function name with compiler detection for every example
    // with macros?
    examples->push_back(example_func_ptr);
    names->push_back(example_description);
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
