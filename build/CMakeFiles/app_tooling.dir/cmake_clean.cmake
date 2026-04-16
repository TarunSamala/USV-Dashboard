file(REMOVE_RECURSE
  "Dashboard/qml/Main.qml"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/app_tooling.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
