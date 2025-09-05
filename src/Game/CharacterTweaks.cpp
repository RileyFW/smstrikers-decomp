#include "Game/CharacterTweaks.h"
#include "NL/nlConfig.h"
#include "NL/nlLexicalCast.h"

static f32 g_pTweaks[0x17] = {
    4000.0f,
    25.0f,
    45.0f,
    9.5f,
    4000.0f,
    17.5f,
    17.5f,
    2600.0f,
    22.5f,
    18.0f,
    3200.0f,
    25.0f,
    18.0f,
    10.0f,
    2600.0f,
    20.0f,
    20.0f,
    5.5f,
    22.5f,
    14.0f,
    75000.0f,
    4000.0f,
    6.0f,
};

inline float GetConfigFloat(Config& cfg, const char* key, float defaultValue)
{
    SetTagValuePair* tvp = cfg.FindTvp(key);
    if (tvp->m_unk_0x00 == NULL)
    {
        cfg.Set(key, defaultValue);
        return defaultValue;
    }

    float val;
    if (tvp->m_unk_0x04 == 0)
    {
        val = LexicalCast<float, bool>(*(const bool*)&tvp->m_unk_0x08);
    }
    else if (tvp->m_unk_0x04 == 1)
    {
        val = LexicalCast<float, int>(*(const int*)&tvp->m_unk_0x08);
    }
    else if (tvp->m_unk_0x04 == 2)
    {
        val = LexicalCast<float, float>(*(const float*)&tvp->m_unk_0x08);
    }
    else if (tvp->m_unk_0x04 == 3)
    {
        val = LexicalCast<float, const char*>(*(const char**)&tvp->m_unk_0x08);
    }
    else
    {
        val = 0.f;
    }
    return val;
}

inline int GetConfigInt(Config& cfg, const char* key, float defaultValue)
{
    SetTagValuePair* tvp = cfg.FindTvp(key);
    if (tvp->m_unk_0x00 == NULL)
    {
        cfg.Set(key, defaultValue);
        return defaultValue;
    }

    int val;
    if (tvp->m_unk_0x04 == 0)
    {
        val = LexicalCast<int, bool>(*(const bool*)&tvp->m_unk_0x08);
    }
    else if (tvp->m_unk_0x04 == 1)
    {
        val = LexicalCast<int, int>(*(const int*)&tvp->m_unk_0x08);
    }
    else if (tvp->m_unk_0x04 == 2)
    {
        val = LexicalCast<int, float>(*(const float*)&tvp->m_unk_0x08);
    }
    else if (tvp->m_unk_0x04 == 3)
    {
        val = LexicalCast<int, const char*>(*(const char**)&tvp->m_unk_0x08);
    }
    else
    {
        val = 0;
    }
    return val;
}

/**
 * Offset/Address/Size: 0x342C | 0x80017E1C | size: 0x60
 */
PlayerTweaks::~PlayerTweaks()
{
}

/**
 * Offset/Address/Size: 0x2E9C | 0x8001788C | size: 0x590
 */
void PlayerTweaks::Init()
{
    Config cfg(Config::AllocateWhere_1);
    cfg.LoadFromFile(m_unk_0x04);

    m_unk_0x24 = GetConfigFloat(cfg, "Jog Speed", 1.6f);
    m_unk_0x28 = GetConfigFloat(cfg, "Running Speed", 6.25f);
    m_unk_0x44 = GetConfigFloat(cfg, "Capsule Height", 0.5f);
    m_unk_0x48 = GetConfigFloat(cfg, "Capsule Width", 0.3f);
    m_unk_0x2C = GetConfigFloat(cfg, "Running Turn Speed", 105000.0f);
    m_unk_0x30 = g_pTweaks[0];
    m_unk_0x34 = GetConfigFloat(cfg, "Pass Ground Speed Max", 16.0f);
    m_unk_0x38 = GetConfigFloat(cfg, "Pass Ground Speed Min", 5.5f);
    m_unk_0x3C = GetConfigFloat(cfg, "Pass Volley Speed Max", 14.0f);
    m_unk_0x40 = GetConfigFloat(cfg, "Pass Volley Speed Min", 5.5f);
}

