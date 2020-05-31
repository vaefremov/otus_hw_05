#pragma once
#include <istream>
#include <exception>
#include "utilities.h"
#include "model.h"


namespace OTUS
{

enum class ControllerState
{
    DEFAULT, LINE
};

class BaseController
{
    public:
    explicit BaseController(Model* m): m_model(m) {}
    virtual ~BaseController() = default;
    virtual void drawPoint(DPoint<> const & pt);
    virtual void startDrawingLine(DPoint<> const & pt);
    virtual void deleteShapesUnder(DPoint<> const & pt);
    virtual void setColour(DPoint<> const & pt, Colour c);
    virtual void loadFromStream(std::istream& in);
    virtual void writeToStream(std::ostream& out);
    protected:
    Model* m_model;
    ControllerState m_state = ControllerState::DEFAULT;
    DPoint<> m_prevPoint;
};
    
} // namespace OTUS
