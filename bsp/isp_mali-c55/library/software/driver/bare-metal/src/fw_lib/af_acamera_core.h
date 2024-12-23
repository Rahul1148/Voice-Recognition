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

#ifndef _AF_ACAMERA_CORE_H_
#define _AF_ACAMERA_CORE_H_

#include "acamera_math.h"
#include "af_standard_api.h"
#include "af_acamera_common.h"


#define AF_SPOT_IGNORE_NUM 1
#define AF_CALIBRATION_BOUNDARIES 1

typedef enum _af_spot_status_t {
    AF_SPOT_STATUS_NOT_FINISHED,
    AF_SPOT_STATUS_FINISHED_VALID,
    AF_SPOT_STATUS_FINISHED_INVALID,
} af_spot_status_t;


typedef enum _af_status_t {
    AF_STATUS_INVALID,
    AF_STATUS_FAST_SEARCH,
    AF_STATUS_TRACKING,
    AF_STATUS_CONVERGED,
} af_status_t;

typedef struct _af_spot_param_t {
    uint64_t max_value;
    uint64_t min_value;
    uint32_t max_position;
    uint64_t before_max_value;
    uint32_t before_max_position;
    uint64_t after_max_value;
    uint32_t after_max_position;
    uint64_t previous_value;
    uint32_t optimal_position;
    uint8_t status;
    uint32_t reliable;
    uint32_t dynamic_range;
} af_spot_param_t;

typedef struct _af_fast_search_param_t {
    uint32_t step;
    uint32_t step_number;
    uint32_t position;
    uint32_t prev_position;
    uint32_t spot_zone_step_x;
    uint32_t spot_zone_step_y;
    uint32_t spot_zone_size_x;
    uint32_t spot_zone_size_y;
    af_spot_param_t spots[AF_SPOT_COUNT_Y][AF_SPOT_COUNT_X];
    uint32_t finished_valid_spot_count;
} af_fast_search_param_t;


typedef struct _af_track_position_param_t {
    uint8_t frames_in_tracking;
    uint8_t scene_is_changed;
    int32_t values[10];
    int values_inx;
    uint32_t diff0_cnt;
} af_track_position_param_t;


typedef struct _af_info_ {
    uint8_t af_mode;
    uint8_t refocus_required;

    uint8_t zones_horiz;
    uint8_t zones_vert;

    uint8_t skip_cur_frame;
    uint8_t is_lens_moving;

    uint32_t roi;
    uint32_t af_pos_manual;
} af_info_t;

typedef struct _af_misc_info_ {

    int16_t accel_angle;

    uint16_t lens_min_step;

    int32_t total_gain;
} af_misc_info_t;


typedef struct _af_calibration_data_ {
    af_lms_param_t *af_param;

    uint16_t *af_zone_whgh_h;
    uint32_t af_zone_whgh_h_len;

    uint16_t *af_zone_whgh_v;
    uint32_t af_zone_whgh_v_len;

    modulation_entry_t *af_calib_exit_thresh;
    uint32_t af_calib_exit_thresh_len;
} af_calibration_data_t;


typedef struct _af_acamera_input_ {
    af_info_t af_info;
    af_misc_info_t misc_info;
    af_calibration_data_t cali_data;
} af_acamera_input_t;


typedef struct _af_custom_input_ {
    uint32_t *custom_cali_data;
    uint32_t custom_cali_data_size;
} af_custom_input_t;


typedef struct _af_acamera_output_ {
    uint16_t af_lens_pos;
    int32_t af_sharp_val;
    uint8_t af_skip_frames;

    af_state_t state;
    caf_state_t caf_state;
} af_acamera_output_t;

typedef struct _af_acamera_input_roi_param_t {
    uint16_t af_input_roi_left_border;
    uint16_t af_input_roi_right_border;
    uint16_t af_input_roi_top_border;
    uint16_t af_input_roi_bottom_border;
} af_acamera_input_roi_param_t;

void *af_acamera_core_init( uint32_t ctx_id );
int32_t af_acamera_core_deinit( void *af_ctx );
int32_t af_acamera_core_proc( void *af_ctx, af_stats_data_t *stats, af_input_data_t *input, af_output_data_t *output );


#endif
