find_package(Qt6 REQUIRED COMPONENTS Test Widgets)
set(QT_TEST_LIBS Qt6::Test Qt6::Core)
set(QT_GUI_TEST_LIBS Qt6::Test Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Network Qt6::Multimedia)

# Helper function to add a non-GUI test
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

# Helper function to add a GUI widget/dialog test
function(add_macrosip_gui_test test_name test_source)
    add_executable(${test_name} ${test_source} ${ARGN})
    set_target_properties(${test_name} PROPERTIES AUTOMOC ON)
    target_include_directories(${test_name} PRIVATE ${CMAKE_SOURCE_DIR}/src)
    target_link_libraries(${test_name} PRIVATE ${QT_GUI_TEST_LIBS})
    if(OpenSSL_FOUND)
        target_link_libraries(${test_name} PRIVATE OpenSSL::SSL OpenSSL::Crypto)
        target_compile_definitions(${test_name} PRIVATE OPENSSL_ENABLED)
    endif()
    if(ENABLE_HEADSET AND HIDAPI_FOUND)
        target_link_libraries(${test_name} PRIVATE PkgConfig::HIDAPI)
        target_compile_definitions(${test_name} PRIVATE HEADSET_ENABLED)
    endif()
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

# ---- Model tests (non-GUI) ----
add_macrosip_test(test_account test_account.cpp ${CMAKE_SOURCE_DIR}/src/models/Account.cpp)
add_macrosip_test(test_contact test_contact.cpp ${CMAKE_SOURCE_DIR}/src/models/Contact.cpp)
add_macrosip_test(test_callrecord test_callrecord.cpp ${CMAKE_SOURCE_DIR}/src/models/CallRecord.cpp)

# ---- Utility tests (non-GUI) ----
add_macrosip_test(test_csvfile test_csvfile.cpp ${CMAKE_SOURCE_DIR}/src/utils/CsvFile.cpp)
add_macrosip_test(test_crypto test_crypto.cpp ${CMAKE_SOURCE_DIR}/src/utils/Crypto.cpp)
add_macrosip_test(test_langpack test_langpack.cpp ${CMAKE_SOURCE_DIR}/src/utils/LangPack.cpp)
add_macrosip_test(test_callhistorystore test_callhistorystore.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/CallHistoryStore.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/CsvFile.cpp
    ${CMAKE_SOURCE_DIR}/src/models/CallRecord.cpp)
add_macrosip_test(test_contactstore test_contactstore.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/ContactStore.cpp
    ${CMAKE_SOURCE_DIR}/src/utils/CsvFile.cpp
    ${CMAKE_SOURCE_DIR}/src/models/Contact.cpp)

# ---- Settings test (non-GUI) ----
add_macrosip_test(test_settings test_settings.cpp
    ${CMAKE_SOURCE_DIR}/src/models/Settings.cpp
    ${CMAKE_SOURCE_DIR}/src/models/Account.cpp)

# ---- SIP tests (non-GUI, stub mode) ----
add_macrosip_test(test_sipcall test_sipcall.cpp
    ${CMAKE_SOURCE_DIR}/src/sip/SipCall.cpp)

add_macrosip_test(test_sipaccount test_sipaccount.cpp
    ${CMAKE_SOURCE_DIR}/src/sip/SipAccount.cpp
    ${CMAKE_SOURCE_DIR}/src/models/Account.cpp)

add_macrosip_test(test_sipmanager test_sipmanager.cpp
    ${CMAKE_SOURCE_DIR}/src/sip/SipManager.cpp
    ${CMAKE_SOURCE_DIR}/src/sip/SipCall.cpp
    ${CMAKE_SOURCE_DIR}/src/sip/SipAccount.cpp
    ${CMAKE_SOURCE_DIR}/src/models/Account.cpp)

# ---- Headset test (non-GUI) ----
add_macrosip_test(test_headsetmanager test_headsetmanager.cpp
    ${CMAKE_SOURCE_DIR}/src/headset/HeadsetManager.cpp)
if(ENABLE_HEADSET AND HIDAPI_FOUND)
    target_link_libraries(test_headsetmanager PRIVATE PkgConfig::HIDAPI)
    target_compile_definitions(test_headsetmanager PRIVATE HEADSET_ENABLED)
endif()

# ---- Widget tests (GUI, need QApplication) ----
add_macrosip_gui_test(test_dialer test_dialer.cpp
    ${CMAKE_SOURCE_DIR}/src/widgets/DialerWidget.cpp)

add_macrosip_gui_test(test_levelsslider test_levelsslider.cpp
    ${CMAKE_SOURCE_DIR}/src/widgets/LevelsSlider.cpp)

add_macrosip_gui_test(test_contactswidget test_contactswidget.cpp
    ${CMAKE_SOURCE_DIR}/src/widgets/ContactsWidget.cpp
    ${CMAKE_SOURCE_DIR}/src/models/Contact.cpp)

add_macrosip_gui_test(test_callswidget test_callswidget.cpp
    ${CMAKE_SOURCE_DIR}/src/widgets/CallsWidget.cpp
    ${CMAKE_SOURCE_DIR}/src/models/CallRecord.cpp)

add_macrosip_gui_test(test_closabletabwidget test_closabletabwidget.cpp
    ${CMAKE_SOURCE_DIR}/src/widgets/ClosableTabWidget.cpp)

# ---- Dialog tests (GUI, need QApplication) ----
add_macrosip_gui_test(test_ringingdialog test_ringingdialog.cpp
    ${CMAKE_SOURCE_DIR}/src/dialogs/RingingDialog.cpp)

add_macrosip_gui_test(test_accountdialog test_accountdialog.cpp
    ${CMAKE_SOURCE_DIR}/src/dialogs/AccountDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/models/Account.cpp)

add_macrosip_gui_test(test_addcontactdialog test_addcontactdialog.cpp
    ${CMAKE_SOURCE_DIR}/src/dialogs/AddContactDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/models/Contact.cpp)

add_macrosip_gui_test(test_messagesdialog test_messagesdialog.cpp
    ${CMAKE_SOURCE_DIR}/src/dialogs/MessagesDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/widgets/ClosableTabWidget.cpp)

add_macrosip_gui_test(test_transferdialog test_transferdialog.cpp
    ${CMAKE_SOURCE_DIR}/src/dialogs/TransferDialog.cpp)

add_macrosip_gui_test(test_aaoptionsdialog test_aaoptionsdialog.cpp
    ${CMAKE_SOURCE_DIR}/src/dialogs/AAOptionsDialog.cpp)

add_macrosip_gui_test(test_featurecodesdialog test_featurecodesdialog.cpp
    ${CMAKE_SOURCE_DIR}/src/dialogs/FeatureCodesDialog.cpp)

add_macrosip_gui_test(test_shortcutsdialog test_shortcutsdialog.cpp
    ${CMAKE_SOURCE_DIR}/src/dialogs/ShortcutsDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/models/Settings.cpp
    ${CMAKE_SOURCE_DIR}/src/models/Account.cpp)

add_macrosip_gui_test(test_settingsdialog test_settingsdialog.cpp
    ${CMAKE_SOURCE_DIR}/src/dialogs/SettingsDialog.cpp
    ${CMAKE_SOURCE_DIR}/src/models/Settings.cpp
    ${CMAKE_SOURCE_DIR}/src/models/Account.cpp)
