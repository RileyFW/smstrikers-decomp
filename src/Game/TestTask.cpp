#include "Game/TestTask.h"

#include "NL/nlDebugFile.h"
#include "NL/nlMemory.h"
#include "NL/nlConfig.h"
#include "types.h"

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
    mMinimumFrameRate = 20.0f;
}

/**
 * Offset/Address/Size: 0x774 | 0x8016D070 | size: 0x3D8
 */
void TestTask::Initialize()
{
    // Get global config
    Config& config = Config::Global();

    // Load test timeout value
    SetTagValuePair* tvp = config.FindTvp("test/time_out_sec");
    float timeoutValue = 0.0f;
    if (tvp->m_unk_0x00 == nullptr)
    {
        config.Set("test/time_out_sec", 0.0f);
        timeoutValue = 0.0f;
    }
    else
    {
        switch (tvp->m_unk_0x04)
        {
        case 0: // bool
            timeoutValue = LexicalCast<float, bool>(*(bool*)&tvp->m_unk_0x08);
            break;
        case 1: // int
            timeoutValue = LexicalCast<float, int>(*(int*)&tvp->m_unk_0x08);
            break;
        case 2: // float
            timeoutValue = LexicalCast<float, float>(*(float*)&tvp->m_unk_0x08);
            break;
        case 3: // string
            timeoutValue = LexicalCast<float, const char*>(*(const char**)&tvp->m_unk_0x08);
            break;
        default:
            timeoutValue = 0.0f;
            break;
        }
    }
    mTestTimeOut = timeoutValue;

    // Load run unit tests flag
    tvp = config.FindTvp("test/run_unit_tests");
    bool runUnitTests = false;
    if (tvp->m_unk_0x00 == nullptr)
    {
        config.Set("test/run_unit_tests", false);
        runUnitTests = false;
    }
    else
    {
        switch (tvp->m_unk_0x04)
        {
        case 0: // bool
            runUnitTests = LexicalCast<bool, bool>(*(bool*)&tvp->m_unk_0x08);
            break;
        case 1: // int
            runUnitTests = LexicalCast<bool, int>(*(int*)&tvp->m_unk_0x08);
            break;
        case 2: // float
            runUnitTests = LexicalCast<bool, float>(*(float*)&tvp->m_unk_0x08);
            break;
        case 3: // string
            runUnitTests = LexicalCast<bool, const char*>(*(const char**)&tvp->m_unk_0x08);
            break;
        default:
            runUnitTests = false;
            break;
        }
    }
    mRunUnitTests = runUnitTests;

    // Load run smoke test flag
    tvp = config.FindTvp("test/run_smoke_test");
    bool runSmokeTest = false;
    if (tvp->m_unk_0x00 == nullptr)
    {
        config.Set("test/run_smoke_test", false);
        runSmokeTest = false;
    }
    else
    {
        switch (tvp->m_unk_0x04)
        {
        case 0: // bool
            runSmokeTest = LexicalCast<bool, bool>(*(bool*)&tvp->m_unk_0x08);
            break;
        case 1: // int
            runSmokeTest = LexicalCast<bool, int>(*(int*)&tvp->m_unk_0x08);
            break;
        case 2: // float
            runSmokeTest = LexicalCast<bool, float>(*(float*)&tvp->m_unk_0x08);
            break;
        case 3: // string
            runSmokeTest = LexicalCast<bool, const char*>(*(const char**)&tvp->m_unk_0x08);
            break;
        default:
            runSmokeTest = false;
            break;
        }
    }
    mRunSmokeTest = runSmokeTest;

    // Load run frame rate test flag
    tvp = config.FindTvp("test/run_frame_rate_test");
    bool runFrameRateTest = false;
    if (tvp->m_unk_0x00 == nullptr)
    {
        config.Set("test/run_frame_rate_test", false);
        runFrameRateTest = false;
    }
    else
    {
        switch (tvp->m_unk_0x04)
        {
        case 0: // bool
            runFrameRateTest = LexicalCast<bool, bool>(*(bool*)&tvp->m_unk_0x08);
            break;
        case 1: // int
            runFrameRateTest = LexicalCast<bool, int>(*(int*)&tvp->m_unk_0x08);
            break;
        case 2: // float
            runFrameRateTest = LexicalCast<bool, float>(*(float*)&tvp->m_unk_0x08);
            break;
        case 3: // string
            runFrameRateTest = LexicalCast<bool, const char*>(*(const char**)&tvp->m_unk_0x08);
            break;
        default:
            runFrameRateTest = false;
            break;
        }
    }
    mRunFrameRateTest = runFrameRateTest;

    // Load minimum frame rate value
    tvp = config.FindTvp("test/minimum_frame_rate");
    float minimumFrameRate = 20.0f;
    if (tvp->m_unk_0x00 == nullptr)
    {
        config.Set("test/minimum_frame_rate", 20.0f);
        minimumFrameRate = 20.0f;
    }
    else
    {
        switch (tvp->m_unk_0x04)
        {
        case 0: // bool
            minimumFrameRate = LexicalCast<float, bool>(*(bool*)&tvp->m_unk_0x08);
            break;
        case 1: // int
            minimumFrameRate = LexicalCast<float, int>(*(int*)&tvp->m_unk_0x08);
            break;
        case 2: // float
            minimumFrameRate = LexicalCast<float, float>(*(float*)&tvp->m_unk_0x08);
            break;
        case 3: // string
            minimumFrameRate = LexicalCast<float, const char*>(*(const char**)&tvp->m_unk_0x08);
            break;
        default:
            minimumFrameRate = 0.0f;
            break;
        }
    }
    mMinimumFrameRate = minimumFrameRate;

    // Open debug log file if enabled
    if (mRunFrameRateTest)
    {
        mTestLog = nlOpenFileDebug("testLog__22@unnamed@TestTask_cpp@", false, false);
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
    if (!mRunSmokeTest)
    {
        return;
    }

    if (mTestTimeOut > 0.0f)
    {
        return;
    }

    // Get the smoke test success output filename
    const char* smokeTestSuccessOutput = "smokeTestSuccessOutput__22@unnamed@TestTask_cpp@";

    // Open debug file for writing
    void* debugFile = nlOpenFileDebug(smokeTestSuccessOutput, false, false);
    if (debugFile)
    {
        nlWriteLineDebug(debugFile, smokeTestSuccessOutput, false);
        nlFlushFileDebug(debugFile);
        nlCloseFileDebug(debugFile);
    }

    // Create a BasicString for formatting
    BasicString<char, Detail::TempStringAllocator>* formatString = (BasicString<char, Detail::TempStringAllocator>*)nlMalloc(0x10, 8, true);
    if (formatString)
    {
        const char* formatTemplate = "SUCCESS: smoke test successful, didn't crash for {0} seconds";
        formatString->m_data = nullptr;
        formatString->m_size = 0;
        formatString->m_capacity = 0;

        const char* p = formatTemplate;
        while (*p != '\0')
        {
            formatString->m_size++;
            p++;
        }
        formatString->m_size++; // Include null terminator

        formatString->m_data = (char*)nlMalloc(formatString->m_size, 8, true);
        formatString->m_capacity = formatString->m_size;

        // Copy the format template
        for (int i = 0; i < formatString->m_size - 1; i++)
        {
            formatString->m_data[i] = formatTemplate[i];
        }
        formatString->m_data[formatString->m_size - 1] = '\0';
        formatString->m_refCount = 1;
    }

    // Get global config and look up a specific value
    Config& config = Config::Global();
    const char* configKey = "test/time_out_sec ";
    SetTagValuePair* tvp = config.FindTvp(configKey);

    float configValue = 0.0f;
    if (tvp->m_unk_0x00 == nullptr)
    {
        // Set default value if not found
        config.Set(configKey, 1.0f);
        configValue = 1.0f;
    }
    else
    {
        // Convert the config value based on its type
        switch (tvp->m_unk_0x04)
        {
        case 0: // bool
            configValue = LexicalCast<float, bool>(*(bool*)&tvp->m_unk_0x08);
            break;
        case 1: // int
            configValue = LexicalCast<float, int>(*(int*)&tvp->m_unk_0x08);
            break;
        case 2: // float
            configValue = LexicalCast<float, float>(*(float*)&tvp->m_unk_0x08);
            break;
        case 3: // string
            configValue = LexicalCast<float, const char*>(*(const char**)&tvp->m_unk_0x08);
            break;
        default:
            configValue = 0.0f;
            break;
        }
    }

    // Format the string with the config value
    BasicString<char, Detail::TempStringAllocator> formattedString;
    Format(formattedString, *formatString, configValue);

    // Write the formatted string to debug output
    if (mTestLog)
    {
        nlWriteLineDebug(mTestLog, formattedString.c_str(), false);
        nlWriteLineDebug(mTestLog, "\n", false); // Additional debug message
        nlFlushFileDebug(mTestLog);
    }

    // Clean up the format string
    if (formatString)
    {
        formatString->m_refCount--;
        if (formatString->m_refCount == 0)
        {
            if (formatString->m_data)
            {
                nlFree(formatString->m_data);
            }
            nlFree(formatString);
        }
    }

    // Clean up the formatted string
    if (formattedString.m_refCount == 0)
    {
        if (formattedString.m_data)
        {
            nlFree(formattedString.m_data);
        }
        nlFree(&formattedString);
    }
}

/**
 * Offset/Address/Size: 0x0 | 0x8016C8FC | size: 0x424
 */
void TestTask::RunFrameRateTest(float dt)
{
    // Check if frame rate test is enabled
    if (!mRunFrameRateTest)
    {
        return;
    }

    // Calculate frame rate threshold: 1.0f / mMinimumFrameRate
    float frameRateThreshold = 1.0f / mMinimumFrameRate;

    // Check if current frame time exceeds threshold (frame rate too low)
    if (dt > frameRateThreshold)
    {
        // Mark frame rate test as failed
        mFrameRateTestFailure = true;

        // Create format string for failure message
        BasicString<char, Detail::TempStringAllocator>* formatString = (BasicString<char, Detail::TempStringAllocator>*)nlMalloc(0x10, 8, true);
        if (formatString)
        {
            const char* formatTemplate = "FAILURE: frame rate test failed, frame time {0} exceeds threshold {1}";
            formatString->m_data = nullptr;
            formatString->m_size = 0;
            formatString->m_capacity = 0;

            // Calculate string length
            const char* p = formatTemplate;
            while (*p != '\0')
            {
                formatString->m_size++;
                p++;
            }
            formatString->m_size++; // Include null terminator

            // Allocate memory for string data
            formatString->m_data = (char*)nlMalloc(formatString->m_size, 8, true);
            formatString->m_capacity = formatString->m_size;

            // Copy the format template
            for (int i = 0; i < formatString->m_size - 1; i++)
            {
                formatString->m_data[i] = formatTemplate[i];
            }
            formatString->m_data[formatString->m_size - 1] = '\0';
            formatString->m_refCount = 1;
        }

        // Format the failure message with frame time and threshold
        BasicString<char, Detail::TempStringAllocator> formattedString;
        Format(formattedString, *formatString, dt, mMinimumFrameRate);

        // Write to debug log if available
        if (mTestLog)
        {
            nlWriteLineDebug(mTestLog, formattedString.c_str(), false);
            nlWriteLineDebug(mTestLog, "\n", false);
            nlFlushFileDebug(mTestLog);
        }

        // Clean up format string
        if (formatString)
        {
            formatString->m_refCount--;
            if (formatString->m_refCount == 0)
            {
                if (formatString->m_data)
                {
                    nlFree(formatString->m_data);
                }
                nlFree(formatString);
            }
        }

        // Clean up formatted string
        if (formattedString.m_refCount == 0)
        {
            if (formattedString.m_data)
            {
                nlFree(formattedString.m_data);
            }
            nlFree(&formattedString);
        }
    }

    // Check if test timeout has expired and frame rate test hasn't failed yet
    if (mTestTimeOut <= 0.0f && !mFrameRateTestFailure)
    {
        // Get the success output filename
        const char* frameRateTestSuccessOutput = "frameRateTestSuccessOutput__22@unnamed@TestTask_cpp@";

        // Open debug file for writing
        void* debugFile = nlOpenFileDebug(frameRateTestSuccessOutput, false, false);
        if (debugFile)
        {
            nlWriteLineDebug(debugFile, frameRateTestSuccessOutput, false);
            nlFlushFileDebug(debugFile);
            nlCloseFileDebug(debugFile);
        }

        // Create format string for success message
        BasicString<char, Detail::TempStringAllocator>* formatString = (BasicString<char, Detail::TempStringAllocator>*)nlMalloc(0x10, 8, true);
        if (formatString)
        {
            const char* formatTemplate = "SUCCESS: frame rate test successful, maintained {0} FPS";
            formatString->m_data = nullptr;
            formatString->m_size = 0;
            formatString->m_capacity = 0;

            // Calculate string length
            const char* p = formatTemplate;
            while (*p != '\0')
            {
                formatString->m_size++;
                p++;
            }
            formatString->m_size++; // Include null terminator

            // Allocate memory for string data
            formatString->m_data = (char*)nlMalloc(formatString->m_size, 8, true);
            formatString->m_capacity = formatString->m_size;

            // Copy the format template
            for (int i = 0; i < formatString->m_size - 1; i++)
            {
                formatString->m_data[i] = formatTemplate[i];
            }
            formatString->m_data[formatString->m_size - 1] = '\0';
            formatString->m_refCount = 1;
        }

        // Format the success message with minimum frame rate
        BasicString<char, Detail::TempStringAllocator> formattedString;
        Format(formattedString, *formatString, mMinimumFrameRate);

        // Write to debug log if available
        if (mTestLog)
        {
            nlWriteLineDebug(mTestLog, formattedString.c_str(), false);
            nlWriteLineDebug(mTestLog, "\n", false);
            nlFlushFileDebug(mTestLog);
        }

        // Clean up format string
        if (formatString)
        {
            formatString->m_refCount--;
            if (formatString->m_refCount == 0)
            {
                if (formatString->m_data)
                {
                    nlFree(formatString->m_data);
                }
                nlFree(formatString);
            }
        }

        // Clean up formatted string
        if (formattedString.m_refCount == 0)
        {
            if (formattedString.m_data)
            {
                nlFree(formattedString.m_data);
            }
            nlFree(&formattedString);
        }
    }
}
