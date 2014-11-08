set (SOURCES
	a_star.cpp
	block.cpp
	board.cpp
	cenwidget.cpp
	global.cpp
	mainwindow.cpp
	main.cpp
)

set (HEADERS
	a_star.h
	block.h
	board.h
	cenwidget.h
	global.h
	mainwindow.h
)

set (RESOURCES
	img.qrc
)

	qt5_add_resources (RESOURCES_RCC ${RESOURCES})
	qt5_wrap_cpp (SOURCES ${HEADERS})
	
	add_executable(15Game ${SOURCES} ${RESOURCES_RCC})

  # The Qt5Widgets_LIBRARIES variable also includes QtGui and QtCore
	target_link_libraries(15Game ${Qt5Widgets_LIBRARIES})