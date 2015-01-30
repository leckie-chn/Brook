# Build library in_memory_store.
add_library(in_memory_store dense_vector.cc sparse_vector.cc)

# Build unittests
set(LIBS in_memory_store)

# Install library and header files
