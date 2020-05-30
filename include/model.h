#pragma once
#include <vector>
#include <map>
#include <list>
#include <memory>

#include "shapes.h"

namespace OTUS
{

class IObserver 
{
    public:
    virtual ~IObserver() = default;
    virtual void update() = 0;

};

class IObservable 
{
    public:
    virtual ~IObservable() = default;
    virtual void subscribe(std::shared_ptr<IObserver> const&) = 0;
};


class BaseObservable : public IObservable {
public:
    void subscribe(const std::shared_ptr<IObserver>& obs) override {
        m_subscribers.emplace_back(obs);
    }

    void notify() {
        auto iter = std::begin(m_subscribers);
        while(iter != std::end(m_subscribers)) {
            auto ptr = iter->lock();
            if (ptr) {
                ptr->update();
                ++iter;
            } else {
                m_subscribers.erase(iter++);
            }
        }
    }
private:
    std::list<std::weak_ptr<IObserver>> m_subscribers;
};


class Model: public BaseObservable
{
    public:
    Model() = default;
    ~Model() = default;
    Point const* createPoint(DPoint<> const& pt)
    {
        auto pt_ptr = new Point(pt);
        std::unique_ptr<BaseShape> up(pt_ptr);

        // auto p = std::pair<size_t, std::unique_ptr<BaseShape>>(m_id++, up);
        // // m_elements.emplace(p);
        // m_elements[m_id++] = up;
        m_elements.emplace_back(std::move(up));
        notify();
        return pt_ptr;
    }
    Line const* createLine(DPoint<> const& start, DPoint<> const& end)
    {
        auto pt_ptr = new Line(start, end);
        std::unique_ptr<BaseShape> up(pt_ptr);
        // auto p = std::pair<size_t, std::unique_ptr<BaseShape>>(m_id++, pt_line);
        // m_elements.emplace(p);
        // m_elements[++m_id] = pt_ptr;
        // m_elements.emplace_back(pt_ptr);
        m_elements.emplace_back(std::move(up));
        notify();
        return pt_ptr;
    }
    void setColourById(size_t id, Colour c)
    {
        m_elements[id]->setColour(c);
        notify();
    }

    void walk(IDrawVisitor *visitor)
    {
        for(auto& e: m_elements)
        {
            e->accept(visitor);
        }
    }
    
    private:
    size_t m_id = 0;
    std::vector<std::unique_ptr<BaseShape>> m_elements;
    // std::map<size_t, std::unique_ptr<BaseShape>> m_elements;
    // std::map<size_t, BaseShape*> m_elements;

};


}