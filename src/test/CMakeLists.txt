aux_source_directory(. SRC_LIST)
aux_source_directory(../proto proto_LIST)
add_executable(test ${SRC_LIST} ${proto_LIST})

target_link_libraries(test 
                        rpc
                        jsoncpp
                        protobuf)