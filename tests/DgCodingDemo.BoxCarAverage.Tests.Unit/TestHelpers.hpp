#pragma once

#include <array>
#include <iostream>
#include <CppUnitTestAssert.h>

namespace Microsoft {
    namespace VisualStudio {
        namespace CppUnitTestFramework {
            template<> static inline std::wstring ToString(const std::array<int, 10>& object)
            {
                std::wostringstream os;

                os << object[0];
                for(auto i = 1; i < object.size(); ++i)
                {
                    os << L", " << object[i];
                }

                std::wstring output(os.str());
                return output;
            }

            template<> static inline std::wstring ToString(const std::array<double, 10>& object)
            {
                std::wostringstream os;
                os.precision(16);

                os << object[0];
                for (auto i = 1; i < object.size(); ++i)
                {
                    os << L", " << std::fixed << object[i];
                }

                std::wstring output(os.str());
                return output;
            }

            template<> static inline std::wstring ToString(const std::array<float, 10>& object)
            {
                std::wostringstream os;
                os.precision(16);

                os << object[0];
                for (auto i = 1; i < object.size(); ++i)
                {
                    os << L", " << std::fixed << object[i];
                }

                std::wstring output(os.str());
                return output;
            }
        }
    }
}