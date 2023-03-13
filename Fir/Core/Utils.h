#ifndef __FIR_CORE_UTILS_H__
#define __FIR_CORE_UTILS_H__

namespace Fir
{
    template<typename FirstType, typename SecondType, typename... Error>
    struct IsTypeSame
    {
        static constexpr bool value = false;
    };

    template<typename Type, typename... Checking>
    struct IsTypeSame<Type, Type, Checking...> : public IsTypeSame<Type, Checking...> {  };

    template<typename Type>
    struct IsTypeSame<Type, Type>
    {
        static constexpr bool value = true;
    };
}

#endif      // Utils.h