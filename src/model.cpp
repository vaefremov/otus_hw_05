#include "model.h"

using namespace OTUS;

BaseShape* Model::findByID(ModelID id)
{
    auto res = std::find_if(std::begin(m_elements), std::end(m_elements), [id](auto& e){return e.get() == id;});
    if(res != std::end(m_elements))
    {
        return (*res).get();
    }
    return nullptr;
}

std::vector<ModelID> Model::findCollisions(DPoint<> const& pt)
{
    std::vector<ModelID> res;
    for(auto& e: m_elements)
    {
        if(e->coords().isNear(pt))
        {
            res.push_back(e.get());
        }
    }
    return res;        
}
