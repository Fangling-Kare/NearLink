#===============================================================================
# @brief    cmake file
# Copyright (c) HiSilicon (Shanghai) Technologies Co., Ltd. 2022-2022. All rights reserved.
#===============================================================================

# Wi-Fi基础ROM组件
set(COMPONENT_NAME "wifi_driver_rom")
set(SOURCES
    ${WIFI_DEVICE_DIR}/source/common/romable/common_dft_rom.c
    ${WIFI_DEVICE_DIR}/source/common/romable/wlan_util_common_rom.c
    ${WIFI_DEVICE_DIR}/source/device/frw/romable/frw_timer_rom.c
    ${WIFI_DEVICE_DIR}/source/device/frw/romable/frw_rom_cb_rom.c
    ${WIFI_DEVICE_DIR}/source/device/frw/romable/frw_util_rom.c
    ${WIFI_DEVICE_DIR}/source/device/frw/romable/frw_hcc_adapt_rom.c
    ${WIFI_DEVICE_DIR}/source/device/frw/romable/oal_mem_rom.c
    ${WIFI_DEVICE_DIR}/source/device/frw/romable/frw_task_rom.c
    ${WIFI_DEVICE_DIR}/source/device/frw/romable/oal_fsm_rom.c
    ${WIFI_DEVICE_DIR}/source/device/frw/romable/frw_dmac_rom.c
    ${WIFI_DEVICE_DIR}/source/device/frw/romable/frw_dmac_adapt_rom.c
    ${WIFI_DEVICE_DIR}/source/device/frw/romable/oal_pkt_netbuf_rom.c
    ${WIFI_DEVICE_DIR}/source/device/mac/romable/mac_resource_rom.c
    ${WIFI_DEVICE_DIR}/source/device/mac/romable/mac_frame_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_device_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_latency_stat_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_smooth_phase_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_apf_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_psm_ap_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_keep_alive_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_sta_pm_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_csi_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_dfx_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_alg_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_vap_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_sdp_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_data_sample_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_psm_sta_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_intf_det_scan_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_fcs_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_twt_sta_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_user_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_independent_tx_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_p2p_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_param_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_hook_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_uapsd_sta_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_btcoex_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_blockack_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_psd_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_alrx_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_common_rom.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/romable/dmac_feature_dft_rom.c
    ${WIFI_DEVICE_DIR}/source/device/forward/romable/dmac_tx_data_rom.c
    ${WIFI_DEVICE_DIR}/source/device/forward/romable/dmac_rx_data_rom.c
    ${WIFI_DEVICE_DIR}/source/device/forward/romable/dmac_tx_bss_comm_rom.c
    ${WIFI_DEVICE_DIR}/source/device/forward/romable/dmac_tx_complete_retry_rom.c
    ${WIFI_DEVICE_DIR}/source/device/forward/romable/dmac_tx_queue_rom.c
    ${WIFI_DEVICE_DIR}/source/device/forward/romable/dmac_tx_complete_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_alg_dbac_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_alg_txbf_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_ampdu_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_bcn_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_chan_mgmt_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_chip_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_coex_reg_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_csi_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_device_fsm_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_device_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_dscr_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_event_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_ftm_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_gcl_slp_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_gp_reg_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_intf_det_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_irq_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_mac_err_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_mac_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_omi_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_one_pkt_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_p2p_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_phy_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_pm_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_psd_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_rx_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_tb_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_tx_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_tbtt_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_vap_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_mac_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_phy_reg_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_reset_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_rx_filter.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_ant_sel_rom.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_power_rom.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/online_cali/fe_log_calc_rom.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/rf_res_manage/fe_rf_dev.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/romable/hal_radar_sensor_rom.c
)
wifi_alg_compiler_entry(ws63_alg_wifi_rom OUT_SOURCES SOURCES OUT_INCLUDES Wi-Fi-ROM-PUBLIC_HEADER OUT_DEFINES Wi-Fi-PRIVATE_DEFINES
    WIFI_SOURCES ${SOURCES} WIFI_INCLUDES ${Wi-Fi-ROM-PUBLIC_HEADER} WIFI_DEFINES ${Wi-Fi-PRIVATE_DEFINES})
add_rom_base_config()
build_component()

