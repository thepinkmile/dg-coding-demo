#pragma once

#include <algorithm>
#include <array>
#include <concepts>

/// <summary>
/// A template constraint to ensure only numerical types are used.
/// </summary>
template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;

/// <summary>
/// A template constraint to ensure positive non-zero values.
/// </summary>
template<size_t T>
concept positive_size = T > 0;

/// <summary>
/// A class containing static methods for calulating Box Car Average for given inputs.
/// </summary>
/// <typeparam name="TArrayType">The type of the input and output arrays.</typeparam>
/// <typeparam name="TArraySize">The size of the input and output arrays.</typeparam>
/// <typeparam name="TFrameSize">The required Frame size for smoothing values.</typeparam>
template<arithmetic TArrayType, size_t TArraySize, size_t TFrameSize>
	requires positive_size<TArraySize>&& positive_size<TFrameSize>
class BoxCarAverage
{
public:

	/// <summary>
	/// Calculates the Box Car Average for the given <paramref name="input"/>.
	/// </summary>
	/// <param name="input">An input of numeric values to be smoothed.</param>
	/// <returns>An array of the smoothed values.</returns>
	static inline std::array<TArrayType, TArraySize> Calculate(const std::array<TArrayType, TArraySize>& input)
	{
		std::array<TArrayType, TArraySize> output {};

		// perform calculations for sets under the desired frame size
		TArrayType currentSum {};
		constexpr size_t initialFrameDataSize = std::min(TFrameSize, TArraySize);
		for (size_t i = 0; i < initialFrameDataSize; ++i)
		{
			output[i] = CalculateDataPoint(currentSum, input[i], i + 1);
		}

		if (TArraySize > initialFrameDataSize)
		{
			// perform calculations for all remaining data
			for (size_t i = initialFrameDataSize; i < TArraySize; ++i)
			{
				output[i] = CalculateDataPoint(currentSum, input[i] - input[i - initialFrameDataSize], TFrameSize);
			}
		}

		return output;
	}

private:
	BoxCarAverage() {}
	bool operator==(const BoxCarAverage& other) const = default;

	static inline TArrayType CalculateDataPoint(TArrayType& currentSum, const TArrayType& newValue, const TArrayType& currentFrameSize)
	{
		currentSum += newValue;
		return currentSum / currentFrameSize;
	}
};
