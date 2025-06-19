#!/bin/bash

cleanup(){
    python -m space_collector.killall
}

# Kill le client et le serveur localhost de space_collector
python -m space_collector.killall

trap cleanup SIGINT

# choisir un port non utilisé
PORT=$((RANDOM % 1001 + 2000))

# Démarrer le serveur
python -m space_collector.game.server -p $PORT --timeout 4 &
SERVER_PID=$!

# Démarrer le viewer
python -m space_collector.viewer -p $PORT --small-window &
VIEWER_PID=$!

# Attendre que le serveur soit prêt
echo "En attente que le serveur écoute sur le port $PORT..."
while ! nc -z localhost $PORT; do
  sleep 0.5
done

# Démarrer le client serial2tcp
SERIAL=/dev/ttyUSB0  # sur Linux
python -m space_collector.serial2tcp -p $PORT --serial $SERIAL --team-name "CHANGE ME"

