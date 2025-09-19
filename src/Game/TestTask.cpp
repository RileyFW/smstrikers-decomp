#pragma pool_data off

#include "Game/TestTask.h"

#include "NL/nlDebugFile.h"
#include "NL/nlMemory.h"
#include "NL/nlConfig.h"
#include "types.h"

#include "NL/nlBasicString.h"

static const char* testLog;
static const char* smokeTestSuccessOutput;     // size: 0x4, address: 0x80396644
static const char* frameRateTestSuccessOutput; // size: 0x4, address: 0x80396648

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
    mTestTimeOut = GetConfigFloat(Config::Global(), "test/time_out_sec", 0.0f);
    mRunUnitTests = GetConfigBool(Config::Global(), "test/run_unit_tests", false);
    mRunSmokeTest = GetConfigBool(Config::Global(), "test/run_smoke_test", false);
    mRunFrameRateTest = GetConfigBool(Config::Global(), "test/run_frame_rate_test", false);
    mMinimumFrameRate = GetConfigFloat(Config::Global(), "test/minimum_frame_rate", 20.0f);

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

            float configValue = GetConfigFloat(Config::Global(), "test/time_out_sec ", 1.0f);

            BasicString<char, Detail::TempStringAllocator> formattedString;
            Format(formattedString, *formatString, configValue);

            if (mTestLog)
            {
                nlWriteLineDebug(mTestLog, formattedString.c_str(), false);
                nlWriteLineDebug(mTestLog, "\n", false); // Additional debug message
                nlFlushFileDebug(mTestLog);
            }

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

        BasicString<char, Detail::TempStringAllocator> formattedString;
        Format(formattedString, *formatString, mMinimumFrameRate);

        if (mTestLog)
        {
            nlWriteLineDebug(mTestLog, formattedString.c_str(), false);
            nlWriteLineDebug(mTestLog, "\n", false);
            nlFlushFileDebug(mTestLog);
        }

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
