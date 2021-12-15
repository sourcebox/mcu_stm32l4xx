/**
 * @file        USB_ControlEndpoint.cpp
 *
 * Driver for USB control endpoint on STM32L4xx
 *
 * @author:     Oliver Rockstedt <info@sourcebox.de>
 * @license     MIT
 */


// Corresponding header
#include "USB_ControlEndpoint.h"

// Local includes
#include "USB.h"

// System libraries
#include <algorithm>


namespace mcu {


// ============================================================================
// Public members
// ============================================================================


// ============================================================================
// Protected members
// ============================================================================


void USB_ControlEndpoint::onReset()
{
    setType(Type::CONTROL);
    setTransmissionStatus(Status::NAK);
    setReceptionStatus(Status::VALID);
}


void USB_ControlEndpoint::onSetupReceptionComplete()
{
    dataStage = DataStage::NONE;
    dataStageLength = 0;
    onSetupStage();
    setReceptionStatus(Status::VALID);
}


void USB_ControlEndpoint::onReceptionComplete()
{
    if (dataStage == DataStage::IN) {
        onDataStageIN();
    } else if (dataStage == DataStage::OUT) {
        onDataStageOUT();
    }

    if (dataStage == DataStage::NONE) {
        onStatusStage();
    }

    setReceptionStatus(Status::VALID);
}


void USB_ControlEndpoint::onTransmissionComplete()
{
    if (dataStage == DataStage::IN) {
        onDataStageIN();
    }

    if (dataStage == DataStage::NONE) {
        onStatusStage();
    }
}


// ============================================================================
// Private members
// ============================================================================


void USB_ControlEndpoint::onSetupStage()
{
    // Packet received
    struct Request
    {
        uint8_t bmRequestType;
        uint8_t bRequest;
        uint16_t wValue;
        uint16_t wIndex;
        uint16_t wLength;
    } __attribute__((packed));

    uint8_t requestBuffer[sizeof(Request)];
    auto request = (Request*)requestBuffer;

    receive(requestBuffer, sizeof(requestBuffer));

    if (request->wLength > 0) {
        dataStage = request->bmRequestType & 0x80 ? DataStage::IN : DataStage::OUT;
        dataStageLength = request->wLength;
    } else {
        dataStage = DataStage::NONE;
        dataStageLength = 0;
    }

    if (request->bRequest == 0x00 && request->bmRequestType == 0x80) {
        // GET_STATUS
        // Todo: implement correct response
        uint8_t statusData[] = { 0, 0 };
        transmit(statusData, 2);
    } else if (request->bRequest == 0x01 && request->bmRequestType == 0x00) {
        // CLEAR_FEATURE
        transmit(nullptr, 0);
    } else if (request->bRequest == 0x03 && request->bmRequestType == 0x00) {
        // SET_FEATURE
        transmit(nullptr, 0);
    } else if (request->bRequest == 0x05 && request->bmRequestType == 0x00) {
        // SET_ADDRESS
        addressTemp = request->wValue & 0x7F;
        transmit(nullptr, 0);
    } else if (request->bRequest == 0x06 && request->bmRequestType == 0x80) {
        // GET_DESCRIPTOR
        auto type = request->wValue >> 8;
        auto index = request->wValue & 0xFF;

        if (descriptorCallbackFunc != nullptr) {
            auto descriptor = descriptorCallbackFunc(
                (USB_Descriptor::Type)type,
                index,
                descriptorCallbackContext
            );
            if (descriptor != nullptr) {
                descriptor->onInit();

                auto descriptorLength = descriptor->onGetLength();

                auto transmitSize = std::min((int)request->wLength,
                                             (int)descriptorLength);
                transmitSize = std::min(transmitSize, (int)txBufferSize);

                uint8_t descriptorBuffer[transmitSize];

                for (auto i = 0; i < transmitSize; i++) {
                    descriptorBuffer[i] = descriptor->onGetData(i);
                }

                transmit(descriptorBuffer, transmitSize);

                if (request->wLength > transmitSize
                        && descriptorLength > transmitSize) {
                    pendingDescriptor = descriptor;
                    pendingDescriptorDataIndex = transmitSize;
                } else {
                    descriptor->onDeinit();
                }
            }
        }
    } else if (request->bRequest == 0x07 && request->bmRequestType == 0x00) {
        // SET_DESCRIPTOR
        transmit(nullptr, 0);
    } else if (request->bRequest == 0x08 && request->bmRequestType == 0x80) {
        // GET_CONFIGURATION
        uint8_t configurationData[] = { 0 };
        transmit(configurationData, 1);
    } else if (request->bRequest == 0x09 && request->bmRequestType == 0x00) {
        // SET_CONFIGURATION
        auto& usb = USB::get();
        usb.status = USB::Status::CONFIGURED;
        transmit(nullptr, 0);
    }
}


void USB_ControlEndpoint::onDataStageIN()
{
    auto rxLength = getReceivedLength();

    if (rxLength == 0) {
        dataStage = DataStage::NONE;
        dataStageLength = 0;
    }

    if (pendingDescriptor != nullptr) {
        auto descriptorLength = pendingDescriptor->onGetLength();
        auto remainingLength = descriptorLength - pendingDescriptorDataIndex;

        auto transmitSize = std::min((int)txBufferSize, remainingLength);

        uint8_t descriptorBuffer[transmitSize];

        for (auto i = 0; i < transmitSize; i++) {
            descriptorBuffer[i] = pendingDescriptor->onGetData(i + pendingDescriptorDataIndex);
        }

        transmit(descriptorBuffer, transmitSize);

        pendingDescriptorDataIndex += transmitSize;

        if (pendingDescriptorDataIndex >= descriptorLength) {
            // Transfer complete
            pendingDescriptor->onDeinit();
            pendingDescriptor = nullptr;
            pendingDescriptorDataIndex = 0;
        }
    }
}


void USB_ControlEndpoint::onDataStageOUT()
{
}


void USB_ControlEndpoint::onStatusStage()
{
    if (addressTemp != 0) {
        auto registers = USB_Registers::get();
        registers->DADDR = addressTemp | (1 << USB_Registers::DADDR::EF);

        auto& usb = USB::get();
        usb.status = USB::Status::ADDRESSED;

        addressTemp = 0;
    }
}


}   // namespace mcu
