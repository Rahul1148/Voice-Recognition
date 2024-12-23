/*
*
* SPDX-License-Identifier: BSD-3-Clause
*
* Copyright (c) 2016-2022, Arm Limited. All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
* - Redistributions of source code must retain the above copyright notice, this
*   list of conditions and the following disclaimer.
* - Redistributions in binary form must reproduce the above copyright notice, this
*    list of conditions and the following disclaimer in the documentation and/or
*    other materials provided with the distribution.
* - Neither the name of ARM nor the names of its contributors may be used to
*    endorse or promote products derived from this software without specific prior
*    written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/

#ifndef _ACAMERA_COMMAND_API_H_
#define _ACAMERA_COMMAND_API_H_
#include "acamera_types.h"


// ------------------------------------------------------------------------------ //
//		ERROR REASONS
// ------------------------------------------------------------------------------ //
#define ERR_UNKNOWN                                       0x00000000
#define ERR_BAD_ARGUMENT                                  0x00000001
#define ERR_WRONG_SIZE                                    0x00000002


// ------------------------------------------------------------------------------ //
//		WDR MODES
// ------------------------------------------------------------------------------ //
#define WDR_MODE_LINEAR                                   0x00000000
#define WDR_MODE_NATIVE                                   0x00000001
#define WDR_MODE_FS_LIN                                   0x00000002
#define WDR_MODE_COUNT                                    0x00000003


// ------------------------------------------------------------------------------ //
//		STATIC CALIBRATION VALUES
// ------------------------------------------------------------------------------ //
#define CALIBRATION_LIGHT_SRC                             0x00000000
#define CALIBRATION_RG_POS                                0x00000001
#define CALIBRATION_BG_POS                                0x00000002
#define CALIBRATION_MESH_RGBG_WEIGHT                      0x00000003
#define CALIBRATION_MESH_LS_WEIGHT                        0x00000004
#define CALIBRATION_MESH_COLOR_TEMPERATURE                0x00000005
#define CALIBRATION_WB_STRENGTH                           0x00000006
#define CALIBRATION_SKY_LUX_TH                            0x00000007
#define CALIBRATION_CT_RG_POS_CALC                        0x00000008
#define CALIBRATION_CT_BG_POS_CALC                        0x00000009
#define CALIBRATION_COLOR_TEMP                            0x0000000A
#define CALIBRATION_CT65POS                               0x0000000B
#define CALIBRATION_CT40POS                               0x0000000C
#define CALIBRATION_CT30POS                               0x0000000D
#define CALIBRATION_EVTOLUX_EV_LUT                        0x0000000E
#define CALIBRATION_EVTOLUX_LUX_LUT                       0x0000000F
#define CALIBRATION_BLACK_LEVEL_R                         0x00000010
#define CALIBRATION_BLACK_LEVEL_GR                        0x00000011
#define CALIBRATION_BLACK_LEVEL_GB                        0x00000012
#define CALIBRATION_BLACK_LEVEL_B                         0x00000013
#define CALIBRATION_STATIC_WB                             0x00000014
#define CALIBRATION_MT_ABSOLUTE_LS_A_CCM                  0x00000015
#define CALIBRATION_MT_ABSOLUTE_LS_D40_CCM                0x00000016
#define CALIBRATION_MT_ABSOLUTE_LS_D50_CCM                0x00000017
#define CALIBRATION_SHADING_LS_A_R                        0x00000018
#define CALIBRATION_SHADING_LS_A_G                        0x00000019
#define CALIBRATION_SHADING_LS_A_B                        0x0000001A
#define CALIBRATION_SHADING_LS_TL84_R                     0x0000001B
#define CALIBRATION_SHADING_LS_TL84_G                     0x0000001C
#define CALIBRATION_SHADING_LS_TL84_B                     0x0000001D
#define CALIBRATION_SHADING_LS_D65_R                      0x0000001E
#define CALIBRATION_SHADING_LS_D65_G                      0x0000001F
#define CALIBRATION_SHADING_LS_D65_B                      0x00000020
#define CALIBRATION_AWB_WARMING_LS_A                      0x00000021
#define CALIBRATION_AWB_WARMING_LS_D50                    0x00000022
#define CALIBRATION_AWB_WARMING_LS_D75                    0x00000023
#define CALIBRATION_AWB_WARMING_CCT                       0x00000024
#define CALIBRATION_NOISE_PROFILE                         0x00000025
#define CALIBRATION_DEMOSAIC                              0x00000026
#define CALIBRATION_GAMMA                                 0x00000027
#define CALIBRATION_IRIDIX_ASYMMETRY                      0x00000028
#define CALIBRATION_AWB_SCENE_PRESETS                     0x00000029
#define CALIBRATION_WDR_NP_LUT                            0x0000002A
#define CALIBRATION_DECOMPANDER0_MEM                      0x0000002B
#define CALIBRATION_DECOMPANDER1_MEM                      0x0000002C
#define CALIBRATION_AWB_MIX_LIGHT_PARAMETERS              0x0000002D
#define CALIBRATION_SCALER_H_FILTER                       0x0000002E
#define CALIBRATION_SCALER_V_FILTER                       0x0000002F


// ------------------------------------------------------------------------------ //
//		DYNAMIC CALIBRATION VALUES
// ------------------------------------------------------------------------------ //
#define CALIBRATION_STITCHING_LM_MED_NOISE_INTENSITY      0x00000030
#define CALIBRATION_AWB_COLOUR_PREFERENCE                 0x00000031
#define CALIBRATION_PF_CONFIG                             0x00000032
#define CALIBRATION_PF_RADIAL_LUT                         0x00000033
#define CALIBRATION_PF_RADIAL_PARAMS                      0x00000034
#define CALIBRATION_SINTER_RADIAL_LUT                     0x00000035
#define CALIBRATION_SINTER_RADIAL_PARAMS                  0x00000036
#define CALIBRATION_AWB_BG_MAX_GAIN                       0x00000037
#define CALIBRATION_IRIDIX8_STRENGTH_DK_ENH_CONTROL       0x00000038
#define CALIBRATION_CMOS_CONTROL                          0x00000039
#define CALIBRATION_CMOS_EXPOSURE_PARTITION_LUTS          0x0000003A
#define CALIBRATION_STATUS_INFO                           0x0000003B
#define CALIBRATION_AUTO_LEVEL_CONTROL                    0x0000003C
#define CALIBRATION_DP_SLOPE                              0x0000003D
#define CALIBRATION_DP_THRESHOLD                          0x0000003E
#define CALIBRATION_STITCHING_LM_MOV_MULT                 0x0000003F
#define CALIBRATION_STITCHING_LM_NP                       0x00000040
#define CALIBRATION_STITCHING_MS_MOV_MULT                 0x00000041
#define CALIBRATION_STITCHING_MS_NP                       0x00000042
#define CALIBRATION_STITCHING_SVS_MOV_MULT                0x00000043
#define CALIBRATION_STITCHING_SVS_NP                      0x00000044
#define CALIBRATION_EVTOLUX_PROBABILITY_ENABLE            0x00000045
#define CALIBRATION_AWB_AVG_COEF                          0x00000046
#define CALIBRATION_IRIDIX_AVG_COEF                       0x00000047
#define CALIBRATION_IRIDIX_STRENGTH_MAXIMUM               0x00000048
#define CALIBRATION_IRIDIX_MIN_MAX_STR                    0x00000049
#define CALIBRATION_IRIDIX_EV_LIM_FULL_STR                0x0000004A
#define CALIBRATION_IRIDIX_EV_LIM_NO_STR                  0x0000004B
#define CALIBRATION_AE_CORRECTION                         0x0000004C
#define CALIBRATION_AE_EXPOSURE_CORRECTION                0x0000004D
#define CALIBRATION_SINTER_STRENGTH                       0x0000004E
#define CALIBRATION_SINTER_STRENGTH1                      0x0000004F
#define CALIBRATION_SINTER_THRESH1                        0x00000050
#define CALIBRATION_SINTER_THRESH4                        0x00000051
#define CALIBRATION_SINTER_INTCONFIG                      0x00000052
#define CALIBRATION_SINTER_NOISE_PROFILE_CONFIG           0x00000053
#define CALIBRATION_SHARP_FR_CONFIG                       0x00000054
#define CALIBRATION_SHARP_DS1_CONFIG                      0x00000055
#define CALIBRATION_CNR_CONFIG                            0x00000056
#define CALIBRATION_SHARP_ALT_D                           0x00000057
#define CALIBRATION_SHARP_ALT_UD                          0x00000058
#define CALIBRATION_SHARP_ALT_DU                          0x00000059
#define CALIBRATION_DEMOSAIC_CONFIG                       0x0000005A
#define CALIBRATION_DEMOSAIC_UU_SLOPE                     0x0000005B
#define CALIBRATION_DEMOSAIC_UU_SH_SLOPE                  0x0000005C
#define CALIBRATION_MESH_SHADING_STRENGTH                 0x0000005D
#define CALIBRATION_SATURATION_STRENGTH                   0x0000005E
#define CALIBRATION_CCM_ONE_GAIN_THRESHOLD                0x0000005F
#define CALIBRATION_RGB2YUV_CONVERSION                    0x00000060
#define CALIBRATION_AWB_ZONE_WGHT_HOR                     0x00000061
#define CALIBRATION_AWB_ZONE_WGHT_VER                     0x00000062
#define CALIBRATION_SHARPEN_FR                            0x00000063
#define CALIBRATION_SHARPEN_DS1                           0x00000064
#define CALIBRATION_TEMPER_STRENGTH                       0x00000065
#define CALIBRATION_TEMPER_MOT_THRESH                     0x00000066
#define CALIBRATION_TEMPER_MOT_SLOPE                      0x00000067
#define CALIBRATION_TEMPER_NOISE_PROFILE_CONFIG           0x00000068
#define CALIBRATION_SINTER_STRENGTH_MC_CONTRAST           0x00000069
#define CALIBRATION_EXPOSURE_RATIO_ADJUSTMENT             0x0000006A
#define CALIBRATION_CNR_UV_DELTA12_SLOPE                  0x0000006B
#define CALIBRATION_FS_MC_OFF                             0x0000006C
#define CALIBRATION_SINTER_SAD                            0x0000006D
#define CALIBRATION_AF_LMS                                0x0000006E
#define CALIBRATION_AF_INPUT_ROI                          0x0000006F
#define CALIBRATION_AF_LMS_EXIT_THRESHOLD                 0x00000070
#define CALIBRATION_AF_ZONE_WGHT_HOR                      0x00000071
#define CALIBRATION_AF_ZONE_WGHT_VER                      0x00000072
#define CALIBRATION_AE_CONTROL_HDR_TARGET                 0x00000073
#define CALIBRATION_AE_CONTROL                            0x00000074
#define CALIBRATION_CUSTOM_SETTINGS_CONTEXT               0x00000075
#define CALIBRATION_GAMMA_EV1                             0x00000076
#define CALIBRATION_GAMMA_EV2                             0x00000077
#define CALIBRATION_GAMMA_THRESHOLD                       0x00000078
#define CALIBRATION_DEMOSAIC_FC_SLOPE                     0x00000079
#define CALIBRATION_PF_SAD_THRESH                         0x0000007A
#define CALIBRATION_PF_SAD_SLOPE                          0x0000007B
#define CALIBRATION_SINTER_MOTION_OFFSET_0                0x0000007C
#define CALIBRATION_SINTER_MOTION_OFFSET_1                0x0000007D
#define CALIBRATION_SINTER_MOTION_OFFSET_2                0x0000007E


// ------------------------------------------------------------------------------ //
//		DYNAMIC STATE VALUES
// ------------------------------------------------------------------------------ //

#define CALIBRATION_TOTAL_SIZE 127
//------------------FILE TRANSFER-------------------


// ------------------------------------------------------------------------------ //
//		COMMAND TYPE LIST
// ------------------------------------------------------------------------------ //
#define TGENERAL                                          0x00000000
#define TSELFTEST                                         0x00000001
#define TSENSOR                                           0x00000002
#define TLENS                                             0x00000003
#define TSYSTEM                                           0x00000004
#define TISP_MODULES                                      0x00000005
#define TSTATUS                                           0x00000006
#define TIMAGE                                            0x00000008
#define TALGORITHMS                                       0x00000009
#define TSCENE_MODES                                      0x0000000A
#define TREGISTERS                                        0x0000000B
#define TMONITOR                                          0x0000000C


// ------------------------------------------------------------------------------ //
//		BUFFER TYPES
// ------------------------------------------------------------------------------ //
#define STATIC_CALIBRATIONS_ID                            0x00000000
#define DYNAMIC_CALIBRATIONS_ID                           0x00000001
#define FILE_TRANSFER_ID                                  0x00000002
#define DYNAMIC_STATE_ID                                  0x00000003


// ------------------------------------------------------------------------------ //
//		COMMAND LIST
// ------------------------------------------------------------------------------ //
#define CONTEXT_NUMBER                                    0x00000000
#define ACTIVE_CONTEXT                                    0x00000001
#define FW_REVISION                                       0x00000002
#define SENSOR_STREAMING                                  0x00000003
#define SENSOR_SUPPORTED_PRESETS                          0x00000004
#define SENSOR_PRESET                                     0x00000005
#define SENSOR_WDR_MODE                                   0x00000006
#define SENSOR_FPS                                        0x00000007
#define SENSOR_WIDTH                                      0x00000008
#define SENSOR_HEIGHT                                     0x00000009
#define SENSOR_EXPOSURES                                  0x0000000A
#define SENSOR_INFO_PRESET                                0x0000000B
#define SENSOR_INFO_WDR_MODE                              0x0000000C
#define SENSOR_INFO_FPS                                   0x0000000D
#define SENSOR_INFO_WIDTH                                 0x0000000E
#define SENSOR_INFO_HEIGHT                                0x0000000F
#define SENSOR_INFO_BITS                                  0x00000010
#define SENSOR_INFO_EXPOSURES                             0x00000011
#define SENSOR_LINES_PER_SECOND                           0x00000012
#define SENSOR_INTEGRATION_TIME_MIN                       0x00000013
#define SENSOR_INTEGRATION_TIME_LIMIT                     0x00000014
#define SENSOR_INFO_PHYSICAL_WIDTH                        0x00000015
#define SENSOR_INFO_PHYSICAL_HEIGHT                       0x00000016
#define LENS_INFO_MINFOCUS_DISTANCE                       0x00000017
#define LENS_INFO_HYPERFOCAL_DISTANCE                     0x00000018
#define LENS_INFO_FOCAL_LENGTH                            0x00000019
#define LENS_INFO_APERTURE                                0x0000001A
#define SYSTEM_LOGGER_LEVEL                               0x0000001B
#define SYSTEM_LOGGER_MASK                                0x0000001C
#define BUFFER_DATA_TYPE                                  0x0000001D
#define TEST_PATTERN_ENABLE_ID                            0x0000001E
#define TEST_PATTERN_MODE_ID                              0x0000001F
#define M2M_PROCESS_REQUEST                               0x00000020
#define TEMPER4_MODE                                      0x00000021
#define TEMPER4_COMPRESS_PIXEL_MODE                       0x00000022
#define TEMPER4_COMPRESS_META_MODE                        0x00000023
#define SYSTEM_FREEZE_FIRMWARE                            0x00000024
#define SYSTEM_MANUAL_EXPOSURE                            0x00000025
#define SYSTEM_MANUAL_EXPOSURE_RATIO                      0x00000026
#define SYSTEM_MANUAL_INTEGRATION_TIME                    0x00000027
#define SYSTEM_MANUAL_MAX_INTEGRATION_TIME                0x00000028
#define SYSTEM_MANUAL_SENSOR_ANALOG_GAIN                  0x00000029
#define SYSTEM_MANUAL_SENSOR_DIGITAL_GAIN                 0x0000002A
#define SYSTEM_MANUAL_ISP_DIGITAL_GAIN                    0x0000002B
#define SYSTEM_MANUAL_AWB                                 0x0000002C
#define SYSTEM_MANUAL_CCM                                 0x0000002D
#define SYSTEM_MANUAL_SATURATION                          0x0000002E
#define SYSTEM_EXPOSURE                                   0x0000002F
#define SYSTEM_EXPOSURE_RATIO                             0x00000030
#define SYSTEM_MAX_EXPOSURE_RATIO                         0x00000031
#define SYSTEM_INTEGRATION_TIME                           0x00000032
#define SYSTEM_LONG_INTEGRATION_TIME                      0x00000033
#define SYSTEM_SHORT_INTEGRATION_TIME                     0x00000034
#define SYSTEM_MAX_INTEGRATION_TIME                       0x00000035
#define SYSTEM_SENSOR_ANALOG_GAIN                         0x00000036
#define SYSTEM_MAX_SENSOR_ANALOG_GAIN                     0x00000037
#define SYSTEM_SENSOR_DIGITAL_GAIN                        0x00000038
#define SYSTEM_MAX_SENSOR_DIGITAL_GAIN                    0x00000039
#define SYSTEM_ISP_DIGITAL_GAIN                           0x0000003A
#define SYSTEM_MAX_ISP_DIGITAL_GAIN                       0x0000003B
#define SYSTEM_AWB_RED_GAIN                               0x0000003C
#define SYSTEM_AWB_GREEN_EVEN_GAIN                        0x0000003D
#define SYSTEM_AWB_GREEN_ODD_GAIN                         0x0000003E
#define SYSTEM_AWB_BLUE_GAIN                              0x0000003F
#define SYSTEM_CCM_MATRIX_RR                              0x00000040
#define SYSTEM_CCM_MATRIX_RG                              0x00000041
#define SYSTEM_CCM_MATRIX_RB                              0x00000042
#define SYSTEM_CCM_MATRIX_GR                              0x00000043
#define SYSTEM_CCM_MATRIX_GG                              0x00000044
#define SYSTEM_CCM_MATRIX_GB                              0x00000045
#define SYSTEM_CCM_MATRIX_BR                              0x00000046
#define SYSTEM_CCM_MATRIX_BG                              0x00000047
#define SYSTEM_CCM_MATRIX_BB                              0x00000048
#define SYSTEM_SATURATION_TARGET                          0x00000049
#define SYSTEM_ANTIFLICKER_ENABLE                         0x0000004A
#define SYSTEM_ANTI_FLICKER_FREQUENCY                     0x0000004B
#define SYSTEM_DYNAMIC_GAMMA_ENABLE                       0x0000004C
#define CALIBRATION_UPDATE                                0x0000004D
#define ISP_MODULES_MANUAL_IRIDIX                         0x0000004E
#define ISP_MODULES_MANUAL_SINTER                         0x0000004F
#define ISP_MODULES_MANUAL_TEMPER                         0x00000050
#define ISP_MODULES_MANUAL_AUTO_LEVEL                     0x00000051
#define ISP_MODULES_MANUAL_FRAME_STITCH                   0x00000052
#define ISP_MODULES_MANUAL_RAW_FRONTEND                   0x00000053
#define ISP_MODULES_MANUAL_BLACK_LEVEL                    0x00000054
#define ISP_MODULES_MANUAL_SHADING                        0x00000055
#define ISP_MODULES_MANUAL_DEMOSAIC                       0x00000056
#define ISP_MODULES_MANUAL_CNR                            0x00000057
#define ISP_MODULES_MANUAL_SHARPEN                        0x00000058
#define STATUS_INFO_EXPOSURE_LOG2_ID                      0x00000059
#define STATUS_INFO_GAIN_ONES_ID                          0x0000005A
#define STATUS_INFO_GAIN_LOG2_ID                          0x0000005B
#define STATUS_INFO_AWB_MIX_LIGHT_CONTRAST                0x0000005C
#define STATUS_INFO_AF_LENS_POS                           0x0000005D
#define STATUS_INFO_AF_FOCUS_VALUE                        0x0000005E
#define DMA_READER_OUTPUT_ID                              0x00000066
#define FR_FORMAT_BASE_PLANE_ID                           0x00000067
#define FR_RAW_BYPASS                                     0x00000068
#define FR_FPS_THROTTLE_FACTOR_ID                         0x00000069
#define DS1_FORMAT_BASE_PLANE_ID                          0x0000006A
#define DS1_FPS_THROTTLE_FACTOR_ID                        0x0000006B
#define ORIENTATION_VFLIP_ID                              0x0000006C
#define IMAGE_RESIZE_TYPE_ID                              0x0000006D
#define IMAGE_RESIZE_ENABLE_ID                            0x0000006E
#define IMAGE_RESIZE_WIDTH_ID                             0x0000006F
#define IMAGE_RESIZE_HEIGHT_ID                            0x00000070
#define IMAGE_CROP_XOFFSET_ID                             0x00000071
#define IMAGE_CROP_YOFFSET_ID                             0x00000072
#define AF_LENS_STATUS                                    0x00000073
#define AF_MODE_ID                                        0x00000074
#define AF_STATE_ID                                       0x00000075
#define CAF_STATE_ID                                      0x00000076
#define AF_ROI_ID                                         0x00000077
#define AF_MANUAL_CONTROL_ID                              0x00000078
#define AE_MODE_ID                                        0x00000079
#define AE_STATE_ID                                       0x0000007A
#define AE_SPLIT_PRESET_ID                                0x0000007B
#define AE_GAIN_ID                                        0x0000007C
#define AE_EXPOSURE_ID                                    0x0000007D
#define AE_ROI_ID                                         0x0000007E
#define AE_COMPENSATION_ID                                0x0000007F
#define AWB_MODE_ID                                       0x00000080
#define AWB_STATE_ID                                      0x00000081
#define AWB_TEMPERATURE_ID                                0x00000082
#define NOISE_REDUCTION_MODE_ID                           0x00000083
#define COLOR_MODE_ID                                     0x00000084
#define BRIGHTNESS_STRENGTH_ID                            0x00000085
#define CONTRAST_STRENGTH_ID                              0x00000086
#define SATURATION_STRENGTH_ID                            0x00000087
#define SHARPENING_STRENGTH_ID                            0x00000088
#define SHADING_STRENGTH_ID                               0x00000089
#define HUE_THETA_ID                                      0x0000008A
#define REGISTERS_ADDRESS_ID                              0x0000008B
#define REGISTERS_SIZE_ID                                 0x0000008C
#define REGISTERS_SOURCE_ID                               0x0000008D
#define REGISTERS_VALUE_ID                                0x0000008E
#define MON_ERROR_CALIBRATION_LUT_NULL                    0x0000008F
#define MON_ERROR_CMOS_FS_DELAY                           0x00000090
#define MON_ERROR_CMOS_UPDATE_NOT_IN_VB                   0x00000091
#define MON_ERROR_CMOS_UPDATE_DGAIN_WRONG_TIMING          0x00000092
#define MON_ERROR_IRIDIX_UPDATE_NOT_IN_VB                 0x00000093
#define MON_STATUS_AE_RESET                               0x00000094
#define MON_STATUS_AE_FPT_MIN                             0x00000095
#define MON_STATUS_AE_FPT_CUR                             0x00000096
#define MON_STATUS_AE_FPT_MAX                             0x00000097
#define MON_STATUS_AE_DELAY_STATS2EV_MIN                  0x00000098
#define MON_STATUS_AE_DELAY_STATS2EV_CUR                  0x00000099
#define MON_STATUS_AE_DELAY_STATS2EV_MAX                  0x0000009A
#define MON_STATUS_AE_DELAY_EV2APPLY_MIN                  0x0000009B
#define MON_STATUS_AE_DELAY_EV2APPLY_CUR                  0x0000009C
#define MON_STATUS_AE_DELAY_EV2APPLY_MAX                  0x0000009D
#define MON_STATUS_AWB_RESET                              0x0000009E
#define MON_STATUS_AWB_FPT_MIN                            0x0000009F
#define MON_STATUS_AWB_FPT_CUR                            0x000000A0
#define MON_STATUS_AWB_FPT_MAX                            0x000000A1
#define MON_STATUS_AWB_DELAY_STATS2GAIN_MIN               0x000000A2
#define MON_STATUS_AWB_DELAY_STATS2GAIN_CUR               0x000000A3
#define MON_STATUS_AWB_DELAY_STATS2GAIN_MAX               0x000000A4
#define MON_STATUS_AWB_DELAY_GAIN2APPLY_MIN               0x000000A5
#define MON_STATUS_AWB_DELAY_GAIN2APPLY_CUR               0x000000A6
#define MON_STATUS_AWB_DELAY_GAIN2APPLY_MAX               0x000000A7
#define MON_STATUS_GAMMA_RESET                            0x000000A8
#define MON_STATUS_GAMMA_FPT_MIN                          0x000000A9
#define MON_STATUS_GAMMA_FPT_CUR                          0x000000AA
#define MON_STATUS_GAMMA_FPT_MAX                          0x000000AB
#define MON_STATUS_GAMMA_DELAY_STATS2LUT_MIN              0x000000AC
#define MON_STATUS_GAMMA_DELAY_STATS2LUT_CUR              0x000000AD
#define MON_STATUS_GAMMA_DELAY_STATS2LUT_MAX              0x000000AE
#define MON_STATUS_GAMMA_DELAY_LUT2APPLY_MIN              0x000000AF
#define MON_STATUS_GAMMA_DELAY_LUT2APPLY_CUR              0x000000B0
#define MON_STATUS_GAMMA_DELAY_LUT2APPLY_MAX              0x000000B1
#define MON_STATUS_IRIDIX_RESET                           0x000000B2
#define MON_STATUS_IRIDIX_FPT_MIN                         0x000000B3
#define MON_STATUS_IRIDIX_FPT_CUR                         0x000000B4
#define MON_STATUS_IRIDIX_FPT_MAX                         0x000000B5
#define MON_STATUS_IRIDIX_DELAY_STATS2TARGET_MIN          0x000000B6
#define MON_STATUS_IRIDIX_DELAY_STATS2TARGET_CUR          0x000000B7
#define MON_STATUS_IRIDIX_DELAY_STATS2TARGET_MAX          0x000000B8
#define MON_STATUS_IRIDIX_DELAY_TARGET2APPLY_MIN          0x000000B9
#define MON_STATUS_IRIDIX_DELAY_TARGET2APPLY_CUR          0x000000BA
#define MON_STATUS_IRIDIX_DELAY_TARGET2APPLY_MAX          0x000000BB


// ------------------------------------------------------------------------------ //
//		VALUE LIST
// ------------------------------------------------------------------------------ //
#define OFF                                               0x00000000
#define ON                                                0x00000001
#define DEBUG                                             0x00000000
#define INFO                                              0x00000001
#define NOTICE                                            0x00000002
#define WARNING                                           0x00000003
#define ERROR                                             0x00000004
#define CRITICAL                                          0x00000005
#define NOTHING                                           0x00000006
#define TEMPER4_MODE_NORMAL                               0x00000000
#define TEMPER4_MODE_LOW_LATENCY                          0x00000001
#define TEMPER4_MODE_FINITE                               0x00000002
#define UPDATE                                            0x00000000
#define DONE                                              0x00000001
#define DMA_READER_OUT_FR                                 0x00000000
#define DMA_READER_OUT_DS                                 0x00000001
#define DMA_DISABLE                                       0x00000000
#define RGB32                                             0x00000001
#define A2R10G10B10                                       0x00000002
#define RGB565                                            0x00000003
#define RGB24                                             0x00000004
#define GEN32                                             0x00000005
#define RAW16                                             0x00000006
#define RAW12                                             0x00000007
#define AYUV                                              0x00000008
#define Y410                                              0x00000009
#define YUY2                                              0x0000000A
#define UYVY                                              0x0000000B
#define Y210                                              0x0000000C
#define NV12_YUV                                          0x0000000D
#define NV12_YVU                                          0x0000000E
#define YV12_YU                                           0x0000000F
#define YV12_YV                                           0x00000010
#define DISABLE                                           0x00000000
#define ENABLE                                            0x00000001
#define CROP_FR                                           0x00000000
#define CROP_DS                                           0x00000001
#define SCALER_DS                                         0x00000002
#define SCALER_FR                                         0x00000003
#define RUN                                               0x00000000
#define LENS_SUCCESS                                      0x00000000
#define LENS_FAILED                                       0x00000001
#define AF_AUTO_SINGLE                                    0x00000000
#define AF_AUTO_CONTINUOUS                                0x00000001
#define AF_MANUAL                                         0x00000002
#define AF_CALIBRATION                                    0x00000003
#define AF_INACTIVE                                       0x00000000
#define AF_SCAN                                           0x00000001
#define AF_FOCUSED                                        0x00000002
#define AF_UNFOCUSED                                      0x00000003
#define CAF_NOT_RUNNING                                   0x00000000
#define CAF_RUNNING                                       0x00000001
#define CAF_WAITING_FOR_SCENE_CHANGE                      0x00000002
#define CAF_WAITING_FOR_STABLE_SCENE                      0x00000003
#define CAF_FINISHED_FAILED                               0x00000004
#define CAF_FINISHED_SUCCESSFUL                           0x00000005
#define AE_AUTO                                           0x00000000
#define AE_FULL_MANUAL                                    0x00000001
#define AE_MANUAL_GAIN                                    0x00000002
#define AE_MANUAL_EXPOSURE_TIME                           0x00000003
#define AE_INACTIVE                                       0x00000000
#define AE_SEARCHING                                      0x00000001
#define AE_CONVERGED                                      0x00000002
#define AE_SPLIT_BALANCED                                 0x00000000
#define AE_SPLIT_INTEGRATION_PRIORITY                     0x00000001
#define AWB_AUTO                                          0x00000000
#define AWB_MANUAL                                        0x00000001
#define AWB_DAY_LIGHT                                     0x00000002
#define AWB_CLOUDY                                        0x00000003
#define AWB_INCANDESCENT                                  0x00000004
#define AWB_FLOURESCENT                                   0x00000005
#define AWB_TWILIGHT                                      0x00000006
#define AWB_SHADE                                         0x00000007
#define AWB_WARM_FLOURESCENT                              0x00000008
#define AWB_INACTIVE                                      0x00000000
#define AWB_SEARCHING                                     0x00000001
#define AWB_CONVERGED                                     0x00000002
#define NOISE_REDUCTION_OFF                               0x00000000
#define NOISE_REDUCTION_ON                                0x00000001
#define NORMAL                                            0x00000000
#define BLACK_AND_WHITE                                   0x00000001
#define NEGATIVE                                          0x00000002
#define SEPIA                                             0x00000003
#define VIVID                                             0x00000004
#define SENSOR                                            0x00000000
#define LENS                                              0x00000001
#define ISP                                               0x00000002


// ------------------------------------------------------------------------------ //
//		RETURN VALUES
// ------------------------------------------------------------------------------ //
#define SUCCESS                                           0x00000000
#define NOT_IMPLEMENTED                                   0x00000001
#define NOT_SUPPORTED                                     0x00000002
#define NOT_PERMITTED                                     0x00000003
#define NOT_EXISTS                                        0x00000004
#define FAIL                                              0x00000005



// ------------------------------------------------------------------------------ //
//		DIRECTION VALUES
// ------------------------------------------------------------------------------ //
#define COMMAND_SET                                       0x00000000
#define COMMAND_GET                                       0x00000001
#define API_VERSION                                       0x00000064


// ------------------------------------------------------------------------------ //
//		SET/GET FUNCTION
// ------------------------------------------------------------------------------ //
//set command: ret = acamera_command( ctx_id, TALGORITHMS, AF_MODE, AF_AUTO, COMMAND_SET, &RET_VALUE);
//get command: ret = acamera_command( ctx_id, TALGORITHMS, AF_MODE, AF_AUTO, COMMAND_GET, &RET_VALUE);

//The main api function to control and change the firmware state
uint8_t acamera_command( uint32_t ctx_id, uint8_t command_type, uint8_t command, uint32_t value, uint8_t direction, uint32_t *ret_value);

//The function to change firmware internal calibrations.
uint8_t acamera_api_calibration( uint32_t ctx_id, uint8_t type, uint8_t id, uint8_t direction, void* data, uint32_t data_size, uint32_t* ret_value);

uint8_t acamera_api_dma_buffer( uint32_t ctx_id, uint8_t type, void* data, uint32_t data_size, uint32_t* ret_value);

#endif//_ACAMERA_COMMAND_API_H_
