#include "ostream_view.h"

using namespace OTUS;

void OstreamView::update()
{
    OstreamViewVisitor visitor(m_out);
    m_out << m_name << " [" << std::endl;
    m_model->walk(&visitor);
    m_out << "]" << std::endl;
}

void OstreamView::OstreamViewVisitor::visit(const Point * point)
{
    m_out << point->colour() <<  " Point " << point->coords() << std::endl;
}

void OstreamView::OstreamViewVisitor::visit(const Line* line)
{
    m_out <<  line->colour() << " Line " << line->coords() << std::endl;
}