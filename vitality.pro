QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

VERSION = 1.0.0.1

TARGET = Vitality
TEMPLATE = app

SOURCES += \
    main.cpp \
    initDB.cpp \
    ui_PeriodMap.cpp \
    PeriodMap.cpp \
    ExerciseMap.cpp \
    EditExerciseMap.cpp \
    ui_EditExerciseMap.cpp \
    ui_ExerciseMap.cpp \
    ModelForMap.cpp \
    ModelForForm.cpp \
    EditExercise.cpp \
    ui_EditExercise.cpp \
    ReplaceOrRename.cpp \
    MyTableWidget.cpp

HEADERS += \
    initDB.h \
    ui_PeriodMap.h \
    PeriodMap.h \
    ExerciseMap.h \
    EditExerciseMap.h \
    ui_EditExerciseMap.h \
    ui_ExerciseMap.h \
    ModelForMap.h \
    ModelForForm.h \
    EditExercise.h \
    ui_EditExercise.h \
    ReplaceOrRename.h \
    MyTableWidget.h

RESOURCES += \
    resources.qrc

TRANSLATIONS += \
    translations/Vitality_ru.ts

CODECFORSRC     = UTF-8

DISTFILES += \
    android/AndroidManifest.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew \
    android/gradlew.bat \
    android/res/values/libs.xml

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android
}
