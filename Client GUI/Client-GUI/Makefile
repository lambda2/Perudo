#############################################################################
# Makefile for building: Client-GUI
# Generated by qmake (2.01a) (Qt 4.6.2) on: sam. juin 11 00:35:40 2011
# Project:  Client-GUI.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile Client-GUI.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I. -I.
LINK          = g++
LFLAGS        = -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = configuration.cpp \
		connecter.cpp \
		identification.cpp \
		LClient.cpp \
		LDebug.cpp \
		main.cpp \
		mainwindow.cpp moc_configuration.cpp \
		moc_connecter.cpp \
		moc_identification.cpp \
		moc_mainwindow.cpp \
		qrc_ressouces.cpp
OBJECTS       = configuration.o \
		connecter.o \
		identification.o \
		LClient.o \
		LDebug.o \
		main.o \
		mainwindow.o \
		moc_configuration.o \
		moc_connecter.o \
		moc_identification.o \
		moc_mainwindow.o \
		qrc_ressouces.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		Client-GUI.pro
QMAKE_TARGET  = Client-GUI
DESTDIR       = 
TARGET        = Client-GUI

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_configuration.h ui_connecter.h ui_identification.h ui_mainwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: Client-GUI.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -unix -o Makefile Client-GUI.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile Client-GUI.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/Client-GUI1.0.0 || $(MKDIR) .tmp/Client-GUI1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/Client-GUI1.0.0/ && $(COPY_FILE) --parents configuration.hpp connecter.hpp header.h identification.hpp LClient.h LDebug.h mainwindow.hpp .tmp/Client-GUI1.0.0/ && $(COPY_FILE) --parents ressouces.qrc .tmp/Client-GUI1.0.0/ && $(COPY_FILE) --parents configuration.cpp connecter.cpp identification.cpp LClient.cpp LDebug.cpp main.cpp mainwindow.cpp .tmp/Client-GUI1.0.0/ && $(COPY_FILE) --parents configuration.ui connecter.ui identification.ui mainwindow.ui .tmp/Client-GUI1.0.0/ && (cd `dirname .tmp/Client-GUI1.0.0` && $(TAR) Client-GUI1.0.0.tar Client-GUI1.0.0 && $(COMPRESS) Client-GUI1.0.0.tar) && $(MOVE) `dirname .tmp/Client-GUI1.0.0`/Client-GUI1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/Client-GUI1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_configuration.cpp moc_connecter.cpp moc_identification.cpp moc_mainwindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_configuration.cpp moc_connecter.cpp moc_identification.cpp moc_mainwindow.cpp
moc_configuration.cpp: LClient.h \
		LDebug.h \
		header.h \
		identification.hpp \
		mainwindow.hpp \
		configuration.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) configuration.hpp -o moc_configuration.cpp

moc_connecter.cpp: LClient.h \
		LDebug.h \
		header.h \
		configuration.hpp \
		identification.hpp \
		mainwindow.hpp \
		connecter.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) connecter.hpp -o moc_connecter.cpp

moc_identification.cpp: LClient.h \
		LDebug.h \
		header.h \
		mainwindow.hpp \
		identification.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) identification.hpp -o moc_identification.cpp

moc_mainwindow.cpp: LClient.h \
		LDebug.h \
		header.h \
		mainwindow.hpp
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) mainwindow.hpp -o moc_mainwindow.cpp

