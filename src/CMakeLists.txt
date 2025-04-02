add_executable( lascra main.cxx )
set_property( TARGET lascra PROPERTY CXX_STANDARD 17 )
target_link_libraries( lascra argh bparser ZipLib )
