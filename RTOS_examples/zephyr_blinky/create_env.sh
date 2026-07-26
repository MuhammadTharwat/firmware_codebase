export ZEPHYR_BASE=/home/muhammad/firmware_codebase/RTOS/zephyr

python3 -m venv ./venv
source ./venv/bin/activate

pip install -r ${ZEPHYR_BASE}/scripts/requirements.txt
