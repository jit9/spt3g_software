add_library(so3g SHARED
  src/SOMemoryLeaker.cxx
)
target_link_libraries(so3g core)
link_python_dir()
