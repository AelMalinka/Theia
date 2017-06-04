# Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
# Distributed under the terms of the GNU Affero General Public License v3

ACLOCAL_AMFLAGS = -Im4
AM_CPPFLAGS = -I$(srcdir)/src

theiaheadersdir = $(includedir)/Entropy/Theia
theiaheaders_HEADERS = \
	src/Exception.hh \
	src/Array.hh \
	src/Bind.hh \
	src/Buffer.hh \
	src/Buffer.impl.hh \
	src/Program.hh \
	src/Program.impl.hh \
	src/Shader.hh \
	src/Texture.hh \
	src/Drawable.hh \
	src/Object.hh \
	src/Camera.hh \
	src/Scene.hh \
	src/Scene.impl.hh \
	src/IWindow.hh \
	src/Window.hh \
	src/Window.impl.hh \
	src/Application.hh

utilityheadersdir = $(includedir)/Entropy/Theia/Utility
utilityheaders_HEADERS = \
	src/Utility/DefaultedList.hh \
	src/Utility/DefaultedList.impl.hh \
	src/Utility/PolymorphicListIterator.hh \
	src/Utility/PolymorphicListIterator.impl.hh \
	src/Utility/PolymorphicList.hh \
	src/Utility/PolymorphicList.impl.hh \
	src/Utility/SharedData.hh \
	src/Utility/SharedData.impl.hh

glfwheadersdir = $(includedir)/Entropy/Theia/GLFW
glfwheaders_HEADERS = \
	src/GLFW/Glfw.hh \
	src/GLFW/Window.hh

lib_LTLIBRARIES = libtheia.la

libtheia_la_SOURCES = \
	src/GLFW/Glfw.cc \
	src/GLFW/Window.cc \
	src/Array.cc \
	src/Bind.cc \
	src/Buffer.cc \
	src/Program.cc \
	src/Shader.cc \
	src/Texture.cc \
	src/Object.cc \
	src/Camera.cc \
	src/Drawable.cc \
	src/Scene.cc \
	src/Window.cc \
	src/Application.cc

check_PROGRAMS = \
	hand-glfwwindow \
	hand-object \
	hand-camera \
	hand-scene \
	hand-window \
	hand-application \
	hand-application-no-inheritance

hand_glfwwindow_SOURCES = test/hand/glfwwindow.cc
hand_glfwwindow_LDADD = libtheia.la

hand_object_SOURCES = test/hand/object.cc
hand_object_LDADD = libtheia.la

hand_camera_SOURCES = test/hand/camera.cc
hand_camera_LDADD = libtheia.la

hand_scene_SOURCES = test/hand/scene.cc
hand_scene_LDADD = libtheia.la

hand_window_SOURCES = test/hand/window.cc
hand_window_LDADD = libtheia.la

hand_application_SOURCES = test/hand/application.cc
hand_application_LDADD = libtheia.la

hand_application_no_inheritance_SOURCES = test/hand/application-no-inheritance.cc
hand_application_no_inheritance_LDADD = libtheia.la

if GTEST
check_PROGRAMS += \
	utility-defaulted-list \
	utility-polymorphic-list-iterator \
	utility-polymorphic-list \
	utility-shared-data

utility_defaulted_list_SOURCES = test/utility/defaulted-list.cc
utility_defaulted_list_LDADD = $(GTEST_LIBS) libtheia.la

utility_polymorphic_list_SOURCES = test/utility/polymorphic-list.cc
utility_polymorphic_list_LDADD = $(GTEST_LIBS) libtheia.la

utility_polymorphic_list_iterator_SOURCES = test/utility/polymorphic-list-iterator.cc
utility_polymorphic_list_iterator_LDADD = $(GTEST_LIBS) libtheia.la

utility_shared_data_SOURCES = test/utility/shared-data.cc
utility_shared_data_LDADD = $(GTEST_LIBS) libtheia.la
endif

TESTSUITE = $(srcdir)/test/testsuite

TESTSUITE_FILES = \
	$(srcdir)/test/utility.at

EXTRA_DIST = $(TESTSUITE_FILES) \
	$(srcdir)/test/testsuite.at \
	$(srcdir)/package.m4 \
	$(TESTSUITE) \
	$(srcdir)/test/atlocal.in

$(srcdir)/package.m4: $(top_srcdir)/configure.ac
	:; {\
		echo '# Signature of the current package. (auto-generated)' && \
		echo 'm4_define([AT_PACKAGE_NAME],' && \
		echo '  [$(PACKAGE_NAME)])' && \
		echo 'm4_define([AT_PACKAGE_TARNAME],' && \
		echo '  [$(PACKAGE_TARNAME)])' && \
		echo 'm4_define([AT_PACKAGE_VERSION],' && \
		echo '  [$(PACKAGE_VERSION)])' && \
		echo 'm4_define([AT_PACKAGE_STRING],' && \
		echo '  [$(PACKAGE_STRING)])' && \
		echo 'm4_define([AT_PACKAGE_BUGREPORT],' && \
		echo '  [$(PACKAGE_BUGREPORT)])'; \
		echo 'm4_define([AT_PACKAGE_URL],' && \
		echo '  [$(PACKAGE_URL)])'; \
	} >'$(srcdir)/package.m4'

check-local: test/atconfig atlocal $(TESTSUITE) $(check_PROGRAMS)
	$(SHELL) '$(TESTSUITE)' AUTOTEST_PATH='$(shell pwd)' $(TESTSUITEFLAGS)

clean-local:
	test ! -f '$(TESTSUITE)' || \
		$(SHELL) '$(TESTSUITE)' --clean

AUTOM4TE = $(SHELL) $(srcdir)/build-aux/missing --run autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest
$(TESTSUITE): $(srcdir)/test/testsuite.at $(TESTSUITE_FILES) $(srcdir)/package.m4
	$(AUTOTEST) -I '$(srcdir)/test' -I $(srcdir) -o $@.tmp $@.at
	mv $@.tmp $@
