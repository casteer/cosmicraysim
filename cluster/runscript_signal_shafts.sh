
# Get Inputs
RUNID=$1
RUNLENGTH=$2
CHUNKLENGTH=$3
GEOMETRY="/home/steer/cosmicraysim/macros/ca"
WORKDIR="/home/steer/cosmicraysim/build/work/outputs/ca"

# Let Condor know where everything is
source setup.sh
source setupgeant4.sh

# Make new temp scratch area
scratchdir=$(source make_temp_scratch.sh)

# Move to scratch
cd $scratchdir

# Run Job
echo "Running target and background simulation..."
cosmicraysim -t ${RUNLENGTH} -c ${CHUNKLENGTH} -g ${GEOMETRY}/ca_variables_vent_shafts.geo -g ${GEOMETRY}/ca_vent_shafts.geo -g ${GEOMETRY}/ca_world_rock.geo -g ${GEOMETRY}/ca_detector_system_vent_shafts.geo -g ${GEOMETRY}/ca_source_flux_alt.geo -o ca_vent_shafts_signal

# Copy Outputs back to WORK Area
cp -rv ./* $WORKDIR/
cd -

# Remove temp directory
rm -rv $scratchdir
