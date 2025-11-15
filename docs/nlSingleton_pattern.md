# The nlSingleton Pattern

## Overview

The `nlSingleton` pattern is a template-based singleton implementation used throughout the Super Mario Strikers codebase. It ensures that only one instance of a class exists throughout the application's lifetime, providing global access to that instance.

## Implementation

The `nlSingleton` template is defined in `include/NL/nlSingleton.h`:

```cpp
template <class T>
class nlSingleton
{
public:
    static T* Instance() { return s_pInstance; }

    static void CreateInstance()
    {
        if (!s_pInstance)
            s_pInstance = new T();
    }

    static void DestroyInstance()
    {
        T* p = s_pInstance;
        if (p)
        {
            delete p;
            s_pInstance = 0;
        }
    }

    static T* s_pInstance;
};

template <class T>
T* nlSingleton<T>::s_pInstance = 0;
```

### Key Components

- **`s_pInstance`**: A static pointer that holds the single instance of the class
- **`Instance()`**: Returns a pointer to the singleton instance (may return `nullptr` if not created)
- **`CreateInstance()`**: Creates the singleton instance if it doesn't already exist
- **`DestroyInstance()`**: Safely deletes the singleton instance and resets the pointer

## How to Use nlSingleton

### Step 1: Inherit from nlSingleton

To make a class a singleton, inherit from `nlSingleton` with your class as the template parameter:

```cpp
class FEResourceManager : public nlTask, public nlSingleton<FEResourceManager>
{
    // ... class implementation
};
```

Note that you can inherit from multiple base classes (like `nlTask` in this example) alongside `nlSingleton`.

### Step 2: Create the Instance

Before using the singleton, you must create it by calling `CreateInstance()`:

```cpp
FEResourceManager::CreateInstance();
```

This should typically be done during initialization, before the singleton is first accessed.

### Step 3: Access the Instance

Access the singleton instance using the `Instance()` static method:

```cpp
FEResourceManager::Instance()->Run(dt);
```

The `Instance()` method returns a pointer to the singleton, so you can:
- Call methods directly: `FEResourceManager::Instance()->SomeMethod()`
- Check if it exists: `if (FEResourceManager::Instance() != nullptr)`
- Store a reference: `FEResourceManager* manager = FEResourceManager::Instance();`

## Real-World Examples

### Example 1: FEResourceManager

```cpp
// In FrontEndTask.cpp
if (FEResourceManager::Instance() != nullptr)
{
    FEResourceManager::Instance()->Run(dt);
    FESceneManager::Instance()->Update(dt);
    FESceneManager::Instance()->RenderActiveScenes();
}
```

### Example 2: GameInfoManager

```cpp
// Accessing the singleton instance
short side = GameInfoManager::Instance()->GetPlayingSide(padIdx);
```

### Example 3: StatsTracker

```cpp
// Multiple calls to the same singleton instance
StatsTracker::Instance()->AddStat(STATS_BUTTON_PRESSES, side, -1, buttonPressCount);
StatsTracker::Instance()->AddUserStatByPad(STATS_BUTTON_PRESSES, padIdx, buttonPressCount);
```

## Important Notes

1. **Null Safety**: Always check if the instance exists before using it, as `Instance()` can return `nullptr` if `CreateInstance()` hasn't been called yet.

2. **Initialization Order**: Singletons must be created before they're accessed. Ensure `CreateInstance()` is called during appropriate initialization phases.

3. **Destruction**: Use `DestroyInstance()` to clean up the singleton when it's no longer needed, typically during shutdown.

4. **Thread Safety**: This implementation is not thread-safe. If multiple threads access the singleton, additional synchronization would be required.

5. **Multiple Inheritance**: The pattern works well with multiple inheritance, as shown with `FEResourceManager` which inherits from both `nlTask` and `nlSingleton<FEResourceManager>`.

## Common Patterns in the Codebase

Many manager classes use this pattern:
- `FEResourceManager` - Manages front-end resources
- `FESceneManager` - Manages scene transitions
- `GameInfoManager` - Manages game state information
- `StatsTracker` - Tracks game statistics
- `FontManager` - Manages font resources

All of these follow the same pattern: inherit from `nlSingleton<T>`, create the instance during initialization, and access it via `Instance()` throughout the codebase.
