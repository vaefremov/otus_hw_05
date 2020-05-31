#pragma once
#include "shapes.h"
#include "model.h"
#include <ostream>
#include <string>
#include <exception>

namespace OTUS
{

class OstreamView: public IObserver, public std::enable_shared_from_this<OstreamView>
{
    public:
    static std::shared_ptr<OstreamView> create(std::string const& name, Model* model, std::ostream& out)
    {
        if(model == nullptr)
        {
            throw std::invalid_argument("Invalid model");
        }
        auto ptr =  std::shared_ptr<OstreamView>{new OstreamView(name, out)};
        ptr->setModel(model);
        return ptr;
    }
    virtual ~OstreamView() = default;
    virtual void update() override;

    private:

    class OstreamViewVisitor: public IDrawVisitor
    {
        public:
        OstreamViewVisitor(std::ostream& out): m_out(out) {}
        virtual void visit(const Point * point) override;
        virtual void visit(const Line* line) override;
        private:
        std::ostream& m_out;  
    };

    void setModel(Model* m)
    {
        m_model = m;
        m->subscribe(shared_from_this());
    }
    OstreamView(std::string const& name, std::ostream & out): m_out(out), m_name(name){}
    std::ostream& m_out;
    Model* m_model;
    std::string m_name;
};

}