/**
 * Offset/Address/Size: 0x2E1C | 0x8001780C | size: 0x80
 */
FielderTweaks::FielderTweaks(const char* arg0)
    : PlayerTweaks(arg0)
{
    Init();
}

/**
 * Offset/Address/Size: 0x2DAC | 0x8001779C | size: 0x70
 */
FielderTweaks::~FielderTweaks()
{
}

/**
 * Offset/Address/Size: 0x19F4 | 0x800163E4 | size: 0x13B8
 */
void FielderTweaks::Init()
{
    PlayerTweaks::Init();

    Config cfg(Config::AllocateWhere_1);
    cfg.LoadFromFile(m_unk_0x04);

    m_unk_0x4C = g_pTweaks[1];
    m_unk_0x50 = g_pTweaks[2];
    m_unk_0x54 = g_pTweaks[3];
    m_unk_0x58 = GetConfigFloat(cfg, "Strafe Turn Speed", 140000.0f);
    m_unk_0x5C = g_pTweaks[4];
    m_unk_0x60 = GetConfigFloat(cfg, "Strafe Speed", 3.5f);
    m_unk_0x64 = GetConfigFloat(cfg, "Run Backwards Speed", 4.0f);
    m_unk_0x68 = g_pTweaks[5];
    m_unk_0x6C = g_pTweaks[6];
    m_unk_0x70 = GetConfigFloat(cfg, "Turbo Turn Speed", 65000.0f);
    m_unk_0x74 = g_pTweaks[7];
    m_unk_0x78 = GetConfigFloat(cfg, "Turbo Speed", 7.5f);
    m_unk_0x7C = g_pTweaks[8];
    m_unk_0x80 = g_pTweaks[9];
    m_unk_0x84 = GetConfigFloat(cfg, "WB Run Turn Speed", 90000.0f);
    m_unk_0x88 = g_pTweaks[10];
    m_unk_0x8C = GetConfigFloat(cfg, "WB Run Speed", 6.0f);
    m_unk_0x90 = g_pTweaks[11];
    m_unk_0x94 = g_pTweaks[12];
    m_unk_0x98 = g_pTweaks[13];
    m_unk_0x9C = GetConfigFloat(cfg, "WB Run Turbo Turn Speed", 70000.0f);
    m_unk_0xA0 = g_pTweaks[14];
    m_unk_0xA4 = GetConfigFloat(cfg, "WB Run Turbo Level 1 Speed", 6.5f);

    m_unk_0xA8 = GetConfigFloat(cfg, "WB Run Turbo Level 2 Speed", 7.0f);
    m_unk_0xAC = GetConfigFloat(cfg, "WB Run Turbo Level 3 Speed", 7.5f);

    m_unk_0xB0 = g_pTweaks[15];
    m_unk_0xB4 = g_pTweaks[16];
    m_unk_0xB8 = g_pTweaks[17];
    m_unk_0xBC = g_pTweaks[18];
    m_unk_0xC0 = g_pTweaks[19];

    m_unk_0xD4 = g_pTweaks[20];
    m_unk_0xD8 = g_pTweaks[21];
    m_unk_0xDC = g_pTweaks[22];

    m_unk_0xF0 = GetConfigFloat(cfg, "S2S Nis Begin Frame", 9.0f);
    m_unk_0xF4 = GetConfigFloat(cfg, "S2S Nis End Frame", 9.0f);
    m_unk_0xF8 = GetConfigFloat(cfg, "S2S Kick Frame", 9.0f);
    m_unk_0xFC = GetConfigFloat(cfg, "S2S 1st Jump Frame", 9.0f);

    m_unk_0x100 = GetConfigInt(cfg, "Red Shell Chance", 0x17);
    m_unk_0x104 = GetConfigInt(cfg, "Green Shell Chance", 0x17);
    m_unk_0x108 = GetConfigInt(cfg, "Spiny Shell Chance", 0x17);
    m_unk_0x10C = GetConfigInt(cfg, "Freeze Shell Chance", 0x17);
    m_unk_0x110 = GetConfigInt(cfg, "Mushroom Chance", 0x17);
    m_unk_0x114 = GetConfigInt(cfg, "Banana Chance", 0x17);
    m_unk_0x118 = GetConfigInt(cfg, "Bobomb Chance", 0x17);

    m_unk_0x11C = GetConfigFloat(cfg, "Big Chance", 23.0f);
    m_unk_0x120 = GetConfigFloat(cfg, "Multiples Chance", 23.0f);

    m_unk_0xC4 = GetConfigFloat(cfg, "Aggression", 0.5f);
    m_unk_0xC8 = GetConfigFloat(cfg, "Shooting", 0.5f);
    m_unk_0xCC = GetConfigFloat(cfg, "Passing", 0.5f);
    m_unk_0xD0 = GetConfigFloat(cfg, "Dekeing", 0.5f);

    m_unk_0xE0 = GetConfigFloat(cfg, "Shot Min Speed", 0.0f);
    m_unk_0xE4 = GetConfigFloat(cfg, "Shot Max Speed", 0.0f);
    m_unk_0xE8 = GetConfigFloat(cfg, "Chip Shot Min Speed", 0.0f);
    m_unk_0xEC = GetConfigFloat(cfg, "Chip Shot Max Speed", 0.0f);
}

