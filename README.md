# Coding Demo
This project contains the coding demo solution.
This solution is built using Visual Studio 2022 Community Edition.

### Solution Layout
I decided to follow a common solution structure (as seen in most GitHub repositories):
- src - This is where the code demo project is located
- tests - This is the directory that contains any unit test projects

### Requirements
- Visual Studio 2022 (with c++ desktop development packages)
- C++20 standard library usage within the consuming application

## The Problem (Boxcar average)
Samples over time from a voltage sensor are received periodically into a buffer holding “N” samples. Each sample is a value > = 0.

The system requires smoothed voltage data and it has been decided to use “boxcar” averaging with a  window length “W” (each smoothed sample is the average of  the current and W-1 previous samples). This function is sometimes also referred to as a “moving” average.
For example if the most recent input samples have values: 1,2,3,4,5,6,7,8,9,10 and W = 3 then the most recent  smoothed value is (8+9+10) / 3, the one before was (7+8+9) / 3 and so on.

Design software to perform the processing described above using C/C++ or another suitable high-level language. The solution should be optimised for efficiency (i.e. minimising the number of CPU clocks per iteration). 
For each input buffer of N samples, the output should also be a buffer of N smoothed samples. Assume that other software has already taken care of receiving the input into a buffer; your solution should just focus on doing the averaging.
The solution does not need to be a complete application. For example, it can just provide the C/C++ function (or equivalent in another language) that performs smoothing of a buffer of samples, including any global data and/or initialisation code required.

### Solution Design
My idea is to provide a static method that could be used by an external system.
This static method will be defined within a class for simplicity when implementing related internal functionality.
The static method will take a single array of numerical types as input and return an equivalent array containing the smoothed values.

In order to efficiently calculate the boxcar average, I want to allow for the tracking of the current sum of `W` elements.
This allows each iteration to only require the following actions:
1. Remove the overflowing array value (if current frame size is equal to `W`, then this would be the `currentPosition - W` element of the input array)
2. Add the new value
3. Update output array value at `currentPosition` with the result of `currentSum / frameSize`
**Note:** This will require initially setting up the output array to be the same size and type of the input array.
**Note:** Potential performance hits expected would be for the first `W` elements of the input, as these will not require the first action listed as the frame size is not big enough to "overflow".

Because of the notes defined above I would break the actual algorithm into 2 parts:
1. Process initial data up to the frame size of `W` (which will not perform the remove action)
2. Process tail data (which will include the removal action of oveflowing values)
This allows me to avoid spending CPU cycles on every iteration to determine if the remove action is required.
**Note:** There would need to be a single check within the method to only execute the second loop if the input array is bigger than `W`.

Additional ideas to incorporate:
- Make the methods Templates - to allow for any numeric type for the input and output
- Specify `W` and array size as template parameters to enable optimisations at compile time
- Constrained template parameters - to ensure correct usage (compile time errors over run time errors)

### Testing
I have selected to use the Microsoft Unit Testing Framework for C++, as this already has project templates available within Visual Studio.
There are currently a minimal number of tests to ensure the solution works with multiple numeric types and the effects of providing different array and frame sizes.

## Future Possibilities
As I was limited with time to create this solution, there are several areas I would investigate if given more time.
- Update the existing method to return currentSum, currentFrameSize as well as the output array - This enable the next point by providing the inputs required to "continue" smothing with another input array
- Add a method that takes the "tail" of the previous input, currentSum, currentFrameSize and a new input array - To enable continuing smoothing if another related array needs processing (e.g. if the input has been split by an upstream system)
- Update to use variadic templates - This could improve efficiency as the inputs could be defined in a much better way to remove the need for bounds checking at run time