compiler_rcc_make_all: qrc_ressouces.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_ressouces.cpp
qrc_ressouces.cpp: ressouces.qrc \
		res/Iago.png \
		res/Iago_64.png \
		res/loading_big.gif \
		res/icone-yago.gif \
		res/icone-yago_32.png \
		res/64/Accessories-Dictionary-64.png \
		res/64/Gnome-Scanner-64.png \
		res/64/Gnome-Document-Revert-64.png \
		res/64/Gnome-Text-X-Preview-64.png \
		res/64/Gnome-Weather-Snow-64.png \
		res/64/Gnome-Go-Previous-64.png \
		res/64/Gnome-Face-Kiss-64.png \
		res/64/Gnome-Input-Tablet-64.png \
		res/64/Gnome-Network-Offline-64.png \
		res/64/Gnome-Package-X-Generic-64.png \
		res/64/Gnome-Preferences-Desktop-Locale-64.png \
		res/64/Gnome-Go-Down-64.png \
		res/64/Gnome-X-Office-Address-Book-64.png \
		res/64/Gnome-Go-First-64.png \
		res/64/Gtk-Dnd-Multiple-64.png \
		res/64/Gnome-Folder-Saved-Search-64.png \
		res/64/Gnome-Format-Text-Direction-Ltr-64.png \
		res/64/Gnome-Help-Faq-64.png \
		res/64/Gnome-Accessories-Text-Editor-64.png \
		res/64/Gnome-Pda-64.png \
		res/64/Gnome-View-Sort-Descending-64.png \
		res/64/Gnome-Preferences-Desktop-Screensaver-64.png \
		res/64/Gnome-Object-Flip-Horizontal-64.png \
		res/64/Gnome-Weather-Few-Clouds-64.png \
		res/64/Gnome-Media-Playback-Start-64.png \
		res/64/Gnome-User-Desktop-64.png \
		res/64/Gnome-Emblem-Package-64.png \
		res/64/Gnome-Mail-Forward-64.png \
		res/64/Gnome-Go-Jump-64.png \
		res/64/Evince-Logo-64.png \
		res/64/Gnome-Application-X-Executable-64.png \
		res/64/Gnome-Security-Medium-64.png \
		res/64/Gnome-Face-Smile-Big-64.png \
		res/64/Add-Files-To-Archive-Yellow-64.png \
		res/64/Gnome-Zoom-Fit-Best-64.png \
		res/64/Gnome-Colors-Emblem-Desktop-64.png \
		res/64/Gnome-Audio-Card-64.png \
		res/64/Gnome-Document-Print-Preview-64.png \
		res/64/Gnome-Object-Flip-Vertical-64.png \
		res/64/Gnome-Applications-Utilities-64.png \
		res/64/Gnome-Modem-64.png \
		res/64/Gnome-Computer-64.png \
		res/64/Gnome-Go-Next-64.png \
		res/64/Gnome-Help-Browser-64.png \
		res/64/Gnome-X-Office-Spreadsheet-64.png \
		res/64/Gnome-Mail-Message-New-64.png \
		res/64/Gnome-Preferences-Desktop-Keyboard-Shortcuts-64.png \
		res/64/Gnome-System-File-Manager-64.png \
		res/64/Gnome-Emblem-Default-64.png \
		res/64/Gnome-Media-Seek-Backward-64.png \
		res/64/Gnome-System-Search-64.png \
		res/64/Gnome-Emblem-Readonly-64.png \
		res/64/Gnome-Input-Mouse-64.png \
		res/64/Gnome-Application-Exit-64.png \
		res/64/Gnome-Web-Browser-64.png \
		res/64/Gnome-Media-Eject-64.png \
		res/64/Gnome-Insert-Object-64.png \
		res/64/Gnome-Media-Skip-Backward-64.png \
		res/64/Gnome-Network-Receive-64.png \
		res/64/Gnome-Accessories-Calculator-64.png \
		res/64/Gnome-Web-Calendar-64.png \
		res/64/Gnome-List-Remove-64.png \
		res/64/Gnome-Face-Sad-64.png \
		res/64/Gnome-Applications-Games-64.png \
		res/64/Gnome-Mail-Mark-Important-64.png \
		res/64/Gnome-Help-Contents-64.png \
		res/64/Gnome-View-Restore-64.png \
		res/64/Gnome-Printer-Printing-64.png \
		res/64/Gnome-Colors-Emblem-Desktop-Orange-64.png \
		res/64/Gnome-Emblem-Web-64.png \
		res/64/Gnome-Zoom-Out-64.png \
		res/64/Gnome-Input-Gaming-64.png \
		res/64/Gnome-Edit-Redo-64.png \
		res/64/Gnome-Phone-64.png \
		res/64/Gnome-Network-Workgroup-64.png \
		res/64/Gnome-Format-Text-Strikethrough-64.png \
		res/64/Gnome-Audio-X-Generic-64.png \
		res/64/Gnome-Dialog-Information-64.png \
		res/64/Gnome-Document-Save-64.png \
		res/64/Gnome-Preferences-System-Network-64.png \
		res/64/Gnome-Window-New-64.png \
		res/64/Gnome-Applications-Accessories-64.png \
		res/64/Gnome-Security-Low-64.png \
		res/64/Gnome-Object-Rotate-Left-64.png \
		res/64/Gnome-Video-X-Generic-64.png \
		res/64/Gnome-Printer-64.png \
		res/64/Gnome-Audio-Volume-Muted-64.png \
		res/64/Gnome-List-Add-64.png \
		res/64/Gnome-Weather-Severe-Alert-64.png \
		res/64/Emblem-Money-64.png \
		res/64/Gnome-Applications-Multimedia-64.png \
		res/64/Gnome-Dialog-Question-64.png \
		res/64/Gnome-Face-Wink-64.png \
		res/64/Gnome-Tools-Check-Spelling-64.png \
		res/64/Gnome-Appointment-Missed-64.png \
		res/64/Gnome-Image-X-Generic-64.png \
		res/64/Gnome-Emblem-Unreadable-64.png \
		res/64/Gnome-Preferences-System-Windows-64.png \
		res/64/Gnome-Preferences-Desktop-Theme-64.png \
		res/64/Gnome-Drive-Optical-64.png \
		res/64/Gnome-Go-Top-64.png \
		res/64/Gnome-Colors-Emblem-Desktop-Red-64.png \
		res/64/Gnome-Window-Close-64.png \
		res/64/Gnome-Emblem-Generic-64.png \
		res/64/Gnome-Preferences-Desktop-Wallpaper-64.png \
		res/64/Gnome-Media-Floppy-64.png \
		res/64/Gnome-Format-Justify-Right-64.png \
		res/64/Im-Msn-64.png \
		res/64/Im-Icq-64.png \
		res/64/Im-Nov-64.png \
		res/64/Gnome-Audio-Input-Microphone-64.png \
		res/64/Gnome-Address-Book-New-64.png \
		res/64/Gnome-Edit-Delete-64.png \
		res/64/Gnome-Network-Wired-64.png \
		res/64/Gnome-Emblem-Mail-64.png \
		res/64/Gnome-Media-Optical-64.png \
		res/64/Gnome-Emblem-Symbolic-Link-64.png \
		res/64/Gnome-Aptoncd-64.png \
		res/64/Gnome-Logviewer-64.png \
		res/64/Gnome-Mail-Mark-Unread-64.png \
		res/64/Gnome-Insert-Image-64.png \
		res/64/Gnome-Colors-Emblem-Green-64.png \
		res/64/Gnome-Document-Properties-64.png \
		res/64/Gnome-Face-Crying-64.png \
		res/64/Gnome-Face-Smirk-64.png \
		res/64/Gnome-Weather-Showers-64.png \
		res/64/Gnome-Applications-Development-64.png \
		res/64/Application-Default-Icon-64.png \
		res/64/Gnome-Mail-Attachment-64.png \
		res/64/Gnome-Face-Angel-64.png \
		res/64/Gnome-Mail-Reply-Sender-64.png \
		res/64/Gnome-Face-Smile-64.png \
		res/64/Gnome-Dialog-Warning-64.png \
		res/64/Dialog-Apply-64.png \
		res/64/Gnome-X-Office-Calendar-64.png \
		res/64/Gnome-Document-Open-64.png \
		res/64/Gnome-System-Log-Out-64.png \
		res/64/Gnome-Preferences-Desktop-Accessibility-64.png \
		res/64/Gnome-Emblem-System-64.png \
		res/64/File-Roller-64.png \
		res/64/Gnome-Media-Record-64.png \
		res/64/Gnome-Input-Keyboard-64.png \
		res/64/Gnome-Weather-Few-Clouds-Night-64.png \
		res/64/Gnome-Stock-Person-64.png \
		res/64/Gnome-Weather-Overcast-64.png \
		res/64/Gnome-Security-High-64.png \
		res/64/Mail-Import-64.png \
		res/64/Gnome-Media-Playback-Pause-64.png \
		res/64/Gnome-Face-Devilish-64.png \
		res/64/Gnome-Audio-Volume-Low-64.png \
		res/64/Gnome-Utilities-System-Monitor-64.png \
		res/64/Gnome-User-Home-64.png \
		res/64/Gnome-Media-Playlist-Shuffle-64.png \
		res/64/Gnome-Format-Indent-More-64.png \
		res/64/Gnome-Face-Cool-64.png \
		res/64/Gnome-Dialog-Error-64.png \
		res/64/Gnome-Preferences-Desktop-Font-64.png \
		res/64/Gnome-Insert-Link-64.png \
		res/64/Gnome-Image-Missing-64.png \
		res/64/Glade-3-64.png \
		res/64/Gnome-Network-Transmit-64.png \
		res/64/Gnome-Camera-Web-64.png \
		res/64/Gnome-X-Office-Document-64.png \
		res/64/Gnome-Mail-Send-64.png \
		res/64/Gnome-Drive-Removable-Media-64.png \
		res/64/Gnome-Media-Tape-64.png \
		res/64/Im-Yahoo-64.png \
		res/64/Gnome-Utilities-Terminal-64.png \
		res/64/Gnome-Folder-64.png \
		res/64/Gnome-Application-Certificate-64.png \
		res/64/Gnome-View-Refresh-64.png \
		res/64/Gnome-Edit-Find-Replace-64.png \
		res/64/Gnome-Accessories-Character-Map-64.png \
		res/64/Gnome-Folder-Open-64.png \
		res/64/Gnome-Battery-Low-64.png \
		res/64/Gnome-Contact-New-64.png \
		res/64/Gnome-Battery-Caution-64.png \
		res/64/Gnome-Format-Justify-Fill-64.png \
		res/64/Gnome-Timezone-64.png \
		res/64/Gnome-Appointment-New-64.png \
		res/64/Gnome-Camera-Video-64.png \
		res/64/Gnome-Preferences-Desktop-64.png \
		res/64/Application-Default-Red-64.png \
		res/64/Gnome-Preferences-Desktop-Remote-Desktop-64.png \
		res/64/Gnome-Face-Monkey-64.png \
		res/64/Gnome-X-Office-Presentation-64.png \
		res/64/Add-Files-To-Archive-Blue-64.png \
		res/64/Gnome-Applications-Engineering-64.png \
		res/64/Gnome-Network-Error-64.png \
		res/64/Gnome-Object-Rotate-Right-64.png \
		res/64/Gnome-Edit-Copy-64.png \
		res/64/Gnome-Weather-Storm-64.png \
		res/64/Gnome-System-Lock-Screen-64.png \
		res/64/Gnome-Audio-Volume-High-64.png \
		res/64/Gnome-Applications-Office-64.png \
		res/64/Gnome-Media-Zip-64.png \
		res/64/User-Info-64.png \
		res/64/Gnome-Weather-Clear-64.png \
		res/64/Gnome-Edit-Cut-64.png \
		res/64/Gnome-Edit-Clear-64.png \
		res/64/Gnome-Folder-Remote-64.png \
		res/64/Gnome-Text-Html-64.png \
		res/64/Gnome-Folder-Drag-Accept-64.png \
		res/64/Gnome-Image-Loading-64.png \
		res/64/Gnome-Applications-Graphics-64.png \
		res/64/Gnome-Format-Text-Direction-Rtl-64.png \
		res/64/Gnome-Mail-Read-64.png \
		res/64/Gnome-Mail-Unread-64.png \
		res/64/Gnome-Document-Send-64.png \
		res/64/Gnome-User-Trash-Full-64.png \
		res/64/Gnome-Mail-Replied-64.png \
		res/64/Gnome-System-Help-64.png \
		res/64/Gnome-Edit-Select-All-64.png \
		res/64/Gnome-Emblem-Urgent-64.png \
		res/64/Gnome-Preferences-System-64.png \
		res/64/Gnome-Emblem-Downloads-64.png \
		res/64/Gnome-Settings-Ui-Behavior-64.png \
		res/64/Gnome-Face-Plain-64.png \
		res/64/Gnome-Weather-Clear-Night-64.png \
		res/64/Gnome-Software-Update-Urgent-64.png \
		res/64/Gnome-Edit-Undo-64.png \
		res/64/Gnome-Preferences-Desktop-Peripherals-64.png \
		res/64/Gnome-Go-Bottom-64.png \
		res/64/Gnome-System-Run-64.png \
		res/64/Gnome-Emblem-Documents-64.png \
		res/64/Gnome-Applications-Science-64.png \
		res/64/Gnome-Go-Home-64.png \
		res/64/Gnome-Mail-Send-Receive-64.png \
		res/64/Gnome-Software-Update-Available-64.png \
		res/64/Gnome-Zoom-In-64.png \
		res/64/Gnome-Face-Surprise-64.png \
		res/64/Gnome-System-Software-Installer-64.png \
		res/64/Gnome-Mail-Reply-All-64.png \
		res/64/Gnome-Font-X-Generic-64.png \
		res/64/Gnome-Preferences-Desktop-Personal-64.png \
		res/64/Hyperlink-Internet-Search-64.png \
		res/64/Gnome-Process-Stop-64.png \
		res/64/Add-Files-To-Archive-64.png \
		res/64/Gnome-Preferences-Desktop-Keyboard-64.png \
		res/64/Gnome-Task-Due-64.png \
		res/64/Gnome-Zoom-Original-64.png \
		res/64/Gnome-Applications-Other-64.png \
		res/64/Gnome-Go-Last-64.png \
		res/64/Gnome-Format-Text-Italic-64.png \
		res/64/Gnome-Document-Print-64.png \
		res/64/Gnome-Insert-Text-64.png \
		res/64/Application-Default-Orange-64.png \
		res/64/Gnome-User-Trash-64.png \
		res/64/Gnome-Undelete-64.png \
		res/64/Gnome-Emblem-Shared-64.png \
		res/64/Gnome-Document-New-64.png \
		res/64/Gnome-Media-Seek-Forward-64.png \
		res/64/Gnome-Printer-Error-64.png \
		res/64/Gnome-Audio-Volume-Medium-64.png \
		res/64/Gnome-System-Shutdown-64.png \
		res/64/Gnome-Preferences-Other-64.png \
		res/64/Gnome-Mail-Mark-Read-64.png \
		res/64/Im-Aim-64.png \
		res/64/Gnome-Document-Save-As-64.png \
		res/64/Gnome-Edit-Paste-64.png \
		res/64/Gnome-Drive-Harddisk-64.png \
		res/64/Gnome-Text-X-Generic-64.png \
		res/64/Gnome-Folder-New-64.png \
		res/64/Gnome-Help-About-64.png \
		res/64/Gnome-Bookmark-New-64.png \
		res/64/Gnome-Face-Embarrassed-64.png \
		res/64/Gnome-Network-Idle-64.png \
		res/64/Gnome-Start-Here-64.png \
		res/64/Gnome-Dialog-Password-64.png \
		res/64/Gnome-Media-Playlist-Repeat-64.png \
		res/64/Gnome-Document-Open-Recent-64.png \
		res/64/Gnome-Folder-Visiting-64.png \
		res/64/Gnome-Battery-64.png \
		res/64/Gnome-Go-Up-64.png \
		res/64/Gnome-Network-Wireless-64.png \
		res/64/Gnome-Camera-Photo-64.png \
		res/64/Gnome-Network-Transmit-Receive-64.png \
		res/64/Gnome-Media-Skip-Forward-64.png \
		res/64/Gnome-Format-Justify-Center-64.png \
		res/64/Gnome-Edit-Find-64.png \
		res/64/Gnome-Format-Indent-Less-64.png \
		res/64/Gnome-Format-Text-Underline-64.png \
		res/64/Gnome-Face-Raspberry-64.png \
		res/64/Gnome-Video-Display-64.png \
		res/64/Gnome-Applications-System-64.png \
		res/64/Gnome-Emblem-New-64.png \
		res/64/Gnome-Media-Playback-Stop-64.png \
		res/64/Gnome-Text-X-Generic-Template-64.png \
		res/64/Gnome-Network-Server-64.png \
		res/64/Gnome-Appointment-Soon-64.png \
		res/64/Gnome-System-Users-64.png \
		res/64/Gnome-View-Fullscreen-64.png \
		res/64/Im-Jabber-64.png \
		res/64/Gnome-System-Software-Update-64.png \
		res/64/Gnome-Weather-Showers-Scattered-64.png \
		res/64/Gnome-Format-Text-Bold-64.png \
		res/64/Gnome-X-Office-Drawing-64.png \
		res/64/Gnome-Text-X-Script-64.png \
		res/64/Gnome-Multimedia-Volume-Control-64.png \
		res/64/Gnome-Media-Flash-64.png \
		res/64/Gnome-Multimedia-Player-64.png \
		res/64/Gnome-View-Sort-Ascending-64.png \
		res/64/Gnome-Emblem-Favorite-64.png \
		res/64/Gnome-Task-Past-Due-64.png \
		res/64/Gnome-Document-Page-Setup-64.png \
		res/64/Gnome-Emblem-Important-64.png \
		res/64/Gnome-Emblem-Photos-64.png \
		res/64/Gnome-Format-Justify-Left-64.png
	/usr/bin/rcc -name ressouces ressouces.qrc -o qrc_ressouces.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_configuration.h ui_connecter.h ui_identification.h ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_configuration.h ui_connecter.h ui_identification.h ui_mainwindow.h
