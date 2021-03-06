#--------------------------------------------------------------------
# Inviwo Qt Widgets
ivw_project(inviwo-qtwidgets)

#--------------------------------------------------------------------
# Add MOC files
set(MOC_FILES
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/angleradiuswidget.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/colorwheel.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/customdoublespinboxqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/editablelabelqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/filepathlineeditqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/sliderwidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/inviwoapplicationqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/inviwodockwidget.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/inviwodockwidgettitlebar.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/inviwofiledialog.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/lightpositionwidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/lineeditqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/ordinaleditorwidget.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/propertylistwidget.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/rangesliderqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/spinboxrangesliderwidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/processors/processordockwidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/processors/processorwidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/anglepropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/boolcompositepropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/buttonpropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/collapsiblegroupboxwidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/colorpropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/compositepropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/eventpropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/filepropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/ordinalpropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/htmleditorwidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/htmllistwidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/imageeditorwidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/lightpropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/optionpropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/ordinalminmaxpropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/ordinalminmaxtextpropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/propertysettingswidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/propertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/stringpropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/stringmultilinepropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/syntaxhighlighter.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/texteditorwidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/transferfunctioneditor.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/transferfunctioneditorview.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/transferfunctionpropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/transferfunctionpropertydialog.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/propertyselectiontreewidget.h
)

#--------------------------------------------------------------------
# Add header files
set(HEADER_FILES
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/eventconverterqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/inviwoqtutils.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/inviwoqtwidgetsdefine.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/keyboardutils.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/labelgraphicsitem.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/boolpropertywidgetqt.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/transferfunctioncontrolpointconnection.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/properties/transferfunctioneditorcontrolpoint.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/qstringhelper.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/qtwidgetmodule.h
    ${IVW_INCLUDE_DIR}/inviwo/qt/widgets/rawdatareaderdialogqt.h
    ${MOC_FILES}
)
ivw_group("Header Files" ${HEADER_FILES})

#--------------------------------------------------------------------
# Add source files
set(SOURCE_FILES
    angleradiuswidget.cpp
    colorwheel.cpp
    customdoublespinboxqt.cpp
    editablelabelqt.cpp
    eventconverterqt.cpp
    filepathlineeditqt.cpp
    inviwoapplicationqt.cpp
    inviwodockwidget.cpp
    inviwodockwidgettitlebar.cpp
    inviwofiledialog.cpp
    inviwoqtutils.cpp
    keyboardutils.cpp
    labelgraphicsitem.cpp
    lightpositionwidgetqt.cpp
    lineeditqt.cpp
    ordinaleditorwidget.cpp
    processors/processordockwidgetqt.cpp
    processors/processorwidgetqt.cpp
    properties/anglepropertywidgetqt.cpp
    properties/boolcompositepropertywidgetqt.cpp
    properties/boolpropertywidgetqt.cpp
    properties/buttonpropertywidgetqt.cpp  
    properties/collapsiblegroupboxwidgetqt.cpp
    properties/colorpropertywidgetqt.cpp
    properties/compositepropertywidgetqt.cpp
    properties/eventpropertywidgetqt.cpp
    properties/filepropertywidgetqt.cpp
    properties/glslsyntaxhighlighter.cpp
    properties/htmleditorwidgetqt.cpp
    properties/htmllistwidgetqt.cpp
    properties/imageeditorwidgetqt.cpp
    properties/lightpropertywidgetqt.cpp
    properties/optionpropertywidgetqt.cpp
    properties/ordinalminmaxpropertywidgetqt.cpp
    properties/ordinalminmaxtextpropertywidgetqt.cpp
    properties/ordinalpropertywidgetqt.cpp
    properties/propertysettingswidgetqt.cpp
    properties/propertywidgetqt.cpp
    properties/pythonsyntaxhighlighter.cpp
    properties/stringpropertywidgetqt.cpp
    properties/stringmultilinepropertywidgetqt.cpp
    properties/syntaxhighlighter.cpp
    properties/texteditorwidgetqt.cpp
    properties/transferfunctioncontrolpointconnection.cpp
    properties/transferfunctioneditor.cpp
    properties/transferfunctioneditorcontrolpoint.cpp
    properties/transferfunctioneditorview.cpp
    properties/transferfunctionpropertydialog.cpp
    properties/transferfunctionpropertywidgetqt.cpp 
    propertylistwidget.cpp
    propertyselectiontreewidget.cpp
    qtwidgetmodule.cpp
    rangesliderqt.cpp
    rawdatareaderdialogqt.cpp
    sliderwidgetqt.cpp
    spinboxrangesliderwidgetqt.cpp
)

ivw_group("Source Files" ${SOURCE_FILES})

#--------------------------------------------------------------------
# Create library
find_package(Qt5Core QUIET REQUIRED)
ivw_qt_wrap_cpp(MOC_FILES ${MOC_FILES})
source_group("MOC Files" FILES ${MOC_FILES})
add_library(inviwo-qtwidgets ${SOURCE_FILES} ${MOC_FILES} ${HEADER_FILES})

#--------------------------------------------------------------------
# Define defintions
ivw_define_standard_definitions(IVW_QTWIDGETS inviwo-qtwidgets)
ivw_define_qt_definitions()

# Add qt dependencies to this list
set(IVW_WIDGETS_QT_DEPENDS
    Qt5Core
    Qt5Gui
    Qt5Widgets
    Qt5Help
)

foreach(qtarget ${IVW_WIDGETS_QT_DEPENDS})
    ivw_add_dependencies(${qtarget})  
    ivw_qt_add_to_install(${qtarget} qt_widgets)
endforeach()

# Add core dependencies to this list
ivw_add_dependencies(InviwoCore)

#--------------------------------------------------------------------
# Optimize compilation with pre-compilied headers based on inviwo-core
ivw_compile_optimize_inviwo_core()

#--------------------------------------------------------------------
# Make package (for other projects to find)
ivw_set_cpack_name(qt_widgets)
ivw_make_package(InviwoQtWidgets inviwo-qtwidgets)
