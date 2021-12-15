/**
 * @file        dso_handle.cpp
 *
 * Fix for missing __dso_handle when using static destructors
 *
 * @author      Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


extern "C"
int __aeabi_atexit(void* object, void (*destructor)(void*), void* dso_handle)
{
    static_cast<void>(object);
    static_cast<void>(destructor);
    static_cast<void>(dso_handle);

    return 0;
}


void* __dso_handle = nullptr;
