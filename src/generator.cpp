#include "generator.hpp"

tome::IGenerator::~IGenerator()
{

}

tome::IGenerator::IGenerator()
{

}

tome::IGenerator::IGenerator(const engine_ptr& p_engine)
{
    set_engine(p_engine);
}

bool tome::IGenerator::has_engine()
{
    return m_pEngine != NULL;
}

tome::IGenerator::engine_ptr tome::IGenerator::get_engine()
{
    return m_pEngine;
}

void tome::IGenerator::set_engine(const engine_ptr& engine)
{
    m_pEngine = engine;
}
