#pragma once

#include <algorithm>
#include <array>
#include <concepts>

template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

template<size_t T>
concept positive_size = T > 0;

template<arithmetic TArrayType, size_t TArraySize, size_t TFrameSize>
    requires positive_size<TArraySize> && positive_size<TFrameSize>
class BoxCarAverage
{
public:

	static inline std::array<TArrayType, TArraySize> Calculate(const std::array<TArrayType, TArraySize>& input)
    {
        std::array<TArrayType, TArraySize> output {};

        // perform calculations for sets under the desired frame size
        TArrayType currentSum = 0;
        size_t currentFrameSize = 0;
        for (size_t i = 0; i < std::min<size_t>(TFrameSize, TArraySize); ++i)
        {
            output[i] = CalculateIitialDataPoint(currentSum, input[i], currentFrameSize);
        }

        if (TArraySize > TFrameSize)
        {
            // perform calculations for all remaining data
            for (size_t i = TFrameSize; i < TArraySize; ++i)
            {
                output[i] = CalculateTailDataPoint(currentSum, input[i], input[i - TFrameSize]);
            }
        }

        return output;
    }

private:
    BoxCarAverage() {}
	bool operator==(const BoxCarAverage& other) const = default;

	static inline TArrayType DesiredFrameSize = static_cast<TArrayType>(TFrameSize);

	static inline TArrayType CalculateIitialDataPoint(TArrayType& currentSum, const TArrayType& newValue, size_t& currentFrameSize)
    {
        currentSum += newValue;
        ++currentFrameSize;
        return currentSum / static_cast<TArrayType>(currentFrameSize);
    }

	static inline TArrayType CalculateTailDataPoint(TArrayType& currentSum, const TArrayType& newValue, const TArrayType& overflowValue)
    {
        currentSum += newValue - overflowValue;
        return currentSum / DesiredFrameSize;
    }
};