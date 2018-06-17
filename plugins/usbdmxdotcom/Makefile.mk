if USE_USBDMXDOTCOM
lib_LTLIBRARIES += plugins/usbdmxdotcom/libolausbdmxdotcom.la

# Plugin description is generated from README.md
built_sources += plugins/usbdmxdotcom/UDDCPluginDescription.h
nodist_plugins_usbdmxdotcom_libolausbdmxdotcom_la_SOURCES = \
    plugins/usbdmxdotcom/UDDCPluginDescription.h
plugins/usbdmxdotcom/UDDCPluginDescription.h: plugins/usbdmxdotcom/README.md plugins/usbdmxdotcom/Makefile.mk plugins/convert_README_to_header.sh
	sh $(top_srcdir)/plugins/convert_README_to_header.sh $(top_srcdir)/plugins/usbdmxdotcom $(top_builddir)/plugins/usbdmxdotcom/UDDCPluginDescription.h

plugins_usbdmxdotcom_libolausbdmxdotcom_la_SOURCES = \
    plugins/usbdmxdotcom/UDDCDevice.cpp \
    plugins/usbdmxdotcom/UDDCDevice.h \
    plugins/usbdmxdotcom/UDDCPlugin.cpp \
    plugins/usbdmxdotcom/UDDCPlugin.h \
    plugins/usbdmxdotcom/UDDCPort.h \
    plugins/usbdmxdotcom/UDDCPort.cpp
plugins_uddc_libolausbdmxdotcom_la_CXXFLAGS = $(COMMON_CXXFLAGS) $(liblo_CFLAGS)
plugins_uddc_libolausbdmxdotcom_la_LIBADD = \
    olad/plugin_api/libolaserverplugininterface.la

endif
