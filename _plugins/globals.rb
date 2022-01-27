# An attempt to provide mechanisms for setting and getting global variables
# Supports both functions and tags.  

# Preferred usage
#   Load a global variable.  (Assigns current value of global to name.)
#     {% gload name %}
#   Save a variable as a global.  (Without this, no changes are saved.)
#     {% gsave name %}

# Alternate usage
#   Get a global variable: 
#     {{ "name" | gget }}
#     {% global name %}
#   Set a global variable:
#     {{ "name" | gset: val }}
#     {% gassign name = exp %}

# Ideas on how to build filters and tags garnered from
#   https://github.com/markets/jekyll-timeago/blob/master/lib/jekyll-timeago/jekyll_integration.rb

# Ideas on setting variables garnered from
#   https://github.com/Shopify/liquid/blob/master/lib/liquid/tags/assign.rb

module Jekyll
  module GlobalsHelper
    def self.globals()
      @@globals ||= {}
    end

    def self.get(name)
      globals[name]
    end

    def self.set(name,val)
      globals[name] = val
    end

    module GlobalsFilter
      def gget(name)
        Jekyll::GlobalsHelper.get(name)
      end

      def gset(name,val)
        Jekyll::GlobalsHelper.set(name,val)
        nil
      end
    end

    class GlobalTag < Liquid::Tag
      def initialize(tag_name, text, options)
        super
        @text = text.gsub(/\s*$/, '')
      end

      def render(context)
        Jekyll::GlobalsHelper.get(@text)
      end
    end

    class AssignGlobalTag < Liquid::Tag
      def initialize(tag_name, text, options)
        super
        if text =~ /([a-zA-Z_][a-zA-Z_0-9]*)\s*=\s*(.*)\s*/om
          @name = $1
          @var = Liquid::Variable.new($2, options)
        else
          raise SyntaxError.new options[:locale].t("errors.syntax.gassign".freeze)
        end
      end

      def render(context)
        val = @var.render(context)
        Jekyll::GlobalsHelper.set(@name,val)
        nil
      end
    end

    class SaveGlobalTag < Liquid::Tag
      def initialize(tag_name, text, options)
        super
        if text =~ /([a-zA-Z_][a-zA-Z_0-9]*)\s*/om
          @name = $1;
          @var = Liquid::Variable.new($1, options)
        else
          raise SyntaxError.new options[:locale].t("errors.syntax.gsave".freeze)
        end
      end

      def render(context)
        val = @var.render(context)
        Jekyll::GlobalsHelper.set(@name,val)
        nil
      end
    end

    class LoadGlobalTag < Liquid::Tag
      def initialize(tag_name, text, options)
        super
        if text =~ /([a-zA-Z_][a-zA-Z_0-9]*)\s*/om
          @name = $1;
        else
          raise SyntaxError.new options[:locale].t("errors.syntax.gload".freeze)
        end
      end

      def render(context)
        context.scopes.last[@name] = Jekyll::GlobalsHelper.get(@name)
        nil
      end
    end
  end
end

Liquid::Template.register_filter(Jekyll::GlobalsHelper::GlobalsFilter)
Liquid::Template.register_tag('global', Jekyll::GlobalsHelper::GlobalTag)
Liquid::Template.register_tag('gassign', Jekyll::GlobalsHelper::AssignGlobalTag)
Liquid::Template.register_tag('gload', Jekyll::GlobalsHelper::LoadGlobalTag)
Liquid::Template.register_tag('gsave', Jekyll::GlobalsHelper::SaveGlobalTag)

