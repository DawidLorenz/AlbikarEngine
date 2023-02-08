#pragma once
#include "AlbikarDefines.hpp"

namespace AlbikarAPI {
class IAlbikarEngine {
public:
    ALBIKAR_INTERFACE(IAlbikarEngine)

    /// @brief Start Engine with parameters
    /// @param resolutionWidth - Screen width
    /// @param resolutionHeight - Screen height
    /// @param gameName - Game name
    /// @param fixedResolution - if true, the resolution is fixed, if false, the screen can be scaled
    /// @return ALBIKAR_SUCCESS if success
    virtual auto InitEngine(const uint16_t resolutionWidth, const uint16_t resolutionHeight, const char* gameName, const bool fixedResolution) -> ALBIKAR_RETURN = 0;

    /// @brief Start Engine
    /// @return ALBIKAR_SUCCESS if success
    virtual auto Start() -> ALBIKAR_RETURN = 0;

    /// @brief Close Engine
    /// @return ALBIKAR_SUCCESS if success
    virtual auto Terminate() -> ALBIKAR_RETURN = 0;
};

auto ALBIKAR_API CreateEngine() -> std::shared_ptr<IAlbikarEngine>;
} // namespace AlbikarAPI