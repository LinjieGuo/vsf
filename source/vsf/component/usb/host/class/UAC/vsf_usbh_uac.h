/*****************************************************************************
 *   Copyright(C)2009-2019 by VSF Team                                       *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the "License");          *
 *  you may not use this file except in compliance with the License.         *
 *  You may obtain a copy of the License at                                  *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an "AS IS" BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 ****************************************************************************/

#ifndef __VSF_USBH_UAC_H__
#define __VSF_USBH_UAC_H__


/*============================ INCLUDES ======================================*/
#include "component/usb/vsf_usb_cfg.h"

#if VSF_USE_USB_HOST == ENABLED && VSF_USE_USB_HOST_UAC == ENABLED

#include "component/usb/common/class/UAC/vsf_usb_UAC.h"

#if     defined(VSF_USBH_UAC_IMPLEMENT)
#   undef VSF_USBH_UAC_IMPLEMENT
#   define __PLOOC_CLASS_IMPLEMENT
#   define PUBLIC_CONST
#else
#   define PUBLIC_CONST                         const
#endif
#include "utilities/ooc_class.h"

#ifdef __cplusplus
extern "C" {
#endif

/*============================ MACROS ========================================*/

// for some hcd, one urb will take 2ms(eg. ohci), so need 2 urbs to implement 1ms interval transaction
#ifndef VSF_USBH_UAC_CFG_URB_NUM_PER_STREAM
#   define VSF_USBH_UAC_CFG_URB_NUM_PER_STREAM  1
#endif

/*============================ MACROFIED FUNCTIONS ===========================*/
/*============================ TYPES =========================================*/

declare_simple_class(vk_usbh_uac_stream_t)

def_simple_class(vk_usbh_uac_stream_t) {
    public_member(
        PUBLIC_CONST uint8_t is_in          : 1;
        PUBLIC_CONST uint8_t sample_size    : 3;
        PUBLIC_CONST uint8_t channel_num;
        PUBLIC_CONST uint16_t format;
        PUBLIC_CONST uint32_t sample_rate;
    )

    private_member(
#if VSF_USBH_UAC_CFG_URB_NUM_PER_STREAM > 1
        uint8_t idx;
#endif
        uint8_t is_connected                : 1;
        uint8_t is_to_disconnect            : 1;

        vk_usbh_urb_t urb[VSF_USBH_UAC_CFG_URB_NUM_PER_STREAM];
        vsf_stream_t *stream;
        void *param;
    )
};

/*============================ GLOBAL VARIABLES ==============================*/

extern const vk_usbh_class_drv_t vk_usbh_uac_drv;

/*============================ PROTOTYPES ====================================*/

extern vk_usbh_uac_stream_t * vsf_usbh_uac_get_stream_info(void *param, uint_fast8_t stream_idx);
extern vsf_err_t vsf_usbh_uac_connect_stream(void *param, uint_fast8_t stream_idx, vsf_stream_t *stream);
extern void vsf_usbh_uac_disconnect_stream(void *param, uint_fast8_t stream_idx);

#ifdef __cplusplus
}
#endif

#endif
#endif
