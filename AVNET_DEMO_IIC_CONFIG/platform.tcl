# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct /home/benchmarker/vivado_bsp/INT_test_sw_new/AVNETSW/AVNET_DEMO_IIC_CONFIG/platform.tcl
# 
# OR launch xsct and run below command.
# source /home/benchmarker/vivado_bsp/INT_test_sw_new/AVNETSW/AVNET_DEMO_IIC_CONFIG/platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {AVNET_DEMO_IIC_CONFIG}\
-hw {/home/benchmarker/FPGAProject/AVNET_DEMO_IIC_CONFIG/AVNET_DEMO_IIC_CONFIG.xsa}\
-out {/home/benchmarker/vivado_bsp/INT_test_sw_new/AVNETSW}

platform write
domain create -name {standalone_ps7_cortexa9_0} -display-name {standalone_ps7_cortexa9_0} -os {standalone} -proc {ps7_cortexa9_0} -runtime {cpp} -arch {32-bit} -support-app {hello_world}
platform generate -domains 
platform active {AVNET_DEMO_IIC_CONFIG}
domain active {zynq_fsbl}
domain active {standalone_ps7_cortexa9_0}
platform generate -quick
bsp reload
platform generate
platform active {AVNET_DEMO_IIC_CONFIG}
platform config -updatehw {/home/benchmarker/FPGAProject/AVNET_DEMO_ILA/AVNET_DEMO_ILA.xsa}
platform generate -domains 
platform config -updatehw {/home/benchmarker/FPGAProject/AVNET_DEMO_ILA/AVNET_DEMO_ILA.xsa}
platform config -updatehw {/home/benchmarker/FPGAProject/AVNET_DEMO_ILA/AVNET_DEMO_ILA.xsa}
platform generate -domains 
platform config -updatehw {/home/benchmarker/FPGAProject/AVNET_DEMO_ILA/AVNET_DEMO_ILA.xsa}
platform generate -domains 
platform write
platform active {AVNET_DEMO_IIC_CONFIG}
platform config -updatehw {/home/benchmarker/FPGAProject/AVNET_DEMO_MISMATCH/AVNET_DEMO_MISMATCH.xsa}
platform generate -domains 
platform config -updatehw {/home/benchmarker/FPGAProject/AVNET_DEMO_MISMATCH/AVNET_DEMO_MISMATCH.xsa}
platform generate -domains 
platform active {AVNET_DEMO_IIC_CONFIG}
platform config -updatehw {/home/benchmarker/FPGAProject/AVNET_DEMO_MISMATCH/AVNET_DEMO_MISMATCH.xsa}
platform generate
platform config -updatehw {/home/benchmarker/FPGAProject/AVNET_DEMO_MISMATCH/AVNET_DEMO_MISMATCH.xsa}
platform generate -domains 
