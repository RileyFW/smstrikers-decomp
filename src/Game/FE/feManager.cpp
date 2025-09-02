#include "Game/FE/feManager.h"

/**
 * Offset/Address/Size: 0x0 | 0x80094C84 | size: 0x44
 */
void FrontEnd::ReturnToFE()
{
}

/**
 * Offset/Address/Size: 0x44 | 0x80094CC8 | size: 0x1A0
 */
void FrontEnd::UpdateForGame(float)
{
}

/**
 * Offset/Address/Size: 0x1E4 | 0x80094E68 | size: 0x33C
 */
void FrontEnd::Update(float)
{
}

/**
 * Offset/Address/Size: 0x520 | 0x800951A4 | size: 0x90
 */
void FrontEnd::ExitMenuState()
{
}

/**
 * Offset/Address/Size: 0x5B0 | 0x80095234 | size: 0x188
 */
void FrontEnd::EnterMenuState(FrontEnd::MenuEnterType)
{
}

/**
 * Offset/Address/Size: 0x738 | 0x800953BC | size: 0x70
 */
void FrontEnd::ExitWinnerScreen()
{
}

/**
 * Offset/Address/Size: 0x7A8 | 0x8009542C | size: 0x48
 */
void FrontEnd::EnterStartScreen(bool)
{
}

/**
 * Offset/Address/Size: 0x7F0 | 0x80095474 | size: 0x54
 */
void FrontEnd::SetControllerState()
{
}

/**
 * Offset/Address/Size: 0x844 | 0x800954C8 | size: 0x10
 */
void FrontEnd::Destroy()
{
}

/**
 * Offset/Address/Size: 0x854 | 0x800954D8 | size: 0x48
 */
bool FrontEnd::Initialize()
{
    return true;
}

/**
 * Offset/Address/Size: 0x89C | 0x80095520 | size: 0x9C
 */
void FrontEnd::FEEventHandler(Event*, void*)
{
}
