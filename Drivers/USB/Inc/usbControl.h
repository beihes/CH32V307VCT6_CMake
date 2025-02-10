/*
 * usbControl.h
 *
 *  Created on: 2025年2月3日
 *      Author: 26448
 */

#ifndef DRIVERS_USB_INC_USBCONTROL_H_
#define DRIVERS_USB_INC_USBCONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "cMyLib.h"
#include "ch32v30x_usbhs_device.h"
#include "SW_UDISK.h"
#include "usb_desc.h"
#include "key.h"
#include "led.h"

extern uint8_t usbState;

uint8_t Key_ControlUSB(void);

#ifdef __cplusplus
}
#endif

#endif /* DRIVERS_USB_INC_USBCONTROL_H_ */
