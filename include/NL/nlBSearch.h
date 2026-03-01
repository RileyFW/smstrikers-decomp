#ifndef _NLBSEARCH_H_
#define _NLBSEARCH_H_

/** EXAMPLE USAGE
 * Offset/Address/Size: 0x0 | 0x80213820 | size: 0x8C
 */

template <typename T, typename Key>
T* nlBSearch(const Key& key, T* base, int count)
{
    const unsigned long* keyPtr = (const unsigned long*)&key;
    unsigned long keyVal = (unsigned long)key;
    int high = count - 1;
    int low = -1;

    while ((high - low) > 1)
    {
        int mid = (high + low) / 2;

        if (base[mid].hash > keyVal)
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
    }

    unsigned long highHash = base[high].hash;
    if (highHash == *keyPtr)
    {
        return &base[high];
    }

    if (low == -1)
    {
        return nullptr;
    }

    unsigned long lowHash = base[low].hash;
    if (lowHash == *keyPtr)
    {
        return &base[low];
    }

    return nullptr;
}

#endif // _NLBSEARCH_H_
