find_package(Qt6 REQUIRED COMPONENTS Test)
set(QT_TEST_LIBS Qt6::Test Qt6::Core)

# Helper function to add a test
function(add_macrosip_test test_name test_source)
    add_executable(${test_name} ${test_source} ${ARGN})
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/src)
    target_link_libraries(${test_name} PRIVATE ${QT_TEST_LIBS} ${QT_LIBS})
    if(OpenSSL_FOUND)
        target_link_libraries(${test_name} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
        target_compile_definitions(${test_name} PRIVATE OPENSSL_ENABLED)
    endif()
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

# Model tests
add_macrosip_test(test_account test_account.cpp ${CMAKE_SOURCE_DIR}/src/models/Account.cpp)
add_macrosip_test(test_contact test_contact.cpp ${CMAKE_SOURCE_DIR}/src/models/Contact.cpp)
add_macrosip_test(test_callrecord test_callrecord.cpp ${CMAKE_SOURCE_DIR}/src/models/CallRecord.cpp)
add_macrosip_test(test_csvfile test_csvfile.cpp ${CMAKE_SOURCE_DIR}/src/utils/CsvFile.cpp)
add_macrosip_test(test_crypto test_crypto.cpp ${CMAKE_SOURCE_DIR}/src/utils/Crypto.cpp)
add_macrosip_test(test_langpack test_langpack.cpp ${CMAKE_SOURCE_DIR}/src/utils/LangPack.cpp)
