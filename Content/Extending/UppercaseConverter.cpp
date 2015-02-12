#include "pch.h"


using namespace Noesis;


class UppercaseConverter: public BaseValueConverter
{
public:
    NsBool TryConvert(BaseComponent* value, const Type* targetType, BaseComponent* parameter, Ptr<BaseComponent>& result)
    {
        if (targetType == TypeOf<NsString>() && Boxing::CanUnbox<NsString>(value))
        {
            NsString text = Boxing::Unbox<NsString>(value);
            text.make_upper();
            result = Boxing::Box<NsString>(text);
            return true;
        }

        return false;
    }

private:
    NS_IMPLEMENT_INLINE_REFLECTION(UppercaseConverter, BaseValueConverter)
    {
        NsMeta<TypeId>("Sample.UppercaseConverter");
    }
};


extern "C" NS_DLL_EXPORT void NsRegisterReflection(ComponentFactory* factory, NsBool registerComponents)
{
    NS_REGISTER_COMPONENT(UppercaseConverter)
}
