#include <iostream>
#include "model.h"
#include "ostream_view.h"

int main()
{
    std::cout << "VectEdit" << std::endl;
    // OTUS::Model m;
    std::unique_ptr<OTUS::Model> pm = std::make_unique<OTUS::Model>();
    auto pPt = pm->createPoint(OTUS::DPoint<>(1, 2));
    auto pLn = pm->createLine(OTUS::DPoint<>(1, 1), OTUS::DPoint<>(3, 4));
    std::cout << pPt->coords() << std::endl;
    std::cout << pLn->coords() << std::endl;

    auto v = OTUS::OstreamView::create(pm.get(), std::cout);
    v->update();
    auto pLn2 = pm->createLine(OTUS::DPoint<>(10, 10), OTUS::DPoint<>(20, 20));
}
