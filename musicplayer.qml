/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Copyright (C) 2024 Softwave Labs.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit, modified by Softwave Labs.
**
** @author Anathonic <anathonic@protonmail.com>
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/


import QtQuick 2.12
import QtQuick.Layouts 1.12
import QtQuick.Controls 2.12
import QtQuick.Controls.Material 2.12
import QtQuick.Window 2.0


ApplicationWindow {
    id: window
    width: 1280
    height: 720
    visible: true
    title: "Music Player"
    Material.accent: "#222222"

    background: Rectangle {
        id: backgroundColor
        color: "#fafafa"
    }

    Component.onCompleted: {
        x = Screen.width / 2 - width / 2
        y = Screen.height / 2 - height / 2
    }

    Shortcut {
        sequence: "Ctrl+Q"
        onActivated: Qt.quit()
    }

    header: ToolBar {
        Material.background: "#222222"
        RowLayout {
            id: headerRowLayout
            anchors.fill: parent
            spacing: 0

            Item {
                Layout.fillWidth: true
            }


            ToolButton {
                icon.name: "power"
                onClicked: Qt.quit()
            }
        }
    }

    RowLayout {
        spacing: 100
        anchors.fill: parent
        anchors.margins: 70

        ColumnLayout {
            spacing: 0
            Layout.preferredWidth: 230

            Dial {
                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 50
            }

            Label {
                text: "Volume"

                Layout.alignment: Qt.AlignHCenter
                Layout.topMargin: 12
            }
            Slider {
                id: slider
                Material.accent: "#222222"
                Layout.fillWidth: true
                snapMode: Slider.SnapOnRelease
                enabled: true
                from: 0.5
                to: 2
                stepSize: 0.25
                value: 1.0
            }
            Text {
                Layout.alignment: Qt.AlignCenter
                text: "Speed " + slider.value + "x"
            }
        }

        ColumnLayout {
            spacing: 26
            Layout.preferredWidth: 380

            Item {
                Layout.preferredHeight: 300
                Layout.preferredWidth: 300
                Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                Image {
                    id: albumCover
                    anchors.fill: parent
                    fillMode: Image.PreserveAspectCrop
                    source: "images/Selected_Ambient_Works_85-92.png"
                }
            }

            Item {
                id: songLabelContainer
                clip: true

                Layout.fillWidth: true
                Layout.preferredHeight: songNameLabel.implicitHeight

                SequentialAnimation {
                    running: true
                    loops: Animation.Infinite

                    PauseAnimation {
                        duration: 2000
                    }
                    ParallelAnimation {
                        XAnimator {
                            target: songNameLabel
                            from: 100
                            to: 200
                            duration: 5000
                        }
                    }
                    PauseAnimation {
                        duration: 1000
                    }
                    ParallelAnimation {
                        XAnimator {
                            target: songNameLabel
                            from: 200
                            to: 100
                            duration: 5000
                        }
                    }
                }

                Label {
                    id: songNameLabel
                    text: "Aphex Twin - Xtal"
                    font.pixelSize: 18
                    x: 100

                }

            }

            RowLayout {
                spacing: 8
                Layout.alignment: Qt.AlignHCenter

                RoundButton {
                    id: myRoundButton
                    icon.name: "shuffle"
                    icon.width: 32
                    icon.height: 32
                }
                RoundButton {
                    icon.name: "previous"
                    icon.width: 32
                    icon.height: 32
                }
                RoundButton {
                    icon.name: "pause"
                    icon.width: 32
                    icon.height: 32
                }
                RoundButton {
                    icon.name: "next"
                    icon.width: 32
                    icon.height: 32
                }
                RoundButton {
                    icon.name: "repeat"
                    icon.width: 32
                    icon.height: 32
                }
            }

            Slider {
                id: seekSlider
                value: 113
                to: 261

                Layout.fillWidth: true

                ToolTip {
                    parent: seekSlider.handle
                    visible: seekSlider.pressed
                    text: pad(Math.floor(value / 60)) + ":" + pad(Math.floor(value % 60))
                    y: parent.height

                    readonly property int value: seekSlider.valueAt(seekSlider.position)

                    function pad(number) {
                        if (number <= 9)
                            return "0" + number;
                        return number;
                    }
                }
            }
        }

        ColumnLayout {
            spacing: 16
            Layout.preferredWidth: 230

            RowLayout {
                TextField {
                    Layout.fillWidth: true
                }
                Button {
                    icon.name: "folder"
                }
            }

            Frame {
                id: filesFrame
                leftPadding: 1
                rightPadding: 1

                Layout.fillWidth: true
                Layout.fillHeight: true

                ListView {
                    id: filesListView
                    clip: true
                    anchors.fill: parent
                    model: ListModel {
                        Component.onCompleted: {
                            for (var i = 0; i < 100; ++i) {
                                append({
                                   author: "Author",
                                   album: "Album",
                                   track: "Track 0" + (i % 9 + 1),
                                });
                            }
                        }
                    }
                    delegate: ItemDelegate {
                        required property var model
                        text: model.author + " - " + model.album + " - " + model.track
                    }

                    ScrollBar.vertical: ScrollBar {
                        parent: filesFrame
                        policy: ScrollBar.AlwaysOn
                        anchors.top: parent.top
                        anchors.topMargin: filesFrame.topPadding
                        anchors.right: parent.right
                        anchors.rightMargin: 1
                        anchors.bottom: parent.bottom
                        anchors.bottomMargin: filesFrame.bottomPadding
                    }
                }
            }
            Item {
                Layout.preferredHeight: 30
                Layout.preferredWidth: 140
                Layout.alignment: Qt.AlignRight

                RowLayout {
                    anchors.fill: parent
                    Layout.alignment: Qt.AlignHCenter

                    Image {
                        Layout.alignment: Qt.AlignHCenter
                        Layout.preferredWidth: 38
                        Layout.preferredHeight: 38
                        fillMode: Image.PreserveAspectCrop
                        source: "images/logo.png"
                    }

                    Label {
                        id: author
                        Layout.alignment: Qt.AlignHCenter
                        text: "Softwave Labs"
                        font.pixelSize: 13
                        font.bold: true
                    }
                }
            }
        }
    }
}
