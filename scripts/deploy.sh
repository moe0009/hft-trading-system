#!/bin/bash
# deploy.sh
# author: mohammad bazrouk
# script to deploy the hft trading system to a remote server

set -e

REMOTE_USER="user"
REMOTE_HOST="remote.server.com"
REMOTE_DIR="/path/to/deployment/directory"

echo "packaging build artifacts..."
tar -czf hft_trading_system.tar.gz -C build .

echo "deploying to remote server..."
scp hft_trading_system.tar.gz ${REMOTE_USER}@${REMOTE_HOST}:${REMOTE_DIR}
ssh ${REMOTE_USER}@${REMOTE_HOST} "cd ${REMOTE_DIR} && tar -xzf hft_trading_system.tar.gz && rm hft_trading_system.tar.gz"
echo "deployment completed."
