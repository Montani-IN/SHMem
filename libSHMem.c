#include <stdint.h>
#include <windows.h>

__declspec(dllexport) void* __stdcall GenSHMem(const uint8_t* name, const int32_t size) {
    if (name == 0 || size <= 0) return 0;

    const HANDLE hMapFile = CreateFileMapping(
            INVALID_HANDLE_VALUE,
            0,
            PAGE_READWRITE,
            0,
            size,
            name);

    if (hMapFile == 0)
    {
        return 0;
    }

    return hMapFile;
}

__declspec(dllexport) void* __stdcall GetSHMem(void *handle, const int32_t size) {
    if (handle == 0) return 0;

    void *pBuf = (LPTSTR) MapViewOfFile(handle,
                        FILE_MAP_ALL_ACCESS,
                        0,
                        0,
                        size);
    if (pBuf == 0) {
        CloseHandle(handle);
        return 0;
    }

    return pBuf;
}

__declspec(dllexport) void CloseSHMem(void *handle, const void *buffer) {
    if (buffer != 0) UnmapViewOfFile(buffer);
    if (handle != 0) CloseHandle(handle);
}