QT += qml quick
TARGET = qwx
!android: !ios: !blackberry: qtHaveModule(widgets): QT += widgets

include(src/src.pri)

OTHER_FILES += \
    main.qml \
    content/AndroidDelegate.qml \
    content/ButtonPage.qml \
    content/ListPage.qml \
    content/ProgressBarPage.qml \
    content/SliderPage.qml \
    content/TabBarPage.qml \
    content/TextInputPage.qml

RESOURCES += \
    resources.qrc
