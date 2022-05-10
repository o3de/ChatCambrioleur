#
# Copyright (c) Contributors to the Open 3D Engine Project.
# For complete copyright and license terms please see the LICENSE at the root of this distribution.
#
# SPDX-License-Identifier: Apache-2.0 OR MIT
#
#

# Currently we are in the GentlecatThief/Code folder: ${CMAKE_CURRENT_LIST_DIR}
# Get the platform specific folder ${pal_dir} for the current folder: ${CMAKE_CURRENT_LIST_DIR}/Platform/${PAL_PLATFORM_NAME}
# Note: o3de_pal_dir will take care of the details for us, as this may be a restricted platform
#       in which case it will see if that platform is present here or in the restricted folder.
#       i.e. It could here : GentlecatThief/Code/Platform/<platform_name>  or
#            <restricted_folder>/<platform_name>/GentlecatThief/Code
o3de_pal_dir(pal_dir ${CMAKE_CURRENT_LIST_DIR}/Platform/${PAL_PLATFORM_NAME} "${gem_restricted_path}" "${gem_path}" "${gem_parent_relative_path}")

# Now that we have the platform abstraction layer (PAL) folder for this folder, thats where we will find the
# traits for this platform. Traits for a platform are defines for things like whether or not something in this project
# is supported by this platform.
include(${pal_dir}/PAL_${PAL_PLATFORM_NAME_LOWERCASE}.cmake)

# Now that we have loaded our project traits for this platform, see if this project is even supported on this platform.
# If its not supported we just return after including the unsupported.
if(NOT PAL_TRAIT_GENTLECATTHIEF_SUPPORTED)
    return()
endif()

# We are on a supported platform, so add the GentlecatThief target
# Note: We include the common files and the platform specific files which are set in gentlecatthief_files.cmake and
# in ${pal_dir}/gentlecatthief_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
ly_add_target(
    NAME GentlecatThief.Static STATIC
    NAMESPACE Gem
    FILES_CMAKE
        gentlecatthief_files.cmake
        ${pal_dir}/gentlecatthief_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
    INCLUDE_DIRECTORIES
        PUBLIC
            Include
    BUILD_DEPENDENCIES
        PRIVATE
            AZ::AzGameFramework
            Gem::Atom_AtomBridge.Static
)

ly_add_target(
    NAME GentlecatThief ${PAL_TRAIT_MONOLITHIC_DRIVEN_MODULE_TYPE}
    NAMESPACE Gem
    FILES_CMAKE
        gentlecatthief_shared_files.cmake
        ${pal_dir}/gentlecatthief_shared_${PAL_PLATFORM_NAME_LOWERCASE}_files.cmake
    INCLUDE_DIRECTORIES
        PUBLIC
            Include
    BUILD_DEPENDENCIES
        PRIVATE
            Gem::GentlecatThief.Static
            AZ::AzCore
)

# if enabled, GentlecatThief is used by all kinds of applications
ly_create_alias(NAME GentlecatThief.Builders NAMESPACE Gem TARGETS Gem::GentlecatThief)
ly_create_alias(NAME GentlecatThief.Tools    NAMESPACE Gem TARGETS Gem::GentlecatThief)
ly_create_alias(NAME GentlecatThief.Clients  NAMESPACE Gem TARGETS Gem::GentlecatThief)
ly_create_alias(NAME GentlecatThief.Servers  NAMESPACE Gem TARGETS Gem::GentlecatThief)

################################################################################
# Gem dependencies
################################################################################

# The GameLauncher uses "Clients" gem variants:
ly_enable_gems(
    PROJECT_NAME GentlecatThief GEM_FILE enabled_gems.cmake)

if(PAL_TRAIT_BUILD_HOST_TOOLS)

    # the builder type applications use the "Builders" variants of the enabled gems.
    ly_enable_gems(
        PROJECT_NAME GentlecatThief GEM_FILE enabled_gems.cmake)
    
    # the Editor applications use the "Tools" variants of the enabled gems.
    ly_enable_gems(
        PROJECT_NAME GentlecatThief GEM_FILE enabled_gems.cmake)
endif()

if(PAL_TRAIT_BUILD_SERVER_SUPPORTED)
    # this property causes it to actually make a ServerLauncher.
    # if you don't want a Server application, you can remove this and the
    # following ly_enable_gems lines.
    set_property(GLOBAL APPEND PROPERTY LY_LAUNCHER_SERVER_PROJECTS GentlecatThief)
    
    # The ServerLauncher uses the "Servers" variants of enabled gems:
    ly_enable_gems(
        PROJECT_NAME GentlecatThief GEM_FILE enabled_gems.cmake)
endif()
