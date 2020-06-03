#include <string>
#include "utilities.h"

std::ostream& OTUS::operator<<(std::ostream& out, OTUS::Colour c)
{
    out << ColourName(c);
    return out;
}
