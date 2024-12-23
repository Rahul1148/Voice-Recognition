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

#include "acamera_command_api.h"


#include "acamera_command_api_impl.h"
#include "acamera.h"
#include "acamera_firmware_api.h"
#include "acamera_fw.h"

#if FW_HAS_CONTROL_CHANNEL
#include "acamera_ctrl_channel.h"
#endif

extern void * acamera_get_ctx_ptr( uint32_t ctx_id );

uint8_t acamera_command( uint32_t ctx_id, uint8_t command_type, uint8_t command, uint32_t value, uint8_t direction, uint32_t *ret_value){
acamera_fsm_mgr_t *instance = &((acamera_context_ptr_t)acamera_get_ctx_ptr(ctx_id))->fsm_mgr;
uint8_t ret = NOT_EXISTS;
switch (command_type){
case  TGENERAL:
	switch (command){
		case  CONTEXT_NUMBER:
			ret = general_context_number(instance, value, direction, ret_value);
			break;
		case  ACTIVE_CONTEXT:
			ret = general_active_context(instance, value, direction, ret_value);
			break;
	}//switch (command)
	break;
case  TSELFTEST:
	switch (command){
		case  FW_REVISION:
			ret = selftest_fw_revision(instance, value, direction, ret_value);
			break;
	}//switch (command)
	break;
case  TSENSOR:
	switch (command){
		case  SENSOR_STREAMING:
			ret = sensor_streaming(instance, value, direction, ret_value);
			break;
		case  SENSOR_SUPPORTED_PRESETS:
			ret = sensor_supported_presets(instance, value, direction, ret_value);
			break;
		case  SENSOR_PRESET:
			ret = sensor_preset(instance, value, direction, ret_value);
			break;
		case  SENSOR_WDR_MODE:
			ret = sensor_wdr_mode(instance, value, direction, ret_value);
			break;
		case  SENSOR_FPS:
			ret = sensor_fps(instance, value, direction, ret_value);
			break;
		case  SENSOR_WIDTH:
			ret = sensor_width(instance, value, direction, ret_value);
			break;
		case  SENSOR_HEIGHT:
			ret = sensor_height(instance, value, direction, ret_value);
			break;
		case  SENSOR_EXPOSURES:
			ret = sensor_exposures(instance, value, direction, ret_value);
			break;
		case  SENSOR_INFO_PRESET:
			ret = sensor_info_preset(instance, value, direction, ret_value);
			break;
		case  SENSOR_INFO_WDR_MODE:
			ret = sensor_info_wdr_mode(instance, value, direction, ret_value);
			break;
		case  SENSOR_INFO_FPS:
			ret = sensor_info_fps(instance, value, direction, ret_value);
			break;
		case  SENSOR_INFO_WIDTH:
			ret = sensor_info_width(instance, value, direction, ret_value);
			break;
		case  SENSOR_INFO_HEIGHT:
			ret = sensor_info_height(instance, value, direction, ret_value);
			break;
		case  SENSOR_INFO_BITS:
			ret = sensor_info_bits(instance, value, direction, ret_value);
			break;
		case  SENSOR_INFO_EXPOSURES:
			ret = sensor_info_exposures(instance, value, direction, ret_value);
			break;
		case  SENSOR_LINES_PER_SECOND:
			ret = sensor_lines_per_second(instance, value, direction, ret_value);
			break;
		case  SENSOR_INTEGRATION_TIME_MIN:
			ret = sensor_integration_time_min(instance, value, direction, ret_value);
			break;
		case  SENSOR_INTEGRATION_TIME_LIMIT:
			ret = sensor_integration_time_limit(instance, value, direction, ret_value);
			break;
		case  SENSOR_INFO_PHYSICAL_WIDTH:
			ret = sensor_info_physical_width(instance, value, direction, ret_value);
			break;
		case  SENSOR_INFO_PHYSICAL_HEIGHT:
			ret = sensor_info_physical_height(instance, value, direction, ret_value);
			break;
	}//switch (command)
	break;
case  TLENS:
	switch (command){
		case  LENS_INFO_MINFOCUS_DISTANCE:
			ret = lens_info_minfocus_distance(instance, value, direction, ret_value);
			break;
		case  LENS_INFO_HYPERFOCAL_DISTANCE:
			ret = lens_info_hyperfocal_distance(instance, value, direction, ret_value);
			break;
		case  LENS_INFO_FOCAL_LENGTH:
			ret = lens_info_focal_length(instance, value, direction, ret_value);
			break;
		case  LENS_INFO_APERTURE:
			ret = lens_info_aperture(instance, value, direction, ret_value);
			break;
	}//switch (command)
	break;
case  TSYSTEM:
	switch (command){
		case  SYSTEM_LOGGER_LEVEL:
			ret = system_logger_level(instance, value, direction, ret_value);
			break;
		case  SYSTEM_LOGGER_MASK:
			ret = system_logger_mask(instance, value, direction, ret_value);
			break;
		case  BUFFER_DATA_TYPE:
			ret = buffer_data_type(instance, value, direction, ret_value);
			break;
		case  TEST_PATTERN_ENABLE_ID:
			ret = test_pattern_enable(instance, value, direction, ret_value);
			break;
		case  TEST_PATTERN_MODE_ID:
			ret = test_pattern(instance, value, direction, ret_value);
			break;
		case  M2M_PROCESS_REQUEST:
			ret = m2m_process_request(instance, value, direction, ret_value);
			break;
		case  TEMPER4_MODE:
			ret = temper4_mode(instance, value, direction, ret_value);
			break;
		case  TEMPER4_COMPRESS_PIXEL_MODE:
			ret = temper4_compress_pixel_mode(instance, value, direction, ret_value);
			break;
		case  TEMPER4_COMPRESS_META_MODE:
			ret = temper4_compress_meta_mode(instance, value, direction, ret_value);
			break;
		case  SYSTEM_FREEZE_FIRMWARE:
			ret = system_freeze_firmware(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MANUAL_EXPOSURE:
			ret = system_manual_exposure(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MANUAL_EXPOSURE_RATIO:
			ret = system_manual_exposure_ratio(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MANUAL_INTEGRATION_TIME:
			ret = system_manual_integration_time(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MANUAL_MAX_INTEGRATION_TIME:
			ret = system_manual_max_integration_time(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MANUAL_SENSOR_ANALOG_GAIN:
			ret = system_manual_sensor_analog_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MANUAL_SENSOR_DIGITAL_GAIN:
			ret = system_manual_sensor_digital_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MANUAL_ISP_DIGITAL_GAIN:
			ret = system_manual_isp_digital_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MANUAL_AWB:
			ret = system_manual_awb(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MANUAL_CCM:
			ret = system_manual_ccm(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MANUAL_SATURATION:
			ret = system_manual_saturation(instance, value, direction, ret_value);
			break;
		case  SYSTEM_EXPOSURE:
			ret = system_exposure(instance, value, direction, ret_value);
			break;
		case  SYSTEM_EXPOSURE_RATIO:
			ret = system_exposure_ratio(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MAX_EXPOSURE_RATIO:
			ret = system_max_exposure_ratio(instance, value, direction, ret_value);
			break;
		case  SYSTEM_INTEGRATION_TIME:
			ret = system_integration_time(instance, value, direction, ret_value);
			break;
		case  SYSTEM_LONG_INTEGRATION_TIME:
			ret = system_long_integration_time(instance, value, direction, ret_value);
			break;
		case  SYSTEM_SHORT_INTEGRATION_TIME:
			ret = system_short_integration_time(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MAX_INTEGRATION_TIME:
			ret = system_max_integration_time(instance, value, direction, ret_value);
			break;
		case  SYSTEM_SENSOR_ANALOG_GAIN:
			ret = system_sensor_analog_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MAX_SENSOR_ANALOG_GAIN:
			ret = system_max_sensor_analog_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_SENSOR_DIGITAL_GAIN:
			ret = system_sensor_digital_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MAX_SENSOR_DIGITAL_GAIN:
			ret = system_max_sensor_digital_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_ISP_DIGITAL_GAIN:
			ret = system_isp_digital_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_MAX_ISP_DIGITAL_GAIN:
			ret = system_max_isp_digital_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_AWB_RED_GAIN:
			ret = system_awb_red_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_AWB_GREEN_EVEN_GAIN:
			ret = system_awb_green_even_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_AWB_GREEN_ODD_GAIN:
			ret = system_awb_green_odd_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_AWB_BLUE_GAIN:
			ret = system_awb_blue_gain(instance, value, direction, ret_value);
			break;
		case  SYSTEM_CCM_MATRIX_RR:
			ret = system_ccm_matrix_rr(instance, value, direction, ret_value);
			break;
		case  SYSTEM_CCM_MATRIX_RG:
			ret = system_ccm_matrix_rg(instance, value, direction, ret_value);
			break;
		case  SYSTEM_CCM_MATRIX_RB:
			ret = system_ccm_matrix_rb(instance, value, direction, ret_value);
			break;
		case  SYSTEM_CCM_MATRIX_GR:
			ret = system_ccm_matrix_gr(instance, value, direction, ret_value);
			break;
		case  SYSTEM_CCM_MATRIX_GG:
			ret = system_ccm_matrix_gg(instance, value, direction, ret_value);
			break;
		case  SYSTEM_CCM_MATRIX_GB:
			ret = system_ccm_matrix_gb(instance, value, direction, ret_value);
			break;
		case  SYSTEM_CCM_MATRIX_BR:
			ret = system_ccm_matrix_br(instance, value, direction, ret_value);
			break;
		case  SYSTEM_CCM_MATRIX_BG:
			ret = system_ccm_matrix_bg(instance, value, direction, ret_value);
			break;
		case  SYSTEM_CCM_MATRIX_BB:
			ret = system_ccm_matrix_bb(instance, value, direction, ret_value);
			break;
		case  SYSTEM_SATURATION_TARGET:
			ret = system_saturation_target(instance, value, direction, ret_value);
			break;
		case  SYSTEM_ANTIFLICKER_ENABLE:
			ret = system_antiflicker_enable(instance, value, direction, ret_value);
			break;
		case  SYSTEM_ANTI_FLICKER_FREQUENCY:
			ret = system_anti_flicker_frequency(instance, value, direction, ret_value);
			break;
		case  SYSTEM_DYNAMIC_GAMMA_ENABLE:
			ret = system_dynamic_gamma_enable(instance, value, direction, ret_value);
			break;
		case  CALIBRATION_UPDATE:
			ret = calibration_update(instance, value, direction, ret_value);
			break;
	}//switch (command)
	break;
case  TISP_MODULES:
	switch (command){
		case  ISP_MODULES_MANUAL_IRIDIX:
			ret = isp_modules_manual_iridix(instance, value, direction, ret_value);
			break;
		case  ISP_MODULES_MANUAL_SINTER:
			ret = isp_modules_manual_sinter(instance, value, direction, ret_value);
			break;
		case  ISP_MODULES_MANUAL_TEMPER:
			ret = isp_modules_manual_temper(instance, value, direction, ret_value);
			break;
		case  ISP_MODULES_MANUAL_AUTO_LEVEL:
			ret = isp_modules_manual_auto_level(instance, value, direction, ret_value);
			break;
		case  ISP_MODULES_MANUAL_FRAME_STITCH:
			ret = isp_modules_manual_frame_stitch(instance, value, direction, ret_value);
			break;
		case  ISP_MODULES_MANUAL_RAW_FRONTEND:
			ret = isp_modules_manual_raw_frontend(instance, value, direction, ret_value);
			break;
		case  ISP_MODULES_MANUAL_BLACK_LEVEL:
			ret = isp_modules_manual_black_level(instance, value, direction, ret_value);
			break;
		case  ISP_MODULES_MANUAL_SHADING:
			ret = isp_modules_manual_shading(instance, value, direction, ret_value);
			break;
		case  ISP_MODULES_MANUAL_DEMOSAIC:
			ret = isp_modules_manual_demosaic(instance, value, direction, ret_value);
			break;
		case  ISP_MODULES_MANUAL_CNR:
			ret = isp_modules_manual_cnr(instance, value, direction, ret_value);
			break;
		case  ISP_MODULES_MANUAL_SHARPEN:
			ret = isp_modules_manual_sharpen(instance, value, direction, ret_value);
			break;
	}//switch (command)
	break;
case  TSTATUS:
	switch (command){
		case  STATUS_INFO_EXPOSURE_LOG2_ID:
			ret = status_info_exposure_log2(instance, value, direction, ret_value);
			break;
		case  STATUS_INFO_GAIN_ONES_ID:
			ret = status_info_gain_ones(instance, value, direction, ret_value);
			break;
		case  STATUS_INFO_GAIN_LOG2_ID:
			ret = status_info_gain_log2(instance, value, direction, ret_value);
			break;
		case  STATUS_INFO_AWB_MIX_LIGHT_CONTRAST:
			ret = status_info_awb_mix_light_contrast(instance, value, direction, ret_value);
			break;
		case  STATUS_INFO_AF_LENS_POS:
			ret = status_info_af_lens_pos(instance, value, direction, ret_value);
			break;
		case  STATUS_INFO_AF_FOCUS_VALUE:
			ret = status_info_af_focus_value(instance, value, direction, ret_value);
			break;
	}//switch (command)
	break;
case  TIMAGE:
	switch (command){
		case  DMA_READER_OUTPUT_ID:
			ret = dma_reader_output(instance, value, direction, ret_value);
			break;
		case  FR_FORMAT_BASE_PLANE_ID:
			ret = fr_format_base_plane(instance, value, direction, ret_value);
			break;
		case  FR_RAW_BYPASS:
			ret = fr_raw_bypass(instance, value, direction, ret_value);
			break;
		case  FR_FPS_THROTTLE_FACTOR_ID:
			ret = fr_fps_throttle_factor(instance, value, direction, ret_value);
			break;
		case  DS1_FORMAT_BASE_PLANE_ID:
			ret = ds1_format_base_plane(instance, value, direction, ret_value);
			break;
		case  DS1_FPS_THROTTLE_FACTOR_ID:
			ret = ds1_fps_throttle_factor(instance, value, direction, ret_value);
			break;
		case  ORIENTATION_VFLIP_ID:
			ret = orientation_vflip(instance, value, direction, ret_value);
			break;
		case  IMAGE_RESIZE_TYPE_ID:
			ret = image_resize_type(instance, value, direction, ret_value);
			break;
		case  IMAGE_RESIZE_ENABLE_ID:
			ret = image_resize_enable(instance, value, direction, ret_value);
			break;
		case  IMAGE_RESIZE_WIDTH_ID:
			ret = image_resize_width(instance, value, direction, ret_value);
			break;
		case  IMAGE_RESIZE_HEIGHT_ID:
			ret = image_resize_height(instance, value, direction, ret_value);
			break;
		case  IMAGE_CROP_XOFFSET_ID:
			ret = image_crop_xoffset(instance, value, direction, ret_value);
			break;
		case  IMAGE_CROP_YOFFSET_ID:
			ret = image_crop_yoffset(instance, value, direction, ret_value);
			break;
	}//switch (command)
	break;
case  TALGORITHMS:
	switch (command){
		case  AF_LENS_STATUS:
			ret = af_lens_status(instance, value, direction, ret_value);
			break;
		case  AF_MODE_ID:
			ret = af_mode(instance, value, direction, ret_value);
			break;
		case  AF_STATE_ID:
			ret = af_state(instance, value, direction, ret_value);
			break;
		case  CAF_STATE_ID:
			ret = caf_state(instance, value, direction, ret_value);
			break;
		case  AF_ROI_ID:
			ret = af_roi(instance, value, direction, ret_value);
			break;
		case  AF_MANUAL_CONTROL_ID:
			ret = af_manual_control(instance, value, direction, ret_value);
			break;
		case  AE_MODE_ID:
			ret = ae_mode(instance, value, direction, ret_value);
			break;
		case  AE_STATE_ID:
			ret = ae_state(instance, value, direction, ret_value);
			break;
		case  AE_SPLIT_PRESET_ID:
			ret = ae_split_preset(instance, value, direction, ret_value);
			break;
		case  AE_GAIN_ID:
			ret = ae_gain(instance, value, direction, ret_value);
			break;
		case  AE_EXPOSURE_ID:
			ret = ae_exposure(instance, value, direction, ret_value);
			break;
		case  AE_ROI_ID:
			ret = ae_roi(instance, value, direction, ret_value);
			break;
		case  AE_COMPENSATION_ID:
			ret = ae_compensation(instance, value, direction, ret_value);
			break;
		case  AWB_MODE_ID:
			ret = awb_mode(instance, value, direction, ret_value);
			break;
		case  AWB_STATE_ID:
			ret = awb_state(instance, value, direction, ret_value);
			break;
		case  AWB_TEMPERATURE_ID:
			ret = awb_temperature(instance, value, direction, ret_value);
			break;
		case  NOISE_REDUCTION_MODE_ID:
			ret = noise_reduction_mode(instance, value, direction, ret_value);
			break;
	}//switch (command)
	break;
case  TSCENE_MODES:
	switch (command){
		case  COLOR_MODE_ID:
			ret = color_mode(instance, value, direction, ret_value);
			break;
		case  BRIGHTNESS_STRENGTH_ID:
			ret = brightness_strength(instance, value, direction, ret_value);
			break;
		case  CONTRAST_STRENGTH_ID:
			ret = contrast_strength(instance, value, direction, ret_value);
			break;
		case  SATURATION_STRENGTH_ID:
			ret = saturation_strength(instance, value, direction, ret_value);
			break;
		case  SHARPENING_STRENGTH_ID:
			ret = sharpening_strength(instance, value, direction, ret_value);
			break;
		case  SHADING_STRENGTH_ID:
			ret = shading_strength(instance, value, direction, ret_value);
			break;
		case  HUE_THETA_ID:
			ret = hue_theta(instance, value, direction, ret_value);
			break;
	}//switch (command)
	break;
case  TREGISTERS:
	switch (command){
		case  REGISTERS_ADDRESS_ID:
			ret = register_address(instance, value, direction, ret_value);
			break;
		case  REGISTERS_SIZE_ID:
			ret = register_size(instance, value, direction, ret_value);
			break;
		case  REGISTERS_SOURCE_ID:
			ret = register_source(instance, value, direction, ret_value);
			break;
		case  REGISTERS_VALUE_ID:
			ret = register_value(instance, value, direction, ret_value);
			break;
	}//switch (command)
	break;
case  TMONITOR:
	switch (command){
		case  MON_ERROR_CALIBRATION_LUT_NULL:
			ret = monitor_error_calibration_lut_null(instance, value, direction, ret_value);
			break;
		case  MON_ERROR_CMOS_FS_DELAY:
			ret = monitor_error_cmos_frame_start_delay(instance, value, direction, ret_value);
			break;
		case  MON_ERROR_CMOS_UPDATE_NOT_IN_VB:
			ret = monitor_error_cmos_update_not_in_vb(instance, value, direction, ret_value);
			break;
		case  MON_ERROR_CMOS_UPDATE_DGAIN_WRONG_TIMING:
			ret = monitor_error_cmos_update_dgain_wrong_timing(instance, value, direction, ret_value);
			break;
		case  MON_ERROR_IRIDIX_UPDATE_NOT_IN_VB:
			ret = monitor_error_iridix_update_not_in_vb(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AE_RESET:
			ret = monitor_status_ae_reset(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AE_FPT_MIN:
			ret = monitor_status_ae_fpt_min(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AE_FPT_CUR:
			ret = monitor_status_ae_fpt_cur(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AE_FPT_MAX:
			ret = monitor_status_ae_fpt_max(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AE_DELAY_STATS2EV_MIN:
			ret = monitor_status_ae_delay_stats2ev_min(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AE_DELAY_STATS2EV_CUR:
			ret = monitor_status_ae_delay_stats2ev_cur(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AE_DELAY_STATS2EV_MAX:
			ret = monitor_status_ae_delay_stats2ev_max(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AE_DELAY_EV2APPLY_MIN:
			ret = monitor_status_ae_delay_ev2apply_min(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AE_DELAY_EV2APPLY_CUR:
			ret = monitor_status_ae_delay_ev2apply_cur(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AE_DELAY_EV2APPLY_MAX:
			ret = monitor_status_ae_delay_ev2apply_max(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AWB_RESET:
			ret = monitor_status_awb_reset(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AWB_FPT_MIN:
			ret = monitor_status_awb_fpt_min(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AWB_FPT_CUR:
			ret = monitor_status_awb_fpt_cur(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AWB_FPT_MAX:
			ret = monitor_status_awb_fpt_max(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AWB_DELAY_STATS2GAIN_MIN:
			ret = monitor_status_awb_delay_stats2gain_min(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AWB_DELAY_STATS2GAIN_CUR:
			ret = monitor_status_awb_delay_stats2gain_cur(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AWB_DELAY_STATS2GAIN_MAX:
			ret = monitor_status_awb_delay_stats2gain_max(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AWB_DELAY_GAIN2APPLY_MIN:
			ret = monitor_status_awb_delay_gain2apply_min(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AWB_DELAY_GAIN2APPLY_CUR:
			ret = monitor_status_awb_delay_gain2apply_cur(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_AWB_DELAY_GAIN2APPLY_MAX:
			ret = monitor_status_awb_delay_gain2apply_max(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_GAMMA_RESET:
			ret = monitor_status_gamma_reset(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_GAMMA_FPT_MIN:
			ret = monitor_status_gamma_fpt_min(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_GAMMA_FPT_CUR:
			ret = monitor_status_gamma_fpt_cur(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_GAMMA_FPT_MAX:
			ret = monitor_status_gamma_fpt_max(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_GAMMA_DELAY_STATS2LUT_MIN:
			ret = monitor_status_gamma_delay_stats2lut_min(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_GAMMA_DELAY_STATS2LUT_CUR:
			ret = monitor_status_gamma_delay_stats2lut_cur(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_GAMMA_DELAY_STATS2LUT_MAX:
			ret = monitor_status_gamma_delay_stats2lut_max(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_GAMMA_DELAY_LUT2APPLY_MIN:
			ret = monitor_status_gamma_delay_lut2apply_min(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_GAMMA_DELAY_LUT2APPLY_CUR:
			ret = monitor_status_gamma_delay_lut2apply_cur(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_GAMMA_DELAY_LUT2APPLY_MAX:
			ret = monitor_status_gamma_delay_lut2apply_max(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_IRIDIX_RESET:
			ret = monitor_status_iridix_reset(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_IRIDIX_FPT_MIN:
			ret = monitor_status_iridix_fpt_min(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_IRIDIX_FPT_CUR:
			ret = monitor_status_iridix_fpt_cur(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_IRIDIX_FPT_MAX:
			ret = monitor_status_iridix_fpt_max(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_IRIDIX_DELAY_STATS2TARGET_MIN:
			ret = monitor_status_iridix_delay_stats2target_min(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_IRIDIX_DELAY_STATS2TARGET_CUR:
			ret = monitor_status_iridix_delay_stats2target_cur(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_IRIDIX_DELAY_STATS2TARGET_MAX:
			ret = monitor_status_iridix_delay_stats2target_max(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_IRIDIX_DELAY_TARGET2APPLY_MIN:
			ret = monitor_status_iridix_delay_target2apply_min(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_IRIDIX_DELAY_TARGET2APPLY_CUR:
			ret = monitor_status_iridix_delay_target2apply_cur(instance, value, direction, ret_value);
			break;
		case  MON_STATUS_IRIDIX_DELAY_TARGET2APPLY_MAX:
			ret = monitor_status_iridix_delay_target2apply_max(instance, value, direction, ret_value);
			break;
	}//switch (command)
}//switch (command_type)

#if FW_HAS_CONTROL_CHANNEL
	ctrl_channel_handle_command( ctx_id, command_type, command, value, direction );
#endif

if(ret!=SUCCESS)
{
	LOG(LOG_WARNING,"API COMMAND FAILED: type %d, cmd %d, value %lu, direction %d, ret_value %lu, result %d",command_type, command, (unsigned long)value, direction, (unsigned long)*ret_value, ret);
}
else
{
	LOG(LOG_DEBUG,"API type %d, cmd %d, value %lu, direction %d, ret_value %lu, result %d",command_type, command, (unsigned long)value, direction, (unsigned long)*ret_value, ret);
}
	return ret;
}
