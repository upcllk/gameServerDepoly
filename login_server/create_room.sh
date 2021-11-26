#!/bin/bash
# 这个也没用了
docker run --rm -d -P -e MY_ROOM_NO=$1 game:V1.0 2>&1 >/dev/null

docker ps -n 1 -f ancestor=game:V1.0 | grep game_start | awk -F "->" '{print $1}' | awk -F ":" '{print $NF}'
