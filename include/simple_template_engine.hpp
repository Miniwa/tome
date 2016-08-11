#ifndef _TOME_SIMPLE_TEMPLATE_ENGINE_HPP
#define _TOME_SIMPLE_TEMPLATE_ENGINE_HPP

#include "template_engine.hpp"

#include <string>
#include <map>

namespace tome
{
    //! Represents a template engine based on string contexts.
    class SimpleTemplateEngine : public ITemplateEngine
    {
    public:
        //! Default constructor.
        SimpleTemplateEngine();

        //! With context constructor.
        //! @param context The template context.
        SimpleTemplateEngine(const std::map<std::string, std::string>& context);

        //! With recursive boolean constructor.
        //! @param recursive Whether or not this engine is recursive.
        SimpleTemplateEngine(bool recursive);

        //! With context and recursive boolean constructor.
        //! @param context The template context.
        //! @param recursive Whether or not this engine is recursive.
        SimpleTemplateEngine(const std::map<std::string, std::string>& context, bool recursive);

        // ITemplateEngine overrides.
        virtual ~SimpleTemplateEngine();
        virtual bool has_context();

        //! Renders a text template into a string. If recursive flag is set, the method will continue to render until no text replacements are made anymore.
        //! @param tmpl The template which will be rendered.
        //! @returns The final product of the rendering.
        virtual std::string render(const std::string& tmpl);

        //! Renders a text template into a string. If recursive flag is set, the method will continue to render until no text replacements are made anymore. The user is responsible for any error checking.
        //! @param tmpl The template which will be rendered.
        //! @param p_errors A pointer to the std::vector that will contain all the rendering errors once the method completes.
        //! @returns The final product of the rendering.
        virtual std::string render(const std::string& tmpl, std::vector<std::string>* p_errors);

        //! @returns Whether or not the engine is recursive.
        bool is_recursive();

        //! Sets the context for the engine.
        //! @param context The context.
        void set_context(const std::map<std::string, std::string>& context);

        //! Sets whether or not this engine is recursive.
        void set_recursive(bool recursive);

    private:
        size_t do_step(const std::string& tmpl, std::string* p_result, std::vector<std::string>* p_errors);
        bool m_recursive;
        bool m_has_context;
        std::map<std::string, std::string> m_context;
    };
}
#endif
