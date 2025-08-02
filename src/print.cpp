#include "dummy/print.hpp"


struct Vector3 {
    double x;
    double y;
    double z;
};

namespace BT {
    template <> inline Vector3 convertFromString(StringView str)
    {
        // We expect real numbers separated by semicolons
        // We expect real numbers separated by semicolons
        auto parts = splitString(str, ' ');
        if (parts.size() != 3)
        {
            throw RuntimeError("Invalid Podoubles!");
        }
        
        Vector3 output;
        output.x     = convertFromString<double>(parts[0]);
        output.y     = convertFromString<double>(parts[1]);
        output.z     = convertFromString<double>(parts[2]);
        return output;
    }

}


BT::NodeStatus Print::tick() {
    auto xyz = getInput<Vector3>("xyz").value();
    std::cerr << xyz.x << xyz.y << xyz.z << "\n";
    return BT::NodeStatus::SUCCESS;
  }

BT::PortsList Print::providedPorts() {
    return { 
        BT::InputPort<Vector3>("xyz")
    };
}


#include "behaviortree_cpp/bt_factory.h"
BT_REGISTER_NODES(factory)
{
  factory.registerNodeType<Print>("Print");
}