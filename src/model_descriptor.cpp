#include "field_descriptor.hpp"
#include "model_descriptor.hpp"

tome::ModelDescriptor::ModelDescriptor(const std::string& name)
{
    this->m_name = name;
    this->m_package = "";
    this->m_fields = std::vector<FieldDescriptor>();
}

tome::ModelDescriptor::ModelDescriptor(const std::string& name, const std::string& package)
{
    this->m_name = name;
    this->m_package = package;
    this->m_fields = std::vector<FieldDescriptor>();
}

std::string tome::ModelDescriptor::get_name()
{
    return m_name;
}

std::string tome::ModelDescriptor::get_package()
{
    return m_package;
}

size_t tome::ModelDescriptor::get_field_count()
{
    return m_fields.size();
}

tome::FieldDescriptor* tome::ModelDescriptor::get_field(size_t index)
{
    return &m_fields.at(index);
}

void tome::ModelDescriptor::add_field(const FieldDescriptor& field)
{
    m_fields.push_back(field);
}
