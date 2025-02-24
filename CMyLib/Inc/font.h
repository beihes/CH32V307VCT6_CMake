/*
 * font.h
 *
 *  Created on: 2025年2月24日
 *      Author: 26448
 */

#ifndef CMYLIB_INC_FONT_H_
#define CMYLIB_INC_FONT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

#define ASCII12X06
#define ASCII16X08
#define ASCII24X12

    extern const uint8_t ascii12X06[95][12];
    extern const uint8_t ascii16X08[95][16];
    extern const uint8_t ascii24X12[95][24];

#ifdef __cplusplus
}
#endif

#endif /* CMYLIB_INC_FONT_H_ */
