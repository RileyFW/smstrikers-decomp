#pragma pool_data off

#include "Game/TestTask.h"

#include "NL/nlDebugFile.h"
#include "NL/nlMemory.h"
#include "NL/nlConfig.h"
#include "types.h"

#include "NL/nlBasicString.h"

namespace
{
const char* testLog = "test.log";
}

static const char* smokeTestSuccessOutput = "smoke_test.success";
static const char* frameRateTestSuccessOutput = "frame_rate.success";

/**
 * Offset/Address/Size: 0xB4C | 0x8016D448 | size: 0x44
 */
TestTask::TestTask()
{
    mTestLog = 0;
    mTestTimeOut = 0.0f;
    mRunSmokeTest = false;
    mRunUnitTests = false;
    mFrameRateTestFailure = false;
    mRunFrameRateTest = false;
    mMinimumFrameRate = 10.0f;
}

/**
 * Offset/Address/Size: 0x774 | 0x8016D070 | size: 0x3D8
 */
void TestTask::Initialize()
{
    mTestTimeOut = GetConfigFloat(Config::Global(), "test/time_out_sec ", 10.0f);
    mRunUnitTests = GetConfigBool(Config::Global(), "test/unit_tests", false);
    mRunSmokeTest = GetConfigBool(Config::Global(), "test/smoke", false);
    mRunFrameRateTest = GetConfigBool(Config::Global(), "test/frame_rate", false);
    mMinimumFrameRate = GetConfigFloat(Config::Global(), "test/frame_rate_min", 20.0f);

    if (GetConfigBool(Config::Global(), "test/enable", false))
    {
        mTestLog = nlOpenFileDebug(testLog, false, false);
    }
}

/**
 * Offset/Address/Size: 0x6F0 | 0x8016CFEC | size: 0x84
 */
void TestTask::Run(float dt)
{
    if (!mTestLog)
    {
        return;
    }

    mTestTimeOut = mTestTimeOut - dt;

    RunSmokeTest(dt);
    RunFrameRateTest(dt);

    if (mTestTimeOut < 0.0f)
    {
        nlCloseFileDebug(mTestLog);
        mTestLog = 0;
    }
}

/**
 * Offset/Address/Size: 0x424 | 0x8016CD20 | size: 0x2CC
 */
void TestTask::RunSmokeTest(float)
{
    if (mRunSmokeTest)
    {
        if (mTestTimeOut <= 0.0f)
        {
            void* debugFile = nlOpenFileDebug(smokeTestSuccessOutput, false, false);
            if (debugFile)
            {
                nlWriteLineDebug(debugFile, smokeTestSuccessOutput, false);
                nlFlushFileDebug(debugFile);
                nlCloseFileDebug(debugFile);
            }

            BasicStringInternal* data = (BasicStringInternal*)nlMalloc(0x10, 8, true);
            if (data)
            {
                const char* formatTemplate = "SUCCESS: smoke test successful, didn't crash for {0} seconds";
                data->mData = nullptr;
                data->mSize = 0;
                data->mCapacity = 0;

                const char* p = formatTemplate;
                while (*p != '\0')
                {
                    data->mSize++;
                    p++;
                }
                data->mSize++;

                data->mData = (char*)nlMalloc(data->mSize + 1, 8, true);
                data->mCapacity = data->mSize;

                for (int i = 0; i < data->mSize; i++)
                {
                    data->mData[i] = formatTemplate[i];
                }
                data->mRefCount = 1;
            }

            float configValue = GetConfigFloat(Config::Global(), "test/time_out_sec ", 10.0f);

            BasicString<char, Detail::TempStringAllocator> formatString;
            formatString.m_data = data;

            BasicString<char, Detail::TempStringAllocator> formattedString;
            Format(formattedString, formatString, configValue);

            if (mTestLog)
            {
                nlWriteLineDebug(mTestLog, formattedString.c_str(), false);
                nlWriteLineDebug(mTestLog, "\n", false);
                nlFlushFileDebug(mTestLog);
            }
        }
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x8016C8FC | size: 0x424
 */
void TestTask::RunFrameRateTest(float dt)
{
    if (!mRunFrameRateTest)
    {
        return;
    }

    float frameRateThreshold = 1.0f / mMinimumFrameRate;

    if (dt > frameRateThreshold)
    {
        mFrameRateTestFailure = true;

        BasicStringInternal* data = (BasicStringInternal*)nlMalloc(0x10, 8, true);
        if (data)
        {
            const char* formatTemplate = "FAILURE: frame rate dropped below {0}, namely {1}";
            data->mData = nullptr;
            data->mSize = 0;
            data->mCapacity = 0;

            const char* p = formatTemplate;
            while (*p != '\0')
            {
                data->mSize++;
                p++;
            }
            data->mSize++;

            data->mData = (char*)nlMalloc(data->mSize + 1, 8, true);
            data->mCapacity = data->mSize;

            for (int i = 0; i < data->mSize; i++)
            {
                data->mData[i] = formatTemplate[i];
            }
            data->mRefCount = 1;
        }

        float actualFrameRate = 1.0f / dt;

        BasicString<char, Detail::TempStringAllocator> formatString;
        formatString.m_data = data;

        BasicString<char, Detail::TempStringAllocator> formattedString;
        Format(formattedString, formatString, mMinimumFrameRate, actualFrameRate);

        if (mTestLog)
        {
            nlWriteLineDebug(mTestLog, formattedString.c_str(), false);
            nlWriteLineDebug(mTestLog, "\n", false);
            nlFlushFileDebug(mTestLog);
        }
    }

    if (mTestTimeOut <= 0.0f && !mFrameRateTestFailure)
    {
        void* debugFile = nlOpenFileDebug(frameRateTestSuccessOutput, false, false);
        if (debugFile)
        {
            nlWriteLineDebug(debugFile, frameRateTestSuccessOutput, false);
            nlFlushFileDebug(debugFile);
            nlCloseFileDebug(debugFile);
        }

        BasicStringInternal* data = (BasicStringInternal*)nlMalloc(0x10, 8, true);
        if (data)
        {
            const char* formatTemplate = "SUCCES: frame rate test successful, never dropped below {0}";
            data->mData = nullptr;
            data->mSize = 0;
            data->mCapacity = 0;

            const char* p = formatTemplate;
            while (*p != '\0')
            {
                data->mSize++;
                p++;
            }
            data->mSize++;

            data->mData = (char*)nlMalloc(data->mSize + 1, 8, true);
            data->mCapacity = data->mSize;

            for (int i = 0; i < data->mSize; i++)
            {
                data->mData[i] = formatTemplate[i];
            }
            data->mRefCount = 1;
        }

        BasicString<char, Detail::TempStringAllocator> formatString;
        formatString.m_data = data;

        BasicString<char, Detail::TempStringAllocator> formattedString;
        Format(formattedString, formatString, mMinimumFrameRate);

        if (mTestLog)
        {
            nlWriteLineDebug(mTestLog, formattedString.c_str(), false);
            nlWriteLineDebug(mTestLog, "\n", false);
            nlFlushFileDebug(mTestLog);
        }
    }
}
