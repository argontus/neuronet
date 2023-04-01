#include <cstdint>
#include <iostream>

#include "imgui/imgui.h"

/**
 * Simple neural net study
 */

enum class InputQualities
{
    numberOfSpots,
    lengthOfSpikes,
    count
};

enum class OutputClassification
{
    edible,
    poisonous,
    count
};

void outputClassificationToString(OutputClassification outputClassification,
                                  std::string&         output)
{
    switch (outputClassification)
    {
    case OutputClassification::edible:
        output = "yum";
        break;
    case OutputClassification::poisonous:
        output = "yuck";
        break;
    case OutputClassification::count:
        break;
    }
}

void askForNumber(std::string const &askText, double_t &number)
{
    number = -1;
    while (number < 0)
    {
        std::cout << askText << std::endl;
        std::cin >> number;

        while (!std::cin.good())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                            '\n');
        }
    }
}

int imgui_main(int, char**);
int main(int   argc,
         char* argv[])
{

    imgui_main(argc, argv);
    
    ImGui::Text("Hello, world %d", 123);
    if (ImGui::Button("Save"))
    {
        
    }
    char buf [1024] {0};
    ImGui::InputText("string", buf, IM_ARRAYSIZE(buf));
    float_t f = 0;
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    
    double_t numberOfSpots = 5;
    double_t lengthOfSpikes = 87.5;

    askForNumber("type the number of spots", numberOfSpots);
    askForNumber("type the avg length of spikes", lengthOfSpikes);
    

    // input & output points
    constexpr auto INPUT_COUNT  = static_cast<int32_t>(InputQualities::count);
    constexpr auto OUTPUT_COUNT = static_cast<int32_t>(OutputClassification::count);

    const double_t inputs[INPUT_COUNT]
    {
        numberOfSpots, lengthOfSpikes
    };

    constexpr double_t weights[INPUT_COUNT][OUTPUT_COUNT]
    {
        {0.5, 0.3,}, // 0_0, 0_1
        {0.2, 0.8,}, // 1_0, 1_1
    };

    double_t outputs[OUTPUT_COUNT]{0};

    // inputs
    std::cout << "inputs:" << std::endl;

    for (int32_t inputIndex = 0; inputIndex < INPUT_COUNT; inputIndex++)
    {
        std::cout << inputs[inputIndex] << std::endl;
    }


    // apply weights
    for (int32_t inputIndex = 0; inputIndex < INPUT_COUNT; inputIndex++)
    {
        for (int32_t outputIndex = 0; outputIndex < OUTPUT_COUNT; outputIndex++)
        {
            std::cout << "weight " << inputIndex << "_" << outputIndex << ": " << weights[inputIndex][outputIndex] <<
                std::endl;
            outputs[outputIndex] += inputs[inputIndex] * weights[inputIndex][outputIndex];
        }
    }

    // outputs
    std::cout << "outputs:" << std::endl;
    double_t largestOutput = 0;
    int32_t indexOfLargestOutput = 0;
    for (int32_t outputIndex = 0; outputIndex < OUTPUT_COUNT; outputIndex++)
    {
        std::cout << "output " << outputIndex << ": " << outputs[outputIndex] << std::endl;
        if (outputs[outputIndex] > largestOutput)
        {
            largestOutput = outputs[outputIndex];
            indexOfLargestOutput = outputIndex;
        }
    }

    std::string numberClassString;
    outputClassificationToString(static_cast<OutputClassification>(indexOfLargestOutput),
                                 numberClassString);
    std::cout << "it is " << numberClassString << std::endl;

    return 0;
}
