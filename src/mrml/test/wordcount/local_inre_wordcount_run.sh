#!/bin/bash

# Clean the tmp files such as output file and log files which last execution generated.
rm -rf /tmp/*

# Run local wordcount.
mpiexec -n 3 ./mrml_main                                    \
    --num_agent_workers=2                                   \
    --num_server_workers=1                                  \
    --agent_workers="1,2"                                   \
    --server_workers="0"                                    \
    --mapper_class="WordCountMapper"                        \
    --reducer_class="SumIntegerReducer"                     \
    --cache_file_value="/Users/alex/data/wordcount/text-*"  \
    --cache_file_model="/tmp/model"                         \
    --output_files="/tmp/output"                            \
    --input_format="text"                                   \
    --output_format="text"                                  \
    --log_filebase="/tmp/log"
