# Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
# Distributed under the terms of the GNU Affero General Public License v3

ACLOCAL_AMFLAGS = -Im4
AM_CPPFLAGS = -I$(srcdir)/src

theiaheadersdir = $(includedir)/Entropy/Theia
theiaheaders_HEADERS = \
	src/Application.hh \
	src/Camera.hh \
	src/Context.hh \
	src/Drawable.hh \
	src/Drawables.hh \
	src/Drawables.impl.hh \
	src/Event.hh \
	src/Events.hh \
	src/Exception.hh \
	src/IWindow.hh \
	src/Object.hh \
	src/Scene.hh \
	src/Screen.hh \
	src/Types.hh \
	src/Window.hh \
	src/Window.impl.hh

utilityheadersdir = $(includedir)/Entropy/Theia/Utility
utilityheaders_HEADERS = \
	src/Utility/DefaultedList.hh \
	src/Utility/DefaultedList.impl.hh \
	src/Utility/PolymorphicList.hh \
	src/Utility/PolymorphicList.impl.hh \
	src/Utility/PolymorphicListIterator.hh \
	src/Utility/PolymorphicListIterator.impl.hh \
	src/Utility/SharedData.hh \
	src/Utility/SharedData.impl.hh

glheadersdir = $(includedir)/Entropy/Theia/GL
glheaders_HEADERS = \
	src/GL/Array.hh \
	src/GL/Bind.hh \
	src/GL/Buffer.hh \
	src/GL/Buffer.impl.hh \
	src/GL/Program.hh \
	src/GL/Program.impl.hh \
	src/GL/Shader.hh \
	src/GL/Texture.hh

glfwheadersdir = $(includedir)/Entropy/Theia/GLFW
glfwheaders_HEADERS = \
	src/GLFW/Glfw.hh \
	src/GLFW/Window.hh

lib_LTLIBRARIES = libtheia.la

libtheia_la_SOURCES = \
	src/GL/Array.cc \
	src/GL/Bind.cc \
	src/GL/Buffer.cc \
	src/GL/Program.cc \
	src/GL/Shader.cc \
	src/GL/Texture.cc \
	src/GLFW/Glfw.cc \
	src/GLFW/Window.cc \
	src/Application.cc \
	src/Camera.cc \
	src/Drawables.cc \
	src/Event.cc \
	src/Events.cc \
	src/Logger.cc \
	src/Object.cc \
	src/Scene.cc \
	src/Screen.cc \
	src/Window.cc

check_PROGRAMS = \
	hand-glfwwindow \
	hand-object \
	hand-application \
	hand-ortho

dist_noinst_DATA = \
	data/purple-stars.png

all-local:
	test -d data || $(LN_S) $(top_srcdir)/data $(builddir)/data

hand_glfwwindow_SOURCES = test/hand/glfwwindow.cc
hand_glfwwindow_LDADD = libtheia.la

hand_object_SOURCES = test/hand/object.cc
hand_object_LDADD = libtheia.la

hand_application_SOURCES = test/hand/application.cc
hand_application_LDADD = libtheia.la

hand_ortho_SOURCES = test/hand/ortho.cc
hand_ortho_LDADD = libtheia.la

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
