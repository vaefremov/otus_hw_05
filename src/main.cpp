#include <iostream>
#include <sstream>
#include "model.h"
#include "ostream_view.h"
#include "controller.h"

int main()
{
    OTUS::Model m;
    auto v = OTUS::OstreamView::create("OStreamView", &m, std::cout);
    OTUS::BaseController c(&m);
    // Load from stream object
    std::stringstream ssin("");
    c.loadFromStream(ssin);
    
    // Draw a single point
    c.drawPoint(OTUS::DPoint<>(1, 2));

    // Draw a line with misslepoint at (150, 150)
    c.startDrawingLine(OTUS::DPoint<>(100, 100));
    c.drawPoint(OTUS::DPoint<>(200, 200));

    // Change colour of the line to red
    c.setColour(OTUS::DPoint<>(150, 150), OTUS::Colour::RED);

    // Delete the point
    c.deleteShapesUnder(OTUS::DPoint<>(1, 2));

    // Delete the line
    c.deleteShapesUnder(OTUS::DPoint<>(150, 150));

    // Output to stream
    c.writeToStream(std::cout);
}
