# Define a cleanup function to be executed when the script is interrupted (with Ctrl+C)
cleanup(){
    # In an activated virtual environment
    python -m space_collector.killall
}

trap cleanup SIGINT

# choose a free port
# choisir un port non utilisé
PORT=$((RANDOM % 1001 + 2000))
# start the server
python -m space_collector.game.server -p $PORT --timeout 5 &
# start the viewer on small screens
python -m space_collector.viewer -p $PORT --small-window&
# start players
# using serial port
# SERIAL=COM8          # on Windows
SERIAL=/dev/ttyUSB0  # on Linux
python -m space_collector.serial2tcp -p $PORT --serial $SERIAL --team-name "CHANGE ME"
