# ====== Generate baremetal bsp ======

# Create (or use) a workspace directory
setws ./fsbl

app create -name a9_fsbl -hw ./hamgeek_zynq7010.xsa -os standalone -proc ps7_cortexa9_0 -template {Zynq FSBL}
app config -name a9_fsbl define-compiler-symbols {FSBL_DEBUG_INFO}
app build -name a9_fsbl

exit

