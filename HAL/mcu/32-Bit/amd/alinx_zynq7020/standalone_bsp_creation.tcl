# ====== Generate baremetal bsp ======
set hw_file "./alinx_zynq7020_minimal_system.xsa"
set workspace "./standalone_bsp"
set platform_name "zynq_platform"
set domain_name "standalone_domain"
set fsbl_name "a9_fsbl"

# Create (or use) a workspace directory
setws $workspace

# Import hardware platform (from your Vivado export)
platform create -name $platform_name -hw $hw_file -out $workspace/ -os standalone

# Create a domain (bare-metal environment for one processor)
domain create -name $domain_name -os standalone -proc ps7_cortexa9_0

domain active $domain_name

bsp setlib -name xilffs libmetal openamp

# For extra compiler flags, use ---> bsp config -append extra_compiler_flags -DTEST
bsp config -append extra_compiler_flags "-Wl,--gc-sections -ffunction-sections -fdata-sections -Os"

# Generate the BSP (drivers, libxil, etc.)
platform generate

app create -name $fsbl_name -platform $platform_name -template {Zynq FSBL} -domain $domain_name -lang c
app config -name $fsbl_name define-compiler-symbols {FSBL_DEBUG_INFO}
app build -name $fsbl_name


## Load the new fsbl and bitstream
#connect

#targets 2

#rst

#fpga -f ./standalone_bsp/a9_fsbl/_ide/bitstream/sdr_wrapper.bit
#dow ./standalone_bsp/a9_fsbl/Debug/a9_fsbl.elf
#con 


