#include "ExampleRunner.h"
#include "TerminalCanvas2dViewer.h"

ExampleRunner::ExampleRunner(Canvas2dViewerInterface& cv)
    : actual_canvas2d_viewer_{ cv }
{
}

void ExampleRunner::UseCanvas2dViewer(Canvas2dViewerInterface& cv)
{
    actual_canvas2d_viewer_ = cv;
}

void ExampleRunner::Run(ra_examples::ExamplePackBase& expack)
{
    using namespace ra_examples;

    std::pair<ExamplePackBase::ExampleCIterator, ExamplePackBase::NameCIterator>
        beginPair(expack.getExamplesCBegin(), expack.getNamesCBegin());
    std::pair<ExamplePackBase::ExampleCIterator, ExamplePackBase::NameCIterator>
        endPair(expack.getExamplesCEnd(), expack.getNamesCEnd());

    for (auto i = beginPair; i != endPair; ++i.first, ++i.second)
    {
        auto result = (*i.first)();
        auto name   = *i.second;
        actual_canvas2d_viewer_.ViewResult(result, name);
    }
}
