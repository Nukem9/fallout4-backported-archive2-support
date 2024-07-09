vcpkg_from_github(
        OUT_SOURCE_PATH SOURCE_PATH
        REPO Ryan-rsm-McKenzie/CommonLibF4
        REF cdd932ad1f4e37f33c28ea7d7e429428f5be43dd
        SHA512 fd72180dbecb8145547100e77d39de95400e944c66849ddcf6fdf349c65324551cd8316f25fb70543d0b724fd4241f9f935c4e239efbd4136662a490413d2185
        HEAD_REF master
)

vcpkg_configure_cmake(
        SOURCE_PATH "${SOURCE_PATH}/CommonLibF4"
        PREFER_NINJA
)

vcpkg_install_cmake()
vcpkg_cmake_config_fixup(PACKAGE_NAME "CommonLibF4" CONFIG_PATH "lib/cmake/CommonLibF4")
vcpkg_copy_pdbs()

file(REMOVE_RECURSE "${CURRENT_PACKAGES_DIR}/debug/include")

vcpkg_install_copyright(FILE_LIST "${SOURCE_PATH}/LICENSE")
