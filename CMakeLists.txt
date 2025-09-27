cmake_minimum_required(VERSION 3.15)
project(StyxTelegramBotFramework VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Boost ---
find_package(Boost REQUIRED CONFIG COMPONENTS system locale filesystem)

# --- FTXUI ---
include(FetchContent)
FetchContent_Declare(FTXUI
        GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI
        GIT_TAG v6.1.9
)
FetchContent_MakeAvailable(FTXUI)

file(GLOB_RECURSE SOURCE "Src/*.CPP" "Include/*.HPP")
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE})

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/Include
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
        PROJECT_NAME="${CMAKE_PROJECT_NAME}"
        PROJECT_VERSION="${CMAKE_PROJECT_VERSION}"
)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
        # Boost
        Boost::system
        Boost::locale
        Boost::filesystem

        # FTXUI
        ftxui::screen
        ftxui::dom
        ftxui::component
)

# --- i18n ---
find_package(Gettext REQUIRED)
#message(STATUS "Gettext tools found: ${GETTEXT_MSGFMT_EXECUTABLE}")
#set(I18N_DOMAIN ${PROJECT_NAME})
#set(I18N_POT_FILE "${CMAKE_CURRENT_SOURCE_DIR}/Language/${I18N_DOMAIN}.pot")
#set(I18N_KEYWORDS "--keyword=translate")

#add_custom_target(
#        update_pot
#        COMMAND ${CMAKE_COMMAND} -E env
#        "bash" "-c"
#        "SOURCE_FILES=$(${CMAKE_COMMAND} -E glob_recurse . FOLLOW_SYMLINKS \"Src/*.CPP\" \"Include/*.HPP\") && \
#                 ${GETTEXT_XGETTEXT_EXECUTABLE} \
#                    --language=C++ \
#                    --from-code=UTF-8 \
#                    --output=${I18N_POT_FILE} \
#                    ${I18N_KEYWORDS} \
#                    $SOURCE_FILES"
#        COMMENT "Updating translation template file: ${I18N_POT_FILE}"
#        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
#        VERBATIM
#)

#message(STATUS "Created 'update_pot' target to generate translation template.")

file(GLOB PO_FILES "${CMAKE_CURRENT_SOURCE_DIR}/Language/*/LC_MESSAGES/*.po")

if(PO_FILES)
    set(MO_FILE_OUTPUTS "")

    foreach(PO_FILE ${PO_FILES})
        get_filename_component(LOCALE_DIR ${PO_FILE} DIRECTORY)
        get_filename_component(LOCALE_DIR ${LOCALE_DIR} DIRECTORY)
        get_filename_component(LANG_CODE ${LOCALE_DIR} NAME)
        set(MO_FILE_PATH "${CMAKE_CURRENT_BINARY_DIR}/Language/${LANG_CODE}/LC_MESSAGES/${PROJECT_NAME}.mo")

        add_custom_command(
                OUTPUT ${MO_FILE_PATH}
                COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/Language/${LANG_CODE}/LC_MESSAGES"
                COMMAND ${GETTEXT_MSGFMT_EXECUTABLE} -o ${MO_FILE_PATH} ${PO_FILE}
                DEPENDS ${PO_FILE}
                COMMENT "Compiling ${LANG_CODE} translation..."
                VERBATIM
        )
        list(APPEND MO_FILE_OUTPUTS ${MO_FILE_PATH})
    endforeach()

    add_custom_target(
            compile_translations
            DEPENDS ${MO_FILE_OUTPUTS}
    )

    add_dependencies(${PROJECT_NAME} compile_translations)

    message(STATUS "Translations will be compiled automatically during build.")
else()
    message(WARNING "No .po files found. Skipping automatic compilation of translations.")
endif()