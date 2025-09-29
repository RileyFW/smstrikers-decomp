#ifndef _NLBSEARCH_H_
#define _NLBSEARCH_H_

/** EXAMPLE USAGE
 * Offset/Address/Size: 0x0 | 0x80213820 | size: 0x8C
 */

template <typename T, typename Key>
T* nlBSearch(const Key& key, T* base, int count)
{
    int low = 0;
    int high = count - 1;

    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (key < base[mid].hash)
        {
            high = mid - 1;
        }
        else if (key > base[mid].hash)
        {
            low = mid + 1;
        }
        else
        {
            return &base[mid]; // Found
        }
    }

    return nullptr; // Not found
}

#endif // _NLBSEARCH_H_
