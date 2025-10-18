# ====== Generate baremetal bsp ======

# Create (or use) a workspace directory
setws ./standalone_bsp

# Import hardware platform (from your Vivado export)
platform create -name zynq_platform -hw ./hamgeek_zynq7010.xsa -out ./standalone_bsp/ -os standalone

# Create a domain (bare-metal environment for one processor)
domain create -name standalone_domain -os standalone -proc ps7_cortexa9_0

# For extra compiler flags, use ---> bsp config -append extra_compiler_flags -DTEST
bsp config -append extra_compiler_flags "-Wl,--gc-sections -ffunction-sections -fdata-sections -Os"

# Generate the BSP (drivers, libxil, etc.)
platform generate


exit

