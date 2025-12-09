#ifndef _NLBSEARCH_H_
#define _NLBSEARCH_H_

/** EXAMPLE USAGE
 * Offset/Address/Size: 0x0 | 0x80213820 | size: 0x8C
 */

template <typename T, typename Key>
T* nlBSearch(const Key& key, T* base, int count)
{
    const Key keyVal = key;
    int low = -1;
    int high = count - 1;

    while ((high - low) > 1)
    {
        int mid = (low + high) / 2;

        if (base[mid].hash > keyVal)
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
    }

    if (base[high].hash == keyVal)
    {
        return &base[high];
    }

    if (low != -1 && base[low].hash == keyVal)
    {
        return &base[low];
    }

    return nullptr;
}

#endif // _NLBSEARCH_H_
