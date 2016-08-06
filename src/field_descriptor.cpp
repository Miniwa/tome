#include "field_descriptor.hpp"

tome::FieldDescriptor::FieldDescriptor(std::string name, FIELD_TYPE type, bool required)
{
    this->m_name = name;
    this->m_type = type;
    this->m_required = required;
}

std::string tome::FieldDescriptor::get_name()
{
    return m_name;
}

tome::FIELD_TYPE tome::FieldDescriptor::get_type()
{
    return m_type;
}

bool tome::FieldDescriptor::is_required()
{
    return m_required;
}
