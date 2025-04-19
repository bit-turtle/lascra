add_executable( lascra main.cxx id.cxx checknum.cxx error.cxx block.cxx find.cxx compiler.cxx declare.cxx define.cxx when.cxx code.cxx parameter.cxx )
target_link_libraries( lascra argh bparser ZipLib )

# web build
if( EMSCRIPTEN )
	set( CMAKE_CXX_FLAGS "-s EXPORTED_RUNTIME_METHODS=callMain -s EXPORTED_FUNCTIONS=_main -s INVOKE_RUN=0" )
	configure_file( lascra.html ${CMAKE_CURRENT_BINARY_DIR} COPYONLY )
endif()