ui_configuration.h: configuration.ui
	/usr/bin/uic-qt4 configuration.ui -o ui_configuration.h

ui_connecter.h: connecter.ui
	/usr/bin/uic-qt4 connecter.ui -o ui_connecter.h

ui_identification.h: identification.ui
	/usr/bin/uic-qt4 identification.ui -o ui_identification.h

ui_mainwindow.h: mainwindow.ui
	/usr/bin/uic-qt4 mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_uic_clean 

####### Compile

configuration.o: configuration.cpp configuration.hpp \
		LClient.h \
		LDebug.h \
		header.h \
		identification.hpp \
		mainwindow.hpp \
		ui_configuration.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o configuration.o configuration.cpp

connecter.o: connecter.cpp connecter.hpp \
		LClient.h \
		LDebug.h \
		header.h \
		configuration.hpp \
		identification.hpp \
		mainwindow.hpp \
		ui_connecter.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o connecter.o connecter.cpp

identification.o: identification.cpp identification.hpp \
		LClient.h \
		LDebug.h \
		header.h \
		mainwindow.hpp \
		ui_identification.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o identification.o identification.cpp

LClient.o: LClient.cpp LClient.h \
		LDebug.h \
		header.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o LClient.o LClient.cpp

LDebug.o: LDebug.cpp LDebug.h \
		header.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o LDebug.o LDebug.cpp

main.o: main.cpp mainwindow.hpp \
		LClient.h \
		LDebug.h \
		header.h \
		connecter.hpp \
		configuration.hpp \
		identification.hpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

mainwindow.o: mainwindow.cpp mainwindow.hpp \
		LClient.h \
		LDebug.h \
		header.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o mainwindow.cpp

moc_configuration.o: moc_configuration.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_configuration.o moc_configuration.cpp

moc_connecter.o: moc_connecter.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_connecter.o moc_connecter.cpp

moc_identification.o: moc_identification.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_identification.o moc_identification.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

qrc_ressouces.o: qrc_ressouces.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_ressouces.o qrc_ressouces.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

