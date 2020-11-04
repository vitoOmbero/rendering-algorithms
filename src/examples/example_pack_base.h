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

    typedef std::vector<Canvas2dExampleFunction>::const_iterator
                                                     ExampleCIterator;
    typedef std::vector<std::string>::const_iterator NameCIterator;

    [[nodiscard]] ExampleCIterator getExamplesCBegin() const;
    [[nodiscard]] ExampleCIterator getExamplesCEnd() const;
    [[nodiscard]] NameCIterator    getNamesCBegin() const;
    [[nodiscard]] NameCIterator    getNamesCEnd() const;

    [[nodiscard]] virtual std::string getName() const;

protected:
    /**
     * @brief AddExample - must be called from child class constuctor
     * @param example_func_ptr - pointer to function (it can be free) with
     * example
     * @param example_description - name for example
     */
    void AddExample(Canvas2dExampleFunction exampleFuncPtr,
                    const std::string&         exampleDescription) const;

    /**
     * @brief name - viewable name of pack will be added to the example samples
     * names
     */
    std::string name_;

private:
    std::vector<Canvas2dExampleFunction>* examples_;
    std::vector<std::string>*             names_;
    std::ostringstream*                   oss_;
};
} // namespace ra_examples
#endif // EXAMPLEPACKBASE_H
