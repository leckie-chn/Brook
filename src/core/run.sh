#!/bin/bash

mpiexec -np 1 ./brook_main                                          \
        --num_agent_workers=1                                       \
        --num_server_workers=0                                      \
        --model_cache_file="/tmp/brook_run/model_cache_file"        \
        --subdata_cache_file="/tmp/brook_run/subdata_cache_file"    \
        --model_fifo_file="/tmp/brook_run/model_fifo_file"          \
        --subdata_fifo_file="/tmp/brook_run/subdata_fifo_file"      \
        --output_files="/tmp/brook_run/output"                      \
        --log_filebase="/tmp/brook_run/log"                         \
        --num_features=1000
