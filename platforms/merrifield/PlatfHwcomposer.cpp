/*
 * Copyright © 2012 Intel Corporation
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Jackie Li <yaodong.li@intel.com>
 *
 */
#include <hal_public.h>
#include <HwcTrace.h>
#include <tangier/TngDisplayContext.h>
#include <PlatfDisplayPlaneManager.h>
#include <PlatfBufferManager.h>
#include <IDisplayDevice.h>
#include <PlatfPrimaryDevice.h>
#include <PlatfExternalDevice.h>
#include <PlatfVirtualDevice.h>
#include <PlatfHwcomposer.h>



namespace android {
namespace intel {

PlatfHwcomposer::PlatfHwcomposer()
    : Hwcomposer()
{
    CTRACE();
}

PlatfHwcomposer::~PlatfHwcomposer()
{
    CTRACE();
}

DisplayPlaneManager* PlatfHwcomposer::createDisplayPlaneManager()
{
    CTRACE();
    return (new PlatfDisplayPlaneManager());
}

BufferManager* PlatfHwcomposer::createBufferManager()
{
    CTRACE();
    return (new PlatfBufferManager());
}

IDisplayDevice* PlatfHwcomposer::createDisplayDevice(int disp,
                                                     DisplayPlaneManager& dpm)
{
    CTRACE();

    switch (disp) {
        case IDisplayDevice::DEVICE_PRIMARY:
            return new PlatfPrimaryDevice(*this, dpm);
        case IDisplayDevice::DEVICE_EXTERNAL:
            return new PlatfExternalDevice(*this, dpm);
        case IDisplayDevice::DEVICE_VIRTUAL:
            return new PlatfVirtualDevice(*this, dpm);
        default:
            ETRACE("invalid display device %d", disp);
            return NULL;
    }
}

IDisplayContext* PlatfHwcomposer::createDisplayContext()
{
    CTRACE();
    return new TngDisplayContext();
}

Hwcomposer* Hwcomposer::createHwcomposer()
{
    CTRACE();
    return new PlatfHwcomposer();
}

} //namespace intel
} //namespace android
