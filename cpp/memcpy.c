#include <stddef.h>
#include <stdio.h>

// 始终从前向后逐字节拷贝。
// 一旦 dst 落在 src 范围内，未读的源数据就会被覆盖
void* my_memcpy(void* dst, const void* src, size_t count)
{
    void* ret = dst;
    unsigned char* d = (unsigned char*)dst;
    const unsigned char* s = (const unsigned char*)src;

    while (count--) {
        *d++ = *s++;
    }

    return ret;
}

void *my_memmove(void* dst, const void* src, size_t count) {
    void* ret = dst;
    unsigned char* d = (unsigned char*)dst;
    const unsigned char* s = (const unsigned char*)src;

    if (d == s || count == 0)
        return ret;

    if (d < s || d >= s + count) {
        /* 无重叠，或目标在源前面：正向拷贝 */
        while (count--) {
            *d++ = *s++;
        }
    } else {
        /* 目标在源范围内：反向拷贝，避免覆盖未读数据 */
        d += count-1;
        s += count-1;
        while (count--) {
            *d-- = *s--;
        }
    }

    return ret;
}

int main()
{
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};

    printf("before memmove: \n");
    for (int i = 0; i < sizeof(arr)/sizeof(int); ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 把前5个元素后移2位 → 源和目标重叠
    // 结果: 1 2 1 2 3 4 5 8 9 10
    my_memmove(arr+2, arr, 5*sizeof(int));

    printf("after memmove: \n");
    for (int i = 0; i < sizeof(arr)/sizeof(int); ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
