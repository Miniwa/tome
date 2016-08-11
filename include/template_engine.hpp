#ifndef _TOME_TEMPLATE_ENGINE_HPP
#define _TOME_TEMPLATE_ENGINE_HPP

#include <string>
#include <vector>

namespace tome
{
    //! Represents the interface of a template engine.
    class ITemplateEngine
    {
    public:
        virtual ~ITemplateEngine();

        //! Renders a text template into a string.
        //! @param tmpl The template which will be rendered.
        //! @returns The final product of the rendering.
        virtual std::string render(const std::string& tmpl) = 0;

        //! Renders a text template into a string. The user is responsible for any error checking.
        //! @param tmpl The template which will be rendered.
        //! @param p_errors A pointer to the std::vector that will contain all the rendering errors once the method completes.
        //! @returns The final product of the rendering.
        virtual std::string render(const std::string& tmpl, std::vector<std::string>* p_errors) = 0;

        //! @returns Whether or not a context has been assigned to the engine.
        virtual bool has_context() = 0;

    };
}
#endif
