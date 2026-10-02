#!/bin/bash
set -ex

echo "Deploy REST server"
cd "$(dirname "$(readlink -f "$0")")"

./build.sh

SERVICE_NAME="telemetry_rest.service"
SERVICE_ETC_FILENAME="/etc/systemd/system/$SERVICE_NAME"

sudo cp "systemd/$SERVICE_NAME" "$SERVICE_ETC_FILENAME"
sudo chmod 644 "$SERVICE_ETC_FILENAME"

sudo systemctl daemon-reload
sudo systemctl enable "$SERVICE_NAME"
sudo systemctl restart "$SERVICE_NAME"
sudo systemctl status "$SERVICE_NAME" --no-pager

echo "Deploy REST server successful finished"
