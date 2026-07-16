Blinky Sample

#### Create Env 
# Create and activate a virtual environment
python3 -m venv ./venv
source ./venv/bin/activate


pip install -r ${ZEPHYR_BASE}/scripts/requirements.txt

# This automatically exports your ZEPHYR_BASE and sets up internal script environments
source ${ZEPHYR_BASE}/zephyr-env.sh



To build : 
1 - $ ./build.sh


