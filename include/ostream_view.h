#pragma once
#include "shapes.h"
#include "model.h"
#include <ostream>

namespace OTUS
{


class OstreamView: public IObserver, public std::enable_shared_from_this<OstreamView>
{
    public:
    static std::shared_ptr<OstreamView> create(Model* model, std::ostream& out)
    {
        auto ptr =  std::shared_ptr<OstreamView>{new OstreamView(out)};
        ptr->setModel(model);
        return ptr;
    }
    std::ostream& outstream()
    {
        return m_out;
    }
    void update() override
    {
        OstreamViewVisitor visitor(m_out);
        m_out << "===== Start of scene drawing =====" << std::endl;
        m_model->walk(&visitor);
        m_out << "===== End of scene drawing =====" << std::endl;
    }
    private:

    class OstreamViewVisitor: public IDrawVisitor
    {
        public:
        OstreamViewVisitor(std::ostream& out): m_out(out) {}
        virtual void visit(const Point * point) override
        {
            m_out << "Point " << point->coords() << std::endl;
        }
        virtual void visit(const Line* line) override
        {
            m_out << "Line " << line->coords() << std::endl;
        }
        private:
        std::ostream& m_out;  
    };


    void setModel(Model* m)
    {
        m_model = m;
        m->subscribe(shared_from_this());
    }
    OstreamView(std::ostream & out): m_out(out){}
    std::ostream& m_out;
    Model* m_model;
};


}