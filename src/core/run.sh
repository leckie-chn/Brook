#!/bin/bash

mpiexec -np 6 ./brook_main            \
        --num_agent_workers=4       \
        --num_server_workers=2
