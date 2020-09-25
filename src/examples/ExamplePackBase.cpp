#include "ExamplePackBase.h"

namespace ra_examples
{

ExamplePackBase::ExamplePackBase()
    : examples_{ new std::vector<Canvas2dExampleFunction>() }
    , names_{ new std::vector<std::string>() }
    , oss_{ new std::ostringstream() }
{
}

ExamplePackBase::~ExamplePackBase()
{
    delete examples_;
    delete names_;
    delete oss_;
}

ExamplePackBase::NameCIterator ExamplePackBase::getNamesCEnd() const
{
    return names_->cend();
}

std::string ExamplePackBase::getName() const
{
    return name_;
}

// TODO: provide function name with preprocessor macros ADD + __func__?
void ExamplePackBase::AddExample(Canvas2dExampleFunction example_func_ptr,
                                 std::string         example_description) const
{
    static unsigned int counter = 1;
    examples_->push_back(example_func_ptr);
    *oss_ << "example_";
    *oss_ << getName();
    *oss_ << "_";
    if (counter < 10)
        *oss_ << "0";
    *oss_ << counter;
    *oss_ << "__";
    *oss_ << example_description;

    std::string fullname = oss_->str();

    names_->push_back(fullname);

    oss_->str(std::string());
    ++counter;
}

ExamplePackBase::ExampleCIterator ExamplePackBase::getExamplesCBegin() const
{
    return examples_->cbegin();
}

ExamplePackBase::ExampleCIterator ExamplePackBase::getExamplesCEnd() const
{
    return examples_->cend();
}

ExamplePackBase::NameCIterator ExamplePackBase::getNamesCBegin() const
{
    return names_->cbegin();
}

} // namespace ra_examples