set(COMPONENT_NAME "wifi_driver_dmac")
set(SOURCES
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_device.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_device_fsm.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_init.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_main.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_alg_rts.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_alg_tpc.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_alg_txbf.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_anti_intf.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_csi.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_mac.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_mfg.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_phy.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_pm.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_power.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_tpc.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_reset.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_rf.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_auto_adjust_freq.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_chip.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_dscr.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_msg.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_chan_mgmt.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_coex_reg.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_irq.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_psd.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_phy_event.c
    ${WIFI_DEVICE_DIR}/source/device/hal/hal_ws63/src/hal_wifi_patch.c
    ${WIFI_DEVICE_DIR}/source/device/main/main.c
    ${WIFI_DEVICE_DIR}/source/device/main/device_version.c
    ${WIFI_DEVICE_DIR}/source/device/frw/frw_main.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_param.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_sta_pm.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_btcoex.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_alrx.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_psm_sta.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_psm_ap.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_twt_sta.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_config.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_uapsd_sta.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_slp.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_common_hook.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_dfx.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_wifi_patch.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_dfx_init.c
    ${WIFI_DEVICE_DIR}/source/device/dmac/dmac_phy_event.c
    ${WIFI_DEVICE_DIR}/source/device/forward/dmac_pkt_debug.c
    ${WIFI_DEVICE_DIR}/source/device/forward/dmac_forward_main.c

    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/rf_customize/fe_rf_customize.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/spec/ws63/cali_offline_cali_cfg.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/spec/ws63/cali_comp_cfg.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/spec/ws63/power_ctrl_spec.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/spec/ws63/power_ppa_ctrl_spec.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/offline_cali/cali_tx_pwr.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/offline_cali/cali_logen.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/offline_cali/cali_cap.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/offline_cali/cali_iq.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/offline_cali/cali_iq_tone_alg.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/offline_cali/cali_rc.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/offline_cali/cali_rx_dc.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/offline_cali/cali_tx_dc.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/offline_cali/cali_r.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/offline_cali/cali_c.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/offline_cali/cali_ipa_current.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/online_cali/cali_online.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/online_cali/cali_online_tx_pwr.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/online_cali/cali_tx_complete.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/online_cali/cali_online_common.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_comp/cali_comp.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_comp/cali_offline_comp.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_comp/cali_tx_dc_comp.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_comp/cali_rx_dc_comp.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_comp/cali_rc_comp.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_comp/cali_tx_pwr_comp.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_comp/cali_logen_comp.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_comp/cali_iq_comp.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_comp/cali_r_comp.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_comp/cali_c_comp.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_comp/cali_ipa_current_comp.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_debug/cali_debug.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_debug/cali_iq_debug.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_debug/cali_tx_pwr_debug.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_debug/cali_logen_debug.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_debug/cali_tx_dc_debug.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_debug/cali_rx_dc_debug.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/cali_debug/cali_rc_debug.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/common_utils/cali_mask.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/common_utils/cali_data.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/common_utils/cali_entry.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/common_utils/cali_channel.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/common_utils/cali_complex_num.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/common_utils/cali_accum_data.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/common_utils/cali_proc_dmac_msg.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/common_utils/cali_path.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/calibrate/common_utils/cali_rf_temp_code.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/phy/ws63/fe_power_host.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/phy/ws63/fe_power_device.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/phy/ws63/fe_hal_phy_if.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/phy/ws63/fe_hal_phy_if_pktmem.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/phy/ws63/fe_hal_phy_daq.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/rf_customize/fe_rf_customize.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/rf_res_manage/fe_rf_dev_attach.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/power_ctrl/fe_rate_pow_lut.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/power_ctrl/fe_tpc_rate_pow.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/power_ctrl/fe_init_pow.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/power_ctrl/fe_update_pow.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/rf_customize/fe_rf_customize_rx_insert_loss.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/rf_customize/fe_rf_customize_power.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/rf_customize/fe_rf_customize_power_cali.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/rf_customize/fe_rf_customize_rssi_comp.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/equipment/fe_equipment.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/phy/ws63/fe_hal_phy_if_host.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/phy/ws63/fe_hal_phy_reg_if_host.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/phy/ws63/fe_hal_phy_reg_if_device.c
    ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/phy/ws63/fe_hal_phy_reg_if_rom.c
)
# ASIC和FPGA编译文件有差异
if(BOARD_ASIC IN_LIST DEFINES)
    list(APPEND SOURCES
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_rf_abb_reg_if_rom.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_rf_pll_reg_if_rom.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_rf_if.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_gp_if.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_rf_if_pktmem.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/abb_config.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/rf_init.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/channel.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_rf_if_temperate.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_equipment.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_rf_reg_if.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_rf_reg_if_pktmem.c
    )
else()
    list(APPEND SOURCES
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_rf_abb_reg_if_rom.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_rf_pll_reg_if_rom.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/mpw/fe_hal_rf_if.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/mpw/fe_hal_gp_if.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/mpw/fe_hal_rf_if_pktmem.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/mpw/abb_config.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/mpw/abb_spi_reg_rw.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/mpw/mpw0_poweron.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/mpw/mpw_ssi_reg_if.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/mpw/rf_init.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/mpw/channel.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/mpw/fe_hal_rf_if_temperate.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/mpw/fe_hal_equipment.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_rf_reg_if.c
        ${WIFI_DEVICE_DIR}/source/common/wifi_fe/fe_hal/rf/ws63/fe_hal_rf_reg_if_pktmem.c
    )
endif()

add_base_config()
# 添加算法源码和头文件
wifi_alg_compiler_entry(ws63_alg_wifi_device_ram OUT_SOURCES SOURCES WIFI_SOURCES ${SOURCES})
build_component()


# FEATURE RADAR SENSOR ALG
set(COMPONENT_NAME "wifi_alg_radar_sensor_rom")
set(SOURCES
    ${WIFI_DEVICE_DIR}/source/alg_radar_sensor/romable/alg_radar_fft.c
)
set(COMPONENT_PUBLIC_CCFLAGS ${Wi-Fi-COMPONENT_PUBLIC_CCFLAGS})
set(COMPONENT_CCFLAGS        ${Wi-Fi-COMPONENT_CCFLAGS})
set(WHOLE_LINK               ${Wi-Fi-WHOLE_LINK})
set(MAIN_COMPONENT           ${Wi-Fi-MAIN_COMPONENT})
set(LIB_OUT_PATH ${BIN_DIR}/${CHIP}/libs/wifi/${TARGET_COMMAND})
build_component()