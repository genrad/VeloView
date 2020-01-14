set(SOFTWARE_NAME "grview")
set(VENDOR "General Radar")
set(PROJECT_NAME "${SOFTWARE_NAME}")

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${SOFTWARE_NAME}")
set(CPACK_PACKAGE_NAME "${SOFTWARE_NAME}")
set(CPACK_PACKAGE_VENDOR "${VENDOR}")

set(PARAVIEW_SPLASH_IMAGE splash.png)	# (image display when the software is loading)
set(PARAVIEW_BUNDLE_ICON logo.icns)	# (bunbled app icon)
set(PARAVIEW_APPLICATION_ICON logo.ico)	# (app icon)

# Please make sure to adapt the AboutDialog text in the followin file
#  VelodyneHDL\python\veloview\aboutDialog.py
# You also need to change:
#   - bottom_logo.png (bottom logo)

add_definitions( -DPROJECT_NAME="${PROJECT_NAME}" )
add_definitions( -DSOFTWARE_NAME="${SOFTWARE_NAME}" )
#add_definitions( -DVENDOR="${VENDOR}" ) # spaces here confuses the vtkWrap
