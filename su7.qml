import QtQuick
import QtWebEngine
import Qt5Compat.GraphicalEffects

Item {
    anchors.fill: parent

    Rectangle {
         anchors.fill: parent
         color: "#151515"
     }

    WebEngineView {
        id: webView
        anchors.fill: parent
        url: "qrc:/webview/su7.html"


        layer.enabled: true
        layer.effect: OpacityMask {
            maskSource: Rectangle {
                width: webView.width
                height: webView.height
                radius: 20
                visible: false
            }
        }
    }
}
