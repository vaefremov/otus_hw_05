#include <exception>
#include <iostream>
#include "controller.h"

using namespace OTUS;

void BaseController::drawPoint(DPoint<> const & pt)
{
    switch (m_state)
    {
    case ControllerState::DEFAULT:
        m_model->createPoint(pt);
        break;
    case ControllerState::LINE:
        m_model->createLine(m_prevPoint, pt);
        m_state = ControllerState::DEFAULT;
        break;
    
    default:
        throw std::runtime_error("Invalid controller state");
    }
}

void BaseController::startDrawingLine(DPoint<> const & pt)
{
    m_prevPoint = pt;
    m_state = ControllerState::LINE;
}

void BaseController::deleteShapesUnder(DPoint<> const & pt)
{
    // Find the colliding IDs
    for(auto c:m_model->findCollisions(pt))
    {
        m_model->deleteByID(c);
    }
    // delete them
}

void BaseController::setColour(DPoint<> const & pt, Colour c)
{
    for(auto cl:m_model->findCollisions(pt))
    {
        m_model->setColourById(cl, c);
    }
}

void BaseController::loadFromStream(std::istream& in)
{
    std::cerr << "loadFromStream: Not yet implemented!\n";
}

void BaseController::writeToStream(std::ostream& out)
{
    out << "writeToStream: Not yet implemented!\n";
}