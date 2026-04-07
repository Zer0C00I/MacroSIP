set(MACROSIP_SOURCES
    main.cpp
    app/MacroSipApp.cpp
    app/MainWindow.cpp

    # Models
    models/Account.cpp
    models/Contact.cpp
    models/CallRecord.cpp
    models/Settings.cpp

    # SIP
    sip/SipManager.cpp
    sip/SipCall.cpp
    sip/SipAccount.cpp

    # Dialogs
    dialogs/AccountDialog.cpp
    dialogs/SettingsDialog.cpp
    dialogs/MessagesDialog.cpp
    dialogs/RingingDialog.cpp
    dialogs/TransferDialog.cpp
    dialogs/AddContactDialog.cpp
    dialogs/AAOptionsDialog.cpp
    dialogs/FeatureCodesDialog.cpp
    dialogs/ShortcutsDialog.cpp

    # Widgets
    widgets/DialerWidget.cpp
    widgets/ContactsWidget.cpp
    widgets/CallsWidget.cpp
    widgets/ClosableTabWidget.cpp
    widgets/LevelsSlider.cpp

    # Utilities
    utils/Crypto.cpp
    utils/CsvFile.cpp
    utils/LangPack.cpp

    # Resources
    resources/resources.qrc
)

set(MACROSIP_HEADERS
    app/MacroSipApp.h
    app/MainWindow.h

    models/Account.h
    models/Contact.h
    models/CallRecord.h
    models/Settings.h

    sip/SipManager.h
    sip/SipCall.h
    sip/SipAccount.h
    sip/SipTypes.h

    dialogs/AccountDialog.h
    dialogs/SettingsDialog.h
    dialogs/MessagesDialog.h
    dialogs/RingingDialog.h
    dialogs/TransferDialog.h
    dialogs/AddContactDialog.h
    dialogs/AAOptionsDialog.h
    dialogs/FeatureCodesDialog.h
    dialogs/ShortcutsDialog.h

    widgets/DialerWidget.h
    widgets/ContactsWidget.h
    widgets/CallsWidget.h
    widgets/ClosableTabWidget.h
    widgets/LevelsSlider.h

    utils/Crypto.h
    utils/CsvFile.h
    utils/LangPack.h
)

add_executable(macrosip ${MACROSIP_SOURCES} ${MACROSIP_HEADERS})

target_include_directories(macrosip PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/app
    ${CMAKE_CURRENT_SOURCE_DIR}/models
    ${CMAKE_CURRENT_SOURCE_DIR}/sip
    ${CMAKE_CURRENT_SOURCE_DIR}/dialogs
    ${CMAKE_CURRENT_SOURCE_DIR}/widgets
    ${CMAKE_CURRENT_SOURCE_DIR}/utils
)

# Force-include the forbidden-API header in every translation unit
target_compile_options(macrosip PRIVATE
    -include ${CMAKE_CURRENT_SOURCE_DIR}/security/forbidden.h
)

target_link_libraries(macrosip PRIVATE ${QT_LIBS})

if(ENABLE_PJSIP AND PJSIP_FOUND)
    target_link_libraries(macrosip PRIVATE PkgConfig::PJSIP)
endif()

if(OpenSSL_FOUND)
    target_link_libraries(macrosip PRIVATE OpenSSL::SSL OpenSSL::Crypto)
endif()

install(TARGETS macrosip RUNTIME DESTINATION bin)
