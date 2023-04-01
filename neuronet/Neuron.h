#pragma once
#include <memory>
#include <vector>

class Neuron
{
public:
    Neuron();
    virtual ~Neuron();
    
    void link(std::shared_ptr<Neuron> p_other);

    void activate();

private:
    std::vector<std::shared_ptr<Neuron>> m_inputs;
    std::vector<std::shared_ptr<Neuron>> m_outputs;
    
};
