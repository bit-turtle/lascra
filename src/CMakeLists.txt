add_executable( lascra main.cxx id.cxx checknum.cxx compiler.cxx declare.cxx define.cxx )
target_link_libraries( lascra argh bparser ZipLib )
