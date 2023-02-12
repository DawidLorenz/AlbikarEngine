#pragma once
#include "AlbikarDefines.hpp"
namespace Albikar::render {

class IBackEnd {
public:
    ALBIKAR_INTERFACE(IBackEnd)
    virtual auto Init() -> ALBIKAR_RETURN = 0;
    virtual auto CleanUp() -> ALBIKAR_RETURN = 0;
    virtual auto OnResize(const uint16_t newWidth, const uint16_t newHeight) -> ALBIKAR_RETURN = 0;
    virtual auto BeginFrame(const float deltaTime) -> ALBIKAR_RETURN = 0;
    virtual auto EndFrame(const float deltaTime) -> ALBIKAR_RETURN = 0;

private:
};

} // namespace Albikar::render
