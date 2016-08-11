#ifndef _TOME_TEMPLATE_ERROR_HPP
#define _TOME_TEMPLATE_ERROR_HPP

#include <string>
#include <stdexcept>

namespace tome
{
    //! Represents an error within the template engine.
    class TemplateError : public std::runtime_error
    {
    public:
        TemplateError(const std::string& what) : std::runtime_error(what)
        {

        }
    };
}
#endif
