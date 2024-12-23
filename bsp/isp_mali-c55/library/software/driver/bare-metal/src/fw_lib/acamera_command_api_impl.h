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

#ifndef _ACAMERA_COMMAND_API_IMPL_H_
#define _ACAMERA_COMMAND_API_IMPL_H_
#include "acamera_types.h"
#include "acamera_fw.h"

uint8_t general_context_number(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t general_active_context(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t selftest_fw_revision(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_streaming(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_supported_presets(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_preset(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_wdr_mode(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_fps(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_width(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_height(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_exposures(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_info_preset(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_info_wdr_mode(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_info_fps(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_info_width(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_info_height(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_info_bits(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_info_exposures(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_lines_per_second(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_integration_time_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_integration_time_limit(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_info_physical_width(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sensor_info_physical_height(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t lens_info_minfocus_distance(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t lens_info_hyperfocal_distance(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t lens_info_focal_length(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t lens_info_aperture(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_logger_level(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_logger_mask(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t buffer_data_type(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t test_pattern_enable(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t test_pattern(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t m2m_process_request(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t temper4_mode(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t temper4_compress_pixel_mode(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t temper4_compress_meta_mode(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_freeze_firmware(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_manual_exposure(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_manual_exposure_ratio(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_manual_integration_time(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_manual_max_integration_time(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_manual_sensor_analog_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_manual_sensor_digital_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_manual_isp_digital_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_manual_awb(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_manual_ccm(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_manual_saturation(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_exposure(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_exposure_ratio(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_max_exposure_ratio(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_integration_time(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_long_integration_time(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_short_integration_time(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_max_integration_time(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_sensor_analog_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_max_sensor_analog_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_sensor_digital_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_max_sensor_digital_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_isp_digital_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_max_isp_digital_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_awb_red_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_awb_green_even_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_awb_green_odd_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_awb_blue_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_ccm_matrix_rr(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_ccm_matrix_rg(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_ccm_matrix_rb(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_ccm_matrix_gr(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_ccm_matrix_gg(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_ccm_matrix_gb(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_ccm_matrix_br(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_ccm_matrix_bg(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_ccm_matrix_bb(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_saturation_target(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_antiflicker_enable(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_anti_flicker_frequency(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t system_dynamic_gamma_enable(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t calibration_update(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t isp_modules_manual_iridix(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t isp_modules_manual_sinter(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t isp_modules_manual_temper(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t isp_modules_manual_auto_level(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t isp_modules_manual_frame_stitch(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t isp_modules_manual_raw_frontend(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t isp_modules_manual_black_level(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t isp_modules_manual_shading(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t isp_modules_manual_demosaic(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t isp_modules_manual_cnr(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t isp_modules_manual_sharpen(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t status_info_exposure_log2(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t status_info_gain_ones(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t status_info_gain_log2(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t status_info_awb_mix_light_contrast(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t status_info_af_lens_pos(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t status_info_af_focus_value(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t dma_reader_output(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t fr_format_base_plane(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t fr_raw_bypass(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t fr_fps_throttle_factor(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t ds1_format_base_plane(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t ds1_fps_throttle_factor(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t orientation_vflip(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t image_resize_type(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t image_resize_enable(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t image_resize_width(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t image_resize_height(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t image_crop_xoffset(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t image_crop_yoffset(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t af_lens_status(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t af_mode(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t af_state(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t caf_state(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t af_roi(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t af_manual_control(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t ae_mode(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t ae_state(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t ae_split_preset(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t ae_gain(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t ae_exposure(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t ae_roi(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t ae_compensation(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t awb_mode(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t awb_state(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t awb_temperature(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t noise_reduction_mode(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t color_mode(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t brightness_strength(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t contrast_strength(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t saturation_strength(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t sharpening_strength(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t shading_strength(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t hue_theta(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t register_address(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t register_size(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t register_source(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t register_value(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_error_calibration_lut_null(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_error_cmos_frame_start_delay(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_error_cmos_update_not_in_vb(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_error_cmos_update_dgain_wrong_timing(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_error_iridix_update_not_in_vb(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_ae_reset(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_ae_fpt_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_ae_fpt_cur(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_ae_fpt_max(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_ae_delay_stats2ev_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_ae_delay_stats2ev_cur(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_ae_delay_stats2ev_max(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_ae_delay_ev2apply_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_ae_delay_ev2apply_cur(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_ae_delay_ev2apply_max(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_awb_reset(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_awb_fpt_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_awb_fpt_cur(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_awb_fpt_max(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_awb_delay_stats2gain_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_awb_delay_stats2gain_cur(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_awb_delay_stats2gain_max(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_awb_delay_gain2apply_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_awb_delay_gain2apply_cur(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_awb_delay_gain2apply_max(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_gamma_reset(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_gamma_fpt_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_gamma_fpt_cur(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_gamma_fpt_max(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_gamma_delay_stats2lut_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_gamma_delay_stats2lut_cur(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_gamma_delay_stats2lut_max(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_gamma_delay_lut2apply_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_gamma_delay_lut2apply_cur(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_gamma_delay_lut2apply_max(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_iridix_reset(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_iridix_fpt_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_iridix_fpt_cur(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_iridix_fpt_max(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_iridix_delay_stats2target_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_iridix_delay_stats2target_cur(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_iridix_delay_stats2target_max(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_iridix_delay_target2apply_min(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_iridix_delay_target2apply_cur(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
uint8_t monitor_status_iridix_delay_target2apply_max(acamera_fsm_mgr_t *instance, uint32_t value, uint8_t direction, uint32_t *ret_value);
#endif//_ACAMERA_COMMAND_API_IMPL_H_
