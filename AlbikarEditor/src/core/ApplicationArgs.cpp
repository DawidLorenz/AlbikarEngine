#include "ApplicationArgs.hpp"

CApplicationArgs::CApplicationArgs(int argc, char** argv)
{
    for (auto i = 0; i < argc; i++) {
        m_Args.emplace_back(std::string(argv[i]));
        // TODO(dawid): Create vector with arguments
    }
}