/**
 * Offset/Address/Size: 0x1974 | 0x80016364 | size: 0x80
 */
GoalieTweaks::GoalieTweaks(const char* arg0)
    : PlayerTweaks(arg0)
{
    Init();
}

/**
 * Offset/Address/Size: 0x1904 | 0x800162F4 | size: 0x70
 */
GoalieTweaks::~GoalieTweaks()
{
}

/**
 * Offset/Address/Size: 0x0 | 0x800149F0 | size: 0x1904
 */
void GoalieTweaks::Init()
{
    PlayerTweaks::Init();

    Config cfg(Config::AllocateWhere_1);
    cfg.LoadFromFile(m_unk_0x04);

    m_unk_0x4C = GetConfigFloat(cfg, "Throwing Turn Speed", 50000.0f);
    m_unk_0x50 = GetConfigFloat(cfg, "Throwing Turn falloff", 4000.0f);
    m_unk_0x54 = GetConfigFloat(cfg, "Minimum Kick Distance", 13.0f);
    m_unk_0x58 = GetConfigFloat(cfg, "Minimum Overhand Throw Distance", 7.0f);
    m_unk_0x5C = GetConfigFloat(cfg, "Minimum Kick Velocity", 12.0f);
    m_unk_0x60 = GetConfigFloat(cfg, "Maximum Kick Velocity", 16.0f);
    m_unk_0x64 = GetConfigFloat(cfg, "Minimum Kick Angle", 50.0f);
    m_unk_0x68 = GetConfigFloat(cfg, "Maximum Kick Angle", 60.0f);
    m_unk_0x6C = GetConfigFloat(cfg, "Fatigue Recover Rate", 2.0f);
    m_unk_0x70 = GetConfigFloat(cfg, "Fatigue Catch Threshold", 60.0f);
    m_unk_0x74 = GetConfigFloat(cfg, "Catch Save Max Speed", 0.5f);
    m_unk_0x78 = GetConfigFloat(cfg, "High Getup Energy", 80.0f);
    m_unk_0x7C = GetConfigFloat(cfg, "Low Getup Energy", 20.0f);
    m_unk_0x80 = GetConfigFloat(cfg, "Low Getup Speed", 0.5f);
    m_unk_0x84 = GetConfigFloat(cfg, "Low Strafe Speed", 0.8f);
    m_unk_0x88 = GetConfigFloat(cfg, "Goalie Ball Time", 5.0f);
    m_unk_0x8C = GetConfigFloat(cfg, "Min STS Stun Time", 1.5f);
    m_unk_0x90 = GetConfigFloat(cfg, "Max STS Stun Time", 3.0f);
    m_unk_0x94 = GetConfigFloat(cfg, "Loose Ball Shot Distance", 10.0f);
    m_unk_0x98 = GetConfigFloat(cfg, "Save Turn Speed", 100000.0f);
    m_unk_0x9C = GetConfigFloat(cfg, "Save Turn Falloff", 4000.0f);
    m_unk_0xA0 = GetConfigFloat(cfg, "Save Back Run Scale", 1.5f);
    m_unk_0xA4 = GetConfigFloat(cfg, "Save Ignore Margin", 1.0f);
    m_unk_0xA8 = GetConfigFloat(cfg, "Miss Save Delay", 0.1f);
    m_unk_0xAC = GetConfigFloat(cfg, "Lob Shot Stumble Chance", 0.3f);
    m_unk_0xB0 = GetConfigFloat(cfg, "Intercept Save Tolerance", 0.5f);
    m_unk_0xB4 = GetConfigFloat(cfg, "Catch Save Tolerance", 0.7f);
    m_unk_0xB8 = GetConfigFloat(cfg, "Shot Fatigue Default", 10.0f);
    m_unk_0xBC = GetConfigFloat(cfg, "Shot Fatigue Stand Catch", 5.0f);
    m_unk_0xC0 = GetConfigFloat(cfg, "Shot Fatigue Dive Catch", 10.0f);
    m_unk_0xC4 = GetConfigFloat(cfg, "Shot Fatigue Stand Deflection", 5.0f);
    m_unk_0xC8 = GetConfigFloat(cfg, "Shot Fatigue Dive Deflection", 10.0f);
    m_unk_0xCC = GetConfigFloat(cfg, "Shot Fatigue Stand Punch", 7.0f);
    m_unk_0xD0 = GetConfigFloat(cfg, "Shot Fatigue Leg Save", 6.0f);
    m_unk_0xD4 = GetConfigFloat(cfg, "Shot Fatigue STS Save", 15.0f);
    m_unk_0xD8 = GetConfigFloat(cfg, "Shot Fatigue STS Stun", 20.0f);

    // Find the maximum fatigue value
    m_unk_0xDC = m_unk_0xBC >= m_unk_0xB8 ? m_unk_0xBC : m_unk_0xB8;
    m_unk_0xDC = (m_unk_0xC0 >= m_unk_0xDC) ? m_unk_0xC0 : m_unk_0xDC;
    m_unk_0xDC = (m_unk_0xC4 >= m_unk_0xDC) ? m_unk_0xC4 : m_unk_0xDC;
    m_unk_0xDC = (m_unk_0xC8 >= m_unk_0xDC) ? m_unk_0xC8 : m_unk_0xDC;
    m_unk_0xDC = (m_unk_0xCC >= m_unk_0xDC) ? m_unk_0xCC : m_unk_0xDC;
    m_unk_0xDC = (m_unk_0xD0 >= m_unk_0xDC) ? m_unk_0xD0 : m_unk_0xDC;
    m_unk_0xDC = (m_unk_0xD4 >= m_unk_0xDC) ? m_unk_0xD4 : m_unk_0xDC;
    m_unk_0xDC = (m_unk_0xD8 >= m_unk_0xDC) ? m_unk_0xD8 : m_unk_0xDC;

    m_unk_0xE0 = GetConfigFloat(cfg, "STS Attack Close Distance", 1.0f);
    m_unk_0xE4 = GetConfigFloat(cfg, "STS Attack Max Distance", 7.0f);
    m_unk_0xE8 = GetConfigFloat(cfg, "STS Attack Chance Per Frame", 0.01f);
    m_unk_0xEC = GetConfigFloat(cfg, "STS Attack Ball Speed Multiplier", 0.3f);
    m_unk_0xF0 = GetConfigFloat(cfg, "Pounce Range", 1.0f);
}
