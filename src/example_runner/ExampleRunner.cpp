#include "ExampleRunner.h"
#include "TerminalCanvas2dViewer.h"

ExampleRunner::ExampleRunner()
    : actualCanvas2dViewer{ *new TerminalCanvas2dViewer() }
{
}

ExampleRunner::~ExampleRunner() {}

void ExampleRunner::UseCanvas2dViewer(Canvas2dViewerInterface& cv)
{
    actualCanvas2dViewer = cv;
}

void ExampleRunner::Run(ra_examples::ExamplePackBase& expack)
{
    using namespace ra_examples;

    std::pair<ExamplePackBase::exampleCIterator, ExamplePackBase::nameCIterator>
        beginPair(expack.GetExamplesCBegin(), expack.GetNamesCBegin());
    std::pair<ExamplePackBase::exampleCIterator, ExamplePackBase::nameCIterator>
        endPair(expack.GetExamplesCEnd(), expack.GetNamesCEnd());

    for (auto i = beginPair; i != endPair; ++i.first, ++i.second)
    {
        auto result = (*i.first)();
        auto name   = *i.second;
        actualCanvas2dViewer.ViewResult(result, name);
    }
}
