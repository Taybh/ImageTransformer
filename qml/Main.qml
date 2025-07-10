import QtQuick 2.15
import QtQuick.Controls 2.15

ApplicationWindow {
    id: window
    visible: true
    width: 800
    height: 600
    title: "Image Rotate Demo"

    property real angle: 0
    property var originalImage: null

    Timer {
    id: grabTimer
    interval: 200
    repeat: false
    onTriggered: {
        console.log("Grabbing image after delay...");
        original.grabToImage(function(result) {
            originalImage = result.image;
            rotatedImage.source = Qt.resolvedUrl("../images/test.png"); // initialization
        });
        }
    }

    
    Column {
        anchors.centerIn: parent
        spacing: 20

        Image {
            id: original
            width: 200
            height: 200
            fillMode: Image.PreserveAspectFit
            source: "qrc:/images/test.png"
            visible: true
            onStatusChanged: {
                if (status === Image.Ready && originalImage === null) {
                    console.log("Image ready, will grab it in 200ms...");
                    grabTimer.start();
    }
            }
        }

        Slider {
            id: angleSlider
            width: 300
            from: 0
            to: 360
            value: 0
            onValueChanged: {
                angle = value;
                if (originalImage) {
                    transformer.rotateImage(originalImage, angle, function(rotated) {
                    console.log("Got rotated image:", rotated.length);
                    rotatedImage.source = rotated;
                    });
                }
            }
        }

        Image {
            id: rotatedImage
            width: 200
            height: 200
            fillMode: Image.PreserveAspectFit
            visible: true
        }

    }
